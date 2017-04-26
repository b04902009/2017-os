#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
void *thread_func(void * num){
    int k = num;
    k++;
    for (int i =0;i<3;i++){
        printf("Thread %d is running\n",k);
        double a = 0;
        for (int qq =0 ;qq<1360000000;qq++) a+=0.1f;
    }
}

int main(int argc,char * argv[]){
	pthread_t threads[2];
    pthread_attr_t attr;
    cpu_set_t cpus;
    pthread_attr_init(&attr);
    struct sched_param param[2];
   

    if (argc == 2){
        printf("%s\n",argv[1]);
        for (int i =0 ; i<2 ; i++){
            param[i].sched_priority = sched_get_priority_max(SCHED_FIFO)-i;
    
            CPU_ZERO(&cpus);
            CPU_SET(0,&cpus);
            pthread_attr_setaffinity_np(&attr,sizeof(cpu_set_t),&cpus);
            
            pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
            pthread_attr_setschedpolicy(&attr,SCHED_FIFO);
            pthread_attr_setschedparam(&attr,&param[i]);
            
            assert(pthread_create(&threads[i],&attr,thread_func,(void *) i)==0);
        }
        
    }
    else {
        for (int i =0 ; i<2 ; i++){
            CPU_ZERO(&cpus);
            CPU_SET(0,&cpus);
            pthread_attr_setaffinity_np(&attr,sizeof(cpu_set_t),&cpus);
            pthread_create(&threads[i],&attr,thread_func,(void *) i);
        }
    }
    for (int i =0 ; i<2 ;i++)
        pthread_join(threads[i],NULL);
}
