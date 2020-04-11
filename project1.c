#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
   int n;
   int i;
   pid_t p;
   printf("enter the number:\n");
   scanf("%d",&n);
   if(n<=0||n>2147483647)
     {
       printf("Error!!,Please enter the positive values within the range only\n");
       }
    else
        {
           p=fork();
           switch(p)
              {
                 case -1:
                        printf("process not created\n");
                        break;
                 case 0:
                        i=n;
                        for(;i>0;i=i/2)
                            {
                               printf("%d   ",i);
                            }
                        printf("\n");
                        break;
                  default:
                          wait(NULL);
                          break;
               }
       }
 return 0;
}
