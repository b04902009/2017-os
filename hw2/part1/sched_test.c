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
        for (int qq =0 ;qq<136000000;qq++) a+=0.1f;
    }
}

int main(int argc,char * argv[]){
	pthread_t threads[2];
    pthread_attr_t attr[2];
    cpu_set_t cpus;
    pthread_attr_init(&attr[0]);
    pthread_attr_init(&attr[1]);
    struct sched_param param[2];
    struct sched_param main_param;
    CPU_ZERO(&cpus);
    CPU_SET(0,&cpus);
    sched_setaffinity(0,sizeof(cpu_set_t),&cpus);

    


    if (argc == 2){
        main_param.sched_priority = sched_get_priority_max(SCHED_FIFO);
        sched_setscheduler(getpid(),SCHED_FIFO,&main_param);
        for (int i =0 ; i<2 ; i++){
            param[i].sched_priority = sched_get_priority_max(SCHED_FIFO)-i-1;
//            CPU_ZERO(&cpus);
//            CPU_SET(0,&cpus);
//            pthread_attr_setaffinity_np(&attr[i],sizeof(cpu_set_t),&cpus);
            pthread_attr_setinheritsched(&attr[i], PTHREAD_EXPLICIT_SCHED);
            pthread_attr_setschedpolicy(&attr[i],SCHED_FIFO);
            pthread_attr_setschedparam(&attr[i],&param[i]);
            assert(pthread_create(&threads[i],&attr[i],thread_func,(void *) i)==0);
            printf("Thread %d was created\n",i+1); 
        }
        
    }
    else {
        for (int i =0 ; i<2 ; i++){
//            CPU_ZERO(&cpus);
//            CPU_SET(0,&cpus);
//            pthread_attr_setaffinity_np(&attr[i],sizeof(cpu_set_t),&cpus);
            pthread_create(&threads[i],&attr[i],thread_func,(void *) i);
            printf("Thread %d was created\n",i+1); 
        }
    }
    for (int i =0 ; i<2 ;i++)
        pthread_join(threads[i],NULL);
}
