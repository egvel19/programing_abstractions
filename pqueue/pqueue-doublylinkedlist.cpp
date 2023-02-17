/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	cellLen = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Cell * cell = head;
	while(cell!=NULL){
		Cell * tmp = cell;
		cell = cell->next;
		delete tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return cellLen;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return cellLen==0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Cell * newCell = new Cell;
	newCell->value = value;
	newCell->next = NULL;
	newCell->prev = NULL;

	if(head!=NULL){
		newCell->next = head;
		head->prev = newCell;
	}
	head = newCell;	
	cellLen ++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()) error("List is empty");

	Cell * cell = head;
	string min = head->value;

	while(cell != NULL){
		if(cell->value < min) min = cell->value;
		cell = cell->next;
	}
	
	return min;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	string min = peek();
	
	Cell * minCell = head;
	while(minCell->value != min){
		minCell = minCell->next;
	}

	if(minCell->prev == NULL && minCell->next == NULL){
		head = NULL;
	} else if(minCell->next == NULL){
		minCell->prev->next = NULL;
	}else if(minCell->prev == NULL){
		head = minCell -> next;
		head->prev = NULL;
	}else{
		minCell->prev->next = minCell->next;
		minCell->next->prev = minCell->prev;
	}
	delete minCell;
	cellLen --;
	return min;
}

