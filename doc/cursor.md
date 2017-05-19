# asciigame `cursor` structure

`cursor` : functions for setting the cursor position

Variables:

|Type|Name|Description|Default Value|
|-|-|-|-|
|`int`|x|(useless)||
|`int`|y|(useless)||

Functions:

|Name|Parameters|Return Value|Description|
|-|-|-|-|
|set|`int x, int y`|`int`, success/failure|Set the cursor position to `{x,y}`|
|home|`void`|`void`|set the cursor position to `{1,1}`|