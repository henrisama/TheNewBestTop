#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX 15
#define MAX_TOP 1024

#include "getUser.h"
#include "getState.h"
#include "getPriority.h"
#include "getCpuUsage.h"
#include "getCommand.h"

typedef struct setTop{
  int pid;
  int priority;
  double cpuUsage;
  char state;
  char user[MAX];
  char command[MAX];
}Top;

#include "printTop.h" //printTop(Top* top, int count)

void theNewBestTop(Top* top, int* idx){
  DIR* proc;
  struct dirent* dit;

  if(!(proc = opendir("/proc"))){
    printf("Error opening '/proc'");
    exit(1);
  }

  while((dit = readdir(proc)) != NULL){
    int pid;
    char pathToPid[30] = "/proc/";

    if(!(pid = atoi(dit->d_name))){ continue; }

    strcat(pathToPid, dit->d_name);/* "/proc/[pid]" */
    
    /* ID Pid */
      top[(*idx)].pid = pid;

    /* User */
      char* user = getUser(&pathToPid[0]);
      int len = (strlen(user) >= 15)? 14 : strlen(user);

      strncpy(top[(*idx)].user, user, len);
      top[(*idx)].user[len] = '\0';
    
    /* Command */
      char command[15];
      getCommand(pathToPid, &command[0]);
      strcpy(top[(*idx)].command, command);
      
    /* From stat file */
    strcat(pathToPid, "/stat");/* "/proc/[pid]/stat" */
      /* State */
        top[(*idx)].state = getState(pathToPid);
      /* Priority */
        top[(*idx)].priority = getPriority(pathToPid);
      /* Cpu Usage */
        top[(*idx)].cpuUsage = getCpuUsage(pathToPid);
    (*idx)++;
  }

  closedir(proc);
}

int main(void) {
  Top top[MAX_TOP];
  int idx = 0;
  theNewBestTop(&top[0], &idx);
  printTop(&top[0], idx);
  return 0;
}