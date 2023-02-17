/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	cellLen = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	Cell * tmp;
	while(head!=NULL){
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

int LinkedListPriorityQueue::size() {
	return cellLen;
}

bool LinkedListPriorityQueue::isEmpty() {
	return cellLen == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	Cell * newCell = new Cell;
	newCell -> value = value;
	newCell -> next = NULL;

	cellLen++;

	if(head == NULL){
		head = newCell;
		return;
	}else if(value< head->value){
		newCell->next = head;
		head = newCell;
		return;
	}

	Cell * tmp = head;
	while(tmp -> next != NULL && tmp -> next -> value < value){
		tmp = tmp->next;
	}

	Cell * afterTMP = tmp->next;
	tmp->next = newCell;
	newCell->next = afterTMP;
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("List is empty");
	}
	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	string value = peek();
	Cell * tmp = head;
	head = head -> next;
	delete tmp;
	cellLen --;
	return value;
}

