#include "End.h"
#include "RealMouse.h"

End::End() : Command("end") {}

bool End::isFinished() {
  return true;
}

void End::end() {
  print("DONE.\r\n");
}
