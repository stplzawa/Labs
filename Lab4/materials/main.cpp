#include <iostream>
#include "game.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	char player_symbol=0;
	while (player_symbol != 'x' && player_symbol != '0'){
		system("cls");
		cout << "Выбрите 0 или x: ";
		cin >> player_symbol;
	}

	Game game = initGame(player_symbol);
	while (true){

		if (!updateGame(&game)) {
			updateDisplay(game);
			if (game.isUserTurn)
				userTurn(&game);
			else
				botTurn(&game);
			updateDisplay(game);
		}
		else{
			switch (game.status) {
			case BOT_WIN:
				cout << "Вы проиграли.\n";
				break;
			case USER_WIN:
				cout << "Вы выиграли.\n";
				break;
			case NOT_WIN:
				cout << "Ничья.\n";
				break;
			default:
				cout << "err";
				return 0;
			}

			cout << "Сыграем еще(0/1)? ";
			short replay;
			cin >> replay;
			if (replay)
				game = initGame(player_symbol);
			else
				return 0;
		}
	}
}