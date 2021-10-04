#include <iostream>
using namespace std;
typedef struct BSTNode{
    int key;
    int data;
    int size;
    BSTNode *left, *right, *parent;
    int height;
    BSTNode(int key_,int data_){
		key=key_;
		data=data_;
		left=right=parent=NULL;
		size=1;
		height=1;
	}
} BSTNode;

BSTNode * rotateup(BSTNode *z)
{
    BSTNode *y=z->parent;
    while ((y->data > z->data) && (y->parent !=NULL)){
    	//Previous parent node of y is reconnected
    	z->parent=y->parent;
    	if(y->parent->right==y){
    		y->parent->right=z;
		}
		else {
			y->parent->left=z;	
		}
		//Previous parent node of y is reconnected
		
		BSTNode *temp;
		
		//Right Case
		if(y->right==z){
			temp=z->left;
			y->right=temp;
			z->left=y;
			y->parent=z;
			if(temp!=NULL)
				temp->parent=y;
		}
		else {
			temp=z->right;
			y->left=temp;
			z->right=y;
			y->parent=z;
			if(temp!=NULL)
				temp->parent=y;	
		}
		//Size-height Fix
		if(y->left==NULL&&y->right==NULL){
			y->size=1;
			y->height=1;
		}
		else if(y->left==NULL && y->right!=NULL){
			y->size=y->right->size+1;
			y->height=1+y->right->height;
		}
		else if(y->left!=NULL && y->right==NULL){
			y->size=y->left->size+1;
			y->height=1+y->left->height;
		}
		else {
			y->size=1+y->right->size+y->left->size;
			y->height=(y->right->height > y->left->height) ? y->right->height : y->left->height;
			y->height++;
		}
		if(z->right==NULL){
			z->height=y->height+1;
			z->size=y->size+1;
		}
		else if(z->left==NULL){
				z->height=y->height+1;
				z->size=y->size+1;
			}
		else {
			z->height=1+ ((z->right->height > z->left->height) ? z->right->height : z->left->height);
			z->size=1+z->right->size+z->left->size;
		}
		temp=z->parent;
		while(temp!=NULL){
				if(temp->right==NULL&&temp->left!=NULL){
					temp->height=temp->left->height+1;
				}
				else if(temp->right!=NULL&&temp->left==NULL){
					temp->height=temp->right->height+1;
				}
				else if(temp->right!=NULL&&temp->left!=NULL){
					temp->height=(temp->right->height > temp->left->height) ? temp->right->height : temp->left->height;
					temp->height++;
				}
				temp=temp->parent;
			}	
		//Size-height Fix	
        y=z->parent; 
    }
    if(y->data > z->data){
    	
    	BSTNode *temp;
		z->parent=NULL;
		if(y->right==z){	
			temp=z->left;
			y->right=temp;
			z->left=y;
			y->parent=z;
			if(temp!=NULL)
				temp->parent=y;
		}
		else {
			temp=z->right;
			y->left=temp;
			z->right=y;
			y->parent=z;
			if(temp!=NULL)
				temp->parent=y;	
		}
			//Size-height Fix
			if(y->left==NULL&&y->right==NULL){
				y->size=1;
				y->height=1;
			}
			else if(y->left==NULL && y->right!=NULL){
				y->size=y->right->size+1;
				y->height=1+y->right->height;
			}
			else if(y->left!=NULL && y->right==NULL){
				y->size=y->left->size+1;
				y->height=1+y->left->height;
			}
			else {
				y->size=1+y->right->size+y->left->size;
				y->height=(y->right->height > y->left->height) ? y->right->height : y->left->height;
				y->height++;
			}
			
			if(z->right==NULL){
				z->height=y->height+1;
				z->size=y->size+1;
			}
			else if(z->left==NULL){
				z->height=y->height+1;
				z->size=y->size+1;
			}
			else {
				z->height=1+ ((z->right->height > z->left->height) ? z->right->height : z->left->height);
				z->size=1+z->right->size+z->left->size;
			}
			
			//Size-height Fix
	}
}

BSTNode * insert(BSTNode *root, int key, int data){
	if(root==NULL){
		root=new BSTNode(key,data);
		return root;
	}
	if(root->key>key){
		if(root->left==NULL){
			if(root->right==NULL){
				root->height++;	
			}
			BSTNode *temp=root->parent;
			root->size++;
			while(temp!=NULL){
				if(temp->right==NULL&&temp->left!=NULL){
					temp->height=temp->left->height+1;
				}
				else if(temp->right!=NULL&&temp->left==NULL){
					temp->height=temp->right->height+1;
				}
				else if(temp->right!=NULL&&temp->left!=NULL){
					temp->height=(temp->right->height > temp->left->height) ? temp->right->height : temp->left->height;
					temp->height++;
				}
					
				temp->size++;
				temp=temp->parent;
			}
			BSTNode *temp1=new BSTNode(key,data);
			temp1->parent=root;
			root->left=temp1;
			rotateup(temp1);
			if(temp1->parent==NULL);
				return temp1;
			while(temp1->parent!=NULL){
				temp1=temp1->parent;
			}
			return temp1;
		}
		return insert(root->left,key,data);
		
	}
	else {
		if(root->right==NULL){
			if(root->left==NULL){
				root->height++;
			}
			BSTNode *temp=root->parent;
			root->size++;
			while(temp!=NULL){
				if(temp->right==NULL&&temp->left!=NULL){
					temp->height=temp->left->height+1;
				}
				else if(temp->right!=NULL&&temp->left==NULL){
					temp->height=temp->right->height+1;
				}
				else if(temp->right!=NULL&&temp->left!=NULL){
					temp->height=(temp->right->height > temp->left->height) ? temp->right->height : temp->left->height;
					temp->height++;
				}
					
				temp->size++;
				temp=temp->parent;
			}
			BSTNode *temp1=new BSTNode(key,data);
			temp1->parent=root;
			root->right=temp1;
			rotateup(temp1);	
			while(temp1->parent!=NULL){	
				temp1=temp1->parent;
			}
			return temp1;
		}
		return insert(root->right,key,data);	
	}
	
};
BSTNode * search(BSTNode *root, int key){
	if(root==NULL);
		return NULL;
	if(root->key==key)
		return root;
	if(root->key>key)
		return search(root->left,key);
	if(root->key<key)
		return search(root->right,key);
};
int select(BSTNode *root, int k){
	if (root == NULL){
		return -1;
	}
	int temp=1+ ((root->left==NULL)? 0 : root->left->size);
	if(temp == k){
		return root->key;
	}
	if(temp > k){
		return select(root->left,k);
	}
	
	return select(root->right,k-temp);
};
int rank(BSTNode *root, int key){
	if (root == NULL) 
		return 0;
	else if (key < root->key){
		return rank(root->left,key);	
	}
	else if (key == root->key){
		if(root->left!=NULL)
			return (root->left->size+1);
		return 1;	
	}
	else if(key > root->key){
		if(root->left==NULL)
			return (1+rank(root->right,key));
		return (root->left->size+1+rank(root->right,key));
	}	

};
void traversal(BSTNode *root){
	if(root->left != NULL){
		cout<<'(';
		traversal(root->left);
		cout<<')';
	}
	cout<<root->key<<':'<<root->data<<' ';
	if(root->right != NULL){
		cout<<'(';
		traversal(root->right);
		cout<<')';
	}
}
int maxDepth(BSTNode* node)  
{  
    if (node == NULL)  
        return 0;  
    else
    {  
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left);  
        int rDepth = maxDepth(node->right);  
      
        /* use the larger one */
        if (lDepth > rDepth)  
            return(lDepth + 1);  
        else return(rDepth + 1);  
    }  
}  

