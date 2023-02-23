#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
	// Base case: head is empty
	if (!head) {
		smaller = NULL;
		larger = NULL;
		return;
	}

	if (head->val <= pivot) {
		smaller = head;
		if (larger) {
			larger = larger->next;
		}
		head = head->next;
		llpivot(head, smaller->next, larger, pivot);
		head = NULL;
		return;
	} else {
		larger = head;
		if (smaller) {
			smaller = smaller->next;
		}
		head = head->next;
		llpivot(head, smaller, larger->next, pivot);
		head = NULL;
		return;
	}


}
