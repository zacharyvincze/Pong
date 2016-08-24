//
// Created by Pamela Vincze on 2016-08-23.
//

#ifndef PONG_BALL_H
#define PONG_BALL_H

#include <ncurses.h>

class Ball {
public:
    Ball(double x, double y, int speed);
    double getX() { return x; }
    double getY() { return y; }
    int getSpeed() { return speed; }
    void setX(double a) {
        x = a;
    }
    void setY(double a) {
        y = a;
    }
    void setSpeed(int a){
        speed = a;
    }
    void drawBall(double x, double y) {
        mvaddch(x, y, 'o');
    }
private:
    double x, y;
    int speed;

};


#endif //PONG_BALL_H
