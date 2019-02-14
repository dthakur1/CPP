
//Ideas taken from here: https://stackoverflow.com/a/38478032
//No code copy though.

#ifndef FUNC_HPP
#define FUNC_HPP

#include <iostream>	//if DEBUG messages
#include <stdexcept>	//exception
#include <string.h>	//memcpy

namespace cs540{
	struct BadFunctionCall : public std::exception{
		const char * what () const throw (){
	    	return "BadFunctionCall";
    	}
	};

	template <typename T>
	class Function;

	template <typename R, typename... Args>
	class Function<R(Args...)>
	{
	    template <typename Functor>
	    static R FunctionPointer(char* fnAddr, Args&&... args)
	    {
	    	auto fnc(reinterpret_cast<Functor*>(fnAddr));
	        return (*fnc)(std::forward<Args>(args)...);
	    }
	    R (*callFunction)(char*, Args&&...);	//char * because sizeof &lambda can be 1 byte?
	    char data_ptr[8];		//Lazy coding: Change later
	public:
	    Function() : callFunction(nullptr)
	    {}

	    template <typename Functor>
	    Function(Functor f)
	    {
	    	callFunction = FunctionPointer<Functor>;
	        memcpy(this->data_ptr, reinterpret_cast<char*>(&f), 8);
	    }

	    Function(Function const& rhs)
	        : callFunction(rhs.callFunction)
	    {
	        if (this->callFunction) {
	            memcpy(this->data_ptr, rhs.data_ptr, 8);
	        }
	    }

	    Function &operator=(Function const& rhs)
	    {
	    	callFunction = (rhs.callFunction);
	    	if (this->callFunction)
	            memcpy(this->data_ptr, rhs.data_ptr, 8);
	        return *this;	
	    }

	    ~Function()	{}

	    R operator()(Args&&... args)
	    {
	        if(callFunction == nullptr)
	                throw BadFunctionCall();
	        else                
	            return callFunction(this->data_ptr, std::forward<Args>(args)...);
	    }

	    explicit operator bool() const{
	    	return callFunction != nullptr;
	    }

	    template <typename ResultType, typename... ArgumentTypes>
		friend bool operator==(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t);
		template <typename ResultType, typename... ArgumentTypes>
		friend bool operator==(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> &f);

		template <typename ResultType, typename... ArgumentTypes>
		friend bool operator!=(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t);
		template <typename ResultType, typename... ArgumentTypes>
		friend bool operator!=(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> &f);
	};

    template <typename ResultType, typename... ArgumentTypes>
	bool operator==(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t){
		return f.callFunction==nullptr;
	}
	template <typename ResultType, typename... ArgumentTypes>
	bool operator==(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> &f){
		return f.callFunction==nullptr;		
	}

	template <typename ResultType, typename... ArgumentTypes>
	bool operator!=(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t){
		return f.operator bool();
	}
	template <typename ResultType, typename... ArgumentTypes>
	bool operator!=(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> &f){
		return f.operator bool();
	}
}

#endif