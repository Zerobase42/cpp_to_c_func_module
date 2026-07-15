#include <stdio.h>
#include <unistd.h>
typedef struct {
    unsigned long long data[3];
} stCube;
#define byte unsigned char
const byte __ord[54]={0,1,2,3,4,5,6,7,8,36,37,38,9,10,11,18,19,20,27,28,29,39,40,41,12,13,14,21,22,23,30,31,32,42,43,44,15,16,17,24,25,26,33,34,35,45,46,47,48,49,50,51,52,53};
static inline byte cubeGet(const stCube* cube, int idx) {
    int bit = idx * 3;
    int pos = bit >> 6;
    int off = bit & 63;
    if (off <= 61) {
        return (cube->data[pos] >> off) & 7;
    }
    return ((cube->data[pos] >> off) |
            (cube->data[pos + 1] << (64 - off))) &
           7;
}
static inline void cubeSet(stCube* cube, int idx, byte val) {
    int bit = idx * 3;
    int pos = bit >> 6;
    int off = bit & 63;
    if (off <= 61) {
        cube->data[pos] &= ~(7ULL << off);
        cube->data[pos] |= ((unsigned long long)val << off);
    } else {
        int high = off - 61;
        cube->data[pos] &= ~(7ULL << off);
        cube->data[pos] |= ((unsigned long long)val << off);
        cube->data[pos + 1] &= ~((1ULL << high) - 1);
        cube->data[pos + 1] |= val >> (3 - high);
    }
}
static inline void cubeSwap(stCube* cube, int a, int b) {
    byte t = cubeGet(cube, a);
    cubeSet(cube, a, cubeGet(cube, b));
    cubeSet(cube, b, t);
}
static inline void __cw_turn(stCube* cube, const byte* pos) {
    for (char i = 0; i < 20; i += 4) {
        byte t = cubeGet(cube, pos[i]);
        cubeSet(cube, pos[i], cubeGet(cube, pos[i + 3]));
        cubeSet(cube, pos[i + 3], cubeGet(cube, pos[i + 2]));
        cubeSet(cube, pos[i + 2], cubeGet(cube, pos[i + 1]));
        cubeSet(cube, pos[i + 1], t);
    }
}
static inline void __ccw_turn(stCube* cube, const byte* pos) {
    for (char i = 0; i < 20; i += 4) {
        byte t = cubeGet(cube, pos[i]);
        cubeSet(cube, pos[i], cubeGet(cube, pos[i + 1]));
        cubeSet(cube, pos[i + 1], cubeGet(cube, pos[i + 2]));
        cubeSet(cube, pos[i + 2], cubeGet(cube, pos[i + 3]));
        cubeSet(cube, pos[i + 3], t);
    }
}
static inline void __half_turn(stCube* cube, const byte* pos) {
    for (char i = 0; i < 20; i += 4) {
        cubeSwap(cube, pos[i], pos[i + 2]);
        cubeSwap(cube, pos[i + 1], pos[i + 3]);
    }
}
static inline void turnCube(stCube* cube, byte x) {
    byte q = x / 3, r = x % 3;
    const byte* il;
    static const byte u0[20] = { 0, 2, 8, 6, 3, 1, 5, 7, 9, 36, 27, 18, 10, 37, 28, 19, 11, 38, 29, 20 };
    static const byte u1[20] = { 9, 11, 17, 15, 12, 10, 14, 16, 6, 18, 47, 44, 7, 21, 46, 41, 8, 24, 45, 38 };
    static const byte u2[20] = { 18, 20, 26, 24, 21, 19, 23, 25, 2, 33, 47, 11, 5, 30, 50, 14, 8, 27, 53, 17 };
    static const byte u3[20] = { 27, 29, 35, 33, 30, 28, 32, 34, 0, 42, 53, 20, 1, 39, 52, 23, 2, 36, 51, 26 };
    static const byte u4[20] = { 36, 38, 44, 42, 39, 37, 41, 43, 0, 9, 45, 35, 3, 12, 48, 32, 6, 15, 51, 29 };
    static const byte u5[20] = { 45, 47, 53, 51, 48, 46, 50, 52, 42, 15, 24, 33, 43, 16, 25, 34, 44, 17, 26, 35 };
    switch (q) {
        case 0:
            il = u0;
            break;
        case 1:
            il = u1;
            break;
        case 2:
            il = u2;
            break;
        case 3:
            il = u3;
            break;
        case 4:
            il = u4;
            break;
        case 5:
            il = u5;
            break;
    }
    switch (r) {
        case 0:
            __cw_turn(cube, il);
            break;
        case 1:
            __half_turn(cube, il);
            break;
        case 2:
            __ccw_turn(cube, il);
            break;
    }
}
static inline void readCube(stCube* cube) {
    static char rbuf[144];
#ifdef __linux__
    read(0, rbuf, 144);
#else
    fread(rbuf, 1, 144, stdin);
#endif
    int j = 0;
    memset(cube, 0, sizeof(stCube));
    for (int i = 0; i < 144 && j < 54; i++) {
        if ((unsigned char)rbuf[i] <= ' ')
            continue;
        cubeSet(cube, __ord[j++], rbuf[i]);
    }
}
static inline void printCube(const stCube* cube) {
    static char wbuf[144];
    memset(wbuf, ' ', sizeof(wbuf));
    char i = 0, p = 6;
    for (char a = 0; a < 54; a++) {
        wbuf[p++] = cubeGet(cube, __ord[a]) + '0';
        ++i;
        p++;
        if (i == 3 || i == 6 || i == 45 || i == 48 || i == 51) {
            wbuf[p++] = '\n';
            p += 6;
        }
        if (i == 9 || i == 21 || i == 33) {
            wbuf[p++] = '\n';
        }
    }
#ifdef __linux__
    write(1, wbuf, 144);
#else
    fwrite(wbuf, 1, 144, stdout);
#endif
}