int getPriority(char* pathToPid){
  FILE* file;
  char aux, priority[4];
  int count = 0, i = 0, result;

  if(!(file = fopen(pathToPid, "r"))){
    printf("Error: on %s\n", pathToPid);
    return '0';
  }

  while((aux = fgetc(file)) != EOF){
    if(count > 18){break;}
    if(aux == ' '){count++; continue;}
    if(count == 17){priority[i] = aux; i++;}
  }
  fclose(file);
  priority[i] = '\0';
  result = atoi(priority);
  return (result)? result : -999;
}