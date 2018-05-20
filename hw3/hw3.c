#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>
pthread_mutex_t mutex[5]; 
pthread_cond_t cond_var[5]; 
enum {thinking, hungry, eating, sleeping} state[5]; 
void test(int philosopher_number){
    if ((state[(philosopher_number + 4) % 5] != eating) && (state[philosopher_number] == hungry) 
            && (state[(philosopher_number + 1) % 5] != eating)){ 
        state[philosopher_number] = eating; 
        pthread_cond_signal(&cond_var[philosopher_number]); 
    } 
    return ; 
} 
void pickup_forks(int philosopher_number){ 
    state[philosopher_number] = hungry; 
    test(philosopher_number); 
    pthread_mutex_lock(&mutex[philosopher_number]);

    if(state[philosopher_number] != eating){
        printf("Philosopher %d can’t pick up forks and start waiting.\n", philosopher_number); 
        pthread_cond_wait(&cond_var[philosopher_number], &mutex[philosopher_number]); 
    } 
    printf("Philosopher %d is now EATING.\n", philosopher_number); return; 
} 
void return_forks(int philosopher_number){ 
    printf("Philosopher %d returns forks and then starts TESTING %d and %d.\n", philosopher_number, 
    (philosopher_number+4) % 5, (philosopher_number+1) % 5); state[philosopher_number] = sleeping; pthread_mutex_unlock(&mutex[philosopher_number]); 
    test((philosopher_number+1) % 5); //right first 
    test((philosopher_number+4) % 5); //left 
    return; 
} 
void *philosophers(int philosopher_number){ 
    //thinking 
    srand(philosopher_number); 
    int x = rand() % 3 +1; 
    printf("Philosopher %d is now THINKING for %d seconds.\n", philosopher_number, x);
    sleep(x); 
    
    //become hungry 
    printf("Philosopher %d is now HUNGRY and trying to pick up forks.\n", philosopher_number); 
    pickup_forks(philosopher_number); //start eating 
    x = rand() % 3 +1; 
    sleep(x); 
    //end eating 
    return_forks(philosopher_number); 
    
    return 0;
} 
int main(void){ 
    int test; 
    int i; 
    pthread_t id[5]; 
    for(i = 0; i < 5; i++){ 
        pthread_mutex_init(&mutex[i],NULL); 
        pthread_cond_init(&cond_var[i],NULL); 
        state[i] = thinking; 
    } 
    pthread_create(&id[0],NULL,(void *) philosophers, (void *) 0); 
    pthread_create(&id[1],NULL,(void *) philosophers, (void *) 1); 
    pthread_create(&id[2],NULL,(void *) philosophers, (void *) 2); 
    pthread_create(&id[3],NULL,(void *) philosophers, (void *) 3); 
    pthread_create(&id[4],NULL,(void *) philosophers, (void *) 4); 
    
    pthread_join(id[0],NULL); 
    pthread_join(id[1],NULL); 
    pthread_join(id[2],NULL); 
    pthread_join(id[3],NULL); 
    pthread_join(id[4],NULL); 
    return 0; 
} 