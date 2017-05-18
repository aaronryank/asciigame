ASCIIGAME shall include:

 - player and NPC stuff
 - map stuff (including items and places)
 - screen stuff (clear, etc.)
 - **optional** output buffer-offset-ing stuff

Every `int`-returning function in ASCIIGAME shall return 1 upon success and 0 upon error.
The top right character that can be accessed by `screen.set` is {1,1}.