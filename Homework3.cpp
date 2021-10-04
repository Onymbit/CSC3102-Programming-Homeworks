#include <iostream>
#include <fstream>
using namespace std;

typedef struct Node {
	Node *firstChild,*rightSibling;
	char leadCharacter;
	string label,meaning;
	bool isWord;
	int freq;
	int maxfreq;
	Node(string s){
		leadCharacter=s[0];
		label=s;
		firstChild=NULL;
		rightSibling=NULL;
	}
	Node(){
		firstChild=NULL;
		rightSibling=NULL;
	}
}Node;


void preorder( Node *p, string prefix) {
	
	if (p == NULL) 
		return;
	prefix = prefix + p->label;	
	if (p->isWord) 
		cout<<prefix+" ";
	
	Node *q=p->firstChild;

	while(q != NULL) {
		preorder(q, prefix);
		q=q->rightSibling;	
	}

}
Node * findChild(Node *p,char s){
	Node *q=p->firstChild;
	while(q!=NULL){
		if(q->leadCharacter==s){
			return q;
		}
		q=q->rightSibling;
	}
	return NULL;
	
}
void prefixQuery(Node *p, string prefix, string prev){
	if (p == NULL) 
		return;
	if(p->label=="")
		prefixQuery(p->firstChild,prefix,prev);
	int i=0;
	if(prefix.length()==0){
		preorder(p,prev);
		return;
	}
	while( (i < p->label.length()) && i < prefix.length() && p->label[i] == prefix[i]){
		i++;
	}
	if(i==0){
		return prefixQuery(p->rightSibling,prefix,prev);
	}
	if(i==prefix.length()){
		preorder(p,prev);
		return;
	}

	else { // p->label is not completely consumed then node p will be split
		prev=prev+prefix.substr(0,i);
		prefixQuery(p->firstChild,prefix.substr(i,prefix.length()-1),prev);
		
	}	
}
// node's children are unordered in the linked list ...not sorted in this case
// you may want to do it in sorted order so that your list of matching
//words output is alphabetically ordered

void insert(Node *p, string s, string meaning, int freq){
	int i=0;


	int tempfreq = p->maxfreq;
	if (p->maxfreq < freq) p->maxfreq=freq;

	//cout<<__LINE__;
	while( (i < p->label.length()) && i < s.length() && p->label[i] == s[i] ){
		i++;
	}
	
	s=s.substr(i,s.length()); //s is now unmatched part possibly empty
	if((s.length() == 0) && (p->label.length() == i)) {
		p->isWord=true;
		p->freq=freq; 
		p->meaning = meaning;
	}

	else if(i == p->label.length() ) { //p's label exhausted
		Node *q=findChild(p,s[0]);
		if (q == NULL) { //make a new child of p
			Node *r= new Node(s);
			r->isWord=true; 
			r->freq=freq; 
			r->maxfreq=freq;
			r->meaning=meaning;
			if(p->firstChild==NULL){
				p->firstChild=r;
				r->rightSibling=NULL;
				//cout<<p->label<<"(p points to new)"<<r->label<<'\n';
			}
			else if(r->leadCharacter < p->firstChild->leadCharacter){
				r->rightSibling=p->firstChild;
				p->firstChild=r;
				//cout<<p->label<<"(p points to new)"<<r->label<<"(new points to old first)"<<r->rightSibling->label<<'\n';
			}
			else {
				q=p->firstChild;
				while(q != NULL){
					if(q->rightSibling==NULL){
						q->rightSibling=r;
						break;
					}
					else if(r->leadCharacter < q->rightSibling->leadCharacter){
						r->rightSibling=q->rightSibling;
						q->rightSibling=r;
						//cout<<q->label<<"(p points to new)"<<r->label<<"(new points to old first)"<<r->rightSibling->label<<'\n';
						break;
					}
					else {
						q=q->rightSibling;
					}
				}
			}
		}   //this makes unsorted child list...you should change
		else insert(q,s,meaning,freq);  //continue inserting recursively

	}

	else { // p->label is not completely consumed then node p will be split

		string s1=p->label.substr(i,p->label.length()); // later part of p's label
		string s2=p->label.substr(0,i);  // earlier part of p's label
		Node *q1=new Node(s1);
		q1->firstChild = p->firstChild;  //q1 inherits everything from p
		q1->isWord = p->isWord; 
		q1-> freq = p->freq;
		q1->maxfreq = tempfreq;  // this is the original max freq of p
		q1->meaning=p->meaning;
		if(s.length() != 0){
			p->isWord=false;
			Node *q2=new Node(s);      //s is now original s sans its prefix already matched prefix s2
			p->firstChild = q2;
			p->label = s2;
			q2->rightSibling=q1;
			q2->isWord=true; 
			q2->freq=freq; 
			q2->maxfreq= freq; 
			q2->meaning = meaning; 
		}
		else{
			p->label=s2;
			p->isWord=true;
			p->firstChild=q1;
		} 
		
	}
}

int main(){
	Node *root=new Node;
	ifstream in;
	in.open("minidict_freq.txt");
	string temp;
	int count;
	for(int i=0;i<100;i++){
		in>>temp;
		in>>count;
		insert(root,temp,"hello",count);
	}
	in.close();
	cout<<"The entire list:\n";
	preorder(root,"");
	string prefixSearch="a";
	cout<<"\n\nEverything with the prefix "<<prefixSearch<<":\n";
	prefixQuery(root,prefixSearch,"");

	return 0;
}
