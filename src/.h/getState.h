char getState(char* pathToPid){
  FILE* file;
  char aux;
  int count = 0;

  if(!(file = fopen(pathToPid, "r"))){
    printf("Error: on %s\n", pathToPid);
    return '0';
  }

  while((aux = fgetc(file)) != EOF){
    if(aux == ' '){count++; continue;}
    if(count == 2){break;}
  }
  fclose(file);
  return aux;
}