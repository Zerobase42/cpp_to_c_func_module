#include <string.h>
#define queue(name, size) int name[size], name##_front = 0, name##_rear = 0

#define pushQ(name, val) (name[name##_rear++] = (val))
#define popQ(name) (name[name##_front++])
#define frontQ(name) (name[name##_front])
#define emptyQ(name) (name##_front == name##_rear)
#define sizeQ(name) (name##_rear - name##_front)
#define delQ(name)