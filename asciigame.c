#include "asciigame.h"
#include <string.h>

extern int termsize(int);

colormap asciigame_default_colormap[200] = {
    {'@',FG_RED},
    {'#',FG_YELLOW},
    {'.',FG_YELLOW},
    {'"',ATTR_BOLD FG_YELLOW},
    {'$',ATTR_BOLD FG_YELLOW},
    {'=',ATTR_BOLD FG_YELLOW},
    {'{',FG_CYAN},
    {'}',FG_CYAN},
    {';',FG_RED},
    {':',FG_RED},
    {'^',FG_RED},
    {'~',FG_BLUE},
    {'<',ATTR_BOLD},
    {'>',ATTR_BOLD},
    {'!',ATTR_BOLD FG_GREEN},
    {'\'',FG_YELLOW}
};

struct __asciigame_ asciigame = {0};

struct __asciigame_cursor cursor = {0};
struct __asciigame_screen screen = {0};

struct __asciigame_character player = {0};

struct __asciigame_npc npc[1000] = {0};
int active_npc = 0;

struct __asciigame_map map    = {0};
struct __asciigame_map places = {0};
struct __asciigame_map items  = {0};

void asciigame_init(void)
{
    /* initialize asciigame */
    asciigame.color     = ASCIIGAME_INTERNAL(asciigame,color);
    asciigame.setcolors = ASCIIGAME_INTERNAL(asciigame,setcolors);
    asciigame.setcolors(asciigame_default_colormap);

    /* initialize screen */
    screen.rows      = termsize('r');
    screen.cols      = termsize('c');
    screen.printat   = ASCIIGAME_INTERNAL(screen,printat);
    screen.putcharat = ASCIIGAME_INTERNAL(screen,putcharat);
    screen.clear     = ASCIIGAME_INTERNAL(screen,clear);

    /* initialize cursor */
    cursor.set  = ASCIIGAME_INTERNAL(cursor,set);
    cursor.home = ASCIIGAME_INTERNAL(cursor,home);

    /* initialize player */
    player.icon    = '@';   /* and it should stay this way unless the programmer is a sadistic wacko */
    player.move    = ASCIIGAME_INTERNAL(player,move);
    player.reprint = ASCIIGAME_INTERNAL(player,reprint);

    /* initialize maps */
    map.reprint    = ASCIIGAME_INTERNAL(map,reprint);
    map.load       = ASCIIGAME_INTERNAL(map,load);
    items.reprint  = ASCIIGAME_INTERNAL(items,reprint);
    items.load     = ASCIIGAME_INTERNAL(items,load);
    places.reprint = ASCIIGAME_INTERNAL(places,reprint);
    places.load    = ASCIIGAME_INTERNAL(places,load);

    int i;
    for (i = 0; i < 1000; i++) {
        npc[i].reprint = ASCIIGAME_INTERNAL(npc,reprint);
        npc[i].move    = ASCIIGAME_INTERNAL(npc,move);
    }
}