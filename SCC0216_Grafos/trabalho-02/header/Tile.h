#ifndef TILE_H
#define TILE_H


#include <string>

namespace Tile{
    enum Type{PacMan, Ghost, Obstacle, Free, PacManAndGhost};
    
    std::string getRepresentation(Type tile);

};

#endif