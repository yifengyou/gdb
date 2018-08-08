#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    struct node *left;
    struct node *right;
};

typedef struct node *nsp;

nsp root;

nsp makenode(int x)
{
    nsp tmp;
    tmp = (nsp)malloc(sizeof(struct node));
    tmp -> val =x;
    tmp -> left = tmp -> right =0;
    return tmp;
}

void insert(nsp *btp,int x)
{
    nsp tmp = *btp;
    if ( *btp ==0 ){
        *btp = makenode("x");
        return;
    }   
    while(1){
        if( x < tmp->val){
        	if (tmp->left != 0){
        		tmp = tmp->left;
        	}else{
        		tmp->left = makenode(x);
        		break;
        	}
        }else{
        	if( tmp->right != 0 ){
        		tmp = tmp->right;
        	}else{
        		tmp->right = makenode(x);
        		break;
        	}
        }
    }
}

void printtree(nsp bt)
{
	if (bt == 0) return;
	printtree(bt->left);
	printf("%d\n",bt->val);
	printtree(bt->right);
}

int main(int argc,char * argv[])
{
	int i;
	root = 0;
	for ( i = 1; i < argc ;i++)
	{
		insert(&root,atoi(argv[i]));
	}
	printtree(root);
}