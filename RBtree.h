#include <cstdio>
#include <cstring>
#include "Path.h"

typedef struct SortArray{
	int key;
	int height;
}SA;

SA sortArray[64];
int SAsize = 0;
char str[24][255]; // maximum depth = 20+4 [base + insert ],  -> skewed linear array


class Node{
	/* 이름을 UI에서 만들어서 줄지 아니면 여기서 initial 할지 */ 
public:
	int reserve_id;
	char name[32];
	Path path;
	
	Node* parent;
	Node* left;
	Node* right;
	int color;
	
	Node(){
		reserve_id = -1;
		color = 0; // 1 - red, 0 - black
		parent = NULL;
		left = NULL;
		right = NULL;
	}
	
	Node(int id, char *na, Path p){
		reserve_id = id;
		path = p;
		strcpy(name, na);
	}
};


class Tree{
public:
	// number of node, height of tree, last reservation id 
	int num_node, height, rid;
	Node *root, *NIL;
	Tree(){ // Constructor
		num_node = 0;
		height = 0;
		rid = 1;
		NIL = new Node();
		NIL->left = NIL;
		NIL->right = NIL;
		NIL->parent = NIL;
		root = NIL;
	}
	
	~Tree(){ // Destructor
		freeBST(root);
		delete(NIL);
	}
	
	int getHeight(){
		height = 0;
		dfs(root,0);
		return height;
	}
	
	void leftRotate(Node *x){
		Node *y = x->right;
		x->right = y->left;
		if(y->left != NIL)
			y->left->parent = x;
		y->parent = x->parent;
		if(x->parent == NIL)
			root = y;
		else{
			if(x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
	
	void rightRotate(Node *x){
		Node *y = x->left;
		x->left = y->right;
		if(y->right != NIL)
			y->right->parent = x;
		y->parent = x->parent;
		if(x->parent == NIL)
			root = y;
		else{
			if(x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}
		y->right = x;
		x->parent = y;
	}

	int insert(char *name, Path p){
		Node* y = NIL;
		Node* x = root;
		while(x != NIL){
			y = x;
			if(rid < x->reserve_id)
				x = x->left;
			else
				x = x->right;
		}
		Node *temp = new Node(rid, name, p);
		rid++;
		num_node++;
		temp->left = NIL;
		temp->right = NIL;
		temp->parent = y;
		if(y != NIL){
			if(temp->reserve_id < y->reserve_id)
				y->left = temp;
			else
				y->right = temp;
		}
		if(root == NIL)
			root = temp;
		
		temp->color = 1; // 1 - red, 0 - black
		insertFixup(temp);
		/* return reservation id */
		return temp->reserve_id;	
	}
	
	void insertFixup(Node *z){
		Node *y;
		while(z->parent != NIL && z->parent->color == 1){ // red , red
			if(z->parent == z->parent->parent->left){
				y = z->parent->parent->right;
				//if(y != NULL && y->color == 1){ // case 1
				if(y->color == 1){
					z->parent->color = 0;
					y->color = 0;
					z->parent->parent->color = 1;
					z = z->parent->parent; // move up 2 level
				}else{ // color - black -> case 2 or 3
					if(z == z->parent->right){ // case 2
						z = z->parent;
						leftRotate(z);
					}
					z->parent->color = 0;
					z->parent->parent->color = 1;
					rightRotate(z->parent->parent);
				}
			}else{ // reverse
				y = z->parent->parent->left;
				if(y->color == 1){ // case 1
					z->parent->color = 0;
					y->color = 0;
					z->parent->parent->color = 1;
					z = z->parent->parent; // move up 2 level
				}else{ // color - black -> case 2 or 3
					if(z == z->parent->left){ // case 2
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = 0;
					z->parent->parent->color = 1;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = 0; // make root black.
	}
	
	
	void dfs(Node* n, int d){
		if(n == NIL)
			return;
		if(d > height)
			height = d;
		dfs(n->left,d+1);
		dfs(n->right,d+1);
	}
	
	void inorder(Node *n, int d){
		if(n == NIL)
			return;
		inorder(n->left,d+1);
		sortArray[SAsize].key = n->reserve_id;
		sortArray[SAsize].height = d;
		SAsize++;
		inorder(n->right,d+1);
	}
	
	void printBST(){
		int i,j;
		height = 0;
		dfs(root,0);
		for(i = 0; i<=height; i++){
			sprintf(str[i]," %80s"," ");
		}
		SAsize = 0;
		inorder(root, 0);
		char b[10];
		int h, key;
		for(i = 0; i<SAsize; i++){
			h = sortArray[i].height;
			key = sortArray[i].key;
			sprintf(b,"%02d",key);
			for(j = 0; j<2; j++){
				str[h][2*i+j] = b[j];
			}
		}
		for(i = 0; i<=height; i++){
			printf("level: %2d, %s\n",i,str[i]);
		}
	}
	
	/*  opt 1이면 찾는 과정 출력, 0이면 출력x   .  그냥 출력해서 test용임. */
	Node* search(Node* n, int id, Node *p, int opt){
		if(n != NIL){
			if(opt == 1)
				printf("%d ",n->reserve_id);
			if(n->reserve_id == id)
				return n;
			else{
				if(id < n->reserve_id){
					return search(n->left,id,n,opt);
				}else{
					return search(n->right,id,n,opt);
				}
			}
		}else
			return p;
	}
		
	Node* Successor(Node *x){
		Node *y;
		if(x->right != NIL){
			y = x->right;
			while(y->left != NIL)
				y = y->left;
		}else{
			y = x->parent;
			while(y != NIL && x == y->right){
				x = y;
				y = y->parent;
			}
		}
		return y;
	}
		
	int remove(int val){
		/* search -> true -> delete  */
		Node *z = search(root,val,NIL,0);
		if(z->reserve_id != val) // 없는 경우 
			return 0;
		
		num_node--; 
		Node *y,*x;
		if(z->left == NIL || z->right == NIL) // 0 or 1 child
			y = z;
		else // two children
			y = Successor(z);
		if(y->left != NIL)
			x = y->left;
		else
			x = y->right;
		x->parent = y->parent;
		if(y->parent == NIL)
			root = x;
		else{
			if(y == y->parent->left)
				y->parent->left = x;
			else
				y->parent->right = x;
		}
		if(y != z)
			z->reserve_id = y->reserve_id;
		
		if(y->color == 0)
			deleteFixup(x);
		delete(y);
		
		return 1; // boolean 써도 되는지 모르겠어서 successful remove -> 1,    unsuccessful -> 0
	}

	void deleteFixup(Node *x){
		Node *w;
		while(x != root && x->color == 0){
			if(x == x->parent->left){
				w = x->parent->right; // w cannot be null
				if(w->color == 1){ //case 1
					w->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if(w->left->color == 0 && w->right->color == 0){ // case 2
					w->color = 1;
					x = x->parent;
				}else{
					if(w->right->color == 0){ // case 3
						w->left->color = 0;
						w->color = 1;
						rightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color; // case 4
					x->parent->color = 0;
					w->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}else{
				w = x->parent->left;
				if(w->color == 1){ //case 1
					w->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if(w->left->color == 0 && w->right->color == 0){ // case 2
					w->color = 1;
					x = x->parent;
				}else{
					if(w->left->color == 0){
						w->right->color = 0;
						w->color = 1;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = 0;
					w->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}	
	
	void freeBST(Node* temp){
		if(temp == NIL)
			return;
		if(temp->left != NIL)
			freeBST(temp->left);
		if(temp->right != NIL)
			freeBST(temp->right);
		delete(temp);
	}
};
