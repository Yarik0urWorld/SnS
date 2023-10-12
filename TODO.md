0.4 (CANCELLED):
---------
 * Add some sort of pause menu (and merge it with help menu)
 * Add a second weapon, it will be a gun from first versions (only if I will find the sources (I have found))
 * Give snowmen some color
  Add MinGW support, and use it on Windows rather than Pelles C.

11 Oct 2023:
---------
 * I'm completely tired of piles of bad code in this program. It's impossible to make a game on bare OpenGL without
 a specific plan of the game. Gradually adding new features to SnS results in lots of lazy code that looks awful, awful
 non-reusable realizations of different stuff, and unused pieces of code that I'm afraid to delete. I must transform 
 SnS to a game engine *right now*, at version 0.3.1. At the moment, the code is complete junk that contains all that issues I
 mentioned above. Transformation should renovate it and make it not so junky. I hope this will help.

0.3.1:
---------
 * Clean up the code (model compilation was a bad idea)
 * Add mouse controls
