#ifndef ARRAY_HPP_
#define ARRAY_HPP_

#include <stdexcept>
#include <iostream>
#include <assert.h>
#include <array>

namespace cs540 {

struct OutOfRange : public std::exception {
	const char * what () const throw (){
		return "Bad Index";
	}
};


template <typename T, size_t D1, size_t... Dims>
class Array {
public :
	using ValueType = T;
	static_assert(D1>0, "Dimension is less than or equal to zero\n");

	using myType = Array<T, D1, Dims...>;
	using nextType = Array<T, Dims...>;

	nextType ARR[D1];
	size_t previousDimension;
	
	Array(){
		ARR[0].previousDimension = D1;
	}

	Array(const myType &arr){		//Possible bug
		for(size_t i=0; i<D1; i++)
			ARR[i] = arr.ARR[i];
	}
	
	template <typename T2>
	Array(const Array<T2, D1, Dims...>& arr) {
		for(size_t i=0; i<D1; i++)
			ARR[i] = arr.ARR[i];
	}
//Operators

	myType &operator=(myType &arr){
		if(this == &arr){
			// std::cout << "same\n";
			return *this;
		}
		for(size_t i=0; i<D1; i++)
			ARR[i] = arr.ARR[i];
		return *this;
	}	

	template <typename T2>
	myType &operator=( const Array<T2, D1, Dims...>& arr){
		for(size_t i=0; i<D1; i++)
			ARR[i] = arr.ARR[i];
		return *this;
	}	
	

	nextType &operator[](const size_t ind){
		if(ind >= D1) {
			throw OutOfRange();
		}
		return ARR[ind];
	}

	const nextType &operator[](const size_t ind) const{
		if(ind >= D1) {
			throw OutOfRange();
		}
		return ARR[ind];
	}

//Iterators

	#include "IteratorsRecursive.inl"
};

template <typename T, size_t D1>
class Array<T, D1>{
public:
	static_assert(D1>0, "Dimension is less than or equal to zero\n");
	using myType = T[D1];
	using nextType = T;

	nextType ARR[D1];

	size_t previousDimension;
	using ValueType = T;

	Array(){
		// std::cout << "previousDimension = " << previousDimension << std::endl;
	}

	Array(const myType &arr){		//Possible bug
		for(size_t i=0; i<D1; i++)
			ARR[i] = arr.ARR[i];
	}

	template <typename T2>
	Array(const Array<T2, D1>& arr) {
		for(size_t i=0; i<D1; i++)
			ARR[i] = static_cast<T>(arr.ARR[i]);
	}

//Operators

	Array<T, D1> &operator=(myType &arr){
		if(this == &arr){
			std::cout << "sameBase\n";
			return *this;
		}
		for(size_t i=0; i<D1; i++)
			ARR[i] = arr.ARR[i];
		return *this;
	}	

	template <typename T2>
	Array<T, D1> &operator=(const Array<T2, D1>& arr){
		for(size_t i=0; i<D1; i++)
			this->ARR[i] = static_cast<T>(arr.ARR[i]);
		return *this;
	}	

	nextType &operator[](const size_t ind){
		if(ind >= D1) {
			throw OutOfRange();
		}
		return ARR[ind];
	}

	const nextType &operator[](const size_t ind) const{
		if(ind >= D1) {
			throw OutOfRange();
		}
		return ARR[ind];
	}
//Iterators
	#include "IteratorsBase.inl"
};


}
#endif /* ARRAY_HPP_ */