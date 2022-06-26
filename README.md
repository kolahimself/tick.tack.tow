# tick.tack.tow
a basic command line game for tic-tac-toe written in C. I should warn you though, the Wumpus you'll face knows his stuff.


It's rather simple, you already know the rules: make 3 Xs in a row or lose trying.

The accompanying executable should work on any x86_64 based linux (compiled on ubutu 22.04) but the program is cross platform.
To compile using gcc:
$ gcc tick_tack.c -o tick_tack

Then run with
$ ./tick_tack

or, for Windows:
> tick_tack.exe

The prompts are straightforward, enter a letter for a setting,, or it chooses a default. 
Of course, I wouldn't recommend playing any difficulty less than hard (except for my more juvenile audience far less than 10).
Use keys 1 - 9 to select the squares, counting from top left (so that 3 means top right).


Even though it's not set by default, playing hard and letting Wumpus the Wise go first is the only way it can be worth your while (cause tic-tac-toe).
