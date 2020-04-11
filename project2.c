#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#define size 100
int main(int arguments,char* arg[])
{
  int file[2];
  pid_t p;
  char readBuffer[size];
  pipe(file);
  if(arguments!=3)
    {
        printf("ERROR:Please enter the required parameters and arguments.\n");
        exit(1);
    }
   int InputFile=open(arg[1],0);
   int CopyFile=open(arg[2],O_RDWR|O_CREAT|O_APPEND,0666);
   if(InputFile==-1||CopyFile==-1)
     {
        printf("Files are not opened successfully.\n");
        exit(1);
     }
    p=fork();
    switch(p)
     {
        case -1:
                write(1,"Process not created successfully \n",21);
                break;
        case 0:
               close(file[1]);
               while(read(file[0],readBuffer,sizeof(readBuffer))>0)
                   {
                      write(CopyFile,readBuffer,strlen(readBuffer)-1);
                    }
               close(file[0]);
               close(CopyFile);
               break;
        default:
                close(file[0]);
                while(read(InputFile,readBuffer,sizeof(readBuffer))>0)
                     {
                        write(file[1],readBuffer,sizeof(readBuffer));
                        memset(readBuffer,0,size);
                    }
                 close(file[1]);
                 close(InputFile);
                 wait(NULL);
                 break;
    }
return 0;
}
