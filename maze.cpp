#include "maze.h"
using namespace maze;

Maze::Maze(const char ascii[LICOL][LICOL], startPoint point)
{
	// Créations des nodes en fonction du caractère trouvé
	for (size_t l = 0; l < LICOL; ++l) {
		for (size_t c = 0; c < LICOL; ++c) {
			switch (ascii[l][c]) {
			case 'w':
				this->nodes[l][c] = new mazeNode::NodeWall();
				break;
			case ' ':
				this->nodes[l][c] = new mazeNode::NodeFree();
				break;
			case 'c':
				this->nodes[l][c] = new mazeNode::NodeCheese();
				break;
			default:
				break;
			}
		}
	}

	// Création des liens entre voisins
	for (size_t l = 0; l < LICOL; ++l) {
		for (size_t c = 0; c < LICOL; ++c) {
			if (l == LICOL - 1) { // Si on est sur la dernière ligne 
				if (c != LICOL - 1) { // mais pas sur la dernière colonne
					this->nodes[l][c]->setNeighbor(mazeNode::NodeNeighbor_Right, this->nodes[l][c + 1]);
					this->nodes[l][c + 1]->setNeighbor(mazeNode::NodeNeighbor_Left, this->nodes[l][c]);
				}
			}
			else if (c == LICOL - 1) { // Si on est sur la dernière colonne
				if (l != LICOL - 1) { // mais pas sur la dernière ligne
					this->nodes[l][c]->setNeighbor(mazeNode::NodeNeighbor_Down, this->nodes[l + 1][c]);
					this->nodes[l + 1][c]->setNeighbor(mazeNode::NodeNeighbor_Up, this->nodes[l][c]);
				}
			} else {
				this->nodes[l][c]->setNeighbor(mazeNode::NodeNeighbor_Down, this->nodes[l + 1][c]);
				this->nodes[l + 1][c]->setNeighbor(mazeNode::NodeNeighbor_Up, this->nodes[l][c]);
				this->nodes[l][c]->setNeighbor(mazeNode::NodeNeighbor_Right, this->nodes[l][c + 1]);
				this->nodes[l][c + 1]->setNeighbor(mazeNode::NodeNeighbor_Left, this->nodes[l][c]);
			}
		}	
	}

	// Point de départ
	this->starter = this->nodes[point.line][point.col];
}

Maze::~Maze()
{
	// Je pensais ici avoir à supprimer this->nodes avec delete[]
	// et this->starter mais en réalité tout se fait déjà dans la classe Node.
	// Donc rien à faire ici.
}

bool Maze::checkConsistency()
{
	// Vérifie que tous les noeuds sont bien instanciés/existants
	for (size_t l = 0; l < LICOL; ++l) {
		for (size_t c = 0; c < LICOL; ++c) {
			if (!this->nodes[l][c]) // si au moins une node == nullptr
				return false;
		}
	}

	// On vérifie que le point de départ est valide (NodeType_Free)
	if (this->starter->getType() != mazeNode::NodeType_Free)
		return false;

	return true;
}

bool Maze::solve() {
   return this->parse(this->starter);
}

void Maze::getAsciiFormat(char ascii[LICOL][LICOL])
{
	for (size_t l = 0; l < LICOL; ++l) {
		for (size_t c = 0; c < LICOL; ++c) {
			ascii[l][c] = this->nodes[l][c]->getString();
		}
	}
}

mazeNode::Node* Maze::getStarter() {
	return this->starter;
}

bool Maze::parse(mazeNode::Node* position)
{
	bool exists = false;
	position->setVisited();
	// utilisation d'un autre pointeur pour que la récursion/exploration parallèle 
	// se fasse bien dans toutes les directions
	mazeNode::Node* positionLoc = position;

	// si la position actuelle est celle du fromage, on return true. le labyrinthe est complété.
	if (position->getType() == mazeNode::NodeType_Cheese) {
		return true;
	}
	else {
		if (position->isNeighborFree(mazeNode::NodeNeighbor_Down)) {
			positionLoc = position->getNeighbor(mazeNode::NodeNeighbor_Down);
			if (!exists) exists = parse(positionLoc); // on vérifie que exists n'est pas déjà true avant 
													  // d'entamer une nouvelle récursion
		} 
		if (position->isNeighborFree(mazeNode::NodeNeighbor_Right)) {
			positionLoc = position->getNeighbor(mazeNode::NodeNeighbor_Right);
			if (!exists) exists = parse(positionLoc);
		}
		if (position->isNeighborFree(mazeNode::NodeNeighbor_Up)) {
			positionLoc = position->getNeighbor(mazeNode::NodeNeighbor_Up);
			if (!exists) exists = parse(positionLoc);
		}
		if (position->isNeighborFree(mazeNode::NodeNeighbor_Left)) {
			positionLoc = position->getNeighbor(mazeNode::NodeNeighbor_Left);
			if (!exists) exists = parse(positionLoc);
		}
	}

	return exists;
}
