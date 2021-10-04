#include <iostream>
#include <fstream>
using namespace std;

typedef struct Node{
    int data;
    struct Node *prev,*next;
} Node;

typedef struct DoublyLinkedList{
    Node *head;
    Node *tail;
    int size;
} DoublyLinkedList;

void insertFirst(DoublyLinkedList *l, int data){
	Node *newNode=new Node;
	newNode->data=data;
	if(l->size==0){
		newNode->next=NULL;
		newNode->prev=NULL;
		l->head=newNode;
		l->tail=newNode;
		l->size=l->size+1;
		return;
	}
	newNode->next=l->head;
	newNode->prev=NULL;
	l->head->prev=newNode;
	l->size=l->size+1;
	l->head=newNode;
	
};

void insertLast(DoublyLinkedList *l, int data){
	Node *newNode=new Node;
	newNode->data=data;
	if(l->size==0){
		newNode->next=NULL;
		newNode->prev=NULL;
		l->head=newNode;
		l->tail=newNode;
		l->size=l->size+1;
		return;
	}
	newNode->next=NULL;
	l->tail->next=newNode;
	newNode->prev=l->tail;
	l->size=l->size+1;
	l->tail=newNode;
};


int deleteFirst(DoublyLinkedList *l){
	if(l->size==0){
		return -1;
	}
	Node *oldNode=new Node;
	int data;
	if(l->size==1){
		oldNode=l->head;
		l->head=NULL;
		l->tail=NULL;
		data=oldNode->data;
		delete oldNode;
		l->size=l->size-1;
		return data;
	}
	oldNode=l->head;
	l->head=l->head->next;
	l->head->prev=NULL;
	data=oldNode->data;
	delete oldNode;
	l->size=l->size-1;
	return data;
};
/*should return -1 if the list is empty else return the data of the deleted Node*/

int deleteLast(DoublyLinkedList *l){
	if(l->size==0){
		return -1;
	}
	Node *oldNode=new Node;
	int data;
	if(l->size==1){
		oldNode=l->tail;
		l->head=NULL;
		l->tail=NULL;
		data=oldNode->data;
		delete oldNode;
		l->size=l->size-1;
		return data;
	}
	
	oldNode=l->tail;
	l->tail=l->tail->prev;
	data=oldNode->data;
	delete oldNode;
	l->tail->next=NULL;
	l->size=l->size-1;
	return data;
};
/*should return -1 if the list is empty else return the data of the deleted Node*/

void printList(DoublyLinkedList *l){
	Node *currentNode=l->head;
	while(currentNode->next!=NULL){
		cout<<currentNode->data<<" ";
		currentNode=currentNode->next;
	}
	cout<<currentNode->data;
	
	
};
/*prints the list of keys in order */

void insertAfter(DoublyLinkedList *l, Node *current, int data){
	if(current==l->tail){
		insertLast(l,data);
		return;
	}
	Node *newNode=new Node;
	newNode->data=data;
	newNode->next=current->next;
	newNode->prev=current;
	current->next=newNode;
	newNode->next->prev=newNode;
	l->size=l->size+1;
	
};
/*assumes that current is one of the nodes in the list l*/

int deleteAt(DoublyLinkedList *l, Node *current){
	if(current==l->head){
		return deleteFirst(l);
	}
	if(current==l->tail){
		return deleteLast(l);
	}
	int data;
	data=current->data;
	current->prev->next=current->next;
	current->next->prev=current->prev;
	delete current;
	return data;
};
/*assumes that current is a Node in list l, returns the data from the deleted Node */

int main(){
    DoublyLinkedList *l=new DoublyLinkedList;
    l->size=0;
    
    ifstream in;
    in.open("input.txt");
    
    int count;
	in>>count;
	string temp;
	int tempInt;
	
    for(int i=0;i<count;i++){
    	in>>temp;
    	if(temp=="PRIN"){
			printList(l);
		}
		else if(temp=="INSF"){
			in>>tempInt;
			insertFirst(l,tempInt);
		}
		else if(temp=="INSL"){
			in>>tempInt;
			insertLast(l,tempInt);
		}
		else if(temp=="DELF"){
			deleteFirst(l);
		}
		else if(temp=="DELL"){
			deleteLast(l);
		}
		/*cout<<i<<": ";
		printList(l);
		cout<<"\n"<<"\n";*/	
	}
    in.close();
    
    
/*will read the file line by line and execute instructions */    

}
