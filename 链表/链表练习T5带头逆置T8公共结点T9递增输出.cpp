#include "list.h"
#include "string.h"
#include<iostream>
#include<stack>
using namespace std;
//P37-T5:����ͷ���ĵ�����ԭ������.ʱ��O(n),�ռ�O(1)
ListNode* reverseList(ListNode* &head)
{
    ListNode *prev_node=NULL, *cur_node=head->next, *next_node=NULL;
    while(cur_node!=NULL) {
        next_node = cur_node->next;	//������һ���
        cur_node->next = prev_node;	//�޸���һ���
        prev_node = cur_node;		//���浱ǰ���
        cur_node = next_node;		//�޸ĵ�ǰ���
    }
    head->next = prev_node;
    return head;
}
//ʹ��ͷ�巨��˼��,�Ժ���ÿ�����,�嵽��һ�����ǰ��:O(n),O(1)
ListNode* reverseList2(ListNode* &head)
{
    ListNode *p = head->next, *q=NULL;
    head->next = NULL;
    while(p!=NULL) {
        q = p->next; //������һ���
        p->next = head->next; //��*p�嵽ͷ�ڵ�����һ�����ǰ
        head->next = p;
        p = q;
    }
}
//T8:�ҵ���������Ĺ������.�ÿ�ָ�����߼����ٱȽ�һ��:ʱ��O(n),�ռ�O(1)
ListNode* findCommonNode(ListNode *list1, ListNode *list2)
{
    unsigned len1 = getLength(list1), len2 = getLength(list2),i;
    ListNode *p = list1, *q = list2;
    for(; len1<len2; ++len1)
        q = q->next;
    for(; len2<len1; ++len2)
        p = p->next;
    while(p!=NULL && p!=q) {
        p = p->next;
        q = q->next;
    }
    return p;
}
//T8:�ҵ���������Ĺ������.����1ÿ�����������2�Ľ��Ƚ�:ʱ��O(n^2),�ռ�O(1)
ListNode* findCommonNode2(ListNode *list1, ListNode *list2)
{
    for (ListNode *p=list1; p!=NULL; p=p->next) //���α�������1
        for (ListNode *q=list2; q!=NULL; q=q->next) //���α�������2
            if ( p==q ) //�����������ַ��ͬ���ҵ�������㣬����
                return p;
    return NULL;
}
//T9:���������ͷ���������и���������.
//ÿ���ҵ���������С��Ԫ�����:ʱ��O(n^2),�ռ�O(1)
void increasedPrint(ListNode *head)
{
    if(head==NULL || head->next==NULL)
        return;
    ElemType minData, lastMin=-99999999;
    int minCount, i;  //������ǰ��Сֵ���ĸ���
    while(1) {
        ListNode *p = head->next;
        while(p!=NULL && p->data <= lastMin) //�ҵ���һ����ǰ��ѡ����Сֵ
            p = p->next;
        if(p==NULL) //û�ҵ�˵�����Ѿ������,���˳�ѭ��
            break;
        minData = p->data; //���Ұѵ�ǰ���ֵ��Ϊ��Сֵ
        minCount = 1;
        for(p=p->next; p!=NULL; p=p->next) { //��ÿ�������м��
            if(p->data > lastMin && p->data < minData) { //�и�С�Ľ��ֵ
                minData = p->data;
                minCount = 1;
            } else if(p->data==minData)
                ++minCount;
        }
        lastMin = minData;
        for(i=0; i<minCount; ++i)
            printf("%d ",minData);
    }
    puts("");
}
//T12:�ڵ�����������ɾ����ֵ��ͬ��Ԫ��
//��������������ֵ��ͬ��ɾ�������Ǹ����:ʱ��O(n),�ռ�O(1)
void delEqualNode(ListNode *head, bool noHead=1)
{
    if(head==NULL || head->next==NULL) //��ֹ��Ч����
        return;
    ListNode *p = noHead ? head : head->next, *q = NULL;
    while(p->next != NULL) {
        q = p->next; //ָ��ǰ������һ�����
        if(p->data == q->data) { //���ֵ���,��ɾ�����*(p->next)
            p->next = q->next;
            free(q);
        } else  //�����ʱ�������һ�����
            p = q;
    }
}
//T17.�жϴ�ͷ����ѭ��(Circle)˫(Double)�����Ƿ�Գ�,�� 1->2->3->2->1
//��Ϊ��ѭ��˫����,����ֻ��Ҫ������ָ��ͬʱ�ƶ��ͱȽ�:ʱ��O(n),�ռ�O(1)
bool isSymmetry_CS(ListNode *head)
{
    if(getLength(head,0)<2) //�����������
        return true;
    ListNode *p = head->next, *q = head->prior;
    for(; p->data == q->data; p=p->next, q=q->prior)
        if(p->next==q || p==q)
            return true;
    return false;
}
//��չ:�жϵ������Ƿ�Գ�
//�������ǰ[len/2]Ԫ��ѹ��ջ,Ȼ��һ�߳�ջһ�߱ȽϺ����Ԫ��:ʱ��O(n),�ռ�O(n)
bool isSymmetry(ListNode* head,bool noHead=1)
{
    unsigned len = getLength(head,noHead), i;
    if(len<2) //�����������
        return true;
    stack<ElemType> sta;
    ListNode *p = noHead ? head : head->next;
    for(i=0; i<len/2; ++i, p=p->next)  //ǰһ��Ԫ����ջ
        sta.push(p->data);
    if(len%2==1)   //������Ϊ����ʱ�����м��Ǹ����
        p = p->next;
    for(; p!=NULL; p=p->next) {
        if(p->data != sta.top())  //��ջ�Ƚ�
            return false;
        sta.pop();
    }
    return true;
}
//2009����-�Ҵ�ͷ���ĵ������е�����K�����
//��˫ָ��,һ������K��,��ͬʱ��,ֱ������ȵ���β:ʱ��O(n),�ռ�O(1)
ListNode* getLastKthNode(ListNode *head, int k)
{
    if(head==NULL || k<=0)
        return NULL;
    ListNode *p1 = head, *p2 = head;
    for(int i=0; i<k && p2!=NULL; ++i)
        p2 = p2->next;
    if(p2==NULL)	//����������K
        return NULL;
    while(p2!=NULL) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}
