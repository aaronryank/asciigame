#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "asciigame.h"

/* woo such tests wow */

int main(void)
{
#if !defined(__clang__) && !defined(__GNUC__)
    asciigame_init();
#endif

#if 0
    printf("---ROUND 1: SCREEN/CURSOR---\nClearing screen.\n");
    sleep(1);
    screen.clear();

    printf("Jumping to point {1,1}.\n");
    sleep(1);
    cursor.set(1,1);
    printf("At point {1,1}.\n");

    printf("Jumping to point {10,10}.\n.\n.\n.\n.....");
    sleep(1);
    cursor.set(10,10);
    printf("At point {10,10}.\n");

    printf("Printing '@' at point {5,5}.\n");
    sleep(1);
    screen.putcharat(5,5,'@');

    printf("Printing 'Hello, World!\\n' at point {4,10}.\n");
    sleep(1);
    screen.printat(4,10,"Hello, World!\n");

    printf("Finished tests.\n");
    sleep(3);
    screen.clear();

    printf("---ROUND 2: PLAYER---\nReprinting player.\n");
    sleep(1);
    player.reprint();

    printf("\nMoving player to {3,9} manually and reprinting.\n");
    sleep(1);
    player.x = 3;
    player.y = 9;
    player.reprint();

    printf("\nMoving player to {9,3} using player.move.\n");
    sleep(1);
    player.move(9,3);

    printf("Finished tests.\n");
    sleep(3);
    screen.clear();
#endif
    printf("---ROUND 3: MAPS---\nLoading 'samplemaps" DIRECTORY_TYPE "test.map' into map.\n");
    sleep(1);
    if (map.load("samplemaps" DIRECTORY_TYPE "test.map"))
        map.reprint();
    else
        printf("Failed to load samplemaps" DIRECTORY_TYPE "test.map!\n");

    printf("Loading 'samplemaps" DIRECTORY_TYPE "places.map' into map.\n");
    sleep(1);
    if (places.load("samplemaps" DIRECTORY_TYPE "places.map"))
        places.reprint();
    else
        printf("Failed to load 'samplemaps" DIRECTORY_TYPE "places.map'!\n");

    printf("Loading 'samplemaps" DIRECTORY_TYPE "items.map' into map.\n");
    sleep(1);
    if (items.load("samplemaps" DIRECTORY_TYPE "items.map"))
        items.reprint();
    else
        printf("Failed to load 'samplemaps" DIRECTORY_TYPE "items.map'!\n");

    printf("Exiting...\n");
    sleep(2);
    screen.clear();
    return 0;
}