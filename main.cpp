#include <iostream>
#include "maze.h"

static const char asciiMaze2[LICOL][LICOL] =
{
   {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
   {'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', 'c', 'w', 'w', 'w', 'w', 'w'},
   {'w', ' ', 'w', 'w', 'w', 'w', ' ', 'w', 'w', ' ', ' ', 'w', 'w', 'w', 'w', 'w'},
   {'w', ' ', 'w', ' ', 'w', 'w', ' ', 'w', ' ', ' ', 'w', 'w', 'w', 'w', 'w', 'w'},
   {'w', ' ', ' ', ' ', 'w', 'w', ' ', 'w', ' ', 'w', 'w', ' ', ' ', ' ', ' ', 'w'},
   {'w', ' ', 'w', 'w', 'w', 'w', ' ', 'w', ' ', 'w', 'w', ' ', 'w', 'w', ' ', 'w'},
   {'w', ' ', 'w', ' ', ' ', 'w', ' ', 'w', ' ', ' ', 'w', ' ', 'w', ' ', ' ', 'w'},
   {'w', ' ', 'w', ' ', 'w', 'w', ' ', 'w', 'w', 'w', 'w', 'w', 'w', ' ', 'w', 'w'},
   {'w', ' ', 'w', ' ', 'w', 'w', ' ', 'w', 'w', 'w', 'w', ' ', ' ', ' ', 'w', 'w'},
   {'w', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', 'w', 'w', 'w'},
   {'w', 'w', ' ', 'w', 'w', ' ', 'w', 'w', 'w', 'w', 'w', ' ', 'w', 'w', 'w', 'w'},
   {'w', 'w', ' ', 'w', 'w', ' ', 'w', ' ', ' ', ' ', 'w', ' ', 'w', 'w', 'w', 'w'},
   {'w', ' ', ' ', 'w', 'w', ' ', ' ', ' ', 'w', 'w', 'w', ' ', 'w', 'w', 'w', 'w'},
   {'w', 'w', ' ', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', ' ', ' ', ' ', 'w', 'w'},
   {'w', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', 'w', 'w', ' ', 'w', 'w'},
   {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
};

static const char asciiMaze[LICOL][LICOL] =
{
   {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
   {'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', 'w', 'w', 'w', 'w', 'w'},
   {'w', ' ', 'w', 'w', 'w', 'w', ' ', 'w', 'w', ' ', ' ', 'w', 'w', 'w', 'w', 'w'},
   {'w', ' ', 'w', ' ', 'w', 'w', ' ', 'w', ' ', ' ', 'w', 'w', 'w', 'w', 'w', 'w'},
   {'w', ' ', ' ', ' ', 'w', 'w', ' ', 'w', ' ', 'w', 'w', ' ', ' ', ' ', ' ', 'w'},
   {'w', ' ', 'w', 'w', 'w', 'w', ' ', 'w', ' ', 'w', 'w', ' ', 'w', 'w', ' ', 'w'},
   {'w', ' ', 'w', ' ', ' ', 'w', ' ', 'w', ' ', ' ', ' ', ' ', 'w', ' ', ' ', 'w'},
   {'w', ' ', 'w', ' ', 'w', 'w', ' ', 'w', 'w', 'w', 'w', 'w', 'w', ' ', 'w', 'w'},
   {'w', ' ', 'w', ' ', 'w', 'w', ' ', 'w', 'w', 'w', 'w', ' ', ' ', ' ', 'w', 'w'},
   {'w', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', 'w', 'w', 'w'},
   {'w', 'w', ' ', 'w', 'w', ' ', 'w', 'w', 'w', 'w', 'w', ' ', 'w', 'w', 'w', 'w'},
   {'w', 'w', ' ', 'w', 'w', ' ', 'w', ' ', ' ', ' ', 'w', ' ', 'w', 'w', 'w', 'w'},
   {'w', ' ', ' ', 'w', 'w', ' ', ' ', ' ', 'w', 'w', 'w', ' ', 'w', 'w', 'w', 'w'},
   {'w', 'w', ' ', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', ' ', 'c', ' ', 'w', 'w'},
   {'w', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', 'w', 'w', ' ', 'w', 'w'},
   {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', ' ', 'w', 'w'},
};


int main()
{
   // Instanciation du labyrinthe et de son point de départ
   maze::startPoint start;
   start.line = 3; start.col = 3;
   maze::Maze theMaze(asciiMaze, start);

   // Validation du labyrinthe
   std::cout << "is the maze valid ?";
   if (!theMaze.checkConsistency())
       std::cout << " no. starting point not valid. (Line=" << start.line + 1 << ", Column=" << start.col + 1 << ")." << std::endl;
   else std::cout << " yes." << std::endl;

   std::cout << "is there a cheese? " << ((theMaze.solve()) ? "yes" : "no") << std::endl;
   std::cout << std::endl;


   char ascii[LICOL][LICOL];
   theMaze.getAsciiFormat(ascii);
      // Affichage du labyrinthe
   for (int line = 0; line < LICOL; line++) {
      for (int col = 0; col < LICOL; col++) {
         std::cout << ascii[line][col] << " ";
      }
      std::cout << std::endl;
   }

   return 0;
}