//��չ:�Դ�ͷ�ڵ�ĵ������������
//ʹ�ò��������˼��,��ÿ���������,�ҵ����ĺ���λ��:O(n^2),O(1)
void sortList(ListNode *head)
{
    if(head==NULL || head->next==NULL)
        return ;
    ListNode *p = head->next->next; //�ӵڶ�����㿪ʼ����ȷ��λ��
    head->next->next = NULL;  //�ȼٶ�ֻ��һ��������ź����
    while(p!=NULL) {
        ListNode *q = p->next, *r; //������һ���
        for(r=head; r->next!=NULL && r->next->data < p->data; r=r->next)
            ;
        p->next = r->next; //��*p�嵽*r����
        r->next = p;
        p = q;
    }
}
//��չ2:�Բ���ͷ�ڵ�ĵ������������
void sortList_noHead(ListNode *&head) //������Ҫ�����û��߶���ָ��
{
    if(head==NULL || head->next==NULL)
        return ;
    ListNode *p = head->next;  //�ӵڶ�����㿪ʼ����ȷ��λ��
    head->next = NULL;  //�ȼٶ�ֻ��һ��������ź����
    while(p!=NULL) {
        ListNode *q = p->next, *r; //������һ���
        if(head->data > p->data) { //������Ž��ֵ�ȵ�һ�����ֵС��嵽ǰ��
            p->next = head;
            head = p;
        } else {
            for(r=head; r->next!=NULL && r->next->data < p->data; r=r->next)
                ;
            p->next = r->next; //��*p�嵽*r����
            r->next = p;
        }
        p = q;
    }
}
//����������ͷ�ڵ�ĵ���������ƶ�(jaccard����)
double getListSimilarity(ListNode *listA, ListNode *listB, int n)
{
    int *saved = new int[2*n+1];
    int commonNum = 0, totalNum = 0;
    memset(saved,0,sizeof(int)*(2*n+1));
    for(; listA!=NULL; listA=listA->next)
        saved[n + listA->data] = 1;
    for(; listB!=NULL; listB=listB->next)
        if(saved[n + listB->data] == 0) //A��δ������Ԫ��
            saved[n + listB->data] = 1;
        else if(saved[n + listB->data] == 1) {//A�а�����Ԫ��
            ++saved[n + listB->data];
            ++commonNum;  //����Ԫ��(������Ԫ��)������һ
        }
    for(int i=2*n; i>=0; --i)  //ͳ�Ʋ�����Ԫ�ظ���
        if(saved[i]!=0)
            ++totalNum;
    delete[] saved;
    return (double)commonNum / totalNum;
}
//��һ������ͷ��������ԭ�طָ�������֣�һ����С�ڵ���0����һ���ִ���0
void cutListByZero(ListNode *head, ListNode *&part1, ListNode *&part2)
{
    if(head==NULL)
        return ;
    ListNode *p = head, *part1End, *part2End; //�������ֵ�β���ָ��
    if(p->data <=0) {  //��һ��������ڵ�һ����
        part1 = part1End = p;  //�ֱ��ҵ���һ���ֺ͵ڶ����ֵĵ�һ�����
        while(p!=NULL && p->data <=0) {
            part1End = p;
            p = p->next;
        }
        part2 = part2End = p;
    } else {  //��һ��������ڵڶ�����
        part2 = part2End = p;  //�ֱ��ҵ���һ���ֺ͵ڶ����ֵĵ�һ�����
        while(p!=NULL && p->data > 0) {
            part2End = p;
            p = p->next;
        }
        part1 = part1End = p;
    }
    if(p!=NULL)
        p = p->next;
    for(; p!=NULL; p=p->next) { //�ֱ𿴺���ÿ�����������һ����
        if(p->data <=0) {
            part1End->next = p; //������һ����
            part1End = part1End->next;
        } else {
            part2End->next = p; //�����ڶ�����
            part2End = part2End->next;
        }
    }
    if(part1End!=NULL)
        part1End->next = NULL;
    if(part2End!=NULL)
        part2End->next = NULL;
}
int main()
{
    bool noHeadNode = 1;
    ListNode* head = NULL , *head2;
    createList_head(head,noHeadNode);
    //createList_head(head2,noHeadNode);
    //cout<<getListSimilarity(head,head2,6)<<endl;
    ListNode * p1, *p2;
    cutListByZero(head,p1,p2);
    showList(p1,"��һ����");
    showList(p2,"�ڶ�����");
    /*
    showList(head,"����ṹ����:",noHeadNode);
    printf("������Ϊ: %d\n",getLength(head,noHeadNode));
    cout<<(isSymmetry(head,noHeadNode) ? "����Գ�\n" : "�����Գ�\n")<<endl;
    reverseList2(head);
    showList(head,"��ת������ṹ����:",noHeadNode);
    cout<<"�����ڶ������Ϊ: "<<getLastKthNode(head,2)->data<<endl;
    sortList(head);
    showList(head,"���������ṹ����:",noHeadNode);
    delEqualNode(head,noHeadNode);
    showList(head,"ɾ����ֵͬ��������ṹ����:",noHeadNode);
    */
    return 0;
}
/*
//1. ջ��STLʵ��,����˴��洢intֵ
class stack {
public:
    void push(int e);	//e��ջ
    int top();			//����ջ��Ԫ��
    void pop();  		//��ջ
    unsigned size();
    bool empty();
};
//�÷�
int main()
{
    stack<int> s;	//����һ�����Ա���intֵ��ջ
    s.push(111);	//111��ջ
    s.push(222);	//222��ջ
    int elem = s.top();	//����ջ��Ԫ��
    cout<<elem<<endl;	//���ջ��Ԫ��ֵ:222
    s.pop();			//222��ջ
    elem = s.top();		//����ջ��Ԫ��
    cout<<elem<<endl;	//���ջ��Ԫ��ֵ:111
    s.pop();
}
//2. �����Լ������ջ�ṹ����:
typedef int ElemType;
typedef struct {
    ElemType data[50];
    int top;
} SqStack;
//�����Ǽ������ò���
void InitStack(SqStack &S);
bool Push(SqStack &S, ElemType x);  //x��ջ
bool Pop(SqStack &S, ElemType &x);  //��ջ��ջ�����浽x
bool GetTop(SqStack S, ElemType &x);//ȡ��ջ��Ԫ��,�浽x
//�÷�
int main()
{
	SqStack sta;
	InitStack(sta);
	Push(sta,111);	//111��ջ
	int x;
	GetTop(sta, x);	//���ջ��Ԫ�ص�ֵ,��û�г�ջ
	cout<<x<<endl;	//���111
	Push(sta,222);	//222��ջ
	Pop(sta,x);		//��ջ��������ջ��Ԫ��ֵ��x
	cout<<x<<endl;	//���222
}
//3. �Լ�ͨ������ģ��ջ
int main()
{
    ElemType MyStack[50];//����һ����������50��Ԫ�ص�ջ
    int topIndex = -1;   //��ʼ��ջ������λ��
    MyStack[++topIndex] = 111; //111��ջ
    int temp = MyStack[topIndex--]; //��ջ������temp����ջ��ֵ
    cout<<temp<<endl;
}
*/
