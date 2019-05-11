# Producer Consumer
`Prodcuer_Consumer` is a simple code for Producer/Consumer problem using multithreading. 
I Added a function that you can set the amount of items you want to produce.


## Code of Producing thread
```c
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
```

## Code of Consuming thread

```c 
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
```



## Capture of execution
  ![Alt text](/Capture_Prod_Cons.png)
