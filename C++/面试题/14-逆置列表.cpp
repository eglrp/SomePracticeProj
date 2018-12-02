/*
输入一个链表，反转链表后，输出新链表的表头。
 */

#include <iostream>
#include <stack>
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

ListNode *ReverseList1(ListNode *pHead) {
    if(pHead == NULL || pHead -> next == NULL)
        return pHead;

    ListNode *p = pHead;
    stack<ListNode * > s;
    while(p -> next) {
        s.push(p);
        p = p -> next;
    }

    ListNode *head = p;
    while(!s.empty()) {
        p -> next = s.top();
        p = p -> next;
        s.pop();
    }
    p -> next = NULL;
    return head;
}

ListNode *ReverseList2(ListNode *pHead) {
    if(pHead == NULL || pHead -> next == NULL)
        return pHead;

    ListNode *p = pHead;
    ListNode *q = pHead -> next;
    ListNode *r = NULL;

    pHead -> next = NULL;
    while(q) {
        r = q -> next;
        q -> next = p;
        p = q;
        q = r;
    }
    return p;
}

ListNode *ReverseList3(ListNode *pHead) {

    if(pHead == NULL || pHead -> next == NULL)
        return pHead;

    ListNode *p = pHead -> next;
    ListNode *q = NULL;
    while(p -> next) {
        q = p -> next;
        p -> next = q -> next;
        q -> next = pHead -> next;
        pHead -> next = q;
    }
    p -> next = pHead;
    pHead = p -> next -> next;
    p -> next -> next = NULL;
    return pHead;
}

int main(int argc, char const *argv[]) {
    //Test
    struct ListNode *head = createList();
    printList(head);

    struct ListNode *reverse1 = ReverseList1(head);
    printList(reverse1);

    deleteList(head);
    deleteList(reverse1);

    return 0;
}