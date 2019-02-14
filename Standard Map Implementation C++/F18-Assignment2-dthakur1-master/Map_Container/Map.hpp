
/* Stuff to work on
Iterator copy constructor

ConstIterator end() const; make that const work as declaraton


*/

//Reference:	http://www.drdobbs.com/cpp/skip-lists-in-c/184403579?pgno=1

#include<iostream>
#include<vector>
#include <string>
#include<stdlib.h>
// #include<cstdlib>


namespace cs540{

#define ValueType std::pair<const K, O> 
//Bad practice
//MUST NOT change the template typename identifier(K & O) anywhere below

template<typename K, typename O>
  class SkipList;

template<typename K, typename O>
  class Map;


template<typename K, typename O>  
  class SkipNode{
    public:
      friend class SkipList<K, O>;
      friend class Map<K, O>;
      friend class Map<K, O>::Iterator;
      SkipNode(std::size_t level); //Only to create head and tail
      SkipNode(std::size_t level, const ValueType& v);
      ~SkipNode();
    private:
      std::vector<SkipNode*> suc;  //Successor is an array of pointers
      SkipNode* pred; //Predecessor
      ValueType* value;
  };

template<typename K, typename O>
  class SkipList{
    public:
      friend class Map<K, O>;
      SkipList(std::size_t max_level);  //Initialize head and tail with max level
      ~SkipList();
      //Returns the pointer to node containing v and an update vector for where the node should be in the list.
      std::pair< SkipNode<K, O>* , std::vector<SkipNode<K, O>* > > search(const K& key); 
      std::pair< SkipNode<K, O>*, bool> sklinsert(const ValueType& v);
      void erase(const ValueType& v);
      void erase(const K&);
      std::size_t RandLevel();
    private:
      SkipNode<K, O>* head;
      SkipNode<K, O>* tail;
      std::size_t current_max;
      std::size_t current_node_max_levels;
      std::size_t current_size;
  };

template<typename K, typename O>
  class Map{
    public:
      //Just to make it readable
	  #include "Iterator.inl"
      //////Constructors and Assignment Operator
      Map();
      Map(const Map& map);
      Map &operator=(const Map &map);
      Map(std::initializer_list<ValueType > init_list);
      ~Map();
      //////Size
      size_t size() const;
      bool empty() const;
      //////Iterators
      Iterator begin();
      Iterator end();
	  ConstIterator begin() const;
      ConstIterator end() const;
	  ReverseIterator rbegin() const;
      ReverseIterator rend() const;
      // ConstIterator begin();
      // ConstIterator end();
      // ReverseIterator rbegin();
      // ReverseIterator rend();
      //////Element Access
      Iterator find(const K& key);
      ConstIterator find(const K& key) const;
      // ConstIterator find(const K& key);
      O& at(const K& key);
      const O& at(const K& key) const; 
      // const O& at(const K& key) const();
      O& operator[](const K& key);
      //////Modifiers
      std::pair<Iterator, bool> insert(std::pair<const K, O> v);
      template <typename IT_T>
	  void insert(IT_T range_beg, IT_T range_end);
      void erase(Iterator pos);
      void erase(const K& key);
      void clear();
      //////Comparison
      
      bool operator==(const Map<K, O> &other) const;
      bool operator!=(const Map<K, O> &other) const{ return !(*this== other); }
      bool operator<(const Map<K, O> &other) const;

    private:
      SkipList<K, O> *list;
  };

//Definitions:
#include "Map.inl"

}
