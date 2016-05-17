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




Commands
_____________
the rshell accepts commands that already exist in the bin (e.g ls, mkdir, etc.) and also accepts special commands that do not (e.g cd, exit, etc.) so there is no reason to worry if a command you enter will not work or not.





Connectors
_____________
Available connectors are:

";"
"||"
"&&"

In order to execute multiple commands in the same line, the rshell has designated connectors that allow you to link commands for simultaneous execution.  To create a list of commands, simply put a semicolon at the end of each command.  To incorporate desired logic into your chain of commands, you may add either the operator && or ||.  The || operator will only execute the command after it if the one before it fails. Oppositely, the command following the && operator will only execute if the command before the && operator has  successfully execute.  Here are a few examples to make this more clear:

echo hello && ls  -> if "echo hello" fails for some reason, "ls" will not be executed.

mkdir newdir || ls -> if "mkdir newdir" executes successfully, "ls" will not be executed.

echo hello || mkdir newdir && ls -> if "echo hello" succeeds, "mkdir newdir will not execute" but the or logic will still be 1 so "ls" will execute. 




Comments - #
______________
comments are an available feature with the rshell.  To create a comment, simply place a '#' in front of your command and it will be registered as a comment and thus, not executed. 



Exiting rshell
______________
To exit the rshell, use the "exit" command and you will leave the rshell.



Bugs/future updates
______________
Currently the rshell is experiencing difficulty sorting out commands based on their type.  It is running into problems when trying to execute special commands as they require special implementations.  If you experience trouble with this, it is most likely not a problem on your end
