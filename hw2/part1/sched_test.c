#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>

void *thread_func(void * num){
    int k = num;
    k++;
    printf("thread %d\n",k);
}

int main(int argc,char * argv[]){
	pthread_t threads[2];
    pthread_attr_t attr;
    cpu_set_t cpus;
    pthread_attr_init(&attr);
    CPU_ZERO(&cpus);
    CPU_SET(0,&cpus);

    for (int i =0 ; i<2 ; i++){
        pthread_attr_setaffinity_np(&attr,sizeof(cpu_set_t),&cpus);
        pthread_create(&threads[i],&attr,thread_func,(void *) i);
    }
}
