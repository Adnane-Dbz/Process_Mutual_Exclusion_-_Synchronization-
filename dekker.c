#include <stdio.h>
#include <pthread.h>

int flag[2];         // Flags to indicate the interest of each thread
int turn;            // Variable to decide whose turn it is
const int MAX = 1e9;
int ans = 0;       

void initialize()
{
    flag[0] = flag[1] = 0; // Both threads are initially not interested
    turn = 0;              // Start with turn 0
}

void EnterCS(int self)
{
    flag[self] = 1; 
    while (flag[1 - self] == 1)
    { // While the other thread is interested
        if (turn == 1 - self)
        {                 
            flag[self] = 0;
            while (turn == 1 - self)
                ;        
            flag[self] = 1;
        }
    }
}

void ExitCS(int self)
{
    flag[self] = 0;  // Release the CS
    turn = 1 - self; // Give the turn to the other thread
    printf("Thread %d has exited the Critical Section\n", self);
    printf("\n");
}

void *func(void *s)
{
    int i = 0, j = 0;
    int self = *(int *)s; // Thread identifier (0 or 1) casting int 
    for (j = 0; j < 10; j++)
    {
        printf("Thread %d wants to enter the Critical Section\n", self);
        EnterCS(self);
        printf("Thread %d is now in the Critical Section ... \n", self);
        for (i = 0; i < MAX; i++)
            ans++; 
        ExitCS(self);
    }
}

int main()
{
    pthread_t thread0, thread1; // Declare two threads
    int thread0_num = 0, thread1_num = 1;
    initialize();
    pthread_create(&thread0, NULL, func, &thread0_num);
    pthread_create(&thread1, NULL, func, &thread1_num); 
    pthread_join(thread0, NULL);                        
    pthread_join(thread1, NULL);                        
    return 0;
}