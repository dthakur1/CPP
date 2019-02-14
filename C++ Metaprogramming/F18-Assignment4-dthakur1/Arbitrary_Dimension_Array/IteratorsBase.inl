	class FirstDimensionMajorIterator{
	public:
		nextType* currentPosition;
		size_t currentDimension;
		FirstDimensionMajorIterator() : currentPosition(nullptr), currentDimension(0){
		}

		bool checkIfEnd(){
			if(currentDimension == D1-1)
				return true;
			return false;
		}

		T &operator*(){
			return *currentPosition;
		}

		FirstDimensionMajorIterator operator++(){
			currentPosition++;
			currentDimension++;
			return *this;
		}

		FirstDimensionMajorIterator operator++(int){
			FirstDimensionMajorIterator temp(*this);
			++*this;
			return temp;
		}

		friend bool operator==(const FirstDimensionMajorIterator &itrA, const FirstDimensionMajorIterator &itrB){
			return itrA.currentPosition == itrB.currentPosition;
		}

		friend bool operator!=(const FirstDimensionMajorIterator &itrA, const FirstDimensionMajorIterator &itrB){
			return !(itrA.currentPosition == itrB.currentPosition);
		}

	};


	class LastDimensionMajorIterator{
	public:
		nextType* currentPosition;
		size_t currentDimension;
		LastDimensionMajorIterator() : currentPosition(nullptr), currentDimension(0){
		}

		bool checkIfEnd(){
			if(currentDimension == D1-1)
				return true;
			return false;
		}

		T &operator*(){
			return *currentPosition;
		}

		LastDimensionMajorIterator operator++(){
			currentPosition++;
			currentDimension++;
			return *this;
		}

		LastDimensionMajorIterator operator++(int){
			LastDimensionMajorIterator temp(*this);
			++*this;
			return temp;
		}

		friend bool operator==(const LastDimensionMajorIterator &itrA, const LastDimensionMajorIterator &itrB){
			return itrA.currentPosition == itrB.currentPosition;
		}

		friend bool operator!=(const LastDimensionMajorIterator &itrA, const LastDimensionMajorIterator &itrB){
			return !(itrA.currentPosition == itrB.currentPosition);
		}

	};




	FirstDimensionMajorIterator fmbegin(){
		FirstDimensionMajorIterator  temp;
		temp.currentPosition = &ARR[0];
		return temp;
	}

	FirstDimensionMajorIterator fmend(){
		FirstDimensionMajorIterator  temp;
		temp.currentPosition = &ARR[D1-1]+1;
		return temp;
	}



	LastDimensionMajorIterator lmbegin(){
		LastDimensionMajorIterator  temp;
		temp.currentPosition = &ARR[0];
		return temp;
	}

	LastDimensionMajorIterator lmend(){
		LastDimensionMajorIterator  temp;
		temp.currentPosition = &ARR[D1-1]+1;
		return temp;
	}

