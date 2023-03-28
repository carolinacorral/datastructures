#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int Dato;

//Node structure
struct Node{
    Dato value;
    struct Node* next;
    struct Node* prev;
    int pos;
};

typedef struct Node* List;

void createList(List* l, int *error);
void insertLeft(List* l,Dato value,int *error);
void insertRight(List* l,Dato value,int *error);
Dato extractLeft(List* l,int *error);
Dato extractRight(List* l,int *error);
void insertN(List* l, Dato value,int pos,int *error);
Dato extractN(List* l, Dato value, int pos,int *error);
void findNode(List* l,Dato value,int *error);
int maxPos(List* l,int *error);
void checkHead(List* l,int *error);
void updateN(List* l,Dato value, int pos,int *error);
void printList(List* l,int *error);
void clearList(List* l,int *error);
void deleteList(List* l,int *error);
void copyList(List* l, List* copia,int *error);

void createList(List* l, int *error){
    *l=NULL;
    *error=0;
    puts("Created.");
}

void insertLeft(List* l,Dato value,int *error){
  struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        perror("No memory");
        *error=-1;
    }   
    newNode->pos=0;
    newNode->value=value;
    if(*l==NULL){
        newNode->next=newNode;
        newNode->prev=newNode;
        (*l)=newNode;
        
    } else{
        newNode->next=(*l);
        newNode->prev=(*l)->prev;
        (*l)->prev->next=newNode;
        (*l)->prev=newNode;
        (*l)=newNode;
        struct Node* aux=newNode->next;
        while(aux!=newNode){ //Reasign Positions
            aux->pos=aux->pos+1;
            aux=aux->next;
        }        
    }    
    *error=0;    
}

void insertRight(List* l,Dato value,int *error){ 
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        perror("No memory");
        *error=-1;
    }   
    newNode->value=value;
    if(*l==NULL){
        newNode->next=newNode;
        newNode->prev=newNode;
        (*l)=newNode;
        newNode->pos=0;
        
    } else{
        newNode->pos=(*l)->prev->pos+1;
        newNode->prev=(*l)->prev;
        newNode->next=(*l);
        (*l)->prev->next=newNode;
        (*l)->prev=newNode;        
    }
    
    *error=0;    
}

Dato extractLeft(List* l,int *error){
    Dato extvalue;
    if(*l==NULL){
        perror("List is empty");
        *error=-2;
    } else {
    extvalue=(*l)->value;
    struct Node* aux=(*l);
    if(aux->prev==aux){
        (*l)=NULL;
    } else{
        (*l)=aux->next;
        (*l)->prev=aux->prev;
        aux->prev->next=(*l);
        while(aux!=(*l)){ //Reasign positions
            aux->pos=aux->pos-1;
            aux=aux->next;
        } 
    }
    aux->next=NULL;
    aux->prev=NULL;
    free(aux);
    return extvalue;
    }
}

Dato extractRight(List* l,int *error){
    Dato extvalue;
    if(*l==NULL){
        perror("List is empty");
        *error=-2;
    } else {
    struct Node* aux=(*l)->prev;
    extvalue=(*l)->value;
    if(aux==(*l)){
        (*l)=NULL;
    } else{
        aux->prev->next=(*l);
        (*l)->prev=aux->prev;     
      
    }
    aux->next=NULL;
    aux->prev=NULL;
    free(aux);
    return extvalue;
    }
}

void insertN(List* l, Dato value,int pos,int *error){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        perror("No memory");
        *error=-1;
    } else {        
    if (*l==NULL && pos==0){
        (*l)=newNode;
        newNode->value=value;
        newNode->pos=0;
        newNode->next=newNode;
        newNode->prev=newNode;
    } else if(pos>maxPos(l,error)){
        perror("Out of range");
        *error=-3;
    } else {
        newNode->value=value;
        newNode->pos=pos;
        struct Node* nIzq=(*l); //Left of n
        struct Node* nDer;      //Right of n
        while(nIzq->pos!=pos-1){ // Stops one position before pos to insert to the left
            nIzq=nIzq->next;
        }
        nDer=nIzq->next;
        nIzq->next=newNode;
        newNode->prev=nIzq;
        newNode->next=nDer;
        nDer->prev=newNode;
        if(pos==maxPos(l,error)){ // If pos was maxPos only nDer position changes
            nDer->pos=nIzq->pos+1;
        } else {
        while(nDer!=(*l)){ //Else, reasign positions
            nDer->pos=nDer->pos+1;
            nDer=nDer->next;
        } 
        }
    }
    }
}

Dato extractN(List* l, Dato value, int pos,int *error){
    Dato extvalue;
    if(*l==NULL){
        perror("List is empty");
        *error=-2;
    } 
    else if(pos>maxPos(l,error)){
        perror("Out of range");
        *error=-3; 
    } else {
    if(pos==0 && maxPos(l,error)==0){
        extvalue=(*l)->value;
        (*l)=NULL;
    } else{
        struct Node* n=(*l);         
        while(n->prev->pos<pos){
            n=n->next;
        }
        extvalue=n->value;
        n->prev->next=n->next;
        n->next->prev=n->prev;
        struct Node* aux=n->next;
        n->next=NULL;
        n->prev=NULL;
        free(n);
        while(aux!=(*l)){
            aux->pos=aux->pos-1;
            aux=aux->next;
        }        
    }
    return extvalue;
    }
    
}

void checkHead(List* l,int *error){
    if (*l==NULL){
        perror("List is empty");
        *error=-2;
    } else {
    Dato head=(*l)->value;
    printf("Head: %d\n",head);
    }
}

void updateN(List* l,Dato value, int pos,int *error){
    if (*l==NULL){
        perror("List is empty");
        *error=-2;
    } else {
        if(pos>maxPos(l,error)){
            perror("Out of range."); 
            *error=-3;           
        } 
        else{
            struct Node* aux=(*l);
            while(aux->pos!=pos){
                aux=aux->next;
            }
            Dato old=aux->value;
            aux->value=value;
            printf("Value %d. %d updated to %d\n",pos,old,value);   
            free(old);       
        }

    }
}

void buscarNodo(List* l,Dato value, int *error){
    if(*l==NULL){
        perror("La List esta vacia");
        *error=-2;
    } else {
        struct Node* nodoaux=(*l);     
        bool flag=false;
        int pos;        
        while(nodoaux->next!=(*l)){
            if(nodoaux->value==value){
                flag=true;                
                pos=nodoaux->pos;
            }
            nodoaux=nodoaux->next;                     
        }  
        if(flag){
            printf("Value '%d' found in position %d",value,pos);            
        } else {
            puts("Value not found");
        }
    }
}

void clearList(List* l,int *error){
    struct Node* aux=(*l);
    while(aux->next!=(*l)){
        extractLeft(l,error);        
    }    
    (*l)=NULL;
}

void deleteList(List* l,int *error){
    clearList(l,error);
    free(l);
}

void copyList(List* l, List* copia,int *error){
    struct Node* aux=(*l);
    while(aux->next!=(*l)){
        insertRight(copia,aux->value,error);
        aux=aux->next;
    }
    insertRight(copia,aux->value,error);
}


void printList(List* l,int *error){ 
    if(*l==NULL){
        perror("List is empty");
        *error=-1;        
    }      
    struct Node* nodoaux=(*l);
    printf("%d. %d\n",(nodoaux->pos+1),nodoaux->value);
    nodoaux=nodoaux->next;
    while(nodoaux!=(*l)){
        printf("%d. %d\n",(nodoaux->pos+1),nodoaux->value);
        nodoaux=nodoaux->next;   
    }
}

int maxPos(List* l,int *error){
    if(*l==NULL){
        perror("List is empty");
        *error=-2;
    } else {
    int max=(*l)->prev->pos;
    return max;
    }
}

int main (){
    return 0;
}
