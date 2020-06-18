#ifndef XO_FUNC_H
#define XO_FUNC_H

enum Status {
    PLAY,
    USER_WIN,
    BOT_WIN,
    NOT_WIN
};

struct Game {
    char board[3][3];
    bool isUserTurn;
    char userChar;                          // символ пользователя
    char botChar;                           // символ бота
    Status status;
};


Game initGame(char userChar);
void updateDisplay(const Game game);
void botTurn(Game* game);
void userTurn(Game* game);
bool updateGame(Game* game);

#endif
