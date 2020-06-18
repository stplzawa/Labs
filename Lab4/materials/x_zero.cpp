#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "x_zero.h"

using namespace std;

Game player;

void updateDisplay(const Game game) {
    system("cls");
    cout << "0___1___2___." << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "|   |   |   |" << endl;
        cout << "| " << game.board[i][0] << " | " << game.board[i][1] << " | " << game.board[i][2] << " |" << endl;
        cout << "|___|___|___|" << endl;
    }
}

void botTurn(Game* game) {
    bool boardEmpty = true, botTurnStep = false;
    int counter;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (game->board[i][j] == game->userChar || game->board[i][j] == game->botChar) {
                boardEmpty = false;
            }
        }
    }

    if (boardEmpty) {
        game->board[1][1] = game->botChar;          // установка символа бота, если поле является пустым
        game->isUserTurn = true;
    }
    else {
        for (int i = 0; i < 3; ++i) {               //проверка строк на наличие 2х сим-в противника
            counter = 0;
            if (game->board[i][0] == game->userChar)	counter++;
            if (game->board[i][1] == game->userChar)	counter++;
            if (game->board[i][2] == game->userChar)	counter++;
            if (counter > 1) {
                for (int j = 0; j < 3; ++j) {                       //проверка строки
                    if (game->board[i][j] != game->userChar && game->board[i][j] != game->botChar) {
                        game->board[i][j] = game->botChar;
                        game->isUserTurn = true;
                        botTurnStep = true;
                        return;
                    }
                }
                break;
            }
        }

                                    //проверка столбцов
        if (!botTurnStep) {
            for (int j = 0; j < 3; ++j) { //проверяем столбцы на наличие 2х сим-в противника
                counter = 0;
                if (game->board[0][j] == game->userChar)	counter++;
                if (game->board[1][j] == game->userChar)	counter++;
                if (game->board[2][j] == game->userChar)	counter++;
                if (counter > 1) {
                    for (int i = 0; i < 3; ++i) {                       //проверка столбцов
                        if (game->board[i][j] != game->userChar && game->board[i][j] != game->botChar) {
                            game->board[i][j] = game->botChar;
                            game->isUserTurn = true;
                            botTurnStep = true;
                            return;
                        }
                    }
                    break;
                }
            }
        }


        if (!botTurnStep) {
            counter = 0;
            for (int i = 0; i < 3; ++i) {
                if (game->board[i][i] == game->userChar) counter++;
            }
            if (counter > 1) {
                for (int i = 0; i < 3; ++i) {
                    if (game->board[i][i] != game->userChar && game->board[i][i] != game->botChar) {
                        game->board[i][i] = game->botChar;
                        game->isUserTurn = true;
                        botTurnStep = true;
                        return;
                    }
                }
            }
        }


        if (!botTurnStep) {
            counter = 0;
            if (game->board[0][2] == game->userChar) counter++;
            if (game->board[1][1] == game->userChar) counter++;
            if (game->board[2][0] == game->userChar) counter++;
            if (counter > 1) {
                if ((game->board[0][2] != game->userChar && game->board[0][2] != game->botChar) && !botTurnStep) {
                        game->board[0][2] = game->botChar;
                        game->isUserTurn = true;
                        botTurnStep = true;
                        return;
                }
                if ((game->board[1][1] != game->userChar && game->board[1][1] != game->botChar) && !botTurnStep) {
                    game->board[1][1] = game->botChar;
                    game->isUserTurn = true;
                    botTurnStep = true;
                    return;
                }
                if ((game->board[2][0] != game->userChar && game->board[2][0] != game->botChar) && !botTurnStep) {
                    game->board[2][0] = game->botChar;
                    game->isUserTurn = true;
                    botTurnStep = true;
                    return;
                }
            }
        }


        if (!botTurnStep) {               //случайный ход
            while (true) {
                int i = rand() % 3;
                int j = rand() % 3;
                if (game->board[i][j] != game->userChar && game->board[i][j] != game->botChar) {
                    game->board[i][j] = game->botChar;
                    game->isUserTurn = true;
                    botTurnStep = true;
                    break;
                }
            }

        }

    }

}

void userTurn(Game* game) {
    int i, j;
    while (true) {                                  //если поле пусто
        cout << "Choose your line from 0-2 --> "; cin >> i;
        cout << "Choose your column 0-2 --> "; cin >> j;
        if ((i>=0) && (i<=2) && (j>=0) && (j<=2)) {
            if ((game->board[i][j] != game->userChar) && (game->board[i][j] != game->botChar)){
                game->board[i][j] = game->userChar;
                game->isUserTurn = false;
                break;
            }
            else{
                cout << " Invalid input, try again\n";
            }
        }
        else {
            cout << " Invalid input, try again\n";
        }
    }
}

bool updateGame(Game* game) {
    bool endGame = true;
    char activeChar;
    int i, j, counter;

    if (!game->isUserTurn) activeChar = game->userChar;
    else activeChar = game->botChar;


    for(i=0; i<3; ++i){                     // проверка окончания игры по строкам
        counter = 0;
        for(j=0; j<3; ++j){
            if(game->board[i][j] == activeChar) counter++;
        }
        if (counter == 3){
            if(!game->isUserTurn) game->status = USER_WIN;
            else game->status = BOT_WIN;
            return endGame;
        }
    }


    for(j=0; j<3; ++j){                                         // проверка окончания игры по столбцам
        counter = 0;
        for(i=0; i<3; ++i){
            if(game->board[i][j] == activeChar) counter++;
        }
        if (counter == 3){
            if(!game->isUserTurn) game->status = USER_WIN;
            else game->status = BOT_WIN;
            return endGame;
        }
    }

    // проверка окончания игры по главной диагонали
    counter = 0;
    if (game->board[0][0] == activeChar)	counter++;
    if (game->board[1][1] == activeChar)	counter++;
    if (game->board[2][2] == activeChar)	counter++;
    if (counter == 3){
        if(!game->isUserTurn) game->status = USER_WIN;
        else game->status = BOT_WIN;
        return endGame;
    }

    // проверка окончания игры по побочной диагонали
    counter = 0;
    if (game->board[2][0] == activeChar)	counter++;
    if (game->board[1][1] == activeChar)	counter++;
    if (game->board[0][2] == activeChar)	counter++;
    if (counter == 3){
        if(!game->isUserTurn) game->status = USER_WIN;
        else game->status = BOT_WIN;
        return endGame;
    }

    counter = 0;
    for(i=0; i<3; ++i){
        for(j=0; j<3; ++j){
            if ((game->board[i][j] != game->userChar) && (game->board[i][j] != game->botChar)){
                counter++;
            }
        }
    }

    if (!counter){
            game->status = NOT_WIN;
            return endGame;
    }
    else endGame = false;

    return endGame;
}

Game initGame(char userChar){
    int first = rand() % 2;
    char botChar;

    if (userChar == 'X') botChar = 'O';
    else botChar = 'X';

    player.userChar = userChar;
    player.botChar = botChar;

    if (first) player.isUserTurn = true;
    else player.isUserTurn = false;

    player.status = PLAY;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            player.board[i][j] = ' ';
        }
    }


    return player;
}
