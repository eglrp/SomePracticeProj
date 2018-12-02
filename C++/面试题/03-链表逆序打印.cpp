/*
输入一个链表，按链表值从尾到头的顺序返回一个ArrayList。
 */

#include <vector>
#include <stack>
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

vector<int> printListFromTailToHead(struct ListNode *const head) {
    vector <int> result;
    stack<int> arr;
    struct ListNode *p = head;
    while(p != NULL) {
        arr.push(p->val);
        p = p->next;
    }
    int len = arr.size();
    for(int i = 0; i < len; i++) {
        result.push_back(arr.top());
        arr.pop();
    }
    return  result;
}

int main(int argc, char const *argv[]) {
    //Test
    struct ListNode *head = createList();
    cout << "原始列表:\n";
    printList(head);

    cout << "逆序打印列表:\n";
    vector<int> v(printListFromTailToHead(head));
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";

    deleteList(head);

    return 0;
}