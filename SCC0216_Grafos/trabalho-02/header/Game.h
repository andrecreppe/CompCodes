#ifndef GAME_H
#define GAME_H

#include "Tile.h"
#include "Graph.h"
#include <vector>
#include <iostream>

enum class Move {Up, Right, Left, Down, Nothing};

class Game{

public:
    Game(int n, Tile::Type**map, int pacmanRow, int pacmanColumn, int ghostRow, int ghostColumn);
    
    //This function return false if no path was found.
    bool doAllSteps();
    void doOneStep();
    
    void moveGhost(char gm);
    void movePacman(Move gm);
    bool checkEndState();
    bool checkBounds(int row, int column);
    void printResults();

private:
    int size;
    Graph graph;    
    int pacmanRow;
    int pacmanColumn;
    int ghostRow;
    int ghostColumn;
    int numberOfUp;
    int numberOfDown;
    int numberOfLeft;
    int numberOfRight;

    void useRepresentationToAddEdges(Tile::Type**map);
    Move getMove(int rowFrom, int columnFrom, int rowTo, int columnTo);

};

#endif