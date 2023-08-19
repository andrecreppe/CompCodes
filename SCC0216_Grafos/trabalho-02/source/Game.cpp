#include "../header/Game.h"

Game::Game(int n, Tile::Type**map, int pacmanRow, int pacmanColumn, int ghostRow, int ghostColumn){
    this->pacmanRow = pacmanRow;
    this->pacmanColumn = pacmanColumn;
    this->ghostRow = ghostRow;
    this->ghostColumn = ghostColumn;
    this->size = n;

    numberOfUp = 0;
    numberOfLeft = 0;
    numberOfRight = 0;
    numberOfDown = 0;

    graph = Graph();
    useRepresentationToAddEdges(map);
}
void Game::moveGhost(char gm){
    int cloneRow, cloneColumn;
    cloneRow = ghostRow;
    cloneColumn = ghostColumn;

    switch (gm)
    {
    case 'U' :
        cloneRow--;
        break;
    
    case 'D' :
        cloneRow++;
        break;
    
    case 'L' :
        cloneColumn--;
        break;
    
    case 'R' :
        cloneColumn++;
        break; 
    }

    if(checkBounds(cloneRow, cloneColumn)){
        ghostRow = cloneRow;
        ghostColumn = cloneColumn;
    }
}

bool Game::checkBounds(int row, int column){
    return ((row<size) && (column<size) && (row>=0) && (column>=0)); 
}

void Game::movePacman(Move gm){
    switch (gm)
    {
    case Move::Up :
        pacmanRow--;
        numberOfUp++;
        break;
    
    case Move::Down :
        pacmanRow++;
        numberOfDown++;
        break;
    
    case Move::Left :
        pacmanColumn--;
        numberOfLeft++;
        break;
    
    case Move::Right :
        pacmanColumn++;
        numberOfRight++;
        break; 

    case Move::Nothing :
        break;
    }
}

Move Game::getMove(int rowFrom, int columnFrom, int rowTo, int columnTo){
    int difference;

    difference = rowTo - rowFrom;
    if(difference > 0) {
        return Move::Down;
    }
    if(difference < 0) {
        return Move::Up;
    }

    difference = columnTo - columnFrom;
    if(difference > 0) {
        return Move::Right;
    }
    if(difference < 0) {
        return Move::Left;
    }

    return Move::Nothing;
}

bool Game::doAllSteps(){
    auto steps = graph.searchPath(pacmanRow*size+pacmanColumn, ghostRow*size+ghostColumn);
    if(steps.empty()){
        return false;
    }

    for(auto& step : steps){
        movePacman(getMove(pacmanRow, pacmanColumn, step/size, step%size));
    }

    return true;
}

void Game::doOneStep(){
    auto steps = graph.searchPath(pacmanRow*size+pacmanColumn, ghostRow*size+ghostColumn);
    
    //Return if there is no path or if the pacman is already at the ghost.
    if(steps.empty() || steps.size() == 1)
        return;

    //Get next vertex, as the first one is the start vertex
    auto next = *(steps.begin()++);
    auto nextRow = next/size;
    auto nextColumn = next%size;

    auto move = getMove(nextRow, nextColumn, pacmanRow, pacmanColumn);
    movePacman(move);
}

void Game::useRepresentationToAddEdges(Tile::Type**representation){

    //First add all vertices
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            graph.addVertex(i*size + j);
        }
    }

    //Make horizontal and vertical connections
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if((j-1 >= 0)&&(representation[i][j-1] != Tile::Type::Obstacle) && (representation[i][j] != Tile::Type::Obstacle)){
                graph.connectVertex(i*size + j-1, i*size + j);
            }

            if((i-1 >= 0)&&(representation[i-1][j] != Tile::Type::Obstacle) && (representation[i][j] != Tile::Type::Obstacle)){
                graph.connectVertex((i-1)*size + j, i*size + j);
            }
        }
    }
}

bool Game::checkEndState(){
    return ((pacmanColumn==ghostColumn) && (pacmanRow==ghostRow));
}

void Game::printResults(){
    std::cout<<"Número de passos: "<<(numberOfUp+numberOfDown+numberOfLeft+numberOfRight)<<std::endl;
    std::cout<<"Movimentos para cima: "<<(numberOfUp)<<std::endl;
    std::cout<<"Movimentos para baixo: "<<(numberOfDown)<<std::endl;
    std::cout<<"Movimentos para esquerda: "<<(numberOfLeft)<<std::endl;
    std::cout<<"Movimentos para direita: "<<(numberOfRight);
}