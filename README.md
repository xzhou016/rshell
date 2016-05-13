# rshell

Introduction
_____________
This is rshell, established spring 2016,  is a project created by students Xiao Zhou and Xander Villanueva of the CS100 software construction course at BCOE of UCR.  It is a terminal based shell that can run built in and special commands to the users satisfcation. Thus user can choose to enter a single command or a group of commands distinguished by designated connectors (;, ||, &&). A design passed off the well known composite pattern allows for flexability among variable creation and manipulation and therefore, complex groupings of commands such as: echo hello && echo world || mkdir newdir; echo world; cat hello;

Installation
_____________

To run this rshell from the terminal, enter the following commads:

1) git clone https://github.com/xzhou016/rshell.git (this will create a repository with the rshell within)

2) cd rshell  (this goes inside the rshell director where you will be running the program)

3) git checkout hw2 (this switches to the branch containing the true functionality of rshell)

4) make (this runs a makefile that generates an executable ready for action

5) bin/rshell 


