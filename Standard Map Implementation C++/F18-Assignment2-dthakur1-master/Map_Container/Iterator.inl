

	class Iterator{
	    public:
	    	friend class Map<K, O>;	//Is this stupid?
		      Iterator(SkipNode<K, O>* n, SkipList<K, O> *l){	node = n; iterlist = l;	}
		      Iterator(const Iterator &it)	{node = it.node; iterlist = it.iterlist;}
		      Iterator& operator=(const Iterator& itr){
	   								node = itr.node;
								    iterlist = itr.iterlist;
								    return *this;
			  }
		      Iterator& operator++(){
								    if(node == nullptr) return *this;
								    else{
								      node = node->suc[0];
								      return *this;
								    }
			  }
	  		  Iterator& operator--(){
									if(node == nullptr) return *this;
									node = node->pred;
									return *this;
			  }

		      Iterator operator++(int){
								    Map<K, O>::Iterator itr = *this;
								    if(node == nullptr) return itr;
								    node = node->suc[0];
								    return itr;
     		  }
		      Iterator operator--(int){
								    Map<K, O>::Iterator itr = *this;
								    if(node == nullptr) return itr;
								    node = node->pred;
								    return itr;
     		  }

		      ValueType& operator*() const{ return *(node->value); } //How to make this const
		      bool operator==(const Iterator& other) const{ return (node == other.node && other.iterlist == iterlist); }
		      bool operator!=(const Iterator& other) const{ return (node != other.node); }
		      ValueType* operator->(){ return node->value; };

		private:
		      SkipNode<K, O> *node; 
		      SkipList<K, O> *iterlist;
	  };


	class ConstIterator{
	    public:
	    	friend class Map<K, O>;	//Is this stupid?
		      ConstIterator( SkipNode<K, O>* n,  SkipList<K, O> *l){	node = n; iterlist = l;	}
		      ConstIterator(const ConstIterator &it)	{node = it.node; iterlist = it.iterlist;}
		      ConstIterator& operator=(const ConstIterator& itr){
	   								node = itr.node;
								    iterlist = itr.iterlist;
								    return *this;
			  }
		      ConstIterator& operator++(){
								    if(node == nullptr) return *this;
								    else{
								      node = node->suc[0];
								      return *this;
								    }
			  }
	  		  ConstIterator& operator--(){
									if(node == nullptr) return *this;
									node = node->pred;
									return *this;
			  }

		      ConstIterator operator++(int){
								    Map<K, O>::ConstIterator itr = *this;
								    if(node == nullptr) return itr;
								    node = node->suc[0];
								    return itr;
     		  }
		      ConstIterator operator--(int){
								    Map<K, O>::ConstIterator itr = *this;
								    if(node == nullptr) return itr;
								    node = node->pred;
								    return itr;
     		  }

		      const ValueType& operator*() const{ return *(node->value); } //How to make this const
		      bool operator==(const ConstIterator& other) const{ return (node == other.node && other.iterlist == iterlist); }
		      bool operator!=(const ConstIterator& other) const{ return (node != other.node); }
		      const ValueType* operator->(){ return node->value; };

		private:
		      SkipNode<K, O> *node; 
		      SkipList<K, O> *iterlist;
	  };



	class ReverseIterator{
	    public:
	    	friend class Map<K, O>;	//Is this stupid?
		      ReverseIterator(SkipNode<K, O>* n, SkipList<K, O> *l){	node = n; iterlist = l;	}
		      ReverseIterator(const ReverseIterator &it)	{node = it.node; iterlist = it.iterlist;}
		      ReverseIterator& operator=(const ReverseIterator& itr){
	   								node = itr.node;
								    iterlist = itr.iterlist;
								    return *this;
			  }
		      ReverseIterator& operator++(){
								    if(node == nullptr) return *this;
								    else{
								      node = node->pred;
								      return *this;
								    }
			  }
	  		  ReverseIterator& operator--(){
									if(node == nullptr) return *this;
									node = node->suc[0];
									return *this;
			  }

		      ReverseIterator operator++(int){
								    Map<K, O>::ReverseIterator itr = *this;
								    if(node == nullptr) return itr;
								    node = node->pred;
								    return itr;
     		  }
		      ReverseIterator operator--(int){
								    Map<K, O>::ReverseIterator itr = *this;
								    if(node == nullptr) return itr;
								    node = node->suc[0];
								    return itr;
     		  }

		      ValueType& operator*() const{ return *(node->value); } //How to make this const
		      bool operator==(const ReverseIterator& other) const{ return (node == other.node && other.iterlist == iterlist); }
		      bool operator!=(const ReverseIterator& other) const{ return (node != other.node); }
		      ValueType* operator->(){ return node->value; };

		private:
		      SkipNode<K, O> *node; 
		      SkipList<K, O> *iterlist;
	  };




