#include <ncurses.h>
#include <stdlib.h>
#include <fstream>
#include <regex>
#include "Player.h"
#include "Ball.h"
#include "Magics.h"


Magics setup();
void input();
void logic();
void draw();
Config readconf();

bool quit = false;
int player1Points, player2Points = 0;
bool player1Serve, player2Serve = false;

// magic numbers
const Magics data = setup();

enum class Directions {
    right, left, right_up, right_down, left_up, left_down
};
Directions dir = Directions::right;

const Config conf = readconf();

const char wallTexture = conf.wallTexture;

Player player1 (data.mid_height, 2);
Player player2 (data.mid_height, data.width - 3);
Ball ball (data.mid_height, 3, conf.ball_speed);


int main() {

    // Game loop
    while(!quit)
    {
        input();
        logic();
        draw();
    }
    endwin();
    return 0;
}

Config readconf()
{
    using namespace std;

    mvprintw(data.height-4,2,"reading the file...");
    refresh();

    ifstream readfile {"settings.conf"};
    if (!readfile)
        throw "can't open the file for reading";

    Config result;

    regex pattern {R"(^(\w+):\s?(.+)$)"};
    for (string line; getline(readfile, line);) {
        smatch match;
        if (regex_search(line, match, pattern)) {
            // test for valid variables
            if (match[1].str() == "ball_speed")
                result.ball_speed = stoi(match[2].str());
            else if (match[1].str() == "wallTexture")
                result.wallTexture = match[2].str()[1];
        }
    }

    return result;
}

Magics setup()
{
    // Init ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(50);

    return {LINES, COLS};
}

void input()
{
    int ch = getch();
    switch(ch) {
        case KEY_UP:
            if(player2.getY() != data.up_most)
                player2.setY(player2.getY() - 1);
            break;
        case KEY_DOWN:
            if(player2.getY() != data.down_most)
                player2.setY(player2.getY() + 1);
            break;
        case KEY_LEFT:
            if(player2.getX() != data.mid_wall + 4)
                player2.setX(player2.getX() - 1);
            break;
        case KEY_RIGHT:
            if(player2.getX() != data.right_most)
                player2.setX(player2.getX() + 1);
            break;
        case 'w':
            if(player1.getY() != data.up_most)
                player1.setY(player1.getY() - 1);
            break;
        case 's':
            if(player1.getY() != data.down_most)
                player1.setY(player1.getY() + 1);
            break;
        case 'a':
            if(player1.getX() != data.left_most)
                player1.setX(player1.getX() - 1);
            break;
        case 'd':
            if(player1.getX() != data.mid_wall - 4)
                player1.setX(player1.getX() + 1);
            break;
        case ' ':
            if(player1Serve) {
                player1Serve = false;
                dir = Directions::right;
            }
            else if(player2Serve) {
                player2Serve = false;
                dir = Directions::left;
            }
            break;
        case 'q':
            quit = true;
            break;
    }
}

void logic()
{
    // Ball logic
    if(ball.getX() == player1.getX() + 1 || ball.getX() == player1.getX()) {
        if(ball.getY() <= player1.getY() + 2 && ball.getY() >= player1.getY() - 2) {
            if(ball.getY() >= player1.getY() - 2 && ball.getY() < player1.getY())
                dir = Directions::right_up;
            else if(ball.getY() <= player1.getY() + 2 && ball.getY() > player1.getY())
                dir = Directions::right_down;
            else
                dir = Directions::right;
        }
    }
    else if(ball.getX() == player2.getX() - 1  || ball.getX() == player2.getX()) {
        if(ball.getY() <= player2.getY() + 2 && ball.getY() >= player2.getY() - 2) {
            if (ball.getY() >= player2.getY() - 2 && ball.getY() < player2.getY())
                dir = Directions::left_up;
            else if (ball.getY() <= player2.getY() + 2 && ball.getY() > player2.getY())
                dir = Directions::left_down;
            else
                dir = Directions::left;
        }
    }

    // if player collide or already passed the wall
    if(ball.getY() >= data.height - 2) {
        if (dir == Directions::left_down)
            dir = Directions::left_up;
        else
            dir = Directions::right_up;
    }
    else if(ball.getY() <= 1) {
        if(dir == Directions::left_up)
            dir = Directions::left_down;
        else
            dir = Directions::right_down;
    }

    if(ball.getX() == 0) {
        player2Points++;
        player1Serve = true;
    }

    else if(ball.getX() == data.width) {
        player1Points++;
        player2Serve = true;
    }

    if(player1Serve) {
        ball.setX(player1.getX() + 1);
        ball.setY(player1.getY());
    }

    else if(player2Serve) {
        ball.setX(player2.getX() - 1);
        ball.setY(player2.getY());
    }

    // Ball directions
    if(!player1Serve || !player2Serve) {
        const int speed = ball.getSpeed();
        const double yspeed = 0.25 * ball.getSpeed();

        switch(dir) {
            case Directions::right:
                ball.setX(ball.getX() + speed);
                break;
            case Directions::left:
                ball.setX(ball.getX() - speed);
                break;
            case Directions::right_up:
                ball.setX(ball.getX() + speed);
                ball.setY(ball.getY() - yspeed);
                break;
            case Directions::right_down:
                ball.setX(ball.getX() + speed);
                ball.setY(ball.getY() + yspeed);
                break;
            case Directions::left_up:
                ball.setX(ball.getX() - speed);
                ball.setY(ball.getY() - yspeed);
                break;
            case Directions::left_down:
                ball.setX(ball.getX() - speed);
                ball.setY(ball.getY() + yspeed);
                break;
        }
    }
}

void draw()
{
    erase();
    for(int i = 0; i < data.width; i++) {
        mvaddch(0, i, wallTexture);
        mvaddch(data.height - 1, i, wallTexture);
    }

    for(int i = 1; i < data.height - 1; i++)
        mvaddch(i, data.mid_wall, ':');

    mvprintw(1, 0.25 * data.width, "%i", player1Points);
    mvprintw(1, 0.75 * data.width, "%i", player2Points);

    ball.drawBall();
    player1.drawPlayer();
    player2.drawPlayer();

    refresh();
}
