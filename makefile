all: rshell

rshell: bin rshell.o
	
bin:
	mkdir bin

rshell.o: 
	g++ -Wall -Werror -ansi -pedantic ./src/main.cpp -o ./bin/rshell 

clean: 
	rm -rf ./bin