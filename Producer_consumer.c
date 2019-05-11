#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> //library for time.sleep();

#define BUFFER_SIZE 16

int buffer[BUFFER_SIZE];

int k_max=0;
int f=0;
int r=0;
int buff_Size=0;
long int sum; //Set as 'long int' for large size outputs 
sem_t sem;

void *producer(){
    int k;

    for(k=1; k<=k_max; k++){
        while(buff_Size >= BUFFER_SIZE);
        sem_wait(&sem);
        buffer[r]=k;
        buff_Size ++;
        r= (r+1)%BUFFER_SIZE;
        printf("Produced : %d\n",k);
        sem_post(&sem);
    }
}

void *consumer(){
    int k,num;
    sum=0;
    for(k=1; k<=k_max; k++){
        while(buff_Size==0);
        sem_wait(&sem);
        num = buffer[f];
        f=(f+1)%BUFFER_SIZE;
        buff_Size --;
        sum = sum +num;
        printf("Consumed: %d\n", num);
        sem_post(&sem);
    }
}

void scan_num(){
    printf("How many items?  "); //Set how many items you are trying to produce and consume
    scanf("%d",&k_max);
}

int main()
{
    sem_init(&sem, 0, 1);
    pthread_t producer_thread;
    pthread_t consumer_thread;

    scan_num();
    while(1) {
        pthread_create(&producer_thread, NULL, producer, NULL);
        pthread_create(&consumer_thread, NULL, consumer, NULL);

        pthread_join(producer_thread, NULL);
        pthread_join(consumer_thread, NULL);

        printf("Sum = %zu\n", sum);
        sleep(1);
   }
   return 0;
}