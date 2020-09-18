#include <ncurses.h>
#include <stdlib.h>
#include "Player.h"
#include "Ball.h"


int ch;
constexpr int width = 80;
constexpr int height = 24;
int player1Points, player2Points = 0;
bool quit = false;
char wallTexture, playerTexture;
bool player1Serve, player2Serve = false;

// magic numbers
constexpr int mid_wall = width / 2;
constexpr int mid_height = height / 2;
constexpr int right_most = width - 3;
constexpr int left_most = 2;
constexpr int up_most = 3;
constexpr int down_most = height - 4;

enum class Directions {
    right, left, right_up, right_down, left_up, left_down
};
Directions dir = Directions::right;

Player player1(mid_height, 2);
Player player2(mid_height, width - 3);

Ball ball(mid_height, 3, 1);

void setup();
void input();
void logic();
void draw();

int main() {

    setup();

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

void setup()
{
    // Textures
    wallTexture = '*';

    // Init ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(50);

    quit = false;
    player1Points = 0;
    player2Points = 0;
}

void input()
{
    ch = getch();
    switch(ch) {
        case KEY_UP:
            if(player2.getY() != up_most)
                player2.setY(player2.getY() - 1);
            break;
        case KEY_DOWN:
            if(player2.getY() != down_most)
                player2.setY(player2.getY() + 1);
            break;
        case KEY_LEFT:
            if(player2.getX() != mid_wall + 4)
                player2.setX(player2.getX() - 1);
            break;
        case KEY_RIGHT:
            if(player2.getX() != right_most)
                player2.setX(player2.getX() + 1);
            break;
        case 'w':
            if(player1.getY() != up_most)
                player1.setY(player1.getY() - 1);
            break;
        case 's':
            if(player1.getY() != down_most)
                player1.setY(player1.getY() + 1);
            break;
        case 'a':
            if(player1.getX() != left_most)
                player1.setX(player1.getX() - 1);
            break;
        case 'd':
            if(player1.getX() != mid_wall - 4)
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
    if(ball.getY() >= height - 2) {
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

    else if(ball.getX() == width) {
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
    refresh();
    for(int i = 0; i < width; i++) {
        mvaddch(0, i, wallTexture);
        mvaddch(height - 1, i, wallTexture);
    }

    for(int i = 1; i < height - 1; i++)
        mvaddch(i, mid_wall, ':');

    mvprintw(1, 0.25 * width, "%i", player1Points);
    mvprintw(1, 0.75 * width, "%i", player2Points);

    ball.drawBall();
    player1.drawPlayer();
    player2.drawPlayer();
}
