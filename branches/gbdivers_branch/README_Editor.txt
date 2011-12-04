=== OpenAWars Editor ===
by LittleWhite
Project page: http://code.google.com/p/openawars/
Email: lw.demoscene@gmail.com

First public version. This is a BETA! (I am not too sure about it :D), and this may produce some bugs. You can always report it on the bug tracker of the project: http://code.google.com/p/openawars/issues/list 
Be clear in your bug report, and try to define a path to reproduce it.

With this version you can:

- Create maps, with terrains and units, for the four factions
- Load maps

Actually the resources are not animated so don't be surprised that the editor is static.

The program accept some commands coming from the command line (use cmd!):

--widht 		number		The resolution on the x axis
--height 		number		The resolution on the y axis
--fullscreen				Set a fullscreen window
--mapWidth		number		The number of tile on the x axis for the map
--mapHeight		number		The number of tile on the y axis for the map
--load			map_path	Map file to load
--mapName		map_path	Map file to save the map in

The defaults values are
Width: 640
Height: 480
Not fullscreen
mapWidth: 15
mapHeight: 10
No loaded map
Saved in "save.map"

Controls (QWERTY keyboards):

Space bar: To set a tile / unit
'Q': To open the units tile bar
'W': TO open the buildings tile bar
Arrows: To move the cursor
Arrows in tile bar: Left / Right to change the selection ; Up / Down to change the faction.

!!! This part describe something that SHOULD NOT count as a bug:

The screen (camera) will show 15x10 part of the map. This is the minimum size! The tiles have a size of 32x32. The tiles are scaled on the fly. If you have a resolution that has the width lower than the default one, but the height higher than the default one, it will fail.
The opposite will fail too (higher width, lower height)
This is because the scaling algorithm can do zooming / shrinking at the same time.

That's all

Have fun, and send me you map, you will have a chance to see them in the final game :) !