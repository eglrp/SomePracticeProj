/*
输入两个单调递增的链表，输出两个链表合成后的链表，
当然我们需要合成后的链表满足单调不减规则。
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
        cout << head->val << "  ";
        head = head->next;
    }
    cout << endl;
}

ListNode *Merge(ListNode *pHead1, ListNode *pHead2) {
    if(pHead1 == NULL)
        return pHead2;

    else if(pHead2 == NULL)
        return pHead1;

    ListNode *newhead = NULL;

    if(pHead1->val < pHead2->val) {
        newhead = pHead1;
        newhead->next = Merge(pHead1->next, pHead2);
    } else {
        newhead = pHead2;
        newhead->next = Merge(pHead1, pHead2->next);
    }
    return newhead;
}

int main(int argc, char const *argv[]) {
    //Test
    struct ListNode *head1 = createList();
    printList(head1);

    struct ListNode *head2 = createList();
    printList(head2);

    struct ListNode *head_merge = Merge(head1, head2);
    printList(head_merge);

    deleteList(head1);
    deleteList(head2);
    deleteList(head_merge);

    return 0;
}