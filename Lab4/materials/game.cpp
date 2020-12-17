#include <iostream>
#include <ctime>
#include "game.h"
using namespace std;

Game initGame(char player_symbol)
{
	srand(time(NULL));

	Game game;
	game.status = PLAY;
	
	game.userChar = player_symbol;
	if (player_symbol == '0')
		game.botChar = 'x';
	else
		game.botChar = '0';

	for (char i = 0; i <= 2; i++)
		for (char j = 0; j <= 2; j++)
			game.board[i][j] = ' ';

	if (rand() % 2)
		game.isUserTurn = false;
	else
		game.isUserTurn = true;

	return game;
}

void updateDisplay(const Game game)
{
	system("cls");

	std::cout << " | a\tb\tc" << 
		"\n------------------"<<
		"\n1| " << game.board[0][0] << "\t" << game.board[0][1] << "\t" << game.board[0][2] <<
		"\n2| " << game.board[1][0] << "\t" << game.board[1][1] << "\t" << game.board[1][2] <<
		"\n3| " << game.board[2][0] << "\t" << game.board[2][1] << "\t" << game.board[2][2] << "\n";

	return;
}

void botTurn(Game* game)
{
	int quantity_a=0, quantity_b=0, center=0;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (game->board[i][j] != ' ')
				center++; // переменная center подсчитывает колличество совершенных ранее ходов

	if (!center){ // Если боту достался первый ход, то center = 0  и бот ходит в центр поля
		game->board[1][1] = game->botChar;
		return;
	}

	int aux_var = 0; //вспомогательная переменная

	for (int i = 0; i < 3; i++){  // Основна диагональ
		if (game->board[i][i] == game->userChar)
			quantity_a++;  //Считаем кол-во userChar'ов на основной диагонали

		if (game->board[i][i] == ' '){
		 
			quantity_b++; //Считаем пустые места на основной диагонали
			aux_var = i;
		}
	}
	if ( (quantity_a == 2) && (quantity_b == 1) ){ //Если на диагонали 2 userChar'а и оддно пустое место, то
		game->board[aux_var][aux_var] = game->botChar; // бот ставит туда свой символ
		return;
	}

	quantity_a = 0; //обнуляем после прошлых подсчетов
	quantity_b = 0;
	for (int i = 0; i < 3; i++){ // Вторая диагональ
		if (game->board[i][2-i] == game->userChar)
			quantity_a++;

		if (game->board[i][2-i] == ' '){
			quantity_b++;
			aux_var = i;
		}
	}
	if ((quantity_a == 2) && (quantity_b == 1)){
		game->board[aux_var][2-aux_var] = game->botChar;
		return;
	}


	for (int i = 0; i < 3; i++){
		quantity_a = 0; //обнуляем после прошлых подсчетов
		quantity_b = 0;

		for (int j = 0; j < 3; j++){
			aux_var = j;

			if (game->board[j][i] == game->userChar){ //столбцы			
				quantity_b++; //считаем кол-во userChar'ов в столбце
				if (quantity_b == 2){//если их насчитывается 2
					j = 2;
					while (j >= 0){ //то проходим весь столбец в обратном порядке
						if (game->board[j][i] == ' '){//и при нахлождении свободного места
							game->board[j][i] = game->botChar; //бот ходит в это место
							return;
						}

						j--;
					}
				}
				j = aux_var;
			}

			if (game->board[i][j] == game->userChar)  //строки. Очевидно, что для них тот же алгоритм, только меняем местами j и i
			{ 
				quantity_a++; //т.к. проверяем столбцы и строки параллельно в одном цикле, то приходится использовать разные переменные-счетчики
				if (quantity_a == 2){
					j = 2; 
					while (j >= 0){
						if (game->board[i][j] == ' '){
							game->board[i][j] = game->botChar;
							return;
						}

						j--;
					}
				}
				j = aux_var;
			}

		}
	}

	do // Если бот не нашел куда ходить по алгоритму, то ход совершается случайным образом
	{
		quantity_a = rand() % 3;
		quantity_b = rand() % 3;

		if (game->board[quantity_a][quantity_b] == ' ')
		{
			game->board[quantity_a][quantity_b] = game->botChar;
			return;
		}

	} while (true);

}

void userTurn(Game* game)
{
	cout << "Ход игрока, пожалуйста введите клетку (буква цифра): ";
	while (true){

		char letter;
		short numeral;

		cin >> letter >> numeral;
			
		switch (letter){
		case 'a': letter = 0;
			break;
		case 'b': letter = 1;
			break;
		case 'c': letter = 2;
			break;
		default:
			cout << "Неверно введена буква!\n";
			continue;
		}

		switch (numeral){
		case 1:
		case 2: 
		case 3:
			numeral--;
			break;
		default:
			cout << "Неверно введена цифра!\n";
			continue;
		}

		if (game->board[numeral][letter] == ' '){
			game->board[numeral][letter] = game->userChar;
			return;
		}
		else
			std::cout << "Это место уже занято!\n";
	}
}

bool updateGame(Game* game)
{

	for (int i = 0; i <= 2; i++){ // цикл для проверки строк и столбцов

		if ( game->board[i][0] != ' '){ // если в первой ячейки строки не пробел
			if ( (game->board[i][0] == game->board[i][1]) && (game->board[i][0] == game->board[i][2]) ){ // то проверяем всю строчку на равенство 
				if (game->board[i][0] == game->userChar) //если вся строчка состоит только из userChar'ов
					game->status = USER_WIN; // то игрок выиграл
				else 
					game->status = BOT_WIN; // иначе все состоит из botChar'ов и выиграл бот
				return true;
			}
		}

		if (game->board[0][i] != ' '){ //для проверки столбцов используем алгоритм от строк, поменяв местополежение переменной в индексе ячейки
			if ((game->board[0][i] == game->board[1][i]) && (game->board[0][i] == game->board[2][i])){ 
				if (game->board[0][i] == game->userChar)
					game->status = USER_WIN;
				else
					game->status = BOT_WIN;
				return true;
			}
		}
	}

	if (game->board[0][0] != ' '){ 
		if ((game->board[0][0] == game->board[1][1]) && (game->board[0][0] == game->board[2][2])){ // проверяем диагонали на равенство символов
			if (game->board[1][1] == game->userChar)
				game->status = USER_WIN;
			else
				game->status = BOT_WIN;
			return true;
		}
	}

	if (game->board[2][0] != ' '){
		if ((game->board[0][2] == game->board[1][1]) && (game->board[2][0] == game->board[1][1])){ 
			if (game->board[1][1] == game->userChar)
				game->status = USER_WIN;
			else
				game->status = BOT_WIN;
			return true;
		}
	}

	bool is_draw = 1; // переменная отвечает за ничью 
	for (int i = 0; i < 3; i++) { //проходимся по всему полю
		for (int j = 0; j < 3; j++)
			if (game->board[i][j] == ' ') //и если есть хоть одно свободное место 
				is_draw = 0; //то ничья не возможна
	}
	if (is_draw) // и игра подолжается
	{
		game->status = NOT_WIN;
		return true;
	}
	
	game->isUserTurn = !game->isUserTurn; //передача хода другому игроку
	return false;
}