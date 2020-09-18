//
// Created by Pamela Vincze on 2016-08-23.
//

#ifndef PONG_PLAYER_H
#define PONG_PLAYER_H

#include <ncurses.h>


class Player {

public:
    Player(int x, int y);
    int getX() const { return x; }
    int getY() const { return y; }
    int getHeight() const { return height; }
    void setX(int a) {
        x = a;
    }
    void setY(int a) {
        y = a;
    }
    void drawPlayer() const
    {
        mvaddch(y + 2, x, '|');
        mvaddch(y + 1, x, '|');
        mvaddch(y, x, '|');
        mvaddch(y - 1, x, '|');
        mvaddch(y - 2, x, '|');
    }

private:
    int x, y, height;

};


#endif //PONG_PLAYER_H
