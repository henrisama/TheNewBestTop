void printTop(Top* top, int count){
  int i;
  printf("PID\tUSER\tS\tPR\t%%CPU\tCOMMAND\n");
  for(i = 0; i < count; i++){
    printf("%d\t", top[i].pid);
    printf("%s\t", top[i].user);
    printf("%c\t", top[i].state);
    printf("%d\t", top[i].priority);
    printf("%.3lf\t", top[i].cpuUsage);
    printf("%s\n", top[i].command);
  }
}