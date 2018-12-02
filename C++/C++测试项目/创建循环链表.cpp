#include <stdlib.h>

typedef struct dnode {
    int data;
    struct dnode *pre;
    struct dnode *next;
} DNode;

DNode *searchList(DNode *head, int find) {
    DNode *pClock = head->next;
    DNode *pAntiClock = head->pre;
    while (pAntiClock != pClock->pre) {
        if(pClock->data == find)
            return pClock;
        if(pAntiClock->data == find)
            return pAntiClock;
        if(pClock == pAntiClock) //交错而过 一定包含相等的逻辑在里面
            return NULL;
        pClock = pClock->next;
        pAntiClock = pAntiClock->pre;
    }
    return NULL;
}


int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}