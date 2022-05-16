#ifndef _MAZE_H_
#define _MAZE_H_

#include "node.h"

#define LICOL 16

namespace maze
{
   typedef struct _start_point_
   {
      int line, col;
   } startPoint;

   class Maze
   {
   public:
      /**
       * @brief Construct a new Maze object.
       * 
       * @param ascii - Labyrinthe au format ASCII servant à construire le labyrinthe sous forme de noeuds.
       * @param point - Coordonnées du point de départ.
       */
      Maze(const char ascii[LICOL][LICOL], startPoint point);
      virtual ~Maze();

      /**
       * @brief Vérifie que le labyrinthe est conforme.
       * 
       * @return true Le labyrinthe est conforme.
       * @return false Le labyrinthe n'est pas conforme.
       */
      bool checkConsistency();

      /**
       * @brief Cherche le formage dans la labyrinthe à partir du point de départ.
       * 
       * @return true Fromage trouvé/non trouvé
       */
      bool solve();

      /**
       * @brief Retourne une version ASCII du labyrinthe.
       * 
       * @param ascii Buffer pour stocker la version ASCII.
       */
      void getAsciiFormat(char ascii[LICOL][LICOL]);

      /**
       * @brief Retourne la node du point de départ
       * 
      */
      mazeNode::Node* getStarter();

   private:
    /**
     * @brief Parcours du labyrinthe.
     * 
     * @param position - Node de départ et position lors du parcours
     * 
     * @return Fromage trouvé/non trouvé
    */
    bool parse(mazeNode::Node* position);

   private:
      // l'ensemble des noeuds du labyrinthe, on ne conserve pas le format ASCII pour travailler.
      mazeNode::Node* nodes[16][16];
      // le noeud de départ
      mazeNode::Node* starter;
   };

}
#endif /* _MAZE_H_ */
