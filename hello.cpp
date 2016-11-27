// See  FUSE:  example/hello.c

#include "helloFS.h"
#include "structures.h"
int main(int argc, char *argv[])
{

  HelloFS fs;
  initFS();
  
  int status = fs.run(argc, argv);

  return status;
}
