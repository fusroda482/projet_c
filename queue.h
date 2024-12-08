/* ------ QUEUE.H ------ */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h> 

// Nombre maximal d'objets simultanément sur la Map
#define MAX_SIZE 100

typedef struct {
    
    int data[MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// --- PROTOTYPES DES FONCTIONS ---

void init_queue(Queue *q);
bool isEmpty(Queue *q);
bool isFull(Queue *q);
bool enqueue(Queue *q, int value);
bool dequeue(Queue *q, int *value);
void displayQueue(Queue *q);

#endif
