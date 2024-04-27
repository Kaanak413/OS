#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#define SIZE 1024


void collatzConjecture(int input,char *ptr)
{
    if(input==1)
    {
        sprintf(ptr,"%d",input);
        int length = snprintf( NULL, 0, "%d", input );

        ptr += length;
        return;
    }
    else if( input <=0)
    {
        printf("Input is invalid");
        return;
    }
    if(input%2==0)
    {
        sprintf(ptr,"%d",input);
        int length = snprintf( NULL, 0, "%d", input );

        ptr += length;
        collatzConjecture(input/2,ptr);
    }
    else
    {
       sprintf(ptr,"%d",input);
        int length = snprintf( NULL, 0, "%d", input );

        ptr += length;
        collatzConjecture((input*3)+1,ptr);
    }


}
int main()
{
const char* nameOfTheMemory = "OS";

int shm_fd;
int shm_fd_consumer;

void *ptr;
char* temp;
void *ptrConsumer;
printf("Enter an integer: ");  
int input;
scanf ("%d",&input);
int i;
pid_t pid;
pid = fork();
if (pid == 0) {
    shm_fd = shm_open(nameOfTheMemory,O_CREAT | O_RDWR ,0666);
    ftruncate(shm_fd,SIZE);
    ptr= mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0);
    temp = (char*)ptr;
    collatzConjecture(input,temp);
}
else if (pid > 0) {
wait(NULL);
shm_fd_consumer = shm_open(nameOfTheMemory,O_RDONLY ,0666);
ptrConsumer = mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd_consumer,0);
printf("%s",(char*)ptrConsumer);
shm_unlink(nameOfTheMemory);
}
return 0;
}