# pong
Simple pong game

## Install

To create the makefile and the exe file
```
$ > qmake pong.pro
$ > make
```

## Multiplayer

There is 2 mode available :
- Player vs Player
- Player vs AI

### PvP

| Command | Player 1 | Player 2 |
| --- | --- | --- |
| up | Shift | ↑ |
| down | Ctrl | ↓ |
| reset | Backspace | Backspace |

### PvE

By default, you are playing against an AI, if you want to play multiplayer, set
AI to 0 in myScene.h line 24.

Control the difficulty with AI_level in myScene.h line 25, the more it is, the harder it will be.

