#include <fstream>
#include <iostream>

#include <common/commanduino/CommanDuino.h>
#include <common/commands/SolveCommand.h>
#include <console/ConsoleMouse.h>
#include <console/ConsoleTimer.h>
#include <common/core/Flood.h>
#include <cstring>
#include <common/core/util.h>

int main(int argc, char *argv[]) {

  std::string maze_file;
  bool rand = false;
  if (argc <= 1) {
    rand = true;
    printf("Using random maze\n");
  }
  else if (argc == 2) {
    if (strncmp(argv[1], "-q", 2) == 0) {
      GlobalProgramSettings.quiet = true;
      rand = true;
    }
    else {
      maze_file= std::string(argv[1]);
    }
  }
  else if (argc == 3) {
    maze_file = std::string(argv[2]);
    GlobalProgramSettings.quiet = true;
  }

  std::ifstream fs;
  fs.open(maze_file, std::ifstream::in);

  if (rand) {
    AbstractMaze maze = AbstractMaze::gen_random_legal_maze();
    ConsoleMouse::inst()->seedMaze(&maze);
  } else {
    if (fs.good()) {
      AbstractMaze m(fs);
      ConsoleMouse::inst()->seedMaze(&m);
    } else {
        printf("error opening maze file!\n");
      fs.close();
      return EXIT_FAILURE;
    }
  }
  ConsoleTimer timer;
  Command::setTimerImplementation(&timer);

  Scheduler *scheduler;
  Flood *flood = new Flood(ConsoleMouse::inst());
  scheduler = new Scheduler(new SolveCommand(flood));

  while (!scheduler->run());

  if (flood->isSolvable()) {
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

