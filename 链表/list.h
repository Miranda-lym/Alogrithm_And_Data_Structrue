#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct ListNode {
    ElemType data;
    ListNode *next; //ָ����һ�����
    ListNode *prior; //Ԥ������ָ��,���ڴ���ѭ������,��������δʹ��
} ListNode;

//�ж������Ƿ�Ϊ��
bool isEmpty(const ListNode* head, bool noHead = 1)
{
    return noHead ? NULL == head : NULL == head->next;
}
//�õ����������--����ȡ����
unsigned getLength(const ListNode* head, bool noHead = 1)
{
    unsigned length = 0;
    const ListNode* p = noHead ? head : head->next;
    while (p != NULL) {
        p = p->next;
        ++length;
    }
    return length;
}
//��������ע���������Ϊ����ָ�����һ��ָ�������
int createList_head_n(ListNode* &head, unsigned n, bool noHead = 1)
{
    head = noHead ? NULL : (ListNode*)malloc(sizeof(ListNode));
    if (!noHead) {
        head->next = NULL;
    }
    ListNode *p = NULL;
    ElemType temp;
    if (n <= 0) {
        return -1;
    }
    for (int i = n; i >= 1; i--) {
        p = (ListNode*)malloc(sizeof(ListNode));
        if (p == NULL) {
            return -2;
        }
        printf("please input no.%d data \'s value: ", i);
        scanf("%d", &temp);
        fflush(stdin);//������������������
        p->data = temp;
        if (noHead) {
            p->next = head;
            head = p;
        } else {
            p->next = head->next;
            head->next = p;
        }
    }
    return 0;
}
//�����������ض�ֵ(9999)����,�����ǹ̶�����
int createList_head(ListNode* &head, bool noHead = 1)
{
    puts("���������ɽ��ֵ,��9999��ʾ����������:");
    head = noHead ? NULL : (ListNode*)malloc(sizeof(ListNode));
    if (!noHead) {
        head->next = NULL;
    }
    ListNode *p = NULL;
    ElemType temp;
    fflush(stdin);
    scanf("%d", &temp);
    while (temp != 9999) {
        p = (ListNode*)malloc(sizeof(ListNode));
        if (p == NULL) {
            return -2;
        }
        p->data = temp;
        if (noHead) {
            p->next = head;
            head = p;
        } else {
            p->next = head->next;
            head->next = p;
        }
        scanf("%d", &temp);
    }
    return 0;
}
//��ʾ����ṹ
void showList(const ListNode* head, const char* note = "", bool noHead = 1)
{
    if (note && note[0]) {
        puts(note);
    }
    if (isEmpty(head, noHead)) {
        puts("List is empty !");
        return;
    }
    const ListNode* p = noHead ? head : head->next;
    while (p) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    puts("\b\b\b\b\t");
}
#endif //_LIST_H_
