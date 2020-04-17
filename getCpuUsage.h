double cpuUsage(){
  FILE* file;
  double num1, num2, num3;

  if(!(file = fopen("/proc/stat", "r"))){
    printf("Erro ao abir /proc/stat");
    return 0;
  }
  fscanf(file, "%*s %lf %lf %lf", &num1, &num2, &num3);
  fclose(file);

  return num1 + num2 + num3;
}

double getCpuUsage(char* pathToPid){
  FILE* file;
  char aux, utime[50], stime[50];
  int count = 0, i = 0, j = 0;

  if(!(file = fopen(pathToPid, "r"))){
    printf("Error: on %s\n", pathToPid);
    return 0;
  }

  while((aux = fgetc(file)) != EOF){
    if(aux == ' '){count++; continue;}
    if(count == 13){ utime[i] = aux; i++; }
    else if(count == 14){ stime[j] = aux; j++; }
  }
  fclose(file);

  utime[i] = '\0';
  stime[j] = '\0';

  double pidcpu = atoi(utime) + atoi(stime);
  return ((double)pidcpu*100) / cpuUsage();
}