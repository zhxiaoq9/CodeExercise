#include <iostream>
using namespace std;


struct listNode{
	int val;
	listNode *next;
	listNode(int x) :val(x), next(NULL){}
};


listNode *removeElements(listNode *head, int val){
	//find the fist element that does not equal to val
	while (head != NULL && head->val == val){
		head = head->next;
	}
	//check NULL
	if (head == NULL){
		return NULL;
	}
	
	listNode *pre = head;
	listNode *cur = head->next;
	while (cur != NULL){
		if (cur->val == val){
			//remove node
			pre->next = cur->next;
		}
		else{
			pre = cur;
		}
		cur = cur->next;
	}
	return head;
}
