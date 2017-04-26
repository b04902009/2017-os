#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

void *thread_func(void * num){
    int k = num;
    for (int i =0;i<3;i++){
        printf("Thread %d is running\n",k);
        sleep(1); 
    }
}

int main(int argc,char * argv[]){
	pthread_t threads[2];
    pthread_attr_t attr;
    cpu_set_t cpus;
    pthread_attr_init(&attr);
    CPU_ZERO(&cpus);
    CPU_SET(0,&cpus);
    
    if (argc == 2){
        printf("%s\n",argv[1]);
    
    }
    for (int i =0 ; i<2 ; i++){
        pthread_attr_setaffinity_np(&attr,sizeof(cpu_set_t),&cpus);
        printf ("??? %d\n",i);
        pthread_create(&threads[i],&attr,thread_func,(void *) i);
    }
    for (int i =0 ; i<2 ;i++)
        pthread_join(threads[i],NULL);
}
