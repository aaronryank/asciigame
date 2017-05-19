#include <termios.h>
#include <string.h>

void stdin_mod(char cmd[])
{
	struct termios t;
	tcgetattr(1,&t);

	if (!strcmp(cmd,"set"))
		t.c_lflag &= ~(ICANON | ECHO);
	else if (!strcmp(cmd,"reset"))
		t.c_lflag |= (ICANON | ECHO);

	tcsetattr(1,0,&t);
}
