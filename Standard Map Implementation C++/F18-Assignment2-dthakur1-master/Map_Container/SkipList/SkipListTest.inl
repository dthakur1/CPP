////////////////////////////////////////////////////////////////////SkipNode definitions
template<typename K, typename O>
  SkipNode<K, O>::SkipNode(std::size_t level){
    pred = nullptr;
    value = nullptr;
    for(std::size_t i=0; i<level; i++)
      suc.push_back(nullptr);
    std::cout << "Default node defined with pointer vector length: " << suc.size() << "\n";
  }

template<typename K, typename O>
  SkipNode<K, O>::SkipNode(std::size_t level,const ValueType& v){
    pred = nullptr;
    value = new ValueType(v);
    for(std::size_t i=0; i<level; i++)
      suc.push_back(nullptr);
}

template<typename K, typename O>
  SkipNode<K, O>::~SkipNode(){
    if(value != nullptr){ std::cout << "deleting a node\n";  delete value; value = nullptr;}
    pred = nullptr;
  }

////////////////////////////////////////////////////////////////////SkipList definitions
template<typename K, typename O>
  SkipList<K, O>::SkipList(std::size_t max_level){
    current_max = max_level;
    head = new SkipNode<K, O>(current_max);
    tail = new SkipNode<K, O>(current_max);    
    for (std::size_t i = 0; i < max_level; i++ ){  head->suc[i] = tail; tail->suc[i] = nullptr; }
    head->pred = nullptr;
    tail->pred = head;
  }

template<typename K, typename O>
  SkipList<K, O>::~SkipList(){
    for(auto ptr = head->suc[0]; ptr != nullptr; ptr=ptr->suc[0])
      delete ptr->pred;
    delete tail;
    head = nullptr;
    tail = nullptr;
  }

template<typename K, typename O>
  std::pair< SkipNode<K, O>* , std::vector<SkipNode<K, O>* > > SkipList<K, O>::search(const ValueType& v){
    std::pair< SkipNode<K, O>* , std::vector<SkipNode<K, O>* > > rv;
    int h = 0;
    std::vector<SkipNode<K, O>* > updateVec;
    for(std::size_t i=0; i<current_max; i++)  updateVec.push_back(nullptr);
    SkipNode<K, O>* tmp = head;
    const K& k = v.first;  
    K nextKey;

    // Figure out the position of the node
    for ( h = current_max-1; h >= 0; h-- )
    {
      if(tmp->suc[h] == tail){
        updateVec[h] = tmp; 
        continue; 
      }

      nextKey = tmp->suc[h]->value->first;
      while (nextKey < k)
      {
        tmp = tmp->suc[h];
        if(tmp->suc[h] == tail) break;
        nextKey = tmp->suc[h]->value->first;
      }
      updateVec[h] = tmp;
    }

    //std::cout << "Possible SIGSEV\n"; //Does the || operator checks the right expression if the one on left is false?
    if(updateVec[0]->suc[0] == tail || updateVec[0]->suc[0]->value->first != k){
      //Node with key k not found
      rv.first = nullptr;
      rv.second = updateVec;
      return rv;
    }
    
    rv.first = updateVec[0]->suc[0];
    rv.second = updateVec;
    return rv;
} 


template<typename K, typename O>
  bool SkipList<K, O>::insert(const ValueType &v){

    // if(search(v).first != nulptr){std::cout << "Duplicate found\n";  return false; }
    auto search_rv = search(v);

    if(search_rv.first != nullptr){std::cout << "Duplicate found\n";  return false; }

    auto updateVec = search_rv.second;

    // Perform an insert
    std::size_t random_level = RandLevel(); // [0, current_max )
    SkipNode<K, O> *NewNode = new SkipNode<K, O>(random_level, v);
    NewNode->pred = updateVec[0];
    std::size_t i = 0;
    while(i < random_level){
      NewNode->suc[i] = updateVec[i]->suc[i];
      updateVec[i]->suc[i] = NewNode;
      ++i;
    }
    NewNode->suc[0]->pred = NewNode;
    std::cout << "Insert: Value: " << v.first << "," << v.second << " level:" << random_level <<std::endl;
    return true;
  }

template<typename K, typename O>
  void SkipList<K, O>::erase(const ValueType &v){
    auto search_rv = search(v);
    if(search_rv.first == nullptr)  return;

    auto node = search_rv.first;
    auto updateVec = search_rv.second;
    std::size_t level = node->suc.size(), i = 0;
    while(i < level){
      updateVec[i]->suc[i] = node->suc[i];
      ++i;
    }
    node->suc[0]->pred = node->pred;

    delete node;

    return;
}


      
////////////////////////////////////////////////////////////////////Utils
template<typename K, typename O>
  std::size_t SkipList<K, O>::RandLevel(){
    size_t level = 1;
    while(level < current_max && rand()%2 == 1 ){ //Maybe a false assumption of 50% probability
      // std::cout << "RNG OP: " << "\n";      
      ++level;
    }

    return level;  
}

template<typename K, typename O>
  void SkipList<K, O>::print(){
  std::size_t i = 0;
  for(auto ptr = head->suc[0] ; ptr != tail ; ptr = ptr->suc[0], i++){
    std::cout << "Node: " << i << " value: " << ptr->value->first << " levels: " << ptr->suc.size() << "\n" ;
  }
}


