#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <vector>
#include <initializer_list>
#include <chrono> 

#define DEBUG 0

 
class Timer
{
//reference : https://www.learncpp.com/cpp-tutorial/8-16-timing-your-code/
private:
	// Type aliases to make accessing nested type easier
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::milli >;
	
	std::chrono::time_point<clock_t> m_beg;
 
public:
	Timer() : m_beg(clock_t::now())
	{
	}
	
	void reset()
	{
		m_beg = clock_t::now();
	}
	
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};



namespace cs540
{
	class Array
	{
		std::vector<MyInt>* MyIntVP;
	public:
		Array(){
			if(DEBUG)	std::cout << "Array()\n";		
		}

		Array(const std::vector<int>& vec){
			if(DEBUG)	std::cout << "Array(const std::vector<int>& vec)\n";
			MyIntVP = new std::vector<MyInt>;
			for(auto i : vec)
				MyIntVP->push_back(MyInt(i));
		}

		Array(std::initializer_list<int> list){
			if(DEBUG)	std::cout << "Array(std::initializer_list<MyInt> list)\n";
			MyIntVP = new std::vector<MyInt>;
			for(auto i : list){
				MyIntVP->push_back(MyInt(i));
				if(DEBUG) std::cout << i;
			}
		}

		//CopyConstr
		Array(const Array& a){
			if(DEBUG)	std::cout << "Array(const Array& a)\n";
			MyIntVP = new std::vector<MyInt>();
			for(auto i = a.MyIntVP->begin(); i != a.MyIntVP->end(); i++ )
				MyIntVP->push_back(*i);
		}
		//MoveConstr
		Array(Array &&a){
			if(DEBUG)	std::cout << "Array(Array &&a)\n";
			MyIntVP = a.MyIntVP;
			a.MyIntVP = nullptr;	//Do. Or do not. There is no try.
		}
		//Copy assignment
		Array &operator=(const Array& a){
			if(DEBUG)	std::cout << "Array &operator=(const Array&)\n";		

			if(&a == this) return *this;

			delete this->MyIntVP;
			MyIntVP = new std::vector<MyInt>;

			for(auto i = a.MyIntVP->begin(); i != a.MyIntVP->end(); ++i)
				MyIntVP->push_back(*i);

			return *this;
		}
		//Move assignment
		Array &operator=(Array&& a){
			if(DEBUG)	std::cout << "Array &operator=(Array&& a)\n";

			if(&a == this) return *this;

			delete this->MyIntVP;

			MyIntVP = a.MyIntVP;
			a.MyIntVP = nullptr;

			return *this;
		}

		static void move_performance_test(){
			if(DEBUG)	std::cout << "static int move_performance_test()\n";
			std::cout << "Running performance test:\n";

			std::vector<int> vec;
			std::cout << "Generating cs540::Array of 10,000,000 MyInt objects\n";
			for(int i = 0; i < 10000000; i++) vec.push_back(i);

			Array original(vec);

			Timer tC;
			Array aC{original};	//Copy constructor
			std::cout << "Time taken to Copy Construct the Array:	" << tC.elapsed() << " milliseconds" <<std::endl;

			tC.reset();
			Array aM{std::move(original)};	//Move constructor
			std::cout << "Time taken to Move Construct the Array:	" << tC.elapsed() << " milliseconds" << std::endl;			

		}

		friend std::ostream& operator<<(std::ostream& op, const Array& a){
			if(DEBUG)	std::cout << "std::ostream& operator<<(std::ostream& op, const Array& a)\n";		
			for(auto i = a.MyIntVP->begin(); i != a.MyIntVP->end(); ++i)
				op << *i << ( (i == a.MyIntVP->end()-1) ? "" : ", " );
			return op;
		}

		~Array(){
			if(DEBUG)	std::cout << "~Array()\n";
			delete MyIntVP;
		}
		
	};

}



#endif