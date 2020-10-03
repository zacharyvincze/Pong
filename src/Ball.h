//
// Created by Pamela Vincze on 2016-08-23.
//

#ifndef PONG_BALL_H
#define PONG_BALL_H

#include <ncurses.h>

class Ball {
public:
    Ball(double y, double x, int speed);

    double getX() const { return x; }
    double getY() const { return y; }
    int getSpeed() const { return speed; }
    void setX(double a) {
        x = a;
    }
    void setY(double a) {
        y = a;
    }
    void setSpeed(int a){
        speed = a;
    }
    void drawBall() const {
        mvaddch(y, x, 'o');
    }
private:
    double x, y;
    int speed;

};


#endif //PONG_BALL_H
