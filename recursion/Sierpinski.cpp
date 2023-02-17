/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include <simpio.h>
#include <cmath>


using namespace std;

const int theta = 60;
const int theta2 = -60;
const int theta3 = 180;

GPoint drawNthOrderedTriangle(double edgeLength, GPoint initialPt, GWindow gw, int i, int fractOrder){
	GPoint p1 = gw.drawPolarLine(initialPt, edgeLength, theta);
	GPoint p2 = gw.drawPolarLine(p1, edgeLength, theta2);
	GPoint p3 = gw.drawPolarLine(p2, edgeLength, theta3);
	if(i==0 )return p1;
	if(i==1){
		double hSqr = edgeLength*edgeLength - (edgeLength/2)*(edgeLength/2);
		double h = sqrt(hSqr);
		double x = p1.getX();
		double y = p1.getY() + 2*h;
		GPoint pt(x,y);
		return pt;
	}
	if(i==2 || i==-1) return p3;
}

void drawTriangles(double edgeLength,int fractOrder, GPoint initialPoint,GWindow gw){
	if(fractOrder == 0) return;
	for(int i=0; i<3; i++){
		drawTriangles(edgeLength/2, fractOrder-1, initialPoint, gw);
		initialPoint = drawNthOrderedTriangle(edgeLength, initialPoint, gw, i, fractOrder);
	}
}

int main() {
	GWindow gw;
	double edgeLength = getReal("Enter edge length: ");
	int fractOrder = getInteger("Enter fractal order: ");
	double hSqr = edgeLength*edgeLength - (edgeLength/2)*(edgeLength/2);
	double h = sqrt(hSqr);
	GPoint initialPt(gw.getWidth()/2 - edgeLength/2, gw.getHeight()/2 + h/2);
	GPoint newInitialPoint = drawNthOrderedTriangle( edgeLength, initialPt, gw, -1, fractOrder);
	drawTriangles(edgeLength/2, fractOrder, newInitialPoint, gw);
    return 0;
}
