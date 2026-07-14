#include<stdlib.h>
typedef struct{
    int*data;
    int front;
    int rear;
}Queue;
Queue*newQueue(int size){
    Queue*q=(Queue*)malloc(sizeof(Queue));
    q->data=(int*)malloc(sizeof(int)*size);
    q->front=q->rear=0;
    return q;
}
static inline void pushQ(Queue*q,int x){
    q->data[q->rear++]=x;
}
static inline int popQ(Queue*q){
    return q->data[q->front++];
}
static inline int frontQ(Queue*q){
    return q->data[q->front];
}
static inline int emptyQ(Queue*q){
    return q->front==q->rear;
}
static inline int sizeQ(Queue*q){
    return q->rear-q->front;
}
void delQ(Queue*q){
    free(q->data);
    free(q);
}