#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers

char *state[N]; // Array representing the state of each philosopher
sem_t mutex;    // Mutex to control access to shared resources
sem_t S[N];     // Semaphores for each philosopher (to wait for forks)

// Function to get left and right neighbors dynamically
int left(int i) { return (i + N - 1) % N; }
int right(int i) { return (i + 1) % N; }

// Function to check if a philosopher can eat
void test(int i)
{
    if (state[i] == "HUNGRY" && state[left(i)] != "EATING" && state[right(i)] != "EATING")
    {
        state[i] = "EATING";
        printf("Philosopher %d took LEFT fork.\n", i);
        printf("Philosopher %d took RIGHT fork.\n", i);
        sem_post(&S[i]); // Allow philosopher to eat
    }
}

// Function for taking forks
void take_forks(int i)
{
    sem_wait(&mutex); // Lock access to shared resources
    state[i] = "HUNGRY";
    printf("Philosopher %d is HUNGRY and trying to take forks...\n", i);
    test(i);          // Check if the philosopher can eat
    sem_post(&mutex); // Unlock access
    sem_wait(&S[i]);  // Wait if not allowed to eat
}

// Function for putting down forks
void put_forks(int i)
{
    sem_wait(&mutex); // Lock access to shared resources
    state[i] = "THINKING";
    printf("Philosopher %d released LEFT fork.\n", i);
    printf("Philosopher %d released RIGHT fork.\n", i);
    printf("Philosopher %d finished EATING and starts THINKING again.\n", i);
    test(left(i));    // Check if left neighbor can eat
    test(right(i));   // Check if right neighbor can eat
    sem_post(&mutex); // Unlock access
}

// Function for philosopher's life cycle
void *philosopher(void *num)
{
    int i = *(int *)num;
    for (int j = 0; j < 10; j++)
    {
        printf("Philosopher %d is THINKING...\n", i);
        sleep(1); // Thinking time

        take_forks(i);
        printf("Philosopher %d is EATING...\n", i);
        sleep(1); // Eating time

        put_forks(i);
    }
    return NULL;
}

int main()
{
    pthread_t phil[N];

    sem_init(&mutex, 0, 1); // Initialize the mutex
    for (int i = 0; i < N; i++)
    {
        sem_init(&S[i], 0, 0); // Initialize semaphores for each philosopher
        state[i] = "THINKING";
    }

    for (int i = 0; i < N; i++)
        pthread_create(&phil[i], NULL, philosopher, &i);

    for (int i = 0; i < N; i++)
        pthread_join(phil[i], NULL);

    return 0;
}
