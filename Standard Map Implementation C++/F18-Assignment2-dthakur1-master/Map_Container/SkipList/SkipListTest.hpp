
/* Stuff to work on

*/
namespace cs540{

#define ValueType std::pair<const K, O> 
//Bad practice
//MUST NOT change the template typename identifier(K & O) anywhere below

template<typename K, typename O>
  class SkipList;

template<typename K, typename O>
  class Map;

template<typename K, typename O>  //Check if replacing typename with class works.
  class SkipNode{
    //using ValueType = std::pair<const K, O>;
    public:
      friend class SkipList<K, O>;
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
      //friend class SkipNode<K, O>;
      SkipList(std::size_t max_level);  //Initialize head and tail with max level
      ~SkipList();
      //Returns the pointer to node containing v and an update vector for where the node should be in the list.
      std::pair< SkipNode<K, O>* , std::vector<SkipNode<K, O>* > > search(const ValueType& v); 
      bool insert(const ValueType& v);
      void erase(const ValueType& v);
      void print();
      std::size_t RandLevel();
    private:
      SkipNode<K, O>* head;
      SkipNode<K, O>* tail;
      std::size_t current_max;
  };



#include "SkipListTest.inl"
}
