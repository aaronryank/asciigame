# asciigame

ASCIIGAME is a C library for developing ASCII-based games, inspired by Omega-RPG and Nethack.

ASCIIGAME takes advantage of function pointers to make object-oriented-like C programming possible.

To build the library, type `make release`. To build and run the test, type `make test`.

To compile your game with the library, add the `-L. -lasciigame` flags to your compiler.

The documentation can be found in the subdirectory `doc`.

Stuff to note:

 - Every `int`-returning function in ASCIIGAME shall return 1 upon success and 0 upon error.
 - The top right character that can be accessed by `screen.set` is {1,1}.
 - Before accessing any NPCs, set `active_npc`.
 - Actually, on second thought, don't use NPCs. They're untested.
 - If you're not using GCC or Clang, you suck. And you need to call `asciigame_init` upon start.