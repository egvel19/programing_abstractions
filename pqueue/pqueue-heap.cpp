/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"



HeapPriorityQueue::HeapPriorityQueue() {
	initialSize = SIZE;
	pQue = new string[initialSize];
	count = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] pQue;
}

int HeapPriorityQueue::size() {
	return count;

}

bool HeapPriorityQueue::isEmpty() {
	return count==0;
}

void HeapPriorityQueue::enqueue(string value) {
	if(count == initialSize -1){
		resizeQue();
	}
	count ++;
	pQue[count] = value;
	bubbleUp(count);
}

string HeapPriorityQueue::peek() {
	if(isEmpty()) error("List is empty");
	return pQue[1];
}

string HeapPriorityQueue::dequeueMin() {
	string min = peek();
	pQue[1] = pQue[count];
	count--;
	bubbleDown(1);
	return min;
}

void HeapPriorityQueue::bubbleUp(int inx){
	if (inx<=1) return;
	int aboveInx;
	if(inx%2==0){
		aboveInx=inx/2;
	}else{
		aboveInx = (inx-1)/2;
	}
    if (pQue[inx]<pQue[aboveInx]){
        swap(pQue[aboveInx],pQue[inx]);
        bubbleUp(aboveInx);
    }
}

void HeapPriorityQueue::bubbleDown(int inx){
	int firstChildInx = 2*inx;
	int secondChildInx = 2*inx +1;
	if(firstChildInx<=count || secondChildInx<=count){
		int minInx = -1;
		if(pQue[firstChildInx]<pQue[secondChildInx] && firstChildInx<=count){
			minInx = firstChildInx;

		}else if(pQue[firstChildInx]>=pQue[secondChildInx] && secondChildInx<=count){
			minInx = secondChildInx;
		}
	
		if(minInx >= 0 && pQue[inx] > pQue[minInx]){
			swap(pQue[minInx], pQue[inx]);
			bubbleDown(minInx);
		}
	}
}


void HeapPriorityQueue::resizeQue(){
	initialSize = initialSize*2;
	string* tmpData = new string[initialSize];
	for (int i = 1; i <= count; i++){
		tmpData[i] = pQue[i];
	}
	delete[] pQue;
	pQue = tmpData;
}