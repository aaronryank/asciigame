#include "asciigame.h"
#include <stdio.h>
#include <unistd.h>

/* these are annoying to have in here */
extern void win32_clear_screen(void);

/**************************************************
 * <<<NOTE TO SELF>>>
 * NEVER use user-tailored functions such as
 *  `screen.clear` or `cursor.home`. There's no
 *  guarantee they've been initialized yet.
 *  instead, use `ASCIIGAME_INTERNAL(screen,clear)`
 *  and the like. Should save a few errors.
 * <<<NOTE TO ANYONE ELSE READING>>>
 * NEVER use comments like these. They suck.
 *  They're only necessary if the programmer is
 *  too lazy (or, rarely, has a good reason) to
 *  keep a thousand functions in one file.
 **************************************************/

/**************************************************
 * ASCIIGAME
 **************************************************/

ASCIIGAME_INTERNAL_DEF(void,asciigame,color)(char c)
{
    int i;
    for (i = 0; asciigame.colors[i].character; i++) {
        if (asciigame.colors[i].character == c) {
            printf("\e[%sm%c\e[0m",asciigame.colors[i].color,c);
            return;
        }
    }
    putchar(c);
}

ASCIIGAME_INTERNAL_DEF(void,asciigame,setcolors)(colormap newcolors[200])
{
    memset(asciigame.colors,0,sizeof(asciigame.colors));
    memcpy(asciigame.colors,newcolors,200*sizeof(colormap));
}

/**************************************************
 * SCREEN
 **************************************************/

ASCIIGAME_INTERNAL_DEF(void,screen,clear) (void)
{
#ifdef _WIN32
    win32_clear_screen();
#else
    write(0,"\e[H\e[2J",9);
#endif
}

ASCIIGAME_INTERNAL_DEF(int,screen,printat) (int x, int y, char *s)
{
    if (ASCIIGAME_INTERNAL(cursor,set)(x,y)) {
        printf("%s",s);
        fflush(stdout);
        return 1;
    }
    return 0;
}

ASCIIGAME_INTERNAL_DEF(int,screen,putcharat) (int x, int y, char c)
{
    if (ASCIIGAME_INTERNAL(cursor,set)(x,y)) {
        putchar(c);
        fflush(stdout);
        return 1;
    }
    return 0;
}

/**************************************************
 * CURSOR
 **************************************************/

ASCIIGAME_INTERNAL_DEF(int,cursor,set) (int x, int y)
{
    if ((x > screen.cols) || (y > screen.rows))
        return 0;
    if (x < 1)
        x = 1;
    if (y < 1)
        y = 1;

#ifdef _WIN32
    COORD coordScreen = {y-1,x-1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordScreen);
#else
    printf("\e[%d;%dH",y,x);
#endif
    return 1;
}

ASCIIGAME_INTERNAL_DEF(void,cursor,home) (void)
{
#ifdef _WIN32
    COORD coordScreen = {0,0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordScreen);
#else
    write(0,"\e[H",4);
#endif
}

/**************************************************
 * PLAYER
 **************************************************/

ASCIIGAME_INTERNAL_DEF(int,player,reprint) (void)
{
    if (ASCIIGAME_INTERNAL(cursor,set)(player.x,player.y)) {
        ASCIIGAME_INTERNAL(asciigame,color)(player.icon);
        return 1;
    }
    return 0;
    /* return ASCIIGAME_INTERNAL(screen,putcharat)(player.x,player.y,player.icon); */
    /* that was easy. */
}

ASCIIGAME_INTERNAL_DEF(int,player,move) (int x, int y)
{
    player.x = x;
    player.y = y;
    return ASCIIGAME_INTERNAL(player,reprint)();
}

/**************************************************
 * MAPS (untested)
 **************************************************/

ASCIIGAME_INTERNAL_DEF(int,map,load) (char *filename)
{
    FILE *in = fopen(filename,"r");
    if (!in)
        return 0;

    int c, x, y;
    x = y = 0;
    while ((c = getc(in)) != EOF)
    {
        map.coord[y][x++] = c;
        if (c == '\n') {
            y++;
            x = 0;
        }
    }

    fclose(in);
    return 1;
}

ASCIIGAME_INTERNAL_DEF(int,places,load) (char *filename)
{
    FILE *in = fopen(filename,"r");
    if (!in)
        return 0;

    int c, x, y;
    x = y = 0;
    while ((c = getc(in)) != EOF)
    {
        places.coord[y][x++] = c;
        if (c == '\n') {
            y++;
            x = 0;
        }
    }

    fclose(in);
    return 1;
}

ASCIIGAME_INTERNAL_DEF(int,items,load) (char *filename)
{
    FILE *in = fopen(filename,"r");
    if (!in)
        return 0;

    int c, x, y;
    x = y = 0;
    while ((c = getc(in)) != EOF)
    {
        items.coord[y][x++] = c;
        if (c == '\n') {
            y++;
            x = 0;
        }
    }

    fclose(in);
    return 1;
}

ASCIIGAME_INTERNAL_DEF(void,map,reprint) (void)
{
    ASCIIGAME_INTERNAL(screen,clear)();
    int rows,cols;
    for (rows = 0; map.coord[rows][0]; rows++) {
        for (cols = 0; map.coord[rows][cols]; cols++) {
            int c = map.coord[rows][cols];
            if (c != '\n') ASCIIGAME_INTERNAL(asciigame,color)(c);
        }
        putchar('\n');
    }
    fflush(stdout);
}

ASCIIGAME_INTERNAL_DEF(void,places,reprint) (void)
{
    ASCIIGAME_INTERNAL(screen,clear)();
    int rows,cols;
    for (rows = 0; places.coord[rows][0]; rows++) {
        for (cols = 0; places.coord[rows][cols]; cols++) {
            int c = places.coord[rows][cols] != ' ' ? places.coord[rows][cols] : map.coord[rows][cols];
            if (c != '\n') ASCIIGAME_INTERNAL(asciigame,color)(c);
        }
        putchar('\n');
    }
    fflush(stdout);
}

ASCIIGAME_INTERNAL_DEF(void,items,reprint) (void)
{
    ASCIIGAME_INTERNAL(screen,clear)();
    int rows,cols;
    for (rows = 0; items.coord[rows][0]; rows++) {
        for (cols = 0; items.coord[rows][cols]; cols++) {
            int c = items.coord[rows][cols] != ' ' ? items.coord[rows][cols] : places.coord[rows][cols] != ' ' ? places.coord[rows][cols] : map.coord[rows][cols];
            if (c != '\n') ASCIIGAME_INTERNAL(asciigame,color)(c);
        }
        putchar('\n');
    }
    fflush(stdout);
}