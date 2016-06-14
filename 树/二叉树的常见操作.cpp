#include<stdio.h>
#include<iostream>
#include<stack>   //STL
#include<queue>   //STL
using namespace std;
//124##57##8##3#6##
class BiTree {
    typedef char ElemType;
    ElemType data;
    BiTree *left;
    BiTree *right;
public:
    BiTree()
    {
        left = right = NULL;
    }
    ~BiTree() {};

    static void createTree(BiTree* &node);
    static void destroyTree(BiTree* &node);
    //�ݹ�ı��������������
    void preOrderVisit(BiTree *T);
    void inOrderVisit(BiTree *T);
    void lastOrderVisit(BiTree *T);
    //�ǵݹ�ı��������������
    void levelOrderVisit();
    void noRecursivePreVisit();
    void noRecursiveInVisit();
    void noRecursiveLastVisit();

    //�����������
    static int getDepth(const BiTree *T)
    {
        return T == NULL ? 0 : 1 + max(getDepth(T->left), getDepth(T->right));
    }
    //�������Ĵ�Ȩ·������
    static int getWPL(const BiTree *head, int depth = 0)
    {
        if (head == NULL) {
            return 0;
        }
        if (head->left == NULL && head->right == NULL) {
            return depth * head->data;    //�����char����*(head->data-48)
        }
        return getWPL(head->left, depth + 1) + getWPL(head->right, depth + 1);
    }
    //�����ĵ�K��ڵ����
    static int getLevelNode(const BiTree *T, int k, int level = 1)
    {
        if (T == NULL) {
            return 0;
        }
        if (level == k) {
            return 1;
        }
        return getLevelNode(T->left, k, level + 1) + getLevelNode(T->right, k, level + 1);
    }
    //�����ĵ�K��Ҷ�ӽڵ����
    static int getLevelLeaf(const BiTree *T, int k, int level = 1)
    {
        if (T == NULL) {
            return 0;
        }
        if (level == k && NULL == T->left && NULL == T->right) {
            return 1;
        }
        if (level >= k) { //��������K��Ľ�㲻��Ҷ��㣬�Ͳ���Ҫ�����ĺ���
            return 0;
        }
        return getLevelLeaf(T->left, k, level + 1) + getLevelLeaf(T->right, k, level + 1);
    }
    //�Ҹ������ֵ�ĸ��ڵ�
    static ElemType findParent(const BiTree *T, ElemType x)
    {
        if (T == NULL || T->left == NULL && T->right == NULL) {
            return 0;    // �ҵ��ս���Ҷ�ڵ�
        }
        if (T->left && T->left->data == x || T->right && T->right->data == x) {
            return T->data;    // �����ǰ���������ĸ���ֱ�ӷ���
        }
        ElemType pa = findParent(T->left, x); // ��������
        return pa != 0 ? pa : findParent(T->right, x); //������û������������
    }
    //��ʾ���ڵ�
    static void showParent(const BiTree *T, ElemType x)
    {
        ElemType pa = findParent(T, x);
        if (pa == 0) {
            cout << "node " << x << " have no parent!" << endl;
        } else {
            cout << "the parent of " << x << " is " << pa << endl;
        }
    }
    //�ж϶������Ƿ�Ϊƽ�������
    static bool isBalanced(BiTree *T, int *pDepth = 0)
    {
        if (NULL == T) {
            if (0 != pDepth) {
                *pDepth = 0;
            }
            return 1;
        }
        int depthLeft = 0, depthRight = 0;
        if (isBalanced(T->left, &depthLeft) && isBalanced(T->right, &depthRight)) {
            int maxD = max(depthLeft, depthRight), minD = min(depthLeft, depthRight);
            if (0 != pDepth) {
                *pDepth = maxD + 1;
            }
            return maxD - minD < 2; //���Ҿ�ƽ�������֮��
        }
        return 0; //������������һ����ƽ����ƽ��
    }
    //���������ֵ����·��
    static void root2Node(BiTree *T, ElemType x)
    {
        stack<BiTree *>S;
        BiTree *p = T;
        BiTree *p_visited = NULL;
        while (!S.empty() || p != NULL) {
            while (p != NULL) {
                S.push(p);
                p = p->left;
            }
            p = S.top();
            if (p->right == NULL || p->right == p_visited) {
                if (p->data == x) {
                    while (!S.empty()) {
                        cout << S.top()->data << " ";
                        S.pop();
                    }
                    cout << endl;
                    return ;
                }
                p_visited = p;
                p = NULL;
                S.pop();
            } else {
                p = p->right;
            }
        }
    }
};

