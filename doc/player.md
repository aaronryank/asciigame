# asciigame `player` structure

`player` : the player in the game

Variables:

|Type|Name|Description|Default Value|
|-|-|-|-|
|`int`|x|x-coordinate of player position|0|
|`int`|y|y-coordinate of player position|0|
|`int`|hit|hit points of player|0|
|`int`|def|defense points of player|0|
|`int`|atk|attack points of player|0|
|`int`|str|strength of player|0|
|`int`|cha|charisma of player|0|
|`int`|intl|intelligence of player|0|
|`int`|gold|player's gold|0|
|`int`|mana|player's mana|0|
|`int`|lives|player's remaining lives|0|
|`int`|invisible|player is invisible?|0|
|`char`|icon|how the player appears on the screen|red `@`|
|`inventory`|`inventory`|the player's inventory (10 items max)|(empty)|

Functions:

|Name|Parameters|Return Value|Description|
|-|-|-|-|
|reprint|`void`|`int` success/failure|print the player's icon at `{player.x,player.y}` in default color|
|move|`int x, int y`|`int` success/failure|move the player to `{x,y}` and `player.reprint()`|