#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP


#include <atomic>
#include <iostream>
#include <assert.h>
#include <mutex>
// #include <stdatomic.h>

namespace cs540{

#define DEBUG 0

std::mutex mut;

template <typename U>
void typeInfoDelete(void *objectP){
	delete static_cast<U*>(objectP);
}

template <typename T>
class SharedPtr{

public:
	//Make these private and have getters and setters
	int *refCount = nullptr;
	void *ref = nullptr;
	void (*deleteFunction)(void *);

	SharedPtr() : refCount(nullptr), ref(nullptr)  {
		if(DEBUG)		std::cout << "SharedPtr()\n" ;
	}


	template <typename U>
	explicit SharedPtr(U* objectP){
		if(DEBUG)		std::cout << "explicit SharedPtr(U* object)\n" ;
		mut.lock();
		if(DEBUG)		std::cout << "A1\n";
		ref = objectP;
		if(DEBUG)		std::cout << "A2\n";
		refCount = new int;
		if(DEBUG)		std::cout << "A3\n";
		*refCount = 1;		
		if(DEBUG)		std::cout << "A4\n";
		deleteFunction = typeInfoDelete<U>;
		mut.unlock();
	}

	SharedPtr(const SharedPtr& object){
		if(DEBUG)		std::cout << "SharedPtr(const SharedPtr &object)\n" ;
//reset()?
		mut.lock();
		ref = object.ref;
		refCount = object.refCount;
		deleteFunction = object.deleteFunction;
		if(object.refCount != nullptr)	*refCount += 1; 
		mut.unlock();
	}

	template <typename U>
	SharedPtr(const SharedPtr<U>& object){
		if(DEBUG)		std::cout << "SharedPtr(const SharedPtr<U>& object)\n" ;
//reset()?
		ref = object.ref;
		deleteFunction = object.deleteFunction;
		// deleteFunction = typeInfoDelete<U>;
		mut.lock();
		refCount = object.refCount;
		if(object.refCount != nullptr)	*refCount += 1;	
		mut.unlock();
	}

	SharedPtr(SharedPtr &&object){
		mut.lock();
		ref = object.ref;				object.ref = nullptr;
		refCount = object.refCount;		object.refCount = nullptr;
		deleteFunction = object.deleteFunction;	
		mut.unlock();
	}

	template <typename U> 
	SharedPtr(SharedPtr<U> &&object){
		mut.lock();
		ref = object.ref;				object.ref = nullptr;
		refCount = object.refCount;		object.refCount = nullptr;
		deleteFunction = object.deleteFunction;	
		mut.unlock();
	}
//////////////////////////////////////////////////////////////////////// Operators
	SharedPtr &operator=(const SharedPtr& object){
		if(DEBUG)		std::cout << "&operator=(const SharedPtr& object)\n" ;

		if(&object == this) return *this;
		
		this->reset();
		mut.lock();
		ref = object.ref;
		refCount = object.refCount;
		if(refCount != nullptr)		*refCount += 1;		
		deleteFunction = object.deleteFunction;
		mut.unlock();
		return *this;
	}
	template <typename U>
	SharedPtr &operator=(const SharedPtr<U>& object){
		if(DEBUG)		std::cout << "&operator=(const SharedPtr<U>& object)\n" ;
		//Can't compare address here for self-assignment-check coz objects of different types
		if(ref == object.ref && refCount == object.refCount) return *this;

		this->reset();
		mut.lock();
		ref = object.ref;
		refCount = object.refCount;
		if(refCount != nullptr)		*refCount += 1;
		deleteFunction = object.deleteFunction;
		mut.unlock();
		return *this;
	}	

	SharedPtr &operator=(SharedPtr &&object){
		if(&object == this)	return *this;

		this->reset();
		mut.lock();
		ref = object.ref;	object.ref = nullptr;
		refCount = object.refCount;	object.refCount = nullptr;
		deleteFunction = object.deleteFunction;
		mut.unlock();
		return *this;
	} 	
	
	template <typename U> SharedPtr &operator=(SharedPtr<U> &&object){
		if(ref == object.ref && refCount == object.refCount) return *this;

		this->reset();
		mut.lock();
		ref = object.ref;	object.ref = nullptr;
		refCount = object.refCount;	object.refCount = nullptr;
		deleteFunction = object.deleteFunction;
		mut.unlock();
		return *this;		
	}

	T &operator*() const{
		return *static_cast<T*>(ref);
	}

	T *operator->() const{
		return static_cast<T*>(ref);
	}

////////////////////////////////////////////////////////////////////////// Other member functions
	void reset(){
		//Checks if this is the last reference. If it is, delete all the allocated memory
		//Otherwise, reduce the refCount by one.
		mut.lock();
		if(refCount != nullptr)	{
			*refCount -= 1;
			if(*refCount <= 0){// If the owned resource has no other references, it is deleted.
				deleteFunction(ref);//assuming ref != nullptr
				ref = nullptr;	
				delete refCount;
				refCount = nullptr;
			}
		}
		mut.unlock();
		ref = nullptr;
		refCount = nullptr;
		return;
	}

