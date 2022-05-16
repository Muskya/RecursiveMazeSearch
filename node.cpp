#include "node.h"
using namespace mazeNode;

Node::Node()
{
    // par défaut les voisins sont NULLs et le type du noeud NodeType_Wall
    this->visited = false;
    this->down = nullptr;
    this->right = nullptr;
    this->up = nullptr;
    this->left = nullptr;
    this->type = NodeType_Wall;
}

Node::~Node() {
    delete this;
}

eNodeType Node::getType() {
    return this->type;
}

void Node::setNeighbor(eNodeNeighbor position, Node* neighbor)
{
    switch (position) {
    case NodeNeighbor_Down:
        this->down = neighbor;
        break;
    case NodeNeighbor_Right:
        this->right = neighbor;
        break;
    case NodeNeighbor_Up:
        this->up = neighbor;
        break;
    case NodeNeighbor_Left:
        this->left = neighbor;
        break;
    default:
        break;
    }
}

Node* Node::getNeighbor(eNodeNeighbor position)
{
    switch (position) {
    case NodeNeighbor_Down:
        return this->down;
        break;
    case NodeNeighbor_Right:
        return this->right;
        break;
    case NodeNeighbor_Up:
        return this->up;
        break;
    case NodeNeighbor_Left:
        return this->left;
        break;
    default: // S'il n'existe pas de node à la position donnée
        return nullptr;
        break;
    }
}

bool Node::isNeighborFree(eNodeNeighbor position)
{
    if (this->getNeighbor(position) != nullptr)
        return this->getNeighbor(position)->isFreeToVisit();
    else return false;
}

void Node::setVisited() {
    this->visited = true;
}

bool Node::isVisited() {
    return this->visited;
}

bool Node::isFreeToVisit() {
    return !this->isVisited() && this->getType() != NodeType_Wall;
}

NodeWall::NodeWall() : Node() {
   this->type = NodeType_Wall;
}
const char NodeWall::getString() {
   return 'w';
}

NodeFree::NodeFree() : Node() {
   this->type = NodeType_Free;
}
const char NodeFree::getString()
{
   if (this->visited) return '.';
   else return ' ';
}

NodeCheese::NodeCheese() : Node() {
   this->type = NodeType_Cheese;
}
const char NodeCheese::getString()
{
   if (this->visited)
      return 'X';
   else return 'c';
}
