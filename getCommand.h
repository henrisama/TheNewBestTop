void getCommand(char* pathToPid, char* comm){
  FILE* file;
  char aux[1024], pathToComm[50];

  strcpy(pathToComm, pathToPid);
  strcat(pathToComm, "/comm");

  if(!(file = fopen(pathToComm, "r"))){
    printf("Error: getCommand on %s", pathToPid);
  }

  fgets(aux, sizeof(aux), file);

  int len = (strlen(aux) >= 15)? 14 : strlen(aux);
  strncpy(comm, aux, len);
  comm[len-1] = '\0';
}