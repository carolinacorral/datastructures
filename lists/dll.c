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
void updateN(List* l,Dato value, int pos,int *error);
void printList(List* l,int *error);
void clearList(List* l,int *error);
void deleteList(List* l,int *error);
void sortList(struct Node* nodo,int *error);
void copyList(List* l, List* copy,int *error);
int maxPos(List* l,int *error);

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
    if(*l==NULL){ //if List is empty next node is NULL
        newNode->next=NULL;
        newNode->prev=NULL;
        (*l)=newNode;
    } else{ 
        newNode->next=(*l); 
        (*l)->prev=newNode;
        newNode->prev=NULL;
        (*l)=newNode; 
        struct Node* aux=newNode->next;
        while(aux!=NULL){ //Reasign positions
            aux->pos=aux->pos+1;
            aux=aux->next;
        }
    }
}

void insertRight(List* l,Dato value,int *error){ 
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        perror("No memory");
        *error=-1;
    }   
    if(*l==NULL){
        newNode->next=NULL;
        newNode->prev=NULL;
        (*l)=newNode;
        newNode->pos=0;
        newNode->value=value;
    } else{
        struct Node* aux=(*l);
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=newNode;
        newNode->next=NULL;
        newNode->prev=aux;
        newNode->pos=aux->pos+1;
        newNode->value=value;
    }
    
    *error=0;    
}

Dato extractLeft(List* l,int *error){ 
    if(*l==NULL){
        perror("List is empty");
        *error=-2;
    }
    Dato datoext=(*l)->value;
    if(maxPos(l,error)==0){ //If there's only one element in list
        (*l)=NULL;
    } else {    
        struct Node* aux1=(*l);
        (*l)=(*l)->next;
        (*l)->prev=NULL;
        aux1->next=NULL;
        aux1->prev=NULL;
        free(aux1);
        struct Node* aux2=(*l);
        while(aux2!=NULL){ //Reasign positions
            aux2->pos=aux2->pos-1;
            aux2=aux2->next;
        }
        *error=0;
    }
    return datoext;
}

Dato extractRight(List* l,int *error){
    if(*l==NULL){
      perror("List is empty");
        *error=-2;  
    }
    else {
        Dato datoext;
        if((*l)->next==NULL){
          datoext=(*l)->value;  
          (*l)=NULL;          
        } else{
        struct Node* aux=(*l); //Last value 
        struct Node* aux2; 
        while(aux->next!=NULL){            
            aux=aux->next;
        }     
        
        datoext=aux->value; //Retrieves last value
        aux2=aux->prev; //Second to last value
        aux->prev=NULL;
        aux2->next=NULL; //Second to last value is now last value
        free(aux); 
        }
        return datoext;       
        
    }
}

void insertN(List* l, Dato value,int pos,int *error){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        perror("No memory");
        *error=-1;
    }
    if(pos==0 && *l==NULL){ //If N = 0 and the list is empty
        newNode->value=value;
        newNode->pos=pos;
        newNode->next=NULL;
        newNode->prev=NULL;
        (*l)=newNode;
    }
    else if(pos>maxPos(l,error)){
        perror("Out of range");
        *error=-3;
    } else{
        newNode->value=value;
        newNode->pos=pos;
        struct Node* aux=(*l);
        struct Node* aux2;
        while(pos-1>aux->pos){ //Stops one position before N   
            aux=aux->next;
        }
        aux2=aux->next;
        aux->next=newNode;
        newNode->prev=aux;
        newNode->next=aux2;
        aux2->prev=newNode;
        while(aux2!=NULL){
            aux2->pos=aux2->pos+1;
            aux2=aux2->next;
        }
    }
    
}

void findNode(List* l,Dato value, int *error){
    if(*l==NULL){
        perror("List is empty");
        *error=-2;
    } else {
        struct Node* nodoaux=(*l);     
        bool flag=false;
        int pos;        
        while(nodoaux->next!=NULL){
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

void updateN(List* l,Dato value, int pos,int *error){
    if (*l==NULL){
        perror("List is empty");
        *error=-2;
    } else {
        if(pos>maxPos(l,error)){
            perror("Out of range");            
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

void clearList(List* l,int *error){
    struct Node* aux=(*l);
    while(aux->next!=NULL){
        extractLeft(l,error);        
    }    
}

void deleteList(List* l,int *error){
    clearList(l,error);
    free(l);
}

void copyList(List* l, List* copy,int *error){
    struct Node* aux=(*l);
    while(aux!=NULL){
        insertRight(copy,aux->value,error);
        aux=aux->next;
    }
}

void printList(List* l,int *error){
    if(*l==NULL){
        perror("List is empty.");
        *error=-1;
        
    }      
    struct Node* nodoaux=(*l);
      
    while(nodoaux!=NULL){
        printf("%d. %d\n",(nodoaux->pos+1),nodoaux->value);
        nodoaux=nodoaux->next;    
        
    }
}

void sortList(struct Node *nodo,int *error){
    struct Node* aux=nodo;
    while(aux->next!=NULL){
        if(nodo->value>aux->next->value){
            Dato value;
            value=nodo->value;
            nodo->value=aux->next->value;
            aux->next->value=value;
            
        }      
        aux=aux->next;  
    }
    if(nodo->next!=NULL){
        sortList(nodo->next,error);
    }
}

int maxPos(List* l,int *error){
    if(*l==NULL){        
        perror("List is empty");
        *error=-2;
    }
    struct Node* aux1=(*l);
    while(aux1->next!=NULL){
        aux1=aux1->next;
    }
    int tam=aux1->pos;
    return tam;
}

