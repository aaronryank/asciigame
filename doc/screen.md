# asciigame `screen` structure

`screen` : variables and functions for interfacing with the terminal screen

Variables:

|Type|Name|Description|Default value|
|-|-|-|-|
|`int`|rows|rows in terminal screen|`termsize('r')`. **do not change.**|
|`int`|cols|columns in terminal screen|`termsize('c')`. **do not change.**|

Functions:

|Name|Parameters|Return value|Description|
|-|-|-|-|
|clear|`void`|`void`|clear the terminal screen|
|printat|`int x, int y, char *s`|`int`, success/failure|print `s` at `{x,y}` on terminal screen|
|putcharat|`int x, int y, char c`|`int`, success/failure|print `c` at `{x,y}` on terminal screen|