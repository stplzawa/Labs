#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "x_zero.h"

using namespace std;

int main() {
    short int first;
    int i, j;

    system("chcp 1251 > null");       //меняем кодовую страницу на 1251

    Game player = initGame('X');

    srand((unsigned)time(NULL));
    first = rand() % 2;

    if (first) {
        player.isUserTurn = true;
        player.userChar = 'X';
        player.botChar = 'O';
        player.status = PLAY;
    }
    else {
        player.isUserTurn = false;
        player.userChar = 'O';
        player.botChar = 'X';
        player.status = PLAY;
    }

    while (!updateGame(&player)) {
        if (player.isUserTurn) {
            userTurn(&player);
        }
        else {
            botTurn(&player);
        }
        updateDisplay(player);
    }

    switch (player.status) {
    case USER_WIN: cout << "User WIN!"; break;      //в случае победы пользователя высветится надпись о том, что победитель - игрок
    case BOT_WIN: cout << "Bot WIN!"; break;        //в случае победы бота высветится надпись о том, что победитель - бот
    case NOT_WIN: cout << "Draw!"; break;           //в случае ничьей высветится надпись о том, что ничья
    }

    return 0;
}
