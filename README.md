# ConnectFourGUI

This is an open-source project for the classical game Connect Four. Source code is free to use and share! But non-commerical purposes!

You're welcome to ask questions by opening an issue on this repository or just fork and pull your requests!

## GUI

This is a GUI for the Connect Four. You may use this GUI to test your strategy for the course 30240042 Introduction to Artificial Intelligence, Tsinghua University. This project is for Mac OS X users since the program given by the teacher's assistant, which is written in C#, seems to work not very well. However, you can use Qt compilers to release products on other platforms.

### Usage for Mac OS X

It is easy to use this program by double clicking the file `Release/ConnectFourGUI.app` or launch from Terminal
    
    $ Release/ConnectFourGUI.app/Contents/MacOS/ConnectFourGUI

#### Start

Once you launch the GUI, use `Game -> New Game -> Compete` or `Game -> New Game -> Others` to start a new game. The `Compete` mode will load your strategy file (see `Strategy File` part) as the "Black player" defaultly. The `speed` option decide how fast game continues when both players are "Computers".

#### Strategy File

Use `Settings -> My Strategy File` to specify your strategy file, which is a dynamic library (.dylib) file.

### Usage for Other Platforms

You may need to build the project yourself from the source code given. An important thing to remember: you have to use `32-bit` Qt library and `32-bit options` when compiling, since the dynamic libraries given by the course are in 32-bit archtecture.

You can download Qt 32-bit on Windows and Linux from Qt offical website, however, you have to compile yourself all the source code on Mac OS X since no binary of 32-bit is given.

### Compete Tool

A easy tool for competing between strategies.

#### Installing

First of all, goto `CompeteTool/main.cpp`, replace the variable `my` (now it is on line 124) with your strategy file path (better absolute path).

Then change to `CompeteTool/` folder and simply type

    $ make

Now, everything is done.

#### Usage

    $ ./compete <times per each opponent> -all|-ten|<number>

`times per each opponent` means how many rounds of game (2 games per each round) you would like for one opponent.

`-all` means play with all 50 opponents in `Testcases/`.

`-ten` means play with all 10 opponents, i.e., 10, 20, 30, ..., 100.

Or you can just specify a number as your opponent, say, 2 or 52.

Please note that this compete tool is just an outside shell for a more automatical test. The testing logic is derived from our original project that the course gives us. You may modify the `main` function in `main.cpp` to meet your needs!
