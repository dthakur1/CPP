#include<iostream>
#include<vector>
#include <string>
#include<stdlib.h>

#include<iostream>
#include<utility>
#include<string.h>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<stdexcept>

#include "SkipListTest.hpp"

int main(){
	cs540::SkipList<std::string, int> l1(10);

	std::string alp("ABC-GHI-DEFJKLOPMNSTQRWXVUZY");
	int i=0; 

	std::pair<std::string, int> val{"A", 1}; 

	for(auto itr = alp.begin(); itr < alp.end(); itr++, i++){
		val.first = *itr;
		val.second = i;
		l1.insert( val );
	}	

	val.first = "P";
	val.second = 5;
	l1.erase(val);
	l1.print();
}