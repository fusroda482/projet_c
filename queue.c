/* ----- QUEUE.C ----- */

#include "queue.h"
#include <stdio.h>

// Initialisation de la file
void initQueue(Queue *q) {

    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Vérifie si la file est vide
bool isEmpty(Queue *q) {

    return q->size == 0;
}

// Vérifie si la file est pleine
bool isFull(Queue *q) {

    return q->size == MAX_SIZE;
}

// Ajoute un élément à la file
bool enqueue(Queue *q, int value) {

    if (isFull(q)) return false;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = value;
    q->size++;
    return true;
}

// Retire un élément de la file
bool dequeue(Queue *q, int *value) {

    if (isEmpty(q)) return false;
    *value = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return true;
}

// Affiche les éléments de la file
void displayQueue(Queue *q) {

    if (isEmpty(q)) {
        printf("La file est vide.\n");
        return;
    }
    printf("Éléments de la file : ");
    int count = q->size;
    int index = q->front;
    while (count > 0) {
        printf("%d ", q->data[index]);
        index = (index + 1) % MAX_SIZE;
        count--;
    }
    printf("\n");
}

void updateQueue(Queue *q){
    
    if (isEmpty(q)){

        printf("La file est vide.\n");
        return;

        <stdio.h>
    }
    int count = q->size;
    int index = q->front;
    while (count > 0){
        index = (index + 1) % MAX_SIZE;
    }

}

