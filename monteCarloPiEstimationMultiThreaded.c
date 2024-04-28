#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif
const int  INTERVAL =  10000;
const int numberOfThreads = 4;

const int numberOfInputs = 1000;
pthread_t tid[numberOfThreads]; 
int circle_points = 0, square_points = 0;
double rand_x, rand_y,pi;
int lastInput = 0;

pthread_mutex_t lock; 

void *workerGenerateThread(void *param);

double calcRandom();
bool calculateIfItIsInside(double x,double y);

void *workerGenerateThread(void *param)
{
    

    pthread_mutex_lock(&lock);
    double x = calcRandom();
    double y = calcRandom();
    if (calculateIfItIsInside(x,y))
    {
        circle_points++;
        square_points++;
    }
    else
    {   
        square_points++;
    }
    pthread_mutex_unlock(&lock);
    return NULL; 

} 

double calcRandom() 
{ 
    
        double val = (double)(rand() % (INTERVAL + 1)) / INTERVAL;
        return val;
    
}

bool calculateIfItIsInside(double x,double y)
{
    double distance = x*x + y*y;
    if(distance <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(void) 
{ 
    int i = 0; 
    int error; 
  
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
    while (i < numberOfThreads) { 
        error = pthread_create(&(tid[i]), 
                               NULL, 
                               &workerGenerateThread, NULL); 
        if (error != 0) 
            printf("\nThread can't be created :[]"); 
        i++; 
    }
    bool condition = square_points>=INTERVAL*INTERVAL;
    while(!condition)
    {
         
        condition = square_points>=INTERVAL*INTERVAL; 
    }
   
        for (i=0; i<numberOfThreads; i++)
        {
            pthread_join(tid[i] ,NULL);
        }
        pi = (double)(4 * circle_points) / square_points;   
        printf("Estimated pi value is %f",pi);
    
}