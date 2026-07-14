#include <stdlib.h>
typedef struct {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
} queue;
queue* initQ(int capacity) {
    queue* q = malloc(sizeof(queue));
    q->data = malloc(sizeof(int) * capacity);
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = capacity;
    return q;
}
static inline int emptyQ(queue* q) {
    return q->size == 0;
}
static inline void delQ(queue* q) {
    free(q->data);
    free(q);
}
static inline void resize(queue* q) {
    int newCapacity = q->capacity * 2;
    int* newData = malloc(sizeof(int) * newCapacity);
    for (int i = 0; i < q->size; i++) {
        newData[i] = q->data[(q->front + i) % q->capacity];
    }
    free(q->data);
    q->data = newData;
    q->capacity = newCapacity;
    q->front = 0;
    q->rear = q->size;
}
static inline void pushQ(queue* q, int value) {
    if (q->size == q->capacity) resize(q);
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}
static inline int popQ(queue* q) {
    if (q->size == 0) {
        printf("Queue is empty\n");
        exit(1);
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return value;
}
static inline int frontQ(queue* q) {
    return q->data[q->front];
}
static inline int sizeQ(queue* q) {
    return q->size;
}