	template <typename U>
	void reset(U* objectP){
		mut.lock();
		if(refCount != nullptr)	{
			*refCount -= 1;
			if(*refCount <= 0){// If the owned resource has no other references, it is deleted.
				deleteFunction(ref);//assuming ref != nullptr
				ref = nullptr;	
				delete refCount;
				refCount = nullptr;
			}
		}
		ref = objectP;
		refCount = new int;
		*refCount = 1;		
		deleteFunction = typeInfoDelete<U>;
		mut.unlock();
	}

	T* get() const{
		return static_cast<T*>(ref);
	}

	explicit operator bool() const{
		return (ref == nullptr)	? false : true;
	}
//////////////////////////////////////////////////////////////////////////////// Destructor
	~SharedPtr(){
		mut.lock();
		if(DEBUG)		std::cout << "~SharedPtr()\n" ;
		if(ref != nullptr){
			if(DEBUG)		std::cout << "ref != nullptr\n" ;			
			*refCount -= 1;
			if(*refCount <= 0){
				if(DEBUG)		std::cout << "refCount <= 0\n" ;
				delete refCount;	//This doesn't work
				refCount = nullptr;
				deleteFunction(ref);
				ref = nullptr;
				// delete refCount;	//But this does?!?
				// refCount = nullptr;
			}
		}

		mut.unlock();
	}
/////////////////////////////////////////////////////////////////////////////// Non-member (Free) Functions
	template<typename T1, typename T2>
	friend bool operator==(SharedPtr<T1> &, SharedPtr<T2> &);
	template <typename T1>
	friend bool operator==(const SharedPtr<T1> &, std::nullptr_t);
	template <typename T1>
	friend bool operator==(std::nullptr_t, const SharedPtr<T1> &);

	template<typename T1, typename T2>
	friend bool operator!=(SharedPtr<T1> &, SharedPtr<T2> &);	
	template <typename T1>
	friend bool operator!=(const SharedPtr<T1> &, std::nullptr_t);
	template <typename T1>
	friend bool operator!=(std::nullptr_t, const SharedPtr<T1> &);

	template <typename T1, typename T2>
	friend SharedPtr<T1> static_pointer_cast(const SharedPtr<T2> &sp);

	template <typename T1, typename T2>
	friend SharedPtr<T1> dynamic_pointer_cast(const SharedPtr<T2> &sp);

};
	// #include "freeFunctions.inl"
	template<typename T1, typename T2>
	bool operator==(SharedPtr<T1> &A, SharedPtr<T2> &B){	return (A.ref == B.ref) && (A.refCount == B.refCount);	}
	template <typename T1>
	bool operator==(const SharedPtr<T1> &A, std::nullptr_t){ return A.ref==nullptr;	}
	template <typename T1>
	bool operator==(std::nullptr_t, const SharedPtr<T1> &A){ return A.ref==nullptr;	}


	template<typename T1, typename T2>
	bool operator!=(SharedPtr<T1> &A, SharedPtr<T2> &B){	return !(A==B);		}
	template <typename T1>
	bool operator!=(const SharedPtr<T1> &A, std::nullptr_t){  return A.ref!=nullptr;		}
	template <typename T1>
	bool operator!=(std::nullptr_t, const SharedPtr<T1> &A){  return A.ref!=nullptr;		}



	template <typename T1, typename T2>
	SharedPtr<T1> static_pointer_cast(const SharedPtr<T2> &sp){
		return SharedPtr<T1>(sp);
		//have another constructor and increase refCount inside that: same as copy construction though.
		// return SharedPtr<T1>(sp.refCount, sp.ref, sp.deleteFunction);
		//This might be a problem
		// return SharedPtr<T1>(sp.refCount, sp.ref, typeInfoDelete<T1>);

		//Why the hell does this not work!?!
		// SharedPtr<T1> rv;
		// rv.ref = sp.ref;
		// rv.refCount = sp.refCount;
		// rv.deleteFunction = sp.deleteFunction;
		// // rv.deleteFunction = typeInfoDelete<T1>;
		// mut.lock();
		// if(rv.refCount != nullptr)	rv.refCount += 1;
		// mut.unlock();
		// if(DEBUG)		std::cout<< "static_pointer_cast(const SharedPtr<T2> &sp)\n";
		// return rv;
	}

	template <typename T1, typename T2>
	SharedPtr<T1> dynamic_pointer_cast(const SharedPtr<T2> &sp){
		if(DEBUG)		std::cout<< "dynamic_pointer_cast(const SharedPtr<T2> &sp)\n";
		SharedPtr<T1> rv;

		// Check if dynamic cast works
		T2 *foo = static_cast<T2 *>(sp.ref);
		T1 *bar = dynamic_cast<T1 *>(foo);
		if(bar != nullptr){
		if(DEBUG)		std::cout<< "dynamic_cast successful\n";
		return SharedPtr<T1>(sp);

		// This works but not in static_cast_pointer
		// rv.ref = sp.ref;
		// rv.refCount = sp.refCount;
		// mut.lock();
		// *rv.refCount += 1;
		// mut.unlock();
		//This might be a problem. Which one of these is correct?(apparently, both work)
		// rv.deleteFunction = typeInfoDelete<T1>;
		// rv.deleteFunction = sp.deleteFunction;
		// return rv;			

		}
		else{
			if(DEBUG)		std::cout<< "dynamic_cast NOT successful\n";
			return rv;	
		}

	}

}

#endif
