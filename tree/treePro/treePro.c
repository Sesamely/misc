/*************************************************************************
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int key;
    struct Node *p;
    struct Node *l;
    struct Node *r;
}treeNode;

typedef struct N {
    struct Node *root;
}treeRoot;


void disp(const treeNode *t)
{
    if(t!=NULL)
    {
        disp(t->l);
        printf("%d ",t->key);
        disp(t->r);
    }
}

void insert(treeRoot *T,int k)
{
    treeNode *t=T->root;
    treeNode *p=NULL;
    treeNode *temp;
    temp=(treeNode *)malloc(sizeof(treeNode));
    temp->p=temp->l=temp->r=NULL;
    temp->key=k;
    
    while(t!=NULL)
    {
        p=t;
        if(t->key<k)
            t=t->r;
        else
            t=t->l;
    }
    if(p==NULL)
        T->root=temp;
    else if(p->key<k)
        p->r=temp;
    else
        p->l=temp;
    temp->p=p;
}

treeNode *min(treeNode *t)
{
    while(t->l!=NULL)
        t=t->l;
    return t;
}

treeNode *max(treeNode *t)
{
    while(t->r!=NULL)
        t=t->r;
    return t;
}

treeNode *search(treeNode *t,int k)
{
    while(t!=NULL&&t->key!=k)
    {
        if(t->key<k)
            t=t->r;
        else 
            t=t->l;
    }
    return t;
}

treeNode *successor(treeNode *x)
{
    treeNode *y=NULL;
    if(x->r!=NULL)
        return min(x->r);

    y=x->p;
    while(y!=NULL&&x==y->r)
    {
        x=y;
        y=x->p;
    }
    return y;
}

void transplant(treeRoot *T,treeNode *u,treeNode *v)
{
    if(u->p==NULL)
        T->root=v;
    else if(u==u->p->l)
        u->p->l=v;
    else 
        u->p->r=v;

    if(v!=NULL)
        v->p=u->p;
}

void delect(treeRoot *T,treeNode *t)
{
    treeNode *x=NULL;
    if(t->l==NULL)
        transplant(T,t,t->r);
    else if(t->r==NULL)
        transplant(T,t,t->l);
    else
    {
        x=min(t->r);
        if(t!=x->p)
        {
            transplant(T,x,x->r);
            x->r=t->r;
            x->r->p=x;
        }
        transplant(T,t,x);
        x->l=t->l;
        x->l->p=x;
    }
    free(t);
}


int main()
{
    int a;
    char c;
    treeRoot *T;
    T=(treeRoot*)malloc(sizeof(treeRoot));
    T->root=NULL;
;
    while(1)
    {
        printf("请输入:\n");
        scanf("%c",&c);
        getchar();
        
        switch(c)
        {
            case '1':
            {
                scanf("%d",&a);
                getchar();
                insert(T,a);
            }break;
            case '2':
            {
                scanf("%d",&a);
                getchar();
                treeNode *temp=search(T->root,a);
                if(temp!=NULL)
                {
                    printf("%d",temp->key);
                    delect(T,temp);
                }
            }break;
            case '3':
            {
                disp(T->root);
            }break;
            case '4':
            {
                scanf("%d",&a);
                getchar();
                treeNode *temp=search(T->root,a);
                if(temp!=NULL)
                    printf("%d",temp->key);
            }break;
            case '5':
            {
                scanf("%d",&a);
                getchar();
                printf("%d",successor(search(T->root,a))->key);
            }break;
            default:;
        }
    }
}













