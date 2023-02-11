#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <initializer_list>
#include "Pair.h"
#include "Function.h"
namespace sablin{

template <typename Key,typename Value,typename Compare>
class Map;

namespace dzerzhinsky{

namespace lenin{

template <typename Key,typename Value>
class MapNode{
public:
    MapNode<Key,Value>      *parent_node_     = nullptr;
    MapNode<Key,Value>      *left_node_       = nullptr;
    MapNode<Key,Value>      *right_node_      = nullptr;
    sablin::Pair<Key,Value> *element_pointer_ = nullptr;
    bool                    is_black_         = true;
public:
    MapNode() = default;
    MapNode(const Key&,Value&);
    MapNode(const MapNode&)            = delete;
    MapNode(MapNode&&)                 = delete;
    MapNode& operator=(const MapNode&) = delete;
    MapNode& operator=(MapNode&&)      = delete;
    ~MapNode();
};

template <typename Key,typename Value>
MapNode<Key,Value>::MapNode(const Key &key,Value &value){
    element_pointer_ = new Pair<Key,Value>(key,value);
    parent_node_ = left_node_ = right_node_ = nullptr;
}

template <typename Key,typename Value>
MapNode<Key,Value>::~MapNode(){
    if(element_pointer_ != nullptr)
        delete element_pointer_;
    element_pointer_ = nullptr;
}

template <typename Key,typename Value>
class MapIteratorBase{
private:
    MapNode<Key,Value> *node_pointer_;
    bool               is_beyond_head_;
    bool               is_behind_tail_;
public:
    MapIteratorBase() : node_pointer_(nullptr),is_beyond_head_(false),is_behind_tail_(false){}
    MapIteratorBase(const MapIteratorBase&) = default;
    MapIteratorBase& operator=(const MapIteratorBase&) = default;
    MapIteratorBase& operator=(MapIteratorBase&) = default;
    virtual ~MapIteratorBase();

    void set_node_pointer(MapNode<Key,Value>*);
    MapNode<Key,Value>* get_node_pointer() const;

    bool IsBeyondHead() const;
    bool IsBehindTail() const;
    
    void SetBeyondHead();
    void SetBehindTail();
    void UnsetAll();

    virtual void StepNext() = 0;
    virtual void StepLast() = 0;

    MapNode<Key,Value>* GetSuccessorNode() const;
    MapNode<Key,Value>* GetPredecessorNode() const;
    MapNode<Key,Value>* GetMaximumNode(const MapNode<Key,Value>*) const;
    MapNode<Key,Value>* GetMinimumNode(const MapNode<Key,Value>*) const;
};

template <typename Key,typename Value>
MapIteratorBase<Key,Value>::~MapIteratorBase(){
    node_pointer_ = nullptr;
}

template <typename Key,typename Value>
void MapIteratorBase<Key,Value>::set_node_pointer(MapNode<Key,Value> *node_pointer){
    node_pointer_ = node_pointer;
}

template <typename Key,typename Value>
MapNode<Key,Value>* MapIteratorBase<Key,Value>::get_node_pointer() const{
    return node_pointer_;
}

template <typename Key,typename Value>
bool MapIteratorBase<Key,Value>::IsBeyondHead() const{
    return is_beyond_head_;
}

template <typename Key,typename Value>
bool MapIteratorBase<Key,Value>::IsBehindTail() const{
    return is_behind_tail_;
}

template <typename Key,typename Value>
void MapIteratorBase<Key,Value>::SetBeyondHead(){
    is_beyond_head_ |= 1;
    is_behind_tail_ &= 0;
}

template <typename Key,typename Value>
void MapIteratorBase<Key,Value>::SetBehindTail(){
    is_behind_tail_ |= 1;
    is_beyond_head_ &= 0;
}

template <typename Key,typename Value>
void MapIteratorBase<Key,Value>::UnsetAll(){
    is_beyond_head_ &= 0;
    is_behind_tail_ &= 0;
}

template <typename Key,typename Value>
MapNode<Key,Value>* MapIteratorBase<Key,Value>::GetMaximumNode(const MapNode<Key,Value> *root_node) const{
    MapNode<Key,Value> *temp_node = root_node;
    while(temp_node->right_node_->element_pointer_ != nullptr)
        temp_node = temp_node->right_node_;
    return temp_node;
}

template <typename Key,typename Value>
MapNode<Key,Value>* MapIteratorBase<Key,Value>::GetMinimumNode(const MapNode<Key,Value> *root_node) const{
    MapNode<Key,Value> *temp_node = root_node;
    while(temp_node->left_node_->element_pointer_ != nullptr)
        temp_node = temp_node->left_node_;
    return temp_node;
}

template <typename Key,typename Value>
MapNode<Key,Value>* MapIteratorBase<Key,Value>::GetSuccessorNode() const{
    if(IsBehindTail()) throw new std::runtime_error("Iterator Behind Tail!");
    if(IsBeyondHead()) {return node_pointer_;}
    if(node_pointer_->right_node_->element_pointer_ != nullptr)
        return GetMinimumNode(node_pointer_->right_node_);
    MapNode<Key,Value> *temp_node_one = node_pointer_;
    MapNode<Key,Value> *temp_node_two = node_pointer_->parent_node_;
    while(temp_node_two->element_pointer_ != nullptr && temp_node_one == temp_node_two->right_node_){
        temp_node_one = temp_node_two;
        temp_node_two = temp_node_two->parent_node_;
    } 
    if(temp_node_two->element_pointer_ == nullptr)
        return nullptr;
    return temp_node_two;
}

template <typename Key,typename Value>
MapNode<Key,Value>* MapIteratorBase<Key,Value>::GetPredecessorNode() const{
    if(IsBeyondHead()) throw new std::runtime_error("Iterator Beyond Head!");
    if(IsBehindTail()) { return node_pointer_;}
    if(node_pointer_->left_node_->element_pointer_ != nullptr)
        return GetMaximumNode(node_pointer_->left_node_);
    MapNode<Key,Value> *temp_node_one = node_pointer_;
    MapNode<Key,Value> *temp_node_two = node_pointer_->parent_node_;
    while(temp_node_two->element_pointer_ != nullptr && temp_node_one == temp_node_two->left_node_){
        temp_node_one = temp_node_two;
        temp_node_two = temp_node_two->parent_node_;
    }
    if(temp_node_two->element_pointer_ == nullptr)
        return nullptr;
    return temp_node_two;
}

template <typename Key,typename Value>
class MapIteratorPositive : public MapIteratorBase<Key,Value>{
public:
    MapIteratorPositive(MapNode<Key,Value>*,bool,bool);
    MapIteratorPositive(const MapIteratorPositive&);
    MapIteratorPositive(MapIteratorPositive&&);
    MapIteratorPositive& operator=(const MapIteratorPositive&);
    MapIteratorPositive& operator=(MapIteratorPositive&&);
    ~MapIteratorPositive() = default;

    void StepNext() override;
    void StepLast() override;
};

template <typename Key,typename Value>
MapIteratorPositive<Key,Value>::MapIteratorPositive(MapNode<Key,Value> *node_pointer,bool is_beyond_head,bool is_behind_tail){
    this->set_node_pointer(node_pointer);
    if(is_beyond_head) this->SetBeyondHead();
    if(is_behind_tail) this->SetBehindTail();
}

template <typename Key,typename Value>
MapIteratorPositive<Key,Value>::MapIteratorPositive(const MapIteratorPositive &another){
    this->get_node_pointer(another.get_pointer());
    if(another.IsBeyondHead()) this->SetBeyondHead();
    if(another.IsBehindTail()) this->SetBehindTail();
}

template <typename Key,typename Value>
MapIteratorPositive<Key,Value>::MapIteratorPositive(MapIteratorPositive &&another){
    this->set_node_pointer(another.get_node_pointer());
    another.set_node_pointer(nullptr);
    if(another.IsBeyondHead()) this->SetBeyondHead();
    if(another.IsBehindTail()) this->SetBehindTail();
    another.UnsetAll();
}

template <typename Key,typename Value>
MapIteratorPositive<Key,Value>& MapIteratorPositive<Key,Value>::operator=(const MapIteratorPositive &another){
    if(this == &another) return *this;
    this->set_node_pointer(another.get_node_pointer());
    if(another.IsBeyondHead()) this->SetBeyondHead();
    if(another.IsBehindTail()) this->SetBehindTail();
    return *this;
}

template <typename Key,typename Value>
MapIteratorPositive<Key,Value>& MapIteratorPositive<Key,Value>::operator=(MapIteratorPositive &&another){
    if(this == &another) return *this;
    this->set_node_pointer(another.get_node_pointer());
    another.set_node_pointer(nullptr);
    if(another.IsBeyondHead()) this->SetBeyondHead();
    if(another.IsBehindTail()) this->SetBehindTail();
    another.UnsetAll(); 
    return *this;
}

template <typename Key,typename Value>
void MapIteratorPositive<Key,Value>::StepNext(){
    MapNode<Key,Value>* node_pointer_temp = this->get_node_pointer();
    if(node_pointer_temp == nullptr)
        throw new std::runtime_error("StepNext Wrong!");
    if(this->IsBeyondHead()) {
        this->UnsetAll();
        return;
    }
    node_pointer_temp = this->GetSuccessorNode();    
    if(node_pointer_temp == nullptr){
        this->SetBehindTail();
        return;
    }
    this->set_node_pointer(node_pointer_temp);
}

template <typename Key,typename Value>
void MapIteratorPositive<Key,Value>::StepLast(){
    MapNode<Key,Value>* node_pointer_temp = this->get_node_pointer();
    if(node_pointer_temp == nullptr)
        throw new std::runtime_error("StepLast Wrong!");
    if(this->IsBehindTail()){
        this->UnsetAll();
        return;
    }
    node_pointer_temp = this->GetPredecessorNode();
    if(node_pointer_temp == nullptr){
        this->SetBeyondHead();
        return;
    }
    this->set_node_pointer(node_pointer_temp);    
}

template <typename Key,typename Value>
class MapIteratorNegative : public MapIteratorBase<Key,Value>{
public:
    MapIteratorNegative(MapNode<Key,Value>*,bool,bool);
    MapIteratorNegative(const MapIteratorNegative&);
    MapIteratorNegative(MapIteratorNegative&&);
    MapIteratorNegative& operator=(const MapIteratorNegative&);
    MapIteratorNegative& operator=(MapIteratorNegative&&);
    ~MapIteratorNegative() = default;

    void StepNext() override;
    void StepLast() override;
};

template <typename Key,typename Value>
MapIteratorNegative<Key,Value>::MapIteratorNegative(MapNode<Key,Value> *node_pointer,bool is_beyond_head,bool is_behind_tail){
    this->set_node_pointer(node_pointer);
    if(is_beyond_head) this->SetBeyondHead();
    if(is_behind_tail) this->SetBehindTail();
}

template <typename Key,typename Value>
MapIteratorNegative<Key,Value>::MapIteratorNegative(const MapIteratorNegative &another){
    this->get_node_pointer(another.get_pointer());
    if(another.IsBeyondHead()) this->SetBeyondHead();
    if(another.IsBehindTail()) this->SetBehindTail();
}

template <typename Key,typename Value>
MapIteratorNegative<Key,Value>::MapIteratorNegative(MapIteratorNegative &&another){
    this->set_node_pointer(another.get_node_pointer());
    another.set_node_pointer(nullptr);
    if(another.IsBeyondHead()) this->SetBeyondHead();
    if(another.IsBehindTail()) this->SetBehindTail();
    another.UnsetAll();
}

template <typename Key,typename Value>
MapIteratorNegative<Key,Value>& MapIteratorNegative<Key,Value>::operator=(const MapIteratorNegative &another){
    if(this == &another) return *this;
    this->set_node_pointer(another.get_node_pointer());
    if(another.IsBeyondHead()) this->SetBeyondHead();
    if(another.IsBehindTail()) this->SetBehindTail();
    return *this;
}

template <typename Key,typename Value>
MapIteratorNegative<Key,Value>& MapIteratorNegative<Key,Value>::operator=(MapIteratorNegative &&another){
    if(this == &another) return *this;
    this->set_node_pointer(another.get_node_pointer());
    another.set_node_pointer(nullptr);
    if(another.IsBeyondHead()) this->SetBeyondHead();
    if(another.IsBehindTail()) this->SetBehindTail();
    another.UnsetAll();
    return *this;
}

template <typename Key,typename Value>
void MapIteratorNegative<Key,Value>::StepLast(){
    MapNode<Key,Value>* node_pointer_temp = this->get_node_pointer();
    if(node_pointer_temp == nullptr)
        throw new std::runtime_error("StepLast Wrong!");
    if(this->IsBeyondHead()) {
        this->UnsetAll();
        return;
    }
    node_pointer_temp = this->GetSuccessorNode();    
    if(node_pointer_temp == nullptr){
        this->SetBehindTail();
        return;
    }
    this->set_node_pointer(node_pointer_temp);
}

template <typename Key,typename Value>
void MapIteratorNegative<Key,Value>::StepNext(){
    MapNode<Key,Value>* node_pointer_temp = this->get_node_pointer();
    if(node_pointer_temp == nullptr)
        throw new std::runtime_error("StepNext Wrong!");
    if(this->IsBehindTail()){
        this->UnsetAll();
        return;
    }
    node_pointer_temp = this->GetPredecessorNode();
    if(node_pointer_temp == nullptr){
        this->SetBeyondHead();
        return;
    }
    this->set_node_pointer(node_pointer_temp);    
}
}

template <typename Key,typename Value,typename Compare>
class MapIterator{
    friend class Map<Key,Value,Compare>;
    template <typename K,typename V,typename C>
    friend bool operator==(const MapIterator<K,V,C>&,const MapIterator<K,V,C>&);
    template <typename K,typename V,typename C>
    friend bool operator!=(const MapIterator<K,V,C>&,const MapIterator<K,V,C>&);
private:
    lenin::MapIteratorBase<Key,Value> *map_iterator_base_pointer_;
public:
    MapIterator();
    MapIterator(const MapIterator&);
    MapIterator(MapIterator&&);
    MapIterator& operator=(const MapIterator&);
    MapIterator& operator=(MapIterator&&);
    ~MapIterator();

    MapIterator<Key,Value,Compare>& operator++();
    MapIterator<Key,Value,Compare>& operator--();
    MapIterator<Key,Value,Compare> operator++(int);
    MapIterator<Key,Value,Compare> operator--(int);
    
    Pair<Key,Value>& operator*() const;
    Pair<Key,Value>* operator->() const;
};

template <typename Key,typename Value,typename Compare>
MapIterator<Key,Value,Compare>::MapIterator():
    map_iterator_base_pointer_(nullptr){}

template <typename Key,typename Value,typename Compare>
MapIterator<Key,Value,Compare>::MapIterator(const MapIterator &another){
    if(another.map_iterator_base_pointer_ == nullptr){
        map_iterator_base_pointer_ = nullptr;
        return;
    }
    if(typeid(*(another.map_iterator_base_pointer_)) == typeid(lenin::MapIteratorPositive<Key,Value>))
        map_iterator_base_pointer_ = new lenin::MapIteratorPositive<Key,Value>(another.map_iterator_base_pointer_->get_node_pointer(),
                another.map_iterator_base_pointer_->IsBeyondHead(),another.map_iterator_base_pointer_->IsBehindTail());
    else if(typeid(*(another.map_iterator_base_pointer_)) == typeid(lenin::MapIteratorNegative<Key,Value>))
        map_iterator_base_pointer_ = new lenin::MapIteratorNegative<Key,Value>(another.map_iterator_base_pointer_->get_node_pointer(),
                another.map_iterator_base_pointer_->IsBeyondHead(),another.map_iterator_base_pointer_->IsBehindTail());
    else
        throw new std::runtime_error("Construct Wrong Owing to Wrong Type!");
}

template <typename Key,typename Value,typename Compare>
MapIterator<Key,Value,Compare>::MapIterator(MapIterator &&another){
    if(another.map_iterator_base_pointer_ == nullptr){
        map_iterator_base_pointer_ = nullptr;
        return;
    }
    map_iterator_base_pointer_ = another.map_iterator_base_pointer_;
    another.map_iterator_base_pointer_ = nullptr;
}

template <typename Key,typename Value,typename Compare>
MapIterator<Key,Value,Compare>& MapIterator<Key,Value,Compare>::operator=(const MapIterator &another){
    if(this == &another) return *this;

    lenin::MapIteratorBase<Key,Value> *temp_pointer = nullptr;
    if(another.map_iterator_base_pointer_ == nullptr)
        temp_pointer = nullptr;
    else if(typeid(*(another.map_iterator_base_pointer_)) == typeid(lenin::MapIteratorPositive<Key,Value>))
        temp_pointer = new lenin::MapIteratorPositive<Key,Value>(another.map_iterator_base_pointer_->get_node_pointer(),
                another.map_iterator_base_pointer_->IsBeyondHead(),another.map_iterator_base_pointer_->IsBehindTail());
    else if(typeid(*(another.map_iterator_base_pointer_)) == typeid(lenin::MapIteratorNegative<Key,Value>))
        temp_pointer = new lenin::MapIteratorNegative<Key,Value>(another.map_iterator_base_pointer_->get_node_pointer(),
                another.map_iterator_base_pointer_->IsBeyondHead(),another.map_iterator_base_pointer_->IsBehindTail());
    else
        throw new std::runtime_error("Construct Wrong Owing to Wrong Type!");

    if(map_iterator_base_pointer_ != nullptr)
        delete map_iterator_base_pointer_;
    map_iterator_base_pointer_ = temp_pointer;
    return *this;
}

template <typename Key,typename Value,typename Compare>
MapIterator<Key,Value,Compare>& MapIterator<Key,Value,Compare>::operator=(MapIterator &&another){
    if(this == &another) return *this;
    if(map_iterator_base_pointer_ != nullptr)
        delete map_iterator_base_pointer_;
    map_iterator_base_pointer_ = another.map_iterator_base_pointer_;
    another.map_iterator_base_pointer_ = nullptr;
    return *this;
}

template <typename Key,typename Value,typename Compare>
MapIterator<Key,Value,Compare>::~MapIterator(){
    if(map_iterator_base_pointer_ != nullptr)
        delete map_iterator_base_pointer_;
    map_iterator_base_pointer_ = nullptr;
}

template <typename Key,typename Value,typename Compare>
MapIterator<Key,Value,Compare>& MapIterator<Key,Value,Compare>::operator++(){
    if(map_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    map_iterator_base_pointer_->StepNext();
    return *this;
}

template <typename Key,typename Value,typename Compare>
MapIterator<Key,Value,Compare>& MapIterator<Key,Value,Compare>::operator--(){
    if(map_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator");
    map_iterator_base_pointer_->StepLast();
    return *this;
}

template <typename Key,typename Value,typename Compare>
MapIterator<Key,Value,Compare> MapIterator<Key,Value,Compare>::operator++(int){
    if(map_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator");
    MapIterator temp(*this);
    map_iterator_base_pointer_->StepNext();
    return temp;
}

template <typename Key,typename Value,typename Compare>
MapIterator<Key,Value,Compare> MapIterator<Key,Value,Compare>::operator--(int){
    if(map_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator");
    MapIterator temp(*this);
    map_iterator_base_pointer_->StepLast();
    return temp;
}

template <typename Key,typename Value,typename Compare>
Pair<Key,Value>& MapIterator<Key,Value,Compare>::operator*() const{
    if(map_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    if(map_iterator_base_pointer_->IsBeyondHead() || map_iterator_base_pointer_->IsBehindTail())
        throw new std::runtime_error("Iterator Beyond!");
    lenin::MapNode<Key,Value> *temp_node_pointer = map_iterator_base_pointer_->get_node_pointer();
    if(temp_node_pointer == nullptr)
        throw new std::runtime_error("NULL Node!");
    return *(temp_node_pointer->element_pointer_);
}

template <typename Key,typename Value,typename Compare>
Pair<Key,Value>* MapIterator<Key,Value,Compare>::operator->() const{
    if(map_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    if(map_iterator_base_pointer_->IsBeyondHead() || map_iterator_base_pointer_->IsBehindTail())
        throw new std::runtime_error("Iterator Beyond!");
    lenin::MapNode<Key,Value> *temp_node_pointer = map_iterator_base_pointer_->get_node_pointer();
    if(temp_node_pointer == nullptr)
        throw new std::runtime_error("NULL Node!");
    return temp_node_pointer->element_pointer_;
} 

template <typename Key,typename Value,typename Compare>
bool operator==(const MapIterator<Key,Value,Compare> &lhs,const MapIterator<Key,Value,Compare> &rhs){
    if(lhs.map_iterator_base_pointer_ != nullptr && rhs.map_iterator_base_pointer_ != nullptr){
        if(typeid(*(lhs.map_iterator_base_pointer_)) == typeid(*(rhs.map_iterator_base_pointer))){
            int result = lhs.map_iterator_base_pointer_->IsBeyondHead() + lhs.map_iterator_base_pointer_->IsBehindTail()
                            + rhs.map_iterator_base_pointer_->IsBeyondHead() + rhs.map_iterator_base_pointer_->IsBehindTail();
            if(result == 0) return lhs.map_iterator_base_pointer_->get_node_pointer() == rhs.map_iterator_base_pointer_->get_node_pointer();

            if(lhs.map_iterator_base_pointer_->IsBeyondHead() && rhs.map_iterator_base_pointer_->IsBeyondHead()) return true;
            if(lhs.map_iterator_base_pointer_->IsBehindTail() && rhs.map_iterator_base_pointer_->IsBehindTail()) return true;
            return false;
        }else{
            return false;
        }
    }else if(lhs.map_iterator_base_pointer_ == nullptr && rhs.map_iterator_base_pointer_ == nullptr){
        return true;
    }else{
        return false;
    }
}

template <typename Key,typename Value,typename Compare>
bool operator!=(const MapIterator<Key,Value,Compare> &lhs,const MapIterator<Key,Value,Compare> &rhs){
    return !(lhs == rhs);
}

}

template <typename Key,typename Value,typename Compare = Less<Key>>
class Map{
public:
    typedef Key                                         key_type;
    typedef Value                                       mapped_type;
    typedef sablin::Pair<const key_type,mapped_type>    value_type;
    typedef size_t                                      number_type;
    typedef Compare                                     key_compare; 
    typedef dzerzhinsky::MapIterator<Key,Value,Compare> iterator;
private:
    number_type element_size_;
    key_compare compare_func_;
    dzerzhinsky::lenin::MapNode<Key,Value>  *root_node_;
    dzerzhinsky::lenin::MapNode<Key,Value>  *nil_node_; 
private:
    void Initialize(const key_compare&);
    void ReleaseResource();
    void RecursionRelease(dzerzhinsky::lenin::MapNode<Key,Value>*);
    dzerzhinsky::lenin::MapNode<Key,Value>* GetMinNode(dzerzhinsky::lenin::MapNode<Key,Value>*);
    dzerzhinsky::lenin::MapNode<Key,Value>* GetMaxNode(dzerzhinsky::lenin::MapNode<Key,Value>*);
    dzerzhinsky::lenin::MapNode<Key,Value>* Search(const key_type&) const;
    void InsertFixUp(dzerzhinsky::lenin::MapNode<Key,Value>*);
public:
    explicit Map(const key_compare& compare_func = key_compare());
    template <typename Iterator>
    explicit Map(const Iterator&,const Iterator&,const key_compare& compare_func = key_compare());
    explicit Map(std::initializer_list<Pair<Key,Value>>,const key_compare& compare_func = key_compare());

    Map(const Map&);
    Map(Map&&);

    Map& operator=(const Map&);
    Map& operator=(Map&&);

    ~Map();

    void Clear() noexcept;

    iterator Begin()  noexcept;
    iterator End()    noexcept;
    iterator RBegin() noexcept;
    iterator REnd()   noexcept;

    bool IsEmpty() const;
    number_type Size() const;

    mapped_type& At(const key_type&);
    const mapped_type& At(const key_type&) const;

    mapped_type& operator[](const key_type&);

    iterator Insert(const value_type&);
    template <typename Iterator>
    void Insert(Iterator,Iterator);
    void Insert(std::initializer_list<value_type>);
};

template <typename Key,typename Value,typename Compare>
void Map<Key,Value,Compare>::Initialize(const key_compare &compare_func){
    element_size_ = 0;
    root_node_ = nullptr;
    compare_func_ = compare_func;
    nil_node_ = new dzerzhinsky::lenin::MapNode<Key,Value>();
}

template <typename Key,typename Value,typename Compare>
void Map<Key,Value,Compare>::ReleaseResource(){
    if(root_node_ == nullptr) return;
    RecursionRelease(root_node_);
    delete nil_node_;
    nil_node_ = root_node_ = nullptr;
    element_size_ = 0;
}

template <typename Key,typename Value,typename Compare>
void Map<Key,Value,Compare>::RecursionRelease(dzerzhinsky::lenin::MapNode<Key,Value> *node_pointer){
   if(node_pointer.left_node_ != nil_node_) RecursionRelease(node_pointer.left_node_);
   if(node_pointer.right_node_ != nil_node_) RecursionRelease(node_pointer.right_node_);
   delete node_pointer;
   return;
}

template <typename Key,typename Value,typename Compare>
dzerzhinsky::lenin::MapNode<Key,Value>* Map<Key,Value,Compare>::GetMaxNode(dzerzhinsky::lenin::MapNode<Key,Value> *root_node){
    if(root_node == nullptr || root_node->element_pointer_ == nullptr)
        throw new std::runtime_error("No Element In Tree ---- GetMaxNode()");
    while(root_node->right_node_->element_pointer_ != nullptr)
        root_node = root_node->right_node_;
    return root_node;
}

template <typename Key,typename Value,typename Compare>
dzerzhinsky::lenin::MapNode<Key,Value>* Map<Key,Value,Compare>::GetMinNode(dzerzhinsky::lenin::MapNode<Key,Value> *root_node){
    if(root_node == nullptr || root_node->element_pointer_ == nullptr)
        throw new std::runtime_error("No Element In Tree ---- GetMinNode()");
    while(root_node->left_node_->element_pointer_ != nullptr)
        root_node = root_node->left_node_;
    return root_node;
}

template <typename Key,typename Value,typename Compare>
dzerzhinsky::lenin::MapNode<Key,Value>* Map<Key,Value,Compare>::Search(const key_type &key) const{
    if(root_node_ == nullptr)
        throw new std::runtime_error("No Element! ----- Search()");
    dzerzhinsky::lenin::MapNode<Key,Value>* temp_pointer = root_node_;
    while(temp_pointer->element_pointer_ != nullptr && temp_pointer->element_pointer_->first != key)
       if(compare_func_(key,temp_pointer->element_pointer_->first)) temp_pointer = temp_pointer->left_node_;
       else                                                         temp_pointer = temp_pointer->right_node_;
    if(temp_pointer->element_pointer_ == nullptr) return nullptr;
    return temp_pointer;
}


template <typename Key,typename Value,typename Compare>
Map<Key,Value,Compare>::Map(const key_compare& compare_func){
    this->Initialize(compare_func);
}

template <typename Key,typename Value,typename Compare>
template <typename Iterator>
Map<Key,Value,Compare>::Map(const Iterator &iterator_first,const Iterator &iterator_second,
                            const key_compare& compare_func){
    this->Initialize(compare_func);
    for(Iterator iterator_temp = iterator_first;iterator_temp != iterator_second;++iterator_temp)
        this->Insert(*iterator_temp);
}

template <typename Key,typename Value,typename Compare>
Map<Key,Value,Compare>::Map(std::initializer_list<Pair<Key,Value>> list,const key_compare& compare_func){
    number_type size = list.size();
    if(size == 0) throw new std::runtime_error("Size Wrong ----- Map(initializer_list,key_compare)");
    this->Initialize(compare_func);
    for(number_type i = 0;i != size; ++i)
        this->Insert(*(list.begin() + i));
}

template <typename Key,typename Value,typename Compare>
Map<Key,Value,Compare>::Map(const Map<Key,Value,Compare> &another){
    this->Initialize(another.compare_func_);
    for(auto iterator_temp = another.Begin();iterator_temp != another.End(); ++iterator_temp)
        this->Insert(*iterator_temp);
}

template <typename Key,typename Value,typename Compare>
Map<Key,Value,Compare>::Map(Map<Key,Value,Compare> &&another){
    element_size_ = another.element_size_;
    root_node_ = another.root_node_;
    nil_node_ = another.nil_node_;
    compare_func_ = another.compare_func_;

    another.Initialize(compare_func_);
}

template <typename Key,typename Value,typename Compare>
Map<Key,Value,Compare>& Map<Key,Value,Compare>::operator=(const Map &another){
    if(&another == this) return *this;
    this->Clear();
    for(auto iterator_temp = another.Begin();iterator_temp != another.End(); ++iterator_temp)
        this->Insert(*iterator_temp);
    return *this;
}

template <typename Key,typename Value,typename Compare>
Map<Key,Value,Compare>& Map<Key,Value,Compare>::operator=(Map &&another){
    if(&another == this) return *this;
    this->Clear();
    element_size_ = another.element_size_;
    root_node_ = another.root_node_;
    nil_node_ = another.nil_node_;
    compare_func_ = another.compare_func_;

    another.Initialize(compare_func_);
    return *this;
}

template <typename Key,typename Value,typename Compare>
Map<Key,Value,Compare>::~Map<Key,Value,Compare>(){
    this->ReleaseResource();
}

template <typename Key,typename Value,typename Compare>
void Map<Key,Value,Compare>::Clear() noexcept{
    this->ReleaseResource();
    this->Initialize();
}

template <typename Key,typename Value,typename Compare>
typename Map<Key,Value,Compare>::iterator Map<Key,Value,Compare>::Begin() noexcept{
    if(root_node_ == nullptr) throw new std::runtime_error("NULL TREE!");
    dzerzhinsky::MapIterator<Key,Value,Compare> temp;
    temp.map_iterator_base_pointer_ = new dzerzhinsky::lenin::MapIteratorPositive<Key,Value>(GetMinNode(root_node_),false,false);
    return temp;
}

template <typename Key,typename Value,typename Compare>
typename Map<Key,Value,Compare>::iterator Map<Key,Value,Compare>::End() noexcept{
    if(root_node_ == nullptr) throw new std::runtime_error("NULL TREE!");
    dzerzhinsky::MapIterator<Key,Value,Compare> temp;
    temp.map_iterator_base_pointer_ = new dzerzhinsky::lenin::MapIteratorPositive<Key,Value>(GetMaxNode(root_node_),false,true);
    return temp;
}

template <typename Key,typename Value,typename Compare>
typename Map<Key,Value,Compare>::iterator Map<Key,Value,Compare>::RBegin() noexcept{
    if(root_node_ == nullptr) throw new std::runtime_error("NULL TREE!");
    dzerzhinsky::MapIterator<Key,Value,Compare> temp;
    temp.map_iterator_base_pointer_ = new dzerzhinsky::lenin::MapIteratorNegative<Key,Value>(GetMaxNode(root_node_),false,false);
    return temp;
}

template <typename Key,typename Value,typename Compare>
typename Map<Key,Value,Compare>::iterator Map<Key,Value,Compare>::REnd() noexcept{
    if(root_node_ == nullptr) throw new std::runtime_error("NULL TREE!");
    dzerzhinsky::MapIterator<Key,Value,Compare> temp;
    temp.map_iterator_base_pointer_ = new dzerzhinsky::lenin::MapIteratorNegative<Key,Value>(GetMinNode(root_node_),true,false);
    return temp;
}

template <typename Key,typename Value,typename Compare>
bool Map<Key,Value,Compare>::IsEmpty() const{
    return root_node_ == nullptr;
}

template <typename Key,typename Value,typename Compare>
typename Map<Key,Value,Compare>::number_type Map<Key,Value,Compare>::Size() const{
    return element_size_;
}

template <typename Key,typename Value,typename Compare>
typename Map<Key,Value,Compare>::mapped_type& Map<Key,Value,Compare>::At(const key_type &key){
    dzerzhinsky::lenin::MapNode<Key,Value>* temp_pointer = Search(key);
    if(temp_pointer == nullptr)
        throw new std::runtime_error("No Such Key!");
    return temp_pointer->element_pointer_->second;
}

template <typename Key,typename Value,typename Compare>
const typename Map<Key,Value,Compare>::mapped_type& Map<Key,Value,Compare>::At(const key_type &key) const{
    dzerzhinsky::lenin::MapNode<Key,Value>* temp_pointer = Search(key);
    if(temp_pointer == nullptr)
        throw new std::runtime_error("No Such Key!");
    return temp_pointer->element_pointer_->second;
}

template <typename Key,typename Value,typename Compare>
typename Map<Key,Value,Compare>::mapped_type& Map<Key,Value,Compare>::operator[](const key_type &key){
    dzerzhinsky::lenin::MapNode<Key,Value>* temp_pointer = Search(key);
    if(temp_pointer == nullptr){
        auto new_pair = MakePair<Key,Value>(key,Value());
        iterator temp_iterator = this->Insert(new_pair);
        temp_pointer = temp_iterator.map_iterator_base_pointer_;
    }
    return temp_pointer->element_size_->second;
}

template <typename Key,typename Value,typename Compare>
typename Map<Key,Value,Compare>::iterator Map<Key,Value,Compare>::Insert(const value_type &insert_pair){
    dzerzhinsky::lenin::MapNode<Key,Value>* temp_pointer = Search(insert_pair.first);
    if(temp_pointer != nullptr){
        temp_pointer->element_pointer_->second = insert_pair.second;
        Map<Key,Value,Compare>::iterator iterator_temp;
        iterator_temp.map_iterator_base_pointer_ = new dzerzhinsky::lenin::MapIteratorPositive<Key,Value>(temp_pointer,false,false);
        return iterator_temp;
    }
    if(root_node_ == nullptr){
        root_node_ = new dzerzhinsky::lenin::MapNode<Key,Value>(insert_pair.first,insert_pair.second);
        root_node_->parent_node_ = nil_node_;
        root_node_->left_node_   = nil_node_;
        root_node_->right_node_  = nil_node_;
        ++element_size_;
        Map<Key,Value,Compare>::iterator iterator_temp;
        iterator_temp.map_iterator_base_pointer_ = new dzerzhinsky::lenin::MapIteratorPositive<Key,Value>(root_node_,false,false);
        return iterator_temp;
    }
    dzerzhinsky::lenin::MapNode<Key,Value>* temp_pointer_one = root_node_;
    dzerzhinsky::lenin::MapNode<Key,Value>* temp_pointer_two = nullptr;
    while(temp_pointer_one != nil_node_){
        temp_pointer_two = temp_pointer_one;
        if(compare_func_(insert_pair.first,temp_pointer_one->element_pointer_->first))
            temp_pointer_one = temp_pointer_one->left_node_;
        else
            temp_pointer_one = temp_pointer_one->right_node_;
    }
    dzerzhinsky::lenin::MapNode<Key,Value>* new_node = new dzerzhinsky::lenin::MapNode<Key,Value>(insert_pair.first,insert_pair.second);
    new_node->parent_node_ = temp_pointer_two;
    if(compare_func_(insert_pair.first,new_node->element_pointer_->first))
        temp_pointer_two->left_node_ = new_node;
    else
        temp_pointer_two->right_node_ = new_node;
    new_node->left_node_ = nil_node_;
    new_node->right_node_ = nil_node_;
    new_node->is_black_ = false;
    InsertFixUp(new_node);
    ++element_size_;
    Map<Key,Value,Compare>::iterator iterator_temp;
    iterator_temp.map_iterator_base_pointer_ = new dzerzhinsky::lenin::MapIteratorPositive<Key,Value>(new_node,false,false);
    return iterator_temp;
}

template <typename Key,typename Value,typename Compare>
template <typename Iterator>
void Map<Key,Value,Compare>::Insert(Iterator iterator_first,Iterator iterator_second){
    for(Iterator iterator_temp = iterator_first;iterator_temp != iterator_second; ++iterator_temp)
        Insert(*iterator_temp);
}

template <typename Key,typename Value,typename Compare>
void Map<Key,Value,Compare>::Insert(std::initializer_list<value_type> list){
   number_type size = list.size();
   if(size == 0) return;
   for(number_type i = 0;i != size; ++i)
       this->Insert(*(list.begin() + i));
}

template <typename Key,typename Value,typename Compare>
void Map<Key,Value,Compare>::InsertFixUp(dzerzhinsky::lenin::MapNode<Key,Value> *new_node){
    while(!new_node->parent_node_->is_black_){
        if(new_node->parent_node_ == new_node->parent_node_->parent_node_->left_node_){
            dzerzhinsky::lenin::MapNode<Key,Value> *temp_node = new_node->parent_node_->parent_node_->right_node_;
            if(!temp_node->is_black_){
                new_node->parent_node_->is_black_ = true;
                temp_node->is_black_ = true;
                new_node->parent_node_->parent_node_->is_black_ = false;
                new_node = new_node->parent_node_->parent_node_;
            }else if(new_node == new_node->parent_node_->right_node_){
                new_node = new_node->parent_node_;
                LeftRotate(new_node);
            }else{
                new_node->parent_node_->is_black_ = true;
                new_node->parent_node_->parent_node_->is_black_ = false;
                RightRotate(new_node);
            }
        }else{
            dzerzhinsky::lenin::MapNode<Key,Value> *temp_node = new_node->parent_node->parent_node_->left_node_;
            if(!temp_node->is_balck){
                new_node->parent_node_->is_black_ = true;
                temp_node->is_black_ = true;
                new_node->parent_node_->parent_node_->is_black_ = false;
                new_node = new_node->parent_node_->parent_node_;
            }else if(new_node == new_node->parent_node_->left_node_){
                new_node = new_node->parent_node_;
                RightRotate(new_node);
            }else{
                new_node->parent_node_->is_balck_ = true;
                new_node->parent_node_->parent_node_->is_black_ = false;
                LeftRotate(new_node);
            }
        }
    }
    root_node_->is_black_ = true;
}

}
#endif
