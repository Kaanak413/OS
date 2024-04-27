#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 5
int nums[SIZE] = {0,1,2,3,4};
void collatzConjecture(int input)
{
    if(input==1)
    {
        printf("%d",input);
        return;
    }
    else if( input <=0)
    {
        printf("Input is invalid");
        return;
    }
    if(input%2==0)
    {
        printf("%d",input);
        collatzConjecture(input/2);
    }
    else
    {
        printf("%d",input);
        collatzConjecture((input*3)+1);
    }


}
int main()
{
printf("Enter an integer: ");  
int input;
scanf ("%d",&input);
int i;
pid_t pid;
pid = fork();
if (pid == 0) {
    collatzConjecture(input);
}
else if (pid > 0) {
wait(NULL);
}
return 0;
}