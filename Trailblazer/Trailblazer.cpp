/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include <iostream>
#include "map.h"
#include "random.h"
using namespace std;

//helper function
Loc getLoc(int currInx, int maxN){
	return makeLoc(currInx / maxN, currInx %  maxN);
}

//this method writes result into vector
Vector<Loc> getResult(Loc &end, Map<int, pair<int, double> > &map, int maxN){
	Vector<Loc> reverse;
	Vector<Loc> res;
	Loc curr = end;
	Loc parent = getLoc(map[curr.row * maxN + curr.col].first, maxN);
	while(curr != parent){
		reverse.push_back(curr);
		curr = parent;
		parent = getLoc(map[parent.row * maxN + parent.col].first, maxN);
	}
	reverse.push_back(parent);
	
	for(int i = reverse.size() - 1; i >= 0; i--){
		res.push_back(reverse[i]);
	}
	return res;
}

void markYellowLocWithParent(Loc &loc, Loc &parent, double cost, TrailblazerPQueue<int> &pq,
							 Map<int, pair<int, double> > &map, Grid<double>& world, int maxN, double h){
	int locInx = loc.row * maxN + loc.col;
	int parentInx = parent.row * maxN + parent.col;
	colorCell(world, loc, YELLOW);
	map.put(locInx, std::make_pair(parentInx, cost));
	pq.enqueue(locInx, cost + h);
}


/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */

Vector<Loc> shortestPath(Loc start,Loc end,Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {
	//these structures keep information about indexes,
	//which is unique for each loc (rowN*numRows + colN)
	Set<int> green;
	TrailblazerPQueue<int> pq;
	Map<int, pair<int, double> > map;
	int maxN = max(world.numRows(), world.numCols());

	markYellowLocWithParent(start, start, 0, pq, map, world, maxN, heuristic(start, end, world));

	while(!pq.isEmpty()){
		int currInx = pq.dequeueMin();
		Loc curr = makeLoc(currInx / maxN, currInx %  maxN);
		colorCell(world, curr, GREEN);
		green.add(currInx);
		if(curr == end) break;
		for(int newRow = curr.row - 1; newRow <= curr.row + 1; newRow++){
			for(int newCol = curr.col - 1; newCol <= curr.col + 1; newCol++){
				if(newRow != curr.row || newCol != curr.col){
					if(world.inBounds(newRow, newCol)){
						Loc newLoc = makeLoc(newRow, newCol);
						int newIndex = newLoc.row * maxN + newLoc.col;
						double newCost = map[currInx].second + costFn(curr , newLoc, world);
						if(!green.contains(newIndex) && !map.containsKey(newIndex)){
							markYellowLocWithParent(newLoc, curr, newCost, pq, map, world, maxN, heuristic(newLoc, end, world));
						}else if(!green.contains(newIndex)){
							if(newCost < map[newIndex].second){
								map[newIndex].first = curr.row * maxN + curr.col;
								map[newIndex].second = newCost;
								pq.decreaseKey(newIndex, map[newIndex].second + heuristic(newLoc, end, world));
							}
						}
					}
				}
			}
		}
	}
	return getResult(end, map, maxN);
}


void putEdgesInPq(int numRows, int numCols, TrailblazerPQueue<Edge> &pq){
	for(int i=0; i<numRows; i++){
		for(int j=0; j<numCols; j++){
			if(i ==0 && j==0){
			}else if(i!= 0 && j == 0){
				Loc start = makeLoc(i-1, j);
				Loc end = makeLoc(i,j);
				pq.enqueue(makeEdge(start,end), randomReal(0,1));
			}else if(i==0 && j!= 0){
				Loc start = makeLoc(i, j-1);
				Loc end = makeLoc(i,j);
				pq.enqueue(makeEdge(start,end), randomReal(0,1));
			}else{
				Loc start = makeLoc(i-1,j);
				Loc end = makeLoc(i,j);
				pq.enqueue(makeEdge(start,end), randomReal(0,1));
				start = makeLoc(i,j-1);
				pq.enqueue(makeEdge(start,end), randomReal(0,1));
			}
		}
	}

}


int getCluster(int curr, Vector<int> &clusters){
	if(clusters[curr] == curr){
		return curr;
	}
	clusters[curr] = getCluster(clusters[curr], clusters);
	return clusters[curr];
}

void mergeClusters(int maxN, Edge &curr, Vector<int> &clusters, Vector<int> &sizes, int &Nclust, Set<Edge> &res){
	int start = curr.start.row * maxN + curr.start.col;
	int end = curr.end.row * maxN + curr.end.col;
	int parentOfStartSet = getCluster(start,clusters);
	int parentOfEndSet = getCluster(end,clusters);

	if(parentOfStartSet != parentOfEndSet){
		res.add(curr);
		Nclust--;
		if(sizes[parentOfStartSet] < sizes[parentOfEndSet]) swap(parentOfStartSet, parentOfEndSet);
		clusters[parentOfEndSet] = parentOfStartSet;
		sizes[parentOfStartSet] += sizes[parentOfEndSet];
	}
}


Set<Edge> createMaze(int numRows, int numCols) {
	int Nclust = numRows * numCols;
	
	Vector<int> clusters(Nclust);
	Vector<int> sizes(Nclust);

	for(int i = 0; i < Nclust; i++){
		clusters[i] = i;
		sizes[i] = 1;
	}

	TrailblazerPQueue<Edge> pq;
	putEdgesInPq(numRows, numCols, pq);

	Set<Edge> res;
	while(Nclust > 1){
		Edge curr = pq.dequeueMin();
		mergeClusters(max(numRows, numCols), curr, clusters, sizes, Nclust, res);
	}
    return res;
}



