#include <iostream>
#include <stdlib.h>
#include "Homework2.h"
using namespace std;


int main(){
    srand(314);
    int size = 10000;
    BSTNode *root =new BSTNode(1,rand());

    for(int i=2;i<=size;i++){
    	root=insert(root,2*i-1,rand());
	}
	
    printf("height of the tree is %d\n", root->height);
    printf("30th smallest key is %d\n", select(root,30));
    printf("key 55s rank is %d\n", rank(root,55));
		
}
