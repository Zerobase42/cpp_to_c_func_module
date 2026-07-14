#include<stdlib.h>
typedef struct{
    int*buf;
    int front;
    int rear;
}queue;
static inline queue*initQ(int size){
    queue*q=(queue*)malloc(sizeof(queue));
    q->buf=(int*)malloc(sizeof(int)*size);
    q->front=0;
    q->rear=0;
    return q;
}
static inline void delQ(queue*q){
    free(q->buf);
    free(q);
}
static inline int emptyQ(const queue*q){
    return q->front==q->rear;
}
static inline void pushQ(queue*q,int x){
    q->buf[q->rear++]=x;
}
static inline int popQ(queue*q){
    return q->buf[q->front++];
}
static inline int frontQ(const queue*q){
    return q->buf[q->front];
}

/*
queue*q=initQ(2048); // 로 선언

*/