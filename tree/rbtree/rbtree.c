/*************************************************************************
	> File Name: rbtree.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月18日 星期一 16时41分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define red 1
#define black 0
#define false 0
#define true 1

typedef int bool;
typedef int color;

typedef struct Node {
    int k;
    color c;
    struct Node *p;
    struct Node *left;
    struct Node *right;
}rbNode;

rbNode *creatRedNode(rbNode *T,int k)
{
    rbNode *n=(rbNode*)malloc(sizeof(rbNode));
    n->p=n->left=n->right=T;
    n->c=red;
    n->k=k;
    return n;
}

rbNode *min(rbNode *t,rbNode *T)
{
    while(t->left!=T)
        t=t->left;
    return t;
}

rbNode *max(rbNode *t,rbNode *T)
{
    while(t->right!=T)
        t=t->right;
    return t;
}

void transplant(rbNode *T,rbNode *u,rbNode *v)
{
    if(u->p==T)
        T->left=T->right=v;
    else if(u==u->p->left)
        u->p->left=v;
    else
        u->p->right=v;
    v->p=u->p;
}

bool left_rotate(rbNode *T,rbNode *x)
{
    if(x->right==T)
        return false;
    rbNode *temp=x->right;
    x->right=temp->left;
    x->right->p=x;
    transplant(T,x,temp);
    temp->left=x;
    x->p=temp;
    return true;
}

bool right_rotate(rbNode *T,rbNode *x)
{
    if(x->left==T)
        return false;
    rbNode *temp=x->left;
    x->left=temp->right;
    x->left->p=x;
    transplant(T,x,temp);
    temp->right=x;
    x->p=temp;
    return true;
}


void insert_fixed(rbNode *T,rbNode *x)
{
    rbNode *temp;
    while(x->p->c==red)
    {
        if(x->p==x->p->p->left)
        {
            temp=x->p->p->right;
            if(temp->c==red)
            {
                temp->c=black;
                x->p->c=black;
                x->p->p->c=red;
                x=x->p->p;
            }   
            else if(x==x->p->right)
            {
                x=x->p;
                left_rotate(T,x);
            }
            else 
            {
                x->p->p->c=red;
                x->p->c=black;
                right_rotate(T,x->p->p);
            }
        }
        else
        {
            temp=x->p->p->left;
            if(temp->c==red)
            {
                temp->c=black;
                x->p->c=black;
                x->p->p->c=red;
                x=x->p->p;
            }
            else if(x==x->p->left)
            {
                x=x->p;
                right_rotate(T,x);
            }
            else
            {
                x->p->p->c=red;
                x->p->c=black;
                left_rotate(T,x->p->p);
            }
        }
    }
    T->left->c=black;
}

void insert(rbNode *T,rbNode *x)
{
    rbNode *y=T;
    rbNode *p=T->left;
    if(p==T)
    {
        T->left=T->right=x;
        x->p=T;
        x->c=black;
        return;
    }
    while(p!=T)
    {
        y=p;
        if(x->k<p->k)
            p=p->left;
        else 
            p=p->right;
    }
    if(x->k<y->k)
        y->left=x;
    else 
        y->right=x;
    x->p=y;
    x->left=x->right=T;
    x->c=red;
    insert_fixed(T,x);
}

void delect_fixed(rbNode *T,rbNode *n)
{
    rbNode *temp;
    while(n!=T->left&&n->c==black)
    {
        if(n==n->p->left)
        {
            temp=n->p->right;
            if(temp->c==red)
            {
                n->p->c=red;
                temp->c=black;
                left_rotate(T,temp->p);
                temp=n->p->right;
            }
            else if(temp->left->c==black&&temp->right->c==black)
            {
                temp->c=red;
                n=n->p;
            }
            else if(temp->right->c==black)
            {
                temp->left->c=black;
                temp->c=red;
                right_rotate(T,temp);
                temp=n->p->right;
            }
            else
            {
                temp->right->c=black;
                temp->c=n->p->c;
                left_rotate(T,n->p);
                n=T->left;
            }
        }
        else
        {
            temp=n->p->left;
            if(temp->c==red)
            {
                temp->c=black;
                n->p->c=red;
                right_rotate(T,n->p);
                temp=n->p->left;
            }
            else if(temp->left->c==black&&temp->right->c==black)
            {
                temp->c=red;
                n=n->p;
            }
            else if(temp->left==black)
            {
                temp->c=red;
                temp->right->c=black;
                left_rotate(T,temp);
                temp=n->p->left;
            }
            else
            {
                temp->c=n->p->c;
                temp->left->c=black;
                right_rotate(T,n->p);
                n=T->left;
            }
        }
    }
    n->c=black;
}

void delect(rbNode *T,rbNode *x)
{
    rbNode *y;                             //记录实际删除节点的唯一的后代位置
    rbNode *temp=x;                         //实际删除的节点的位子
    color temp_color=temp->c;
    if(x->left==T)
    {
        y=x->right;
        transplant(T,x,x->right);
    }
    else if(x->right==T)
    {
        y=x->left;
        transplant(T,x,x->left);
    }
    else
    {
        temp=min(x->right,T);
        temp_color=temp->c;
        y=temp->right;
        if(y!=T)
            transplant(T,temp,y);
        if(temp->p!=x)
        {
            temp->right=x->right;
            temp->right->p=temp;
        }
        transplant(T,x,temp);
        temp->left=x->left;
        temp->left->p=temp;
        temp->c=x->c;
    }
    if(temp_color==black)
        delect_fixed(T,y);
    free(x);
}

void disp(rbNode *n,rbNode *T)
{
    if(n!=T)
    {
        disp(n->left,T);
        printf("Key is:%d , color is:%d\n",n->k,n->c);
        disp(n->right,T);
    }
}

rbNode *search(rbNode *T,int k)
{
    rbNode *x=T->left;
    while(x!=T&&x->k!=k)
    {
        if(k<x->k)
            x=x->left;
        else 
            x=x->right;
    }
    return x;
}

void disp_f(rbNode *n,rbNode *T)
{
    if(n!=T)
    {
        printf("%d ",n->k);
        disp_f(n->left,T);
        disp_f(n->right,T);
    }
}

int main()
{
    rbNode *temp;
    rbNode *T=(rbNode*)malloc(sizeof(rbNode));
    T->k=0;
    T->p=NULL;
    T->left=T->right=T;
    T->c=black;
    
    int a;
    char c;
    while(true)
    {
        printf("请输入\n");
        c=getchar();
        getchar();
        switch(c)
        {
            case '1':
            {
                scanf("%d",&a);
                getchar();
                insert(T,creatRedNode(T,a));
            }break;
            case '2':
                disp(T->left,T);break;
            case '3':
            {
                scanf("%d",&a);
                getchar();
                temp=search(T,a);
                if(temp!=T)
                    printf("k is:%d,c is:%d\n",temp->k,temp->c);
                else
                    printf("not in or error \n");
             }break;
            case '4':
            {
                scanf("%d",&a);
                getchar();
                temp=search(T,a);
                if(temp!=T)
                    delect(T,temp);
                else
                    printf("not in or error!!!");
            }break;
            case '5':
            {
                scanf("%d",&a);
                getchar();
                temp=min(search(T,a),T);
                if(temp!=T)
                printf("min is :%d\n",temp->k);
            }break;
            case '6':
                disp_f(T->left,T);break;
            default:;
        }
    }
}
