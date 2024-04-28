#include <pthread.h>
#include <stdio.h>

const int arraySize = 7;
int sampleArr[arraySize] = {90,81,78,95,79,72,85};
int* arrptr=sampleArr; 
int average;
int min;
int max; /* this data is shared by the thread(s) */
void *calcAverage(void *param); 
void *calcMax(void *param);
void *calcMin(void* param); 

void *calcAverage(void * param)
{
    int TempAverage = 0;
    for (size_t i = 0; i < arraySize; i++)
    {
        TempAverage+=sampleArr[i];
    }
    average = TempAverage/arraySize;
}
void *calcMax(void * param)
{
    int TempMax = 0;
    for (size_t i = 0; i < arraySize; i++)
    {
        if(TempMax<=sampleArr[i])
        {
            TempMax = sampleArr[i];
        }
    }
    max = TempMax;
}
void *calcMin(void * param)
{
    int TempMin = 0;
    for (size_t i = 0; i < arraySize; i++)
    {
        if(i==0)
        {
            TempMin=sampleArr[i];
        }
        if(TempMin>=sampleArr[i])
        {
            TempMin = sampleArr[i];
        }
    }
    min = TempMin;
}
#define NUM_THREADS 3
int main ()
{
    int i;
    pthread_t workers[NUM_THREADS]; /* the thread array*/
    pthread_attr_t attr; /*attributes for the threads */

    pthread_attr_init(&attr);
    pthread_create(&workers[0], &attr,calcAverage,NULL);  
    pthread_create(&workers[1], &attr,calcMax,NULL);  
    pthread_create(&workers[2], &attr,calcMin,NULL);  
    for (i=0; i<NUM_THREADS; i++)
        pthread_join(workers[i] ,NULL);
printf("avg = %d\n",average);
printf("max = %d\n",max);
printf("min = %d\n",min);


return 0;


}