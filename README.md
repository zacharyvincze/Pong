# Pong

![Screenshot](/screenshots/pong.png)

A simple pong game created in C++ with ncurses.

## Status
[![Build Status](https://travis-ci.org/zacharyvincze/Pong.svg?branch=master)](https://travis-ci.org/zacharyvincze/Pong)

## Usage
In the root directory use `make` or `make build` to compile the program.  This will create a `./pong` executable in the root directory of the project.

* To run the program, use either `make run` or `./pong` on the root directory of the project.
* To remove the program, use `make clean` or just `rm ./pong`.
* If you feel like doing a manual compile.  You can use `g++ src/main.cpp src/Player.cpp src/Ball.cpp -lncurses -o pong`.

You may need to install ncurses depending on what kind of system you're using.

* To install ncurses on a Debian based machine use `sudo apt-get install libncurses5-dev libncursesw5-dev`.
* To install ncurses on OS X use `brew install homebrew/dupes/ncurses`.  Of course, this will require [brew](http://brew.sh/ "Brew Homepage") to install.

## Controls
##### Player 1
* `W` - Move up
* `S` - Move down
* `A` - Move left
* `D` - Move right

##### Player 2
* `UP KEY` - Move up
* `DOWN KEY` - Move down
* `LEFT KEY` - Move left
* `RIGHT KEY` - Move right

To serve the ball, use the `SPACE` button.  It's the same for both players.

## Troubleshooting
I'm saving this section for later, trust me.  Something's gonna come up and I just want to be prepared.

If you have an issue with compiling or have found a bug in the game.  Take a look in the **Issues** section to see if the problem has been solved already.  If it's not, feel free to add the issue.  If it's big, it'll be posted in this troubleshooting section to help out other users.
