# Chess
a chess game using c 

## Features
- initialize a checkboard and the pieces
- display a checkboard on the console

## Todo
- move a piece, capture etc.
- manage the conversion between coordinate and chess notations (ex: Be5) (see [Wikipedia page](https://en.wikipedia.org/wiki/Algebraic_notation_(chess)))
- test check / checkmate
- run a game
- evaluate position (???)
- creating bots
- add elo
  
---


Compiled with :
```
gcc -Wall -Werror -Wextra main.c -o chess ./echiquier.c
```
Current output :
```
TCFDRFCT
PPPPPPPP
# # # #
 # # # #
# # # #
 # # # #
PPPPPPPP
TCFDRFCT
e2 e4
TCFDRFCT
PPPP PPP
# # # #
 # #P# #
# # # #
 # # # #
PPPPPPPP
TCFDRFCT
```
