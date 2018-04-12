#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#define buffsize 5                      //max buffer size is 5 
typedef int buffer_item;
pthread_mutex_t mutex;
sem_t full,empty;
int itembuff;
buffer_item buffer[buffsize];

void *producer(pr) 
 { int item;                                     
   item=(item+rand())%11;               //generating random numbers
   pthread_mutex_lock(&mutex);
   if(itembuff<6)                       //if there is space to produce 
    {sem_wait(&empty);
     printf("Producer %d produced item : %d\n",(pr+1),item);
     buffer[itembuff++]=item;
     sem_post(&full);}
   else                                 //if there is no space to produce
    printf("\nProducer %d Buffer is full Producer can't produce more\n",(pr+1));
   pthread_mutex_unlock(&mutex);
 }


void *consumer(co)
 { int item;
   pthread_mutex_lock(&mutex);
   if(itembuff>1)                       //if there is item in buffer to consume
    {sem_wait(&full);
     item=buffer[--itembuff];
     printf("Consumer %d consumed item : %d\n",(co+1),item);
     sem_post(&empty);
    }
   else                                 //if there is nothing in buffer to consume
    printf("\nConsumer %d Buffer is empty there is nothing to consume \n",(co+1));
   pthread_mutex_unlock(&mutex);
 }

void main()
 {
   pthread_mutex_init(&mutex,NULL);
   sem_init(&full,1,0);
   sem_init(&empty,1,buffsize);
   itembuff=1;
   int pr,co,i,x;
   printf("Number of producer : ");      //number of producer to be enter
   scanf("%d",&pr);
   printf("Number of consumer : ");      //number of consumer to be enter 
   scanf("%d",&co);
   printf("\n\n");
   if(pr==0)                             //if there is zero producer
   { printf("There is no producer\n");
     printf("So ,Consumer can't consume anything\n");}
   if(co==0)                             //if there is zero consumer
    printf("There is no consumer\n");
   pthread_t pro[pr],con[co];
   for(i=0;i<pr;i++) 
    {  
      pthread_create(&pro[i],NULL,producer,i);
      for(x=0;x<co;x++)
        {pthread_create(&con[x],NULL,consumer,x);}
     }
   for(i=0;i<pr;i++)
      { 
      pthread_join(pro[i],NULL);
      for(x=0;x<co;x++)
        {pthread_join(con[x],NULL);}
      }
  }



   
