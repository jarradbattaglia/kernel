#include <errno.h>                                                              
#include <stdio.h>                                                              
                                                                                
int main(int argc, char *argv[]) {                                              
        int pid;                                                                
        char* testbuf = "test" ;                                      
        int n = strlen(testbuf);                                                
        if((pid=fork()) == 0) {                                                 
                printf("testchld: %d\n",getpid());                              
                char* buf = malloc(sizeof(char)*n);                             
                int return1 = syscall(285,getppid(),n,buf);                     
              printf("test: %d\n",return1);                                   
              printf("testThis: %s\n",buf);                                   
                exit(0);                                                        
        }                                                                       
        else {                                                                  
                printf("testpar: %d\n",pid);                                    
                int return1 = syscall(286,pid,n,testbuf);                       
                printf("testret: %d\n",return1);                                
                printf("TestPar: %s\n",testbuf);                                
        }     
        
        return 0;
