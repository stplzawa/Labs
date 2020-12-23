#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct Passanger
{
public:
    int ID;							//ID пассажира
    bool survival = false;			//Выжившие(0=No, 1=Yes)
    int pclass;						//1-1ый класс, 2-2ой класс,3-3ий класс    
    string name;					//Имя	
    string sex;						//Пол(male, female)
    short age;						//Возраст
    short sibsp;					//Количество братьев и сестер / супругов за границей
    short pChild;					//Количество родителей / детей за границей  
    string tickets;					//Количество билетов
    double fare;					//Стоимость проезда)
    string cabin;					//Салон
    string embarked;				//Порт погрузки (C=Cherbourg; Q=Qeenstown; S=Scouthampton

    static Passanger getFromString(string data) {
        auto dataVector = parseString(data);
        auto result = castToStruct(dataVector);
        return result;
    }

private:
    static Passanger castToStruct(vector<string> structParts) {

        if (structParts.size() != 12)
            throw new invalid_argument("Invalid vector size");

        Passanger newPassanger;
        newPassanger.ID = structParts[0].size()         ? stoi(structParts[0]) : 0;
        newPassanger.survival = structParts[1].size()   ? stoi(structParts[1]) : 0;
        newPassanger.pclass = structParts[2].size()     ? stoi(structParts[2]) : 0;
        newPassanger.name = structParts[3].size() > 2   ? structParts[3].substr(1, structParts[3].length() - 2) : "";
        newPassanger.sex = structParts[4];
        newPassanger.age = structParts[5].size()        ? stoi(structParts[5]) : 0;
        newPassanger.sibsp = structParts[6].size()      ? stoi(structParts[6]) : 0;
        newPassanger.pChild = structParts[7].size()     ? stoi(structParts[7]) : 0;
        newPassanger.tickets = structParts[8];
        newPassanger.fare = structParts[9].size()       ? stof(structParts[9]) : 0;
        newPassanger.cabin = structParts[10];
        newPassanger.embarked = structParts[11];

        return newPassanger;
    }

    static vector<string> parseString(string data) {

        vector<string> structParts;

        int nextOffset = data.find(',');

        while (nextOffset != std::string::npos)
        {
            nextOffset = data.find(',');
            structParts.push_back(data.substr(0, nextOffset));

            data = data.substr(nextOffset + 1, std::string::npos);
        }

        vector<string> processedParts;

        string tempBuffer = "";
        bool quotesEntryFlag = false;

        for (auto& item : structParts)
        {
            if (!item.length()) {
                processedParts.push_back(item);
                continue;
            }
            if (item[0] == '\"') {
                quotesEntryFlag = true;
                tempBuffer += item;
                continue;
            }
            if (item[item.length() - 1] == '\"' && quotesEntryFlag) {
                processedParts.push_back(tempBuffer + item);
                tempBuffer = "";
                quotesEntryFlag = false;
                continue;
            }
            processedParts.push_back(item);
        }

        return processedParts;
    }
};

template<typename T>
string listJoin(vector<T> toGlue, string separator) {
    string res;
    for (auto it : toGlue) {
        res += to_string(it) + separator;
    }
    return res.substr(0, res.length() - 1 - separator.length());
}

int main()
{
    setlocale(LC_ALL, "Rus");
    ifstream fin("train.csv");
    vector <string> data;
    string str;

    int passengersCount = 0, all_alive = 0, alive_f = 0, alive_m = 0;
    int alive_first_class = 0, alive_second_class = 0, alive_third_class = 0;
    int Ch = 0, Qe = 0, Sc = 0;
    double all_middle_age = 0.0, count_f = 0.0, count_m = 0.0;


    vector<int>  allNonAdultIDList;
    getline(fin, str, '\r');

    while (getline(fin, str, '\r'))
    {
        if (str.size() <= 0)
            continue;

        auto a = Passanger::getFromString(str);
        passengersCount++;

        if (a.survival == true)
        {
            all_alive++;

            if (a.sex == "male")
                alive_m++;
            else
                alive_f++;

            if (a.pclass == 1)
                alive_first_class++;
              
            if (a.pclass == 2)
                alive_second_class++;
                
            if (a.pclass == 3)
                alive_third_class++;
        }

        if (a.age <= 17)
            allNonAdultIDList.push_back(a.ID);

        if (a.embarked == "C")
            Ch++;
        if (a.embarked == "Q")
            Qe++;
        if (a.embarked == "S")
            Sc++;

        if (a.sex == "male")
        {
            alive_m++;
            count_m += a.age;
        }
        else
            alive_f++;
        count_f += a.age;
        all_middle_age += a.age;

    }
    fin.close();

    int max = 0;
    string state;
    if (Ch > max) {
        max = Ch;
        state = "Cherbourgh";
    }
    if (Qe > max) {
        max = Qe;
        state = "Qeenstown";
    }
    if (Sc > max) {
        max = Sc;
        state = "Scouthampton";
    }

    ofstream fileOut("Train.txt");
    string textResult;

    textResult += "Общее число выживших:" + to_string(all_alive) + "\n";
    textResult += "Число выживших из первого класса: " + to_string(alive_first_class) + "\n";
    textResult += "Число выживших из второго класса: " + to_string(alive_second_class) + "\n";
    textResult += "Число выживших из третьего класса: " + to_string(alive_third_class) + "\n";
    textResult += "Количество выживших женщин: " + to_string(alive_f) + "\n";
    textResult += "Количество выживших мужчин:  " + to_string(alive_m) + "\n";
    textResult += "Средний возраст пассажиров: " + to_string(all_middle_age / passengersCount) + "\n";
    textResult += "Средний женский возраст: " + to_string(count_f / alive_f) + "\n";;
    textResult += "Средний мужской возраст: " + to_string(count_m / alive_m) + "\n";
    textResult += "Штат, в котором село больше всего пассажиров: " + state + "\n";
    textResult += "Список индентификации несовершеннолетних(<18 лет) пассажиров: " + listJoin(allNonAdultIDList, ",");
    
    fileOut << textResult;
    cout << textResult;
}