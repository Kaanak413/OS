#include <stdio.h>

#define MINPID 300
#define MAXPID 5000

#define PID_LEN MAXPID - MINPID + 1

int PIDbitmap[MAXPID -  MINPID];

int allocate_map()
{
    for (int i = 0; i < PID_LEN; i++)
    {
        PIDbitmap[i] = 0;
    }

    return 1;
}

int allocate_pid()
{
    for (int i = 0; i < PID_LEN; i++)
    {
        if(PIDbitmap[i] == 0)
        {
            PIDbitmap[i] = 1; //CREATED PID
            int createdPID=i+MINPID;
            printf("Created PID is :%d\n",createdPID);
            return createdPID; 
        }
    }
        printf("Cannot create PID Slots are full");
        return 1;

}

void release_pid(int pid)
{
    if(pid>MAXPID || pid<MINPID)
    {
        printf("This PID does not exist in manager. Returning...");
        return;
    }
    else
    {
        PIDbitmap[pid-MINPID] = 0;
        printf("Released PID no :%d\n",pid);
    }

}


int main()
{
    int pid;
    allocate_map();

    pid = allocate_pid();

    release_pid(pid);
}