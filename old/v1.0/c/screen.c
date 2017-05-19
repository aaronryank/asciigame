#include <stdio.h>
#include "asciigame.h"

void screen_set(struct point locat)
{
	printf("\033[%d;%dH",locat.v,locat.h);
}

void clear_screen(void)
{
	printf("\e[1;1H\e[2J");
}

void clear(struct point locat, int x)
{
	screen_set(locat);
	printf("\e[%dK",x);
}

int printat(char *str, struct point locat)
{
	screen_set(locat);
	return printf("%s",str);
}

int putcharat(char s, struct point locat)
{
	screen_set(locat);
	return putchar(s);
}
