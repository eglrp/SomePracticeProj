/*
输入一个链表，输出该链表中倒数第k个结点。
 */

#include <iostream>
#include <stdlib.h>

using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

struct ListNode *createList() {
    struct ListNode *head = new ListNode(0);
    struct ListNode *ret = head;
    for(int i = 1; i < 10; i++) {
        struct ListNode *p = new ListNode(i);
        ret->next = p;
        ret = ret->next;
    }
    return head;
}

void deleteList(struct ListNode *list) {
    struct ListNode *p = list;
    while(p != NULL) {
        list = p->next;
        free(p);
        p = list;
    }
    free(p);
}

void printList(ListNode *head) {
    while(head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

ListNode *FindKthToTail(ListNode *p, unsigned int k) {
    //if(!p) return nullptr;
    ListNode *p1 = p;
    for(int i = 0; i != k; ++i)
        if(p1 == NULL)
            return NULL;
        else
            p1 = p1->next;

    while(p1) {
        p1 = p1->next;
        p = p->next;
    }
    return p;
}

int main(int argc, char const *argv[]) {
    // Test
    struct ListNode *head = createList();
    printList(head);

    struct ListNode *tail = FindKthToTail(head, 3);
    printList(tail);

    deleteList(head);
    deleteList(tail);

    return 0;
}