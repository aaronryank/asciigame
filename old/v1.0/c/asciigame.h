struct point {
	int v;
	int h;
};

// point functions
extern struct point makepoint(int, int);

// screen functions
extern void screen_set(struct point);      // set the cursor to the given point
extern void clear_screen(void);            // clear the entire screen and set the cursor to 0,0
extern void clear(struct point, int);      // clear part of a screen row - 0 = point to end, 1 = beginning to point, 2 = whole row containing point
extern int printat(char *, struct point);  // print the given string at the given point
extern int putcharat(char, struct point);  // print the given char at the given point

// stdin functions
extern void stdin_mod(char[]);             // modify standard input - char may be "set" or "reset" (set/reset flags)
