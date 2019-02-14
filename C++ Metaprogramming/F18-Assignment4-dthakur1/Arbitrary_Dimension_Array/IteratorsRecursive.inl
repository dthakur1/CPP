	class FirstDimensionMajorIterator{
	public:
		typename nextType::FirstDimensionMajorIterator nextItr;
		nextType *arr;
		size_t currentDimension;
		bool endOfIterator;
		
		FirstDimensionMajorIterator(): currentDimension(0), endOfIterator(false){
		}

		bool checkIfEnd(){
			return ( (currentDimension >= D1-1) && nextItr.checkIfEnd() );
		}

		T &operator*(){
			return *nextItr;
		}

		FirstDimensionMajorIterator operator++(){
			if(endOfIterator){ return *this; }
			if(nextItr.checkIfEnd())
			{
				if(currentDimension == D1-1){endOfIterator = true; return *this;}
				currentDimension++;
				nextItr = arr[currentDimension].fmbegin();
				return *this;
			}
			++nextItr;
			return *this;
			}

		FirstDimensionMajorIterator operator++(int){
			FirstDimensionMajorIterator tmp(*this);
			++*this;
			return tmp;
		}

		friend bool operator==(const FirstDimensionMajorIterator &itrA, const FirstDimensionMajorIterator &itrB){
			if(itrA.endOfIterator || itrB.endOfIterator) 
				return itrA.endOfIterator == itrB.endOfIterator;
			else 
				return itrA.nextItr == itrB.nextItr;
		}

		friend bool operator!=(const FirstDimensionMajorIterator &itrA, const FirstDimensionMajorIterator &itrB){
			return !(itrA == itrB);
		}

	};



	class LastDimensionMajorIterator{
	public:
		typename nextType::LastDimensionMajorIterator nextItr[D1];
		nextType *arr;
		size_t currentDimension;
		bool endOfIterator;
		
		LastDimensionMajorIterator(): currentDimension(0), endOfIterator(false){
		}

		bool checkIfEnd(){
			return ( (currentDimension >= D1-1) && nextItr[currentDimension].checkIfEnd() );
		}

		T &operator*(){
			return *nextItr[currentDimension];
		}

		LastDimensionMajorIterator operator++(){
			if(endOfIterator){ return *this; }
			if(nextItr[currentDimension].checkIfEnd())
			{
				if(currentDimension == D1-1){endOfIterator = true; return *this;}
				currentDimension++;
				if(currentDimension == D1){ std::cout<<"Not possible\n"; currentDimension = 0;}
				return *this;
			}
			++nextItr[currentDimension];
			currentDimension++;
			if(currentDimension == D1) currentDimension = 0;
			return *this;
			}

		LastDimensionMajorIterator operator++(int){
			LastDimensionMajorIterator tmp(*this);
			++*this;
			return tmp;
		}

		friend bool operator==(const LastDimensionMajorIterator &itrA, const LastDimensionMajorIterator &itrB){
			if(itrA.endOfIterator || itrB.endOfIterator) 
				return itrA.endOfIterator == itrB.endOfIterator;
			else 
			{
				for(size_t i=0; i<D1; i++){
					if(itrA.nextItr[i] != itrB.nextItr[i]	|| itrA.currentDimension != itrB.currentDimension)
						return false;					
				}
				return true;
			}
		}

		friend bool operator!=(const LastDimensionMajorIterator &itrA, const LastDimensionMajorIterator &itrB){
			return !(itrA == itrB);
		}

	};



	FirstDimensionMajorIterator fmbegin(){
		FirstDimensionMajorIterator  temp;
		temp.nextItr = ARR[0].fmbegin();
		temp.arr = ARR;
		return temp;
	}
	FirstDimensionMajorIterator fmend(){
		FirstDimensionMajorIterator  temp;
		temp.nextItr = ARR[D1-1].fmend();
		temp.endOfIterator = true;
		return temp;
	}


	LastDimensionMajorIterator lmbegin(){
		LastDimensionMajorIterator  temp;
		temp.arr = ARR;
		for(size_t i=0; i<D1; i++)
			temp.nextItr[i] = ARR[i].lmbegin();
		
		return temp;
	}
	LastDimensionMajorIterator lmend(){
		LastDimensionMajorIterator  temp;
		temp.endOfIterator = true;
		return temp;
	}


