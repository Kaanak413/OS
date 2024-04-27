#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#define MSGSIZE 12
char* msg1 = "hello world";



int main(){
    char inbuf1[MSGSIZE];
    char inbuf2[MSGSIZE];

    int p1[2],p[2],pid,nbytesfirst,nbytessecond;
    if((pipe(p)<0)||pipe(p1)<0)
    {
        _exit;
    }    
    if(pid = fork()>0)
    {
        
        write(p[1],msg1,MSGSIZE);
        close(p[1]);
        wait(NULL);
        close(p1[1]);
        while((nbytessecond = read(p1[0],inbuf2,MSGSIZE))>0)
        {
            printf("% s\n", inbuf2);
        }
            if(nbytessecond != 0)
            {
                 _exit;
            }
            return 0;
        
    }
    else
    {
        close(p[1]);
        while((nbytesfirst = read(p[0],inbuf1,MSGSIZE))>0)
        {
            for (size_t i = 0; i < MSGSIZE; i++)
            {
                inbuf1[i]=toupper(inbuf1[i]);
            }
            
        }
            if(nbytesfirst != 0)
            {
                 _exit;
            }
        write(p1[1],inbuf1,MSGSIZE);
        close(p1[1]);
    }






    return 0;
}