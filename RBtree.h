#include <cstring>
#include "Path.h"

/* Node Class, */
class Node{
public:
	/* reservation id, name, path information */
	int reserve_id;
	char name[32];
	Path *path;
	
	/* RBT information, pointer, color */
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
	
	Node(int id, char *na, Path *p){
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
	
	/* get height of tree */
	int getHeight(){
		height = 0;
		dfs(root,0);
		return height;
	}
	
	/* left Rotate */
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
	
	/* right rotate */
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

	/* insert */
	int insert(char *name, Path *p){
		Node* y = NIL;
		Node* x = root;
		// 넣을 위치를 탐색  
		while(x != NIL){
			y = x;
			if(rid < x->reserve_id)
				x = x->left;
			else
				x = x->right;
		}
		/* 새로운 node를 만들고 삽입
		*  rid와 num_node를 증가 
		*/ 
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
				if(y->color == 1){ // case 1
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
	
	/* tree의 height를 찾기 위한 dfs */ 
	void dfs(Node* n, int d){
		/* NIL node 도착하면 마침 	*/ 
		if(n == NIL)
			return;
		if(d > height) // max height를 찾은거면 갱신 
			height = d;
		// 탐색 
		dfs(n->left,d+1);
		dfs(n->right,d+1);
	}
	
	/* 찾고자 하는 값이 있으면 본인을 반환하고,
	* 없는 경우에는 탐색과정에서 마지막으로 도달한 Node를 반환(NIL)
	* search 의 return 된 p의 reserve_id 를 찾고자 하는 값과 비교하여
	* 같으면 존재하는 것임을 인지. 
	*/ 
	Node* search(Node* n, int id, Node *p){
		if(n != NIL){
			if(n->reserve_id == id) // 찾은 경우 
				return n;
			else{
				if(id < n->reserve_id){ // 찾고 있는 값이 작은 경우 
					return search(n->left,id,n);
				}else{
					return search(n->right,id,n);
				}
			}
		}else // 존재하지 않으므로 NIL node return 
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
	/* successful remove -> return 1,  else return 0 */
	int remove(int val){
		/* search -> true -> delete  */
		Node *z = search(root,val,NIL);
		if(z->reserve_id != val) // 지우고자 하는 값이 없는 경우 
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
		if(y->parent == NIL) // root인 경우 
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
		delete(y->path);
		delete(y);
		
		return 1;
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
	
	/* 메모리 초기화, LRV 형태로 진행 */ 
	void freeBST(Node* temp){
		if(temp == NIL)
			return;
		if(temp->left != NIL)
			freeBST(temp->left);
		if(temp->right != NIL)
			freeBST(temp->right);
		delete(temp->path);
		delete(temp);
	}
};
