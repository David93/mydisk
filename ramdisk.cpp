
#include "helloFS.h"
#include "structures.h"
#include <string>
int main(int argc, char *argv[])
{
  int status;
  HelloFS fs;
  string size=string(argv[2]);
  //initFS(size);
  argv[2]=NULL;
  if(argc==3)
  {	
  	initFS(size,"none.lol");
  	status = fs.run(argc-1, argv);
  }
  if(argc==4)
  {
  	initFS(size,string(argv[3]));
  	status = fs.run(argc-2, argv);
  }

  return status;
}
