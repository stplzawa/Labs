#include <iostream>
#include <fstream>
#include <httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <string>

using namespace nlohmann;
using namespace std;
using namespace httplib;

string domain = R"(api.openweathermap.org)", filePath = "./Weather.html", responseTemplate;
string path = R"(/data/2.5/forecast?q=Simferopol&appid=7eded384686071d767aea9de63494034&units=metric)";
json jsn;

string transformTemperatureLabel(string str, int prec = 1) {
    return str.substr(0, str.find(".") + 1 + prec);
}

string transformDateStamp(string str) {
    return str.substr(0, str.find(" "));
}

string replacePattern(string source, string templ, string toReplace) {
    return source.replace(source.find(templ), templ.length(), toReplace);
}

void responseProcessor(const Request& request, Response& result) {
    Client extractCli(domain.c_str());
    auto res = extractCli.Get(path.c_str());

    if (!res or res->status != 200)
        throw new runtime_error("Invalid api host");

    jsn = json::parse(res->body);

    string currentWeather = responseTemplate;
    currentWeather = replacePattern(currentWeather, "{city.name}", jsn["city"]["name"].get<string>());

    for (size_t i = 0; i < 40; i+=8){
        currentWeather = replacePattern(currentWeather, 
            "{list.dt}",
            transformDateStamp(
                jsn["list"][i]["dt_txt"].get<string>()
            )
        );
        currentWeather = replacePattern(currentWeather, 
            "{list.weather.icon}",
            jsn["list"][i]["weather"][0]["icon"].get<string>()
        );
        currentWeather = replacePattern(currentWeather, 
            "{list.main.temp}",
            transformTemperatureLabel(
                to_string(jsn["list"][i]["main"]["temp"].get<double>())
            )
        );
    }
    result.set_content(currentWeather, "text/html");
}

int main(){
    ifstream sampleFile(filePath); 

    if (!sampleFile.is_open())
        return EXIT_FAILURE;
    
    getline(sampleFile, responseTemplate, '\0');
    sampleFile.close();

    Server server;
    server.Get("/", responseProcessor);
    server.listen("localhost", 3000);

    return EXIT_SUCCESS;
}