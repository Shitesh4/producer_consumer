#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#define buffsize 5
typedef int buffer_item;
pthread_mutex_t mutex;
sem_t full,empty;
int count;
int x;
buffer_item buffer[buffsize];

void *producer(j)
 { int item,i;
   x=(x+rand())%10;
   item=x;
   pthread_mutex_lock(&mutex);
   //printf("%d \n",count);
   if(count<6)
    {sem_wait(&empty);
     printf("Producer %d produced item : %d\n",(j+1),item);
     buffer[count++]=item;
     //printf("Count is %d \n",count);
     sem_post(&full);}
  else
   printf("Buffer is full Producer can't produce more\n");
  pthread_mutex_unlock(&mutex);
 }

void *consumer(c)
 { int item;
   pthread_mutex_lock(&mutex);
   if(count>1)
    {sem_wait(&full);
     item=buffer[--count];
     printf("Consumer %d has consumed item : %d\n",(c+1),item);
     sem_post(&empty);
    }
   else
    printf("Buffer is empty there is nothing to consume \n");
   pthread_mutex_unlock(&mutex);
 }

void main()
  {
   pthread_mutex_init(&mutex,NULL);
   sem_init(&full,1,0);
   sem_init(&empty,1,buffsize);
   count=1;
   int z,y,i,c;
   printf("Number of producer : ");
   scanf("%d",&z);
   printf("Number of consumer : ");
   scanf("%d",&y);
   printf("\n\n");
   if(z==0)
   { printf("There is no producer\n");
    printf("Consumer can't consume anything\n");}
   if(y==0)
    printf("There is no consumer\n");
   pthread_t pro[z],con[y];
   for(i=0;i<z;i++)
   {  pthread_create(&pro[i],NULL,producer,i);
      for(c=0;c<y;c++){
       pthread_create(&con[c],NULL,consumer,c);}
      }
for(i=0;i<z;i++)
   { 
       pthread_join(pro[i],NULL);
     for(c=0;c<y;c++){
       pthread_join(con[c],NULL);}
      }
 }



   
