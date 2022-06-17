# BadEngine but for linux!
I got around to making it for linux, with some reworked mechanics, like the coord system\
Previous coord system was X, Depth, Y, but this is now X,Y,depth!

It uses some bits of the old render engine, like the screenspace function and the color mapping

this uses ncurses, so if it isnt installed on your system, you'll have to install ncurses (whops) since im too lazy to statically link it!!

CONTROLS:
- w to move up
- s to move down
- a to move left
- d to move right
- q to exit safely

You can exit by simply closing the program but it **will** mess up your terminal session

## Compile instructions 
`g++ main.cpp -lncurses`
you can use the `-Os` flag to get a smaller file size (near 25kb), and it'll still work as intended



# DEBUG KIT!!!
If your terminal is completely messed up after this, use `stty sane` or just run the program again and press `q`

If it fails to compile, use `curses.h` instead of `ncurses.h`\
If it still fails to compile, you probably dont have ncurses installed (!)\
[Install ncurses](https://google.com/search)
If it STILL fails after installing ncurses (and verifying that ncurses works), open an issue with the errors that it outputs


!!!!!
