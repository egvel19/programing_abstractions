/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals, Vector< Set<string> >& result){
	if(cities.isEmpty()){
		return true;
	}else if(locations.isEmpty()){
		return false;
	}
	if(numHospitals==0){
		return false;
	}
	Set<string> curCities = locations.get(locations.size()-1);  
	locations.remove(locations.size()-1); 

	//without 
	Vector< Set<string> > resultWithout;
	bool without = canOfferUniversalCoverage(cities, locations, numHospitals, resultWithout);
	
	//with
	Vector< Set<string> > resultWith;
	cities -= curCities; 
	bool with = canOfferUniversalCoverage(cities, locations, numHospitals-1, resultWith);
	resultWith.add(curCities);
	
	locations.add(curCities);
	cities+=curCities;

	if(with) result = resultWith;
	if(without) result = resultWithout;
	return with || without;

}


int main() {
    /* TODO: Add testing code here! */
	Set<string> cities;
	cities.add("A");
	cities.add("B");
	cities.add("C");
	cities.add("D");
	cities.add("E");
	cities.add("F");

	Vector< Set<string> > locations;
	Set<string> s1;
	s1.add("A");
	s1.add("B");
	s1.add("C");

	Set<string> s2;
	s2.add("A");
	s2.add("C");
	s2.add("D");

	Set<string> s3;
	s3.add("B");
	s3.add("F");

	Set<string> s4;
	s4.add("C");
	s4.add("E");
	s4.add("F");
	
	locations +=s1,s2,s3,s4;

	int numHospitals = 3;
	Vector< Set<string> > result;
	bool res = canOfferUniversalCoverage(cities, locations, numHospitals, result);
	if(res) cout<<"is possible"<<endl;
	if(!res) cout<<"not possible"<<endl;
	cout<<result<<endl;
	//cout<<"locations:"<<locations<<endl;
	//cout<<"cities: "<<cities<<endl;
    return 0;
}
