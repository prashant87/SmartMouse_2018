#ifndef EMBED

#include "KnownMaze.h"
#include "Flood.h"
#include <errno.h>
#include  <fstream>
#include <iostream>

int main(int argc, char* argv[]){

  std::string maze_file;
  if (argc < 2) {
    maze_file = "mazes/16x16.mz";
  }
  else {
    maze_file = std::string(argv[1]);
  }

  std::fstream fs;
  fs.open(maze_file, std::fstream::in);

  if (fs.good()){
    KnownMaze maze(fs);
    Flood solver;
    solver.setup(maze);
    while (!solver.isFinished()) {
      solver.stepOnce();
      std::cin.get();
    }

    solver.teardown();
    fs.close();
    return EXIT_SUCCESS;
  }
  else {
		printf("error opening maze file!\n");
    fs.close();
    return EXIT_FAILURE;
  }
}

#endif