//������
void BiTree::createTree(BiTree* &node)
{
    ElemType temp;
    static unsigned cur_size = 0;
    if (cur_size == 0) {
        cout << "������ڵ������(#��ʾ��)��" << endl;
    }
    cin >> temp;
    if (temp == '#' || temp == -1) {
        node = NULL;
    } else {
        node = new BiTree;
        node->data = temp;
        cur_size++;
        createTree(node->left);
        createTree(node->right);
    }
}

void BiTree::destroyTree(BiTree* &node)
{
    if (node->left != NULL) {
        destroyTree(node->left);
    }
    if (node->right != NULL) {
        destroyTree(node->right);
    }
    delete node;
    node = NULL;
}
//���������
void BiTree::preOrderVisit(BiTree *T)
{
    if (T != NULL) {
        cout << T->data << "  ";
        preOrderVisit(T->left);
        preOrderVisit(T->right);
    }
}
//���������
void BiTree::inOrderVisit(BiTree *T)
{
    if (T != NULL) {
        inOrderVisit(T->left);
        cout << T->data << "  ";
        inOrderVisit(T->right);
    }
}
//���������
void BiTree::lastOrderVisit(BiTree *T)
{
    if (T != NULL) {
        lastOrderVisit(T->left);
        lastOrderVisit(T->right);
        cout << T->data << "  ";
    }
}
//��α��������ǵݹ�
void BiTree::levelOrderVisit()
{
    queue<BiTree *>Q;
    Q.push(this);
    BiTree *temp = NULL;
    while (!Q.empty()) {
        temp = Q.front();
        cout << temp->data << "  ";
        Q.pop();
        if (temp->left) {
            Q.push(temp->left);
        }
        if (temp->right) {
            Q.push(temp->right);
        }
    }
}
//�ǵݹ��������
void BiTree::noRecursivePreVisit()
{
    stack<BiTree *>S;  //�����������ڵ��ջ
    BiTree *p = this;
    while (!S.empty() || p != NULL) {
        if (p != NULL) { //p�ǿ�
            S.push(p);
            cout << p->data << "  ";
            p = p->left;
        } else {
            p = S.top();
            S.pop();
            p = p->right;
        }
    }
}
//�ǵݹ��������
void BiTree::noRecursiveInVisit()
{
    stack<BiTree *>S;  //�����������ڵ��ջ
    BiTree *p = this;
    while (!S.empty() || p != NULL) {
        if (p != NULL) { //p�ǿ�
            S.push(p);
            p = p->left;
        } else {
            p = S.top();
            S.pop();
            cout << p->data << "  ";
            p = p->right;
        }
    }
}
//�ǵݹ�������
void BiTree::noRecursiveLastVisit()
{
    stack<BiTree *>S;
    BiTree *p = this;
    BiTree *p_visited = NULL;
    while (!S.empty() || p != NULL) {
        while (p != NULL) {
            S.push(p);
            p = p->left;
        }
        p = S.top();
        if (p->right == NULL || p->right == p_visited) {
            cout << p->data << "  ";
            p_visited = p;
            p = NULL;
            S.pop();
        } else {
            p = p->right;
        }
    }
}
//  124##57##8##3#6##
int main()
{
    BiTree* mytree;
    BiTree::createTree(mytree);
    cout << "��������ǣ�" << BiTree::getDepth(mytree) << endl;
    cout << "�������" << endl;
    mytree->preOrderVisit(mytree);
    cout << endl;
    cout << "�������" << endl;
    mytree->inOrderVisit(mytree);
    cout << endl;
    cout << "�������" << endl;
    mytree->lastOrderVisit(mytree);
    cout << endl;
    cout << "��α���" << endl;
    mytree->levelOrderVisit();
    cout << endl << endl;
    cout << "�ǵݹ��������" << endl;
    mytree->noRecursivePreVisit();
    cout << endl;
    cout << "�ǵݹ��������" << endl;
    mytree->noRecursiveInVisit();
    cout << endl;
    cout << "�ǵݹ�������" << endl;
    mytree->noRecursiveLastVisit();

    cout << "���Ĵ�Ȩ·������Ϊ: " << BiTree::getWPL(mytree) << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "��" << i << "��ڵ���Ϊ: " << BiTree::getLevelNode(mytree, i)
             << endl;
        cout << "��" << i << "��Ҷ�ӽڵ���Ϊ: " << BiTree::getLevelLeaf(mytree, i)
             << endl;
    }
    BiTree::root2Node(mytree, '7');
    cout << (BiTree::isBalanced(mytree) ? "ƽ��" : "��ƽ��") << endl;
    for (char c = '1'; c < '9'; c++) {
        BiTree::showParent(mytree, c);
    }
    BiTree::destroyTree(mytree);
    cout << endl;
    return 0;
}
