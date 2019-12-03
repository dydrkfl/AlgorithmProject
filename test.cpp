#include <cstdio>
#include "RBtree.h"

int main(){
	Tree T;
	Path p;
	p.source = 1;
	char s[20] = "hi";
	int id = 0;
	Node *t;
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.printBST();
	
	printf("# of nodes %d, height %d\n",T.num_node, T.getHeight());
	
	int check = T.remove(4);
	if(check == 0) // 4 가 없음
		printf("4가 없음\n");
	else
		printf("4를 성공적으로 삭제\n"); 
	T.printBST();
	printf("# of nodes %d, height %d\n",T.num_node, T.getHeight());
	
	
	t = T.search(T.root, id, T.root, 1);
	printf("\n");
	if(t->reserve_id != id){
		printf("%d 는 존재 x\n",id);
	}else{
		printf("%d %d %s\n", t->reserve_id, t->path.source, t->name);
	}
	return 0;
}

