#include <stdio.h>
#include <stdlib.h>

typedef struct Tree Tree;

struct Tree
{
	Tree * parent;
	int info;
	Tree * left;
	Tree * right;
	int bal;
};

Tree * creatTree(int info){
	Tree * t = (Tree *) malloc(sizeof(Tree));

	if(t){
		t->info = info;
		t->bal = 0;
		t->left = NULL;
		t->right = NULL;
		t->parent = NULL;
		return t;
	}

	return NULL;
}

Tree * insert(Tree **t, int value){
	if(!*t)	*t = creatTree(value);

	Tree *new = creatTree(value);

	Tree * p = *t;
	Tree * q = NULL;
	while (p!=NULL)
	{
		q = p;
		if(p->info == new->info) return p;

		if(p->info > new->info){
			p = p->left;
		}else{
			p = p->right;
		}
	}
	
	if(t==NULL){
		*t = new;
	}else{
		if(q->info > new->info){
			q->left = new;
		}else{
			q->right = new;
		}
	}
}

void printTree(Tree * root, int level) {
  if (root == NULL) return;

  printTree(root->right, level+1);
  for (int i = 0; i < level; i++) {
    printf("   ");
  }
  printf("%d\n", root->info);
  printTree(root->left, level+1);
}

void printTreeV(Tree * root, int level) {
  if (root == NULL) return;

  printTree(root->right, level+1);
  printf("%*d\n", level*4, root->info);
  printTree(root->left, level+1);
}
int main(){
	Tree * t = NULL;
	
	insert(&t,40);
	insert(&t,20);
	insert(&t,10);
	insert(&t,25);

	printTree(t,0);

	printf("\n");
    return 0;
}
