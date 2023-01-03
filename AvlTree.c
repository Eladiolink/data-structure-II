#include <stdio.h>
#include <stdlib.h>

typedef struct Tree Tree;

struct Tree
{
	Tree * parent;
	int info;
	Tree * left;
	Tree * right;
	int height;
};

void printTree(Tree * root, int level) {
  if (root == NULL) return;

  printTree(root->right, level+1);
  for (int i = 0; i < level; i++) {
    printf("   ");
  }
  printf("%d\n", root->info);
  printTree(root->left, level+1);
}

Tree * creatTree(int info){
	Tree * t = (Tree *) malloc(sizeof(Tree));

	if(t){
		t->info = info;
		t->height = 0;
		t->left = NULL;
		t->right = NULL;
		t->parent = NULL;
		return t;
	}

	return NULL;
}

// retorna a maior valor entre a e b

int maior(int a, int b){
	return (a>b)? a : b;
}

int alturaDoNo(Tree * n){
	if(!n) return -1;

	return n->height;
}

//Calcula e retorna o fator de balanceamento de um nó

int fatorDeBalanceamento(Tree * r){
	if(r)
		return (alturaDoNo(r->left) - alturaDoNo(r->right));
	return 0; 
}

Tree * RR(Tree * r){ // Rotação da Direita
	Tree *y, *f;

	y = r->right;
	f = y->left;
    
	y->left = r;
	r->right = f;

    r->height = maior(alturaDoNo(r->left),alturaDoNo(r->right)+1);
	y->height = maior(alturaDoNo(y->left),alturaDoNo(y->right)+1);

	return y;
}

Tree * LL(Tree * r){ // Rotação a Esqueda
	Tree *y, *f;

	y = r->left;
	f = y->right;
    
	y->right = r;
	r->left = f;

    r->height = maior(alturaDoNo(r->left),alturaDoNo(r->right)+1);
	y->height = maior(alturaDoNo(y->left),alturaDoNo(y->right)+1);

	return y;
}

Tree * RL(Tree * r){ // Rotação Dupla a Direita Esqueda
	r->right = LL(r->right);
	return RR(r);
}

Tree * LR(Tree * r){ // Rotação Dupla a Esqueda Direita
	r->left =RR(r->left);
	return LL(r);
}		

Tree * balancear(Tree * r){

	int fb = fatorDeBalanceamento(r);

	if(fb< -1 && fatorDeBalanceamento(r->right)<=0)
			r = RR(r);
	else if(fb > 1 && fatorDeBalanceamento(r->left)>=0)
			r = LL(r);
		
	else if(fb > 1 && fatorDeBalanceamento(r->left)<0)
			r = LR(r); 

	else if(fb < -1 && fatorDeBalanceamento(r->right)>0)
			r = RL(r);

	 return r;
}

Tree * insert(Tree * r,int value){
	// Adição
	if(r == NULL){
		return creatTree(value);
	}

	if(r->info == value){
		printf("NÓ JÁ INSERIDO");
		return r;
	}

	if(value < r->info){
		r->left = insert(r->left,value);
	}else{
		r->right = insert(r->right,value);
	}

	r->height = maior(alturaDoNo(r->left),alturaDoNo(r->right)) +1;

	// Balanceamento
	r = balancear(r);

	return r;
}

Tree * removeTree(Tree *r,int value){
	if(r->info == value){
		if(r->left == NULL && r->right==NULL){
			free(r);
			printf("Folha Removido");
			return NULL;
		}else if(r->left != NULL && r->right != NULL){
			Tree * q = r->left;
			Tree * aux= NULL;
			Tree * x = NULL;
			while (q){
			 x = aux;	
			 aux = q;
			 q = q->right;
			}

			r->info = aux->info;

			free(aux);
			x->right = NULL;
			return r;
		}else{
			return (r->left) ?  r->left : r->right;
		}

	}else{
		if(r->info > value){
			r->left = removeTree(r->left,value);
		}else{
			r->right = removeTree(r->right,value);
		}
	}

	r->height = maior(alturaDoNo(r->left),alturaDoNo(r->right))+1;

	r = balancear(r);
	return r;
}

int main(){
	Tree * t = NULL;
	
	t = insert(t,40);
	t = insert(t,44);
	t = insert(t,46);
	t = insert(t,13);
	t = insert(t,9);
    t = insert(t,16);
	t = insert(t,15);
	t = insert(t,14);
	t = insert(t,2);

	printf("\n\n");
	printTree(t,0);
	printf("\n");

	t = removeTree(t,9);
	printf("\n\n");
	printTree(t,0);
	printf("\n");

    return 0;
}
