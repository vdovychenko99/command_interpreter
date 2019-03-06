#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>


pid_t pid;

void exeCommand(char* command){
    char* argv[20];
    int beakground;
    char* token;
    token=strtok(command," ");
    int i=0;
    for(;token!=NULL; i++){
        argv[i]=token;
        token=strtok(NULL," ");
    }
    if(strcmp(argv[i-1], "&")){
        beakground=0;
        argv[i]=NULL;
    } else{
        beakground=1;
        argv[i-1]=NULL;
    }
    if((pid=fork()) == -1)
        exit(1);
    if(pid==0){
        execvp(argv[0],argv);
        exit(1);
    }
    if (!beakground)
        wait(NULL);
}

static void catch_function(int signal){
    kill(pid,SIGINT);
    printf("\n");
}

int main(){
    printf("myShell started\n");
    signal(SIGINT,catch_function);
    char command[200];
    char ex[]="exit";

    while(1){
        printf(">");
        gets(command);

        if(command[0]=='\0')
            continue;
        if(strcmp(command,ex)==0)
            break;
        exeCommand(command);
    }
    printf("Goodbay!\n");
    return 0;
}