#include <iostream>
#include "../header/Tile.h"
#include "../header/Game.h"

int main() {

  int n;
  int number_of_moves;
  int pacmanRow, pacmanColumn, ghostRow, ghostColumn;
  Tile::Type**map;

  std::cin>>n;
  
  //Initialise game map
  map = new Tile::Type*[n]; 

  for (int i = 0; i < n; i++) {
    map[i] = new Tile::Type[n]; 
  }

  //Get map values
  for(int i = 0; i < n; i ++){
    for(int j = 0; j < n; j++){
      int value;
      std::cin>>value;
      map[i][j] = (value == 0)?(Tile::Type::Free):(Tile::Type::Obstacle);
    }
  }

  //Get initial positions
  std::cin>>pacmanRow>>pacmanColumn>>ghostRow>>ghostColumn;

  //Get number of moves
  std::cin>>number_of_moves;

  auto game = Game(n, map, pacmanRow, pacmanColumn, ghostRow, ghostColumn);

  for (int i = 0; i < n; i++) {
    delete[] map[i];
  }

  delete[] map;

  //For all moves, move pacman than move the ghost
  for(int i = 0; i < number_of_moves; i++){
    char move;
    if(game.checkEndState())
      break; 
    game.doOneStep();
    if(game.checkEndState())
      break;
    std::cin>>move;
    game.moveGhost(move);
    if(game.checkEndState())
      break;
    
  }

  if(game.doAllSteps() == false){
    std::cout<<"Não foi possível achar um caminho";
    return 0;
  }

  game.printResults();

  return 0;

  
}


