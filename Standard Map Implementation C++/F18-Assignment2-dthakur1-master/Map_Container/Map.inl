

////////////////////////////////////////////////////////////////////SkipNode definitions
template<typename K, typename O>
  SkipNode<K, O>::SkipNode(std::size_t level){
    pred = nullptr;
    value = nullptr;
    for(std::size_t i=0; i<level; i++)
      suc.push_back(nullptr);
    //std::cout << "Default node defined with pointer vector length: " << suc.size() << "\n";
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
    if(value != nullptr){ delete value; value = nullptr;}
    pred = nullptr;
  }

////////////////////////////////////////////////////////////////////SkipList definitions
template<typename K, typename O>
  SkipList<K, O>::SkipList(std::size_t max_level){
    current_max = max_level;
    current_node_max_levels = 0;
    current_size = 0;
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
  std::pair< SkipNode<K, O>* , std::vector<SkipNode<K, O>* > > SkipList<K, O>::search(const K& key){
    std::pair< SkipNode<K, O>* , std::vector<SkipNode<K, O>* > > rv;
    int h = 0;
    std::vector<SkipNode<K, O>* > updateVec;
    for(std::size_t i=0; i<current_max; i++)  updateVec.push_back(nullptr);
    SkipNode<K, O>* tmp = head;
    // const K& k = v.first;  
    
    // Figure out the position of the node
    for ( h = current_max-1; h >= 0; h-- )
    {
      if(tmp->suc[h] == tail){
        updateVec[h] = tmp; 
        continue; 
      }

      // const K& nextKey = tmp->suc[h]->value->first;
      while (tmp->suc[h]->value->first < key)
      {
        tmp = tmp->suc[h];
        if(tmp->suc[h] == tail) break;
        // nextKey = tmp->suc[h]->value->first;
      }
      updateVec[h] = tmp;
    }

    //std::cout << "Possible SIGSEV\n"; //Does the || operator checks the right expression if the one on left is false?
    if(updateVec[0]->suc[0] == tail || !(updateVec[0]->suc[0]->value->first == key) ){
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
  std::pair<SkipNode<K, O>*, bool> SkipList<K, O>::sklinsert(const ValueType &v){

    auto search_rv = search(v.first);

    // if(search(v).first != nulptr){std::cout << "Duplicate found\n";}
    if(search_rv.first != nullptr){ auto rv = std::make_pair(search_rv.first, false); return rv; }

    auto updateVec = search_rv.second;

    // Perform an insert
    std::size_t random_level = RandLevel(); // [0, current_max )
    if(random_level > current_node_max_levels) current_node_max_levels = random_level;

    SkipNode<K, O> *NewNode = new SkipNode<K, O>(random_level, v);
    ++current_size;
    NewNode->pred = updateVec[0];
    std::size_t i = 0;
    while(i < random_level){
      NewNode->suc[i] = updateVec[i]->suc[i];
      updateVec[i]->suc[i] = NewNode;
      ++i;
    }
    NewNode->suc[0]->pred = NewNode;
    //std::cout << "Insert: Value: " << v.first << "," << v.second << " level:" << random_level <<std::endl;

    auto rv = std::make_pair(NewNode, true); 
    return rv; 
  }

template<typename K, typename O>
  void SkipList<K, O>::erase(const ValueType &v){
    auto search_rv = search(v.first);
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
    --current_size;
    return;
  }
template<typename K, typename O>
  void SkipList<K, O>::erase(const K &k){
    auto search_rv = search(k);
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
    --current_size;
    return;
  }

template<typename K, typename O>
  std::size_t SkipList<K, O>::RandLevel(){
    size_t level = 1;
    while(level < current_max && rand()%2 == 1 ){ //Maybe a false assumption of exact 50% probability
      ++level;
    }

    return level;  
  }





////////////////////////////////////////////////////////////////////Map definitions

template<typename K, typename O>
  Map<K, O>::Map(){
    list = new SkipList<K, O>(100); 
  }

template<typename K, typename O>
  Map<K, O>::Map(const Map& map){
    list = new SkipList<K, O>(100);
    auto itr = map.begin();
    while( itr != map.end() ){
      list->sklinsert(*itr);
      itr++;
    } 
  }

template <typename K, typename O>
  Map<K, O>& Map<K, O>::operator=(const Map<K, O>& map){
    if(this->list == map.list){
      return *this;
    }
    delete list;
    list = new SkipList<K, O>(100);
    auto itr = map.begin();
    while( itr != map.end() ){
      list->sklinsert(*itr);
      itr++;
    }   
    return *this;
  }


template<typename K, typename O>
  Map<K, O>::Map(std::initializer_list<std::pair<const K, O> > init_list){
    list = new SkipList<K, O>(100);
    auto itr = init_list.begin();
    while(itr != init_list.end()){
      list->sklinsert(*itr);
      itr++;
    }    
  }

template<typename K, typename O>
  Map<K, O>::~Map(){
    delete list;
  }

template<typename K, typename O>
  std::size_t Map<K, O>::size() const{
    return list->current_size;
  }

template<typename K, typename O>
  bool Map<K, O>::empty() const{
    return list->current_size == 0;
  }

template<typename K, typename O>
  typename Map<K, O>::Iterator Map<K, O>::begin() {
    return Map<K, O>::Iterator(this->list->head->suc[0], this->list);
  }

template<typename K, typename O>
  typename Map<K, O>::Iterator Map<K, O>::end() {
    return Map<K, O>::Iterator(this->list->tail, this->list);
  }

template<typename K, typename O>
  typename Map<K, O>::ConstIterator Map<K, O>::begin() const{
    return Map<K, O>::ConstIterator(this->list->head->suc[0], this->list);
  }

template<typename K, typename O>
  typename Map<K, O>::ConstIterator Map<K, O>::end() const{
    return Map<K, O>::ConstIterator(this->list->tail, this->list);
  }


template<typename K, typename O>
  typename Map<K, O>::ReverseIterator Map<K, O>::rbegin() const{
    return Map<K, O>::ReverseIterator(this->list->tail->pred, this->list);
  }

template<typename K, typename O>
  typename Map<K, O>::ReverseIterator Map<K, O>::rend() const{
    return Map<K, O>::ReverseIterator(this->list->head, this->list);
  }

template<typename K, typename O>
  typename Map<K, O>::Iterator Map<K, O>::find(const K& k){
    auto search_rv = list->search(k);
    if(search_rv.first == nullptr) { return this->end(); }
    return Map<K, O>::Iterator(search_rv.first, this->list) ;
  }

template<typename K, typename O>
  typename Map<K, O>::ConstIterator Map<K, O>::find(const K& k) const{
    auto search_rv = list->search(k);
    if(search_rv.first == nullptr) { return this->end(); }
    return Map<K, O>::ConstIterator(search_rv.first, this->list) ;
  }

template<typename K, typename O>
  O& Map<K, O>::at(const K& key){
    auto search_rv = list->search(key);
    if(search_rv.first == nullptr)  throw std::out_of_range("out_of_range");
    return search_rv.first->value->second;
  }

template<typename K, typename O>
  const O& Map<K, O>::at(const K& key) const{
    auto search_rv = list->search(key);
    if(search_rv.first == nullptr)  throw std::out_of_range("out_of_range");
    return search_rv.first->value->second;
  }


template <typename K, typename O>
O& Map<K, O>::operator[](const K& k){
  auto search_rv = list->search(k);
  if(search_rv.first == nullptr){
    O obj = O();
    K key = K(k);
    auto insert_rv = this->insert(std::make_pair(key, obj));
    return insert_rv.first.node->value->second;
  }
  return search_rv.first->value->second;  
}



template<typename K, typename O>
  std::pair<class Map<K, O>::Iterator, bool> Map<K, O>::insert(std::pair<const K, O> v){
    auto SkipListInsertRv = list->sklinsert(v);
    Map<K, O>::Iterator itr(SkipListInsertRv.first, list);
    auto rv = std::make_pair(itr, SkipListInsertRv.second);
    return rv;
  }

template <typename K, typename M>
  template <typename IT_T>
  void Map<K, M>::insert(IT_T range_beg, IT_T range_end){
    auto itr = range_beg;
    while(itr != range_end){
      list->sklinsert(*itr);
      ++itr;
    }
  }


template<typename K, typename O>
  void Map<K, O>::erase(Iterator pos){
    auto val = *(pos.node->value);
    pos.iterlist->erase(val);
  }

template<typename K, typename O>
  void Map<K, O>::erase(const K &key){
   list->erase(key);
  }

template<typename K, typename O>
  void Map<K, O>::clear(){
   delete list;
   list = new SkipList<K, O>(100); 
  }


template <typename K, typename O>
  bool Map<K, O>::operator==(const Map<K, O>& other) const{
    if(this->size() != other.size()) return false;
    auto i1 = this->begin();
    auto i2 = other.begin();
    while(i1 != this->end() && i2 != other.end()){
      if(*i1 != *i2){
        return false;
      }
      ++i1;
      ++i2;
    }
    return true;
  }


