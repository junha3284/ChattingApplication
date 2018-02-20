#ifndef Node_H_
#define Node_H_

typedef struct _Node Node;
typedef struct _Node *pNode;

struct _Node {
	void *item;
	pNode prev;
	pNode next;
};

#endif
