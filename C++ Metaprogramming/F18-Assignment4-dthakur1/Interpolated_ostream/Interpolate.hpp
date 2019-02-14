#ifndef INTERPOLATE_HPP
#define INTERPOLATE_HPP

#include <iomanip>

#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

#include <typeinfo>
#include <typeindex>

namespace cs540{

	struct WrongNumberOfArgs : public std::exception {
		const char * what () const throw (){
			return "Wrong num o args";
		}
	};

	// template<class T>
	// auto ffr(T& func)
	// {	
	// 	return static_cast<std::ostream& (*)(std::ostream&)>(func);
	// }

	#define tp std::type_index
	#define ti typeid

	std::vector<std::type_index> manipulators {tp ( ti(std::ios_base &(*)(std::ios_base &)) ),
											   tp ( ti(std::setprecision(5) )),
											   tp ( ti(std::resetiosflags(std::ios_base::basefield) )),
											   tp ( ti(std::setiosflags(std::ios_base::hex))),
											   tp ( ti(std::setbase(16)) ),
											   tp ( ti(std::setw(13)) ),
											   tp ( ti(std::setfill('-')) )
											   // tp ( ti() ),
											   // tp ( ti() ),
											   // tp ( ti() )			
									  }; 

	template <typename... Ts>
	struct helperClass{
		std::string _fmtStr;
		std::tuple<Ts...> _argsTuple;

		helperClass() : _fmtStr("") {}

		helperClass(const char* fmtStr) : _fmtStr(fmtStr){}

		helperClass(const char* fmtStr, std::tuple<Ts...>argsTuple) : _fmtStr(fmtStr), _argsTuple(argsTuple){}

		template <typename... Xs>
		friend std::ostream& operator<<(std::ostream&, const helperClass<Xs...>&);
	};


	std::ostream& printHelper(std::ostream &out, std::string fmtStr, size_t currentIndex){
		auto localIndex = currentIndex;
		while(localIndex < fmtStr.size())
		{
			if(fmtStr[localIndex] == '\\'  &&  fmtStr[localIndex+1] == '%'){
				out << "%";
				localIndex += 2;
				continue;
			}
			if(fmtStr[localIndex] == '%'){
				throw WrongNumberOfArgs();
			}

			out << fmtStr[localIndex];
			++localIndex;
		}
		return out;
	}

	template <typename T, typename... Ts>
	std::ostream& printHelper(std::ostream &out, std::string fmtStr, size_t currentIndex, T& first, Ts&... rest){
		auto localIndex = currentIndex;
		auto isManip = std::find(manipulators.begin(), manipulators.end(), std::type_index(typeid(T)));
		if(isManip != std::end(manipulators) ){
			out << first;
			printHelper(out, fmtStr, localIndex, rest...);
			return out;
		}
		while(localIndex < fmtStr.size()){

			if(fmtStr[localIndex] == '\\'  &&  fmtStr[localIndex+1] == '%'){
				out << "%";
				localIndex += 2;
				continue;
			}

			if(fmtStr[localIndex] == '%'){
				out << first;
				printHelper(out, fmtStr, ++localIndex, rest...);
				return out;
			}
			else
				out << fmtStr[localIndex];
			
			++localIndex;
		}

		throw WrongNumberOfArgs();
		return out;
	}

	template <typename... Ts, std::size_t... Is>
	std::ostream& print(std::ostream& out, const helperClass<Ts...>& helperObject, std::index_sequence<Is...>)
	{
		printHelper(out, helperObject._fmtStr, 0, std::get<Is>(helperObject._argsTuple)...);
		return out;
	}


	template <typename... Ts>
	std::ostream& operator<<(std::ostream& out, const helperClass<Ts...>& helperObject){
		print(out, helperObject, std::index_sequence_for<Ts...>{});
		return out;
	}
   	

	template <typename... Ts>
	auto Interpolate(const char* fmtStr, Ts... args){
		return helperClass<Ts...>(fmtStr, std::make_tuple(args...));
	}


}

#endif 	