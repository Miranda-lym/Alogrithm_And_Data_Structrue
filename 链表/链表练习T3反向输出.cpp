#include "list.h"
#include <string.h>
//��������֮���������ʱ��O(n),�ռ�O(n)
void reversedPrint1(const ListNode* head, bool noHead=1)
{
    if(head==NULL)
        return;
    int length = getLength(head,noHead) ,i; //��ȡ������
    if(length==0) {
        puts("��ǰľ���κν���������~");
        return;
    }
    ElemType* nodes = (ElemType*)malloc(sizeof(ElemType)*length);
    const ListNode* p = noHead ? head : head->next;
    for(i=0; i<length; ++i, p=p->next) //�ѽ�㰴˳�����������
        nodes[i] = p->data;
    for(i=length-1; i>=0; --i) //�������з����������ֵ
        printf("%-3d ",nodes[i]);
    puts("");
    free(nodes);  //�ͷ�����Ŀռ�
}
//�õݹ麯����ʽ���������ʱ��O(n),�ռ�O(1)
void recursivePrint(const ListNode* pNode)
{
    if(pNode->next)
        recursivePrint(pNode->next);
    printf("%-3d ",pNode->data);
}
void reversedPrint2(const ListNode* head, bool noHead=1)
{
    if(head==NULL)
        return;
    int length = getLength(head,noHead) ,i;
    if(length==0) {
        puts("��ǰľ���κν���������~");
        return;
    }
    if(!noHead) //��ͷ�ڵ��������⴦��
        head = head->next;
    recursivePrint(head); //�ݹ����ÿ������ֵ
    puts("");
}
//�ȷ�ת�������������,ʱ��O(n),�ռ�O(1),���ƻ�ԭ�ṹ,���Ƽ�

//��һ������ҵ������Сֵ,�ڶ���ɾ����Сֵ�Ľ��
void delMinNode(ListNode* &head, bool noHead=1)
{
    if(head==NULL)
        return;
    int length = getLength(head,noHead);
    if(length==0) //û�н��ֱ�ӷ���
        return;
    else if(length==1) { //ֻ��һ�����
        ListNode* &firstNode = noHead ? head : head->next;
        free(firstNode); //�ͷ�������ռ�
        firstNode = NULL;//ͷ�ڵ�ָ�����ÿջ�ͷָ���ÿ�
        return;
    }
    ListNode *p = noHead ? head : head->next, *q;
    ElemType minData = p->data; //��ֹɾ����minNode֮����Ҫʹ��
    int minCount = 1; //���浱ǰ��С���ĸ���,�Լ���Сֵ�Ľ��
    for(p=p->next; p!=NULL; p=p->next) {
        if(p->data < minData) { //�ҵ���Сֵ�Ľ��
            minData = p->data;
            minCount = 1;  //���¼���
        } else if(p->data == minData)
            ++minCount;    //��С�������ۼ�
    }
    //ǰ����ж��Ѿ��ܱ�֤���ٰ����������!
    if(noHead) { //û��ͷ�ڵ�
        while(head->data==minData) { //��һ�������Ҫɾ��
            p = head;
            head = head->next;
            free(p);
            --minCount;
        }
    }
    p = head;
    while(minCount>0 && p!=NULL) { //���н���ֵΪ��Сֵ��p����Ҫɾ��
        if(p->next->data == minData) {
            q = p->next;
            p->next = p->next->next; //ָ����һ��������һ�����
            free(q);
            --minCount;
        }else
			p = p->next;
    }
}

void delAbsEqualNode(ListNode *head, int maxValue)
{
	if(head==NULL)
		return ;
	bool *saved = (bool*)malloc(sizeof(bool)*(maxValue+1));//new bool[maxValue+1](0)
	memset(saved,0,sizeof(bool)*(maxValue+1)); //ȫ����ʼ��Ϊ0
	while(head->next!=NULL) {
		if(saved[abs(head->next->data)]==0) {//����0��ʾǰ��û�д洢����ֵ
			saved[abs(head->next->data)] = 1;
			head = head->next;
		}else {  //�Ѵ洢����ֵ����Ҫɾ��������
			ListNode *nextNode = head->next->next;
			free(head->next);
			head->next = nextNode;
		}
	}
	free(saved); //delete[] saved;
}
int main()
{
    bool noHeadNode = 0;
    ListNode* head = NULL;
    createList_head(head,noHeadNode);
    showList(head,"����ṹ����:",noHeadNode);
    printf("������Ϊ: %d\n",getLength(head,noHeadNode));

	puts("�������Ϊ:");
    reversedPrint1(head,noHeadNode);
    reversedPrint2(head,noHeadNode);
    delMinNode(head,noHeadNode);
    showList(head,"ɾ����Сֵ������ṹ����:",noHeadNode);
    delAbsEqualNode(head,5);
    showList(head,"ɾ����ͬ����ֵ��������ṹ����:",noHeadNode);
    return 0;
}
