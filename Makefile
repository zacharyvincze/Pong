default: build

build:
	@g++ src/main.cpp src/Player.cpp src/Ball.cpp -lncurses -o pong || (echo "\n==> $(tput setaf 1)Make failed.  Do you have all the src files?\n$(tput sgr0)"; exit 1)
	@echo "\n==> $(tput setaf 2)Make successful.  Start the game using $(tput sgr0)make run$(tput setaf 2) or $(tput sgr0)./pong$(tput sgr0)\n"

run:
	./pong || true

clean:
	rm pong
