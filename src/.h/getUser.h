#include <sys/stat.h>
#include <pwd.h>

char* getUser(char* pathToPid){
  struct stat arq;
  struct passwd* reg;

  stat(pathToPid, &arq);
  reg = getpwuid(arq.st_uid);
  
  return reg->pw_name;
}