#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

/**************************************************
 * DEFINITIONS
 **************************************************/

#define DIRECTORY_TYPE "/"
#ifdef _WIN32
# undef DIRECTORY_TYPE
# define DIRECTORY_TYPE "\\"
#endif

/* colors */
#define ATTR_BOLD   ";1"
#define ATTR_DIM    ";2"
#define ATTR_INVERT ";7"
#define ATTR_INVIS  ";8"
#define FG_BLACK    ";30"
#define FG_RED      ";31"
#define FG_GREEN    ";32"
#define FG_YELLOW   ";33"
#define FG_BLUE     ";34"
#define FG_MAGENTA  ";35"
#define FG_CYAN     ";36"
#define FG_GRAY     ";37"
#define BG_BLACK    ";40"
#define BG_RED      ";41"
#define BG_GREEN    ";42"
#define BG_YELLOW   ";43"
#define BG_BLUE     ";44"
#define BG_MAGENTA  ";45"
#define BG_CYAN     ";46"
#define BG_GRAY     ";47"

/* some random defaults I thought up on the spot */
#define ASCIIGAME_MAP_ROWS 40
#define ASCIIGAME_MAP_COLS 200

/* possibly useful for interfacing with inventories */
#define item1  items[1]
#define item2  items[2]
#define item3  items[3]
#define item4  items[4]
#define item5  items[5]
#define item6  items[6]
#define item7  items[7]
#define item8  items[8]
#define item9  items[9]
#define item10 items[10]

/**************************************************
 * ASCIIGAME STRUCTURES
 **************************************************/

typedef struct {
    char character;
    char *color;
} colormap;
 
struct __asciigame_ {
    void (*color)(char c);
    colormap colors[200];
    void (*setcolors)(colormap newcolors[]);
};
 
struct __asciigame_screen {
    int rows, cols;
    void (*clear)(void);
    int (*printat)(int x, int y, char *s);
    int (*putcharat)(int x, int y, char c);
};

struct __asciigame_cursor {
    int x, y;
    int (*set)(int x, int y);
    void (*home)(void);
};

struct __asciigame_item {
    char name[100];
    int type, weight;
};

struct __asciigame_inventory {
    struct __asciigame_item items[10];
};

struct __asciigame_character {
    int x, y;
    int hit, def, atk;      /* hit, defense, attack              */
    int str, cha, intl;     /* strength, charisma, intelligence  */
    int gold, mana, lives;
    int invisible;          /* if character is magically invisible */
    char icon;              /* should have defaults sooner or later */
    struct __asciigame_inventory inventory;
    int (*reprint)(void);
    int (*move)(int x, int y);
};

struct __asciigame_npc {
    int x, y;
    int hit, def, atk;
    int str, cha, intl;
    int gold, lives, invisible;
    char *color, icon;
    struct __asciigame_inventory loot;
    int (*reprint)(void);
    int (*move)(int x, int y);
};

struct __asciigame_map {
    char coord[ASCIIGAME_MAP_ROWS][ASCIIGAME_MAP_COLS];
    void (*reprint)(void);
    int (*load)(char *filename);
};

/**************************************************
 * MACRO WIZARDRY
 **************************************************/

#define _cat(x,y) x ## y
#define cat(x,y) _cat(x,y)
#define ASCIIGAME_INTERNAL(class,function) cat(__asciigame_internal_, cat(class,cat(_,function)))
#define ASCIIGAME_INTERNAL_DEF(type,class,function) extern type ASCIIGAME_INTERNAL(class,function)
/* funny story. I figured ASCIIGAME_INTERNAL_DEF would cause a bunch of errors because of using the
 * `extern` keyword in non-extern function deflarations. Then I remembered, when I was 11, I had no
 * idea what the `extern` keyword was actually for, so I'd put it in every function aside from `main`.
 * It had no effect on the code, so I doubt it will now. We're good, I don't have to rethink the entire
 * structure. Moral of the story: code as a kid, it'll help later. Maybe. Or ruin your ability to think
 * creatively and/or positively for the rest of your life. /shrug Creativity and positivity are for losers.
 */

/**************************************************
 * EXTERNS AND DECLARATIONS
 **************************************************/

extern struct __asciigame_          asciigame;
extern struct __asciigame_screen    screen;
extern struct __asciigame_cursor    cursor;
extern struct __asciigame_character player;    /* player */
extern struct __asciigame_npc       npc[1000]; /* NPCs   */
extern struct __asciigame_map       map;
extern struct __asciigame_map       places;
extern struct __asciigame_map       items;

extern int active_npc;

extern colormap asciigame_default_colormap[200];    /* default colors for various characters */

#if defined(__clang__) || defined(__GNUC__)
extern void __attribute__((constructor)) asciigame_init(void);
#else
extern void asciigame_init(void);
#endif

/* ASCII */
ASCIIGAME_INTERNAL_DEF(void,asciigame,color)(char c);                   /* print c with colormap */
ASCIIGAME_INTERNAL_DEF(void,asciigame,setcolors)(colormap newcolors[]); /* set the colormap to new colors */

/* SCREEN */
ASCIIGAME_INTERNAL_DEF(void,screen,clear)   (void);                   /* clear... the... screen */
ASCIIGAME_INTERNAL_DEF(int,screen,printat)  (int x, int y, char *s);  /* print s at position (x,y) on the screen */
ASCIIGAME_INTERNAL_DEF(int,screen,putcharat)(int x, int y, char c);   /* print c at position (x,y) on the screen */

/* CURSOR */
ASCIIGAME_INTERNAL_DEF(int,cursor,set)   (int x, int y);   /* set the cursor to the specified position */
ASCIIGAME_INTERNAL_DEF(void,cursor,home) (void);           /* set the cursor to (1,1) */

/* PLAYER */
ASCIIGAME_INTERNAL_DEF(int,player,reprint) (void);           /* reprint the character */
ASCIIGAME_INTERNAL_DEF(int,player,move)    (int x, int y);   /* move the character to {x,y} */

/* NPCs */
ASCIIGAME_INTERNAL_DEF(int,npc,reprint) (void);           /* reprint active NPC */
ASCIIGAME_INTERNAL_DEF(int,npc,move)    (int x, int y);   /* move active NPC */

/* MAPS */
ASCIIGAME_INTERNAL_DEF(void,map,reprint)    (void);           /* reprint... the... map */
ASCIIGAME_INTERNAL_DEF(void,places,reprint) (void);           /* reprint places */
ASCIIGAME_INTERNAL_DEF(void,items,reprint)  (void);           /* reprint items */
ASCIIGAME_INTERNAL_DEF(int,map,load)        (char *filename); /* load filename into map */
ASCIIGAME_INTERNAL_DEF(int,places,load)     (char *filename); /* load filename into places */
ASCIIGAME_INTERNAL_DEF(int,items,load)      (char *filename); /* load filename into items */