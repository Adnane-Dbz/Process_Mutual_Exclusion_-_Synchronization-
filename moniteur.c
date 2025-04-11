#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    sem_t mutex;  
} Monitor;

typedef struct {
    sem_t sem;    
    int count;    
} Condition;

Monitor moniteur;
Condition cond_prod, cond_cons;
int buffer = 0;
int est_plein = 0; 


void monitor_init(Monitor *m) {
    sem_init(&m->mutex, 0, 1);
}

void monitor_enter(Monitor *m) {
    sem_wait(&m->mutex);
}

void monitor_leave(Monitor *m) {
    sem_post(&m->mutex);
}

void condition_init(Condition *c) {
    sem_init(&c->sem, 0, 0);
    c->count = 0;
}

void condition_destroy(Condition *c) {
    sem_destroy(&c->sem);
}

void monitor_wait(Monitor *m, Condition *c) {
    c->count++;
    monitor_leave(m);     
    sem_wait(&c->sem);    
    monitor_enter(m);     
    c->count--;
}

void monitor_signal(Condition *c) {
    if (c->count > 0) {
        sem_post(&c->sem);  
    }
}

void *producteur(void *arg) {
    for (int i = 1; i <= 5; i++) {
        monitor_enter(&moniteur);

        while (est_plein) {             
            monitor_wait(&moniteur, &cond_prod);
        }

        buffer = i;                      // produire
        printf("Producteur a produit : %d\n", buffer);
        est_plein = 1;

        monitor_signal(&cond_cons);       // réveiller consommateur

        monitor_leave(&moniteur);
    }
    return NULL;
}

void *consommateur(void *arg) {
    for (int i = 1; i <= 5; i++) {
        monitor_enter(&moniteur);

        while (!est_plein) {             // buffer vide => attendre
            monitor_wait(&moniteur, &cond_cons);
        }

        printf("Consommateur a consommé : %d\n", buffer);
        est_plein = 0;

        monitor_signal(&cond_prod);      // réveiller producteur

        monitor_leave(&moniteur);
    }
    return NULL;
}


