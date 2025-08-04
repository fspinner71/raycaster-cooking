#include <cstdlib>

#include "game.h"

int main()
{
  int exitStatus = EXIT_FAILURE;

  Game game;

  if(game.getStatus() == INIT_SUCCESS)
  {
    if(game.run())
    {
      exitStatus = EXIT_SUCCESS;
    }  
  }

  return exitStatus;
}
