# asciigame documentation

ASCIIGAME is a C library for developing ASCII-based games, inspired by Omega-RPG and Nethack.

It takes advantage of function pointers to make object-oriented-like C programming possible.

The structures include:

 - [`asciigame`](asciigame.md) (`.color()`, `.setcolor()`)
 - [`screen`](screen.md) (`.clear()`, `.printat()`, `.putcharat()`)
 - [`cursor`](cursor.md) (`.set()`, `.home()`)
 - [`player`](player.md) (`.reprint()`, `.move()`)
 - [`npc`](npc.md) (`.reprint()`, `.move()`)
 - [`map`/`places`/`items`](maps.md) (`.load(),`.reprint()`)