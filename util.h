#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


using namespace std;
/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{





	set<T> intersection;

	//Finds the smaller set
	if (s1.size() <= s2.size()) {
		//Makes an interator to traverse set
		typename set<T>::iterator itr;
		for (itr = s1.begin(); itr != s1.end(); itr++) {
			//Dereferences the current value and stores it
			T curVal = *itr;

			//Checks if the vlaue is in the other set
			if (s2.find(curVal) != s2.end()) {
				//Adds the value to the intersection set
				intersection.insert(curVal);
			}
		}
	}
	else {
		//Makes an interator to traverse set
		typename set<T>::iterator itr;
		for (itr = s2.begin(); itr != s2.end(); itr++) {
			//Dereferences the current value and stores it
			T curVal = *itr;

			//Checks if the vlaue is in the other set
			if (s1.find(curVal) != s1.end()) {
				//Adds the value to the intersection set
				intersection.insert(curVal);
			}
		}
	}

	return intersection;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	set<T> unionSet;

	//Makes an interator to traverse set
	typename set<T>::iterator itr;
	for (itr = s1.begin(); itr != s1.end(); itr++) {
		//Dereferences the current value and stores it
		T curVal = *itr;

		//Checks if the vlaue is in the other set
		if (s2.find(curVal) != s2.end()) {
			//Deletes every duplicate value from set 2 
			s2.erase(curVal);
		}
		unionSet.insert(curVal);
	}

	//Makes an interator to traverse set
	typename set<T>::iterator itr2;
	//Loops through the non-duplicates of set 2
	for (itr2 = s2.begin(); itr2 != s2.end(); itr2++) {
		T curVal = *itr2;
		//Adds every remaining value of set 2 to the union set
		unionSet.insert(curVal);
	}

	return unionSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
