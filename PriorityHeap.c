#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct node node;

struct node
{
    int info;
    int priority;
};

typedef struct PriorityHeap PriorityHeap;


struct PriorityHeap{
    node * Heap[MAX];
    int tamanho;
};

node * creatNode(int val,int p){
    node * n = (node *) malloc(sizeof(node));

    if(n){
        n->info = val;
        n->priority = p;

        return n;
    }

    return NULL;

}

PriorityHeap * creatHeap(){
    PriorityHeap * heap = (PriorityHeap *) malloc(sizeof(PriorityHeap));

    if(heap){
        heap->tamanho = 0;
        return heap;
    }

    return NULL;
}

void HeapMaxfy(PriorityHeap *Heap,int tree,int length){
    int maior = tree; //5 1
    int left = 2 * tree + 1; // 6 2
    int rigth = 2 * tree +2; // Undefined Undefined

    if(left<length && Heap->Heap[left]->priority > Heap->Heap[maior]->priority) maior = left;
    if(rigth<length && Heap->Heap[rigth]->priority > Heap->Heap[maior]->priority) maior = rigth;
    
    if(maior != tree){
        node * aux = Heap->Heap[tree];
        Heap->Heap[tree] = Heap->Heap[maior];
        Heap->Heap[maior] = aux;
        
        HeapMaxfy(Heap,maior,length);
    }
}

void swap(node * a, node * b) {
  node temp = *a;
  *a = *b;
  *b = temp;
}

//Insere um elemento na fila de prioridade
void insertValue(PriorityHeap *Heap,int value, int priority){
    if( Heap->tamanho == MAX){
        printf("HEAP CHEIA!!\n");
        return;
    }

    node * new = creatNode(value,priority);

    Heap->Heap[Heap->tamanho] = new;
    
    int current = Heap->tamanho;
    int parent = (Heap->tamanho - 1) / 2;
    
    while (Heap->tamanho > 0 && Heap->Heap[current]->priority > Heap->Heap[parent]->priority) {
        swap(Heap->Heap[current], Heap->Heap[parent]);
        current = parent;
        parent = (current - 1) / 2;
    }
    
    Heap->tamanho++;

}

// devolve o elemento com maior prioridade
node * Max(PriorityHeap *Heap){
    return Heap->Heap[0];
}

// remove e devolve o elemento de maior prioridade
node * extractMax(PriorityHeap *Heap){
    node * n = Heap->Heap[0];
    Heap->tamanho -= 1;
    Heap->Heap[0] = Heap->Heap[Heap->tamanho];
    HeapMaxfy(Heap,0,Heap->tamanho);
    return n;
}

// Aumenta a prioridade de uma chave
void creaseKey(PriorityHeap *Heap,int key,int num){
    if(Heap->Heap[key]->priority>num){
        printf("Valor é menor q o valor atual\n");
        return;
    }

    Heap->Heap[key]->priority = num;
    int current = key;
    int parent = (current-1)/2;
    while (Heap->Heap[current]->priority > Heap->Heap[parent]->priority)
    {
        swap(Heap->Heap[current], Heap->Heap[parent]);
        current = parent;
        parent = (current - 1) / 2;
    }
    
}

void printHeap(PriorityHeap *Heap){
    node * x ;
    for(int i= 0;i<Heap->tamanho;i++){
        x = Heap->Heap[i];
        printf("%i ",x->info);
    }
        printf("\n");
}

int main(){
   
    PriorityHeap * Heap = creatHeap();

    insertValue(Heap,5,1);
    insertValue(Heap,6,2);
    insertValue(Heap,7,2);
    insertValue(Heap,8,4);
    insertValue(Heap,9,1);
    insertValue(Heap,10,2);
    
    printHeap(Heap);

    node * max = Max(Heap);
    printf("Maior: %i\n",max->info);
    extractMax(Heap);
    printHeap(Heap);
     extractMax(Heap);
    printHeap(Heap);

    insertValue(Heap,10,5);

    creaseKey(Heap,1,12);
    printHeap(Heap);
    creaseKey(Heap,1,13);
    printHeap(Heap);
    creaseKey(Heap,2,14);
    printHeap(Heap);
    return 0;
}