#include "game.h"

#if defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#undef main

#endif

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
