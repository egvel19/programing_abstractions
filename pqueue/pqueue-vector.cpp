/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

string findMin(Vector<string>&);
string findMinBetweenTwo(string, string,Vector<string>&);
void removeMin(string, Vector<string>&);


VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {
}

int VectorPriorityQueue::size() {
	return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
	return vec.size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	vec.add(value);
}

string VectorPriorityQueue::peek() {
	if(vec.isEmpty()){
		error("List is empty");
	}
	string min = findMin(vec);
	return min;

}

string VectorPriorityQueue::dequeueMin() {
	if(vec.isEmpty()){
		error("List is empty");
	}
	string min = findMin(vec);
	removeMin(min, vec);
	return min;
}

void removeMin(string min, Vector<string>& vec){
	for(int i=0; i<vec.size(); i++){
		if(min == vec.get(i)){
			vec.remove(i);
			break;
		}
	}
}

string findMin(Vector<string>& vec){
	string min = vec.get(0);
	for(int i=1; i<vec.size(); i++){
		string curStr = vec.get(i);
		if(curStr<min){
			min = curStr;
		}
	}
	return min;
}