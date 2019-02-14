//Passing vector by value causes "still reachable" memory leak. Why?

#include<iostream>
#include<vector>

std::vector<int> f()
{
  std::vector<int> result;

  int i=0;
  while(i< 5)
  	{result.push_back(i); i++;}

  return result;
} 

int main(){
	std::vector<int> v = f();

	for(int i : v)
		std::cout << i << "\n" ;

	std::cout<< "Vector length: " << v.size();
	v.clear();
	return 0;
}