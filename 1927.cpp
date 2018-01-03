#include <stdio.h>
#define LEFT(x) 2*x+1
#define RIGHT(x) 2*x+2
#define PARENT(x) (x-1)/2
int heap[100003];
int heapidx = 0;
 
bool overflow(int i) {
    return i >= heapidx;
}
void delete_heap(void) {
    if (heapidx == 0)
        printf("0\n");
    else {
        printf("%d\n", heap[0]);
        heap[0] = heap[--heapidx];
        int current = 0;
        while (true) {
            if (overflow(LEFT(current)))
                break;
            int swapidx;
            if (overflow(RIGHT(current)))
                swapidx = LEFT(current);
            else
                swapidx = heap[LEFT(current)] < heap[RIGHT(current)] ? LEFT(current) : RIGHT(current);
            if (heap[current] > heap[swapidx]) {
                int tmp = heap[swapidx];
                heap[swapidx] = heap[current];
                heap[current] = tmp;
                current = swapidx;
            }
            else
                break;
        }
    }
}
void insert_heap(int val) {
    heap[heapidx++] = val;
    int current = heapidx-1;
    while (true) {
        if (heap[current] < heap[PARENT(current)]) {
            int tmp = heap[current];
            heap[current] = heap[PARENT(current)];
            heap[PARENT(current)] = tmp;            
            current = PARENT(current);
        }
        else
            break;
        if (current == 0)
            break;
    }
 
}
int main(void) {
    int N;
    scanf("%d", &N);
    while (N--) {
        int t;
        scanf("%d", &t);
        if (t == 0)
            delete_heap();
        else
            insert_heap(t);
    }
}
