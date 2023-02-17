#ifndef UNORDEREDMAP_H
#define UNORDEREDMAP_H
#include <iostream>
#include <functional>
#include <initializer_list>
#include "Pair.h"
#include "Function.h"
namespace sablin{

template <typename Key,typename Value,typename Hash,typename Pred>
class UnorderedMap;

namespace dzerzhinsky{

namespace lenin{

template <typename Key,typename Value>
class UnorderedMapListNode{
public:
    sablin::Pair<Key,Value>         *element_pointer_ = nullptr;
    UnorderedMapListNode<Key,Value> *next_node_       = nullptr;
public:
    UnorderedMapListNode() = default;
    UnorderedMapListNode(const Key&,Value&);
    UnorderedMapListNode(Key&&,Value&&);
    UnorderedMapListNode(const UnorderedMapListNode&)            = delete;
    UnorderedMapListNode(UnorderedMapListNode&&)                 = delete;
    UnorderedMapListNode& operator=(const UnorderedMapListNode&) = delete;
    UnorderedMapListNode& operator=(UnorderedMapListNode&&)      = delete;
    ~UnorderedMapListNode();
};

template <typename Key,typename Value>
UnorderedMapListNode<Key,Value>::UnorderedMapListNode(const Key &key,Value &value){
    element_pointer_ = new Pair<Key,Value>(key,value);
    next_node_ = nullptr;
}

template <typename Key,typename Value>
UnorderedMapListNode<Key,Value>::UnorderedMapListNode(Key &&key,Value &&value){
    element_pointer_ = new Pair<Key,Value>(std::move(key),std::move(value));
    next_node_ = nullptr;
}

template <typename Key,typename Value>
UnorderedMapListNode<Key,Value>::~UnorderedMapListNode(){
    if(element_pointer_ != nullptr)
        delete element_pointer_;
    element_pointer_ = nullptr;
}

template <typename Key,typename Value,typename Pred>
class UnorderedMapList{
private:
    UnorderedMapListNode<Key,Value> *head_pointer_ = nullptr;
    Pred                             equal_func_;
public:
    UnorderedMapList()                                   = default;
    UnorderedMapList(const UnorderedMapList&)            = delete;
    UnorderedMapList(UnorderedMapList&&)                 = delete;
    UnorderedMapList& operator=(const UnorderedMapList&) = delete;
    UnorderedMapList& operator=(UnorderedMapList&&)      = delete;
    ~UnorderedMapList();

    UnorderedMapListNode<Key,Value>* get_head_pointer() const;
    void Add(const Key&,Value&);
    void Add(Key&&,Value&&);
    Value* Find(const Key&);
    void Erase(const Key&);
};

template <typename Key,typename Value,typename Pred>
UnorderedMapList<Key,Value,Pred>::~UnorderedMapList(){
    UnorderedMapListNode<Key,Value> *temp_pointer = head_pointer_;
    while(head_pointer_ != nullptr){
        temp_pointer = temp_pointer->next_node_;
        delete head_pointer_;
        head_pointer_ = temp_pointer;
    }
}

template <typename Key,typename Value,typename Pred>
UnorderedMapListNode<Key,Value>* UnorderedMapList<Key,Value,Pred>::get_head_pointer() const{
    return head_pointer_;
}

template <typename Key,typename Value,typename Pred>
void UnorderedMapList<Key,Value,Pred>::Add(const Key &key,Value &value){
    if(head_pointer_ == nullptr){
        head_pointer_ = new UnorderedMapListNode<Key,Value>(key,value);
        return;
    }
    UnorderedMapListNode<Key,Value> *temp_pointer = head_pointer_;
    while(temp_pointer->next_node_ != nullptr){
       if(equal_func_(temp_pointer->element_pointer_->first,key)){
           temp_pointer->element_pointer_->second = value;
           return;
       } 
       temp_pointer = temp_pointer->next_node_;
    }
    if(equal_func_(temp_pointer->element_pointer_->first,key)){
        temp_pointer->element_pointer_->second = value;
        return;
    }
    temp_pointer->next_node_ = new UnorderedMapListNode<Key,Value>(key,value);
    return;
}

template <typename Key,typename Value,typename Pred>
void UnorderedMapList<Key,Value,Pred>::Add(Key &&key,Value &&value){
    if(head_pointer_ == nullptr){
        head_pointer_ = new UnorderedMapListNode<Key,Value>(std::move(key),std::move(value));
        return;
    }
    UnorderedMapListNode<Key,Value> *temp_pointer = head_pointer_;
    while(temp_pointer->next_node_ != nullptr){
       if(equal_func_(temp_pointer->element_pointer_->first,key)){
           temp_pointer->element_pointer_->second = std::move(value);
           return;
       } 
       temp_pointer = temp_pointer->next_node_;
    }
    if(equal_func_(temp_pointer->element_pointer_->first,key)){
        temp_pointer->element_pointer_->second = std::move(value);
        return;
    }
    temp_pointer->next_node_ = new UnorderedMapListNode<Key,Value>(std::move(key),std::move(value));
    return;
}

template <typename Key,typename Value,typename Pred>
Value* UnorderedMapList<Key,Value,Pred>::Find(const Key &key){
    UnorderedMapListNode<Key,Value> *temp_pointer = head_pointer_;
    while(temp_pointer != nullptr){
        if(equal_func_(temp_pointer->element_pointer_->first,key))
            return &temp_pointer->element_pointer_->second;
        temp_pointer = temp_pointer->next_node_;
    }
    return nullptr;
}

template <typename Key,typename Value,typename Pred>
void UnorderedMapList<Key,Value,Pred>::Erase(const Key &key){
    if(head_pointer_ == nullptr) return;
    UnorderedMapListNode<Key,Value> *temp_pointer = head_pointer_;
    while(temp_pointer->next_node_ != nullptr){
        if(equal_func_(temp_pointer->next_node_->element_pointer_->first,key)){
            UnorderedMapListNode<Key,Value> *temp_next_pointer = temp_pointer->next_node_;
            temp_pointer->next_node_ = temp_next_pointer->next_node_;
            delete temp_next_pointer;
            return;
        }
        temp_pointer = temp_pointer->next_node_;
    }
    if(equal_func_(head_pointer_->element_pointer_->first,key)){
        temp_pointer = head_pointer_;
        head_pointer_ = head_pointer_->next_node_;
        delete temp_pointer;
    }
}

}

}

template <typename Key,typename Value,typename Hash = std::hash<Key>,typename Pred = sablin::EqualTo<Key>>
class UnorderedMap{
public:
    typedef Key                                      key_type;
    typedef Value                                    mapped_type;
    typedef sablin::Pair<const key_type,mapped_type> value_type;
    typedef size_t                                   number_type;
    typedef Hash                                     hasher;
    typedef Pred                                     key_equal;
private:
    number_type element_size_;
    number_type bucket_count_;
    hasher      hash_func_;
    key_equal   equal_func_;
    dzerzhinsky::lenin::UnorderedMapList<Key,Value,Pred> **buckets_pointer_;
private:
    void Initialize(number_type,const hasher&,const key_equal&);
public:
    explicit UnorderedMap(number_type bucket_count = 10, const hasher& hash_func = hasher(),
            const key_equal& equal_func = key_equal());
    template <typename Iterator>
    explicit UnorderedMap(const Iterator&,const Iterator&,number_type bucket_count = 10,
            const hasher& hash_func = hasher(), const key_equal& equal_func = key_equal());
    explicit UnorderedMap(std::initializer_list<Pair<Key,Value>>,number_type bucket_count = 10,
            const hasher& hash_func = hasher(), const key_equal& equal_func = key_equal());

    UnorderedMap(const UnorderedMap&);
    UnorderedMap(UnorderedMap&&);

    UnorderedMap& operator=(const UnorderedMap&);
    UnorderedMap& operator=(UnorderedMap&&);

    ~UnorderedMap();

    void Clear() noexcept;
};

template <typename Key,typename Value,typename Hash,typename Pred>
void UnorderedMap<Key,Value,Hash,Pred>::Initialize(number_type bucket_count,const hasher& hash_func,
        const key_equal& equal_func){
    element_size_ = 0;
    bucket_count_ = bucket_count;
    hash_func_ = hash_func;
    equal_func_ = equal_func;
    buckets_pointer_ = new dzerzhinsky::lenin::UnorderedMapList<Key,Value,Pred>*[bucket_count_];
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMap<Key,Value,Hash,Pred>::UnorderedMap(number_type bucket_count,const hasher& hash_func,
        const key_equal& equal_func){
    this->Initialize(bucket_count,hash_func,equal_func);
}

template <typename Key,typename Value,typename Hash,typename Pred>
template <typename Iterator>
UnorderedMap<Key,Value,Hash,Pred>::UnorderedMap(const Iterator &iterator_first,
        const Iterator &iterator_second,number_type bucket_count,const hasher& hash_func,
        const key_equal& equal_func){
    this->Initialize(bucket_count,hash_func,equal_func);
    for(Iterator iterator_temp = iterator_first;iterator_temp != iterator_second; ++iterator_temp)
        this->Insert(*iterator_temp);
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMap<Key,Value,Hash,Pred>::UnorderedMap(std::initializer_list<Pair<Key,Value>> list,
        number_type bucket_count, const hasher& hash_func, const key_equal& equal_func){
    number_type size = list.size();
    if(size == 0) throw new std::runtime_error("Size Wrong ------ UnorderedMap(initializer_list,......)");
    this->Initialize(bucket_count,hash_func,equal_func);
    for(number_type i = 0;i != size; ++i)
        this->Insert(*(list.begin() + i));
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMap<Key,Value,Hash,Pred>::UnorderedMap(const UnorderedMap<Key,Value,Hash,Pred> &another){
    this->Initialize(another.bucket_count_,another.hash_func_,another.equal_func_);
    for(auto iterator_temp = another.Begin(); iterator_temp != another.End(); ++iterator_temp)
        this->Insert(*iterator_temp);
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMap<Key,Value,Hash,Pred>::UnorderedMap(UnorderedMap<Key,Value,Hash,Pred> &&another){
    element_size_ = another.element_size_;
    bucket_count_ = another.bucket_count_;
    hash_func_ = another.hash_func_;
    equal_func_ = another.equal_func_;
    buckets_pointer_ = another.buckets_pointer_;

    another.Initialize(hash_func_,hash_func_,equal_func_);
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMap<Key,Value,Hash,Pred>& UnorderedMap<Key,Value,Hash,Pred>::operator=(const UnorderedMap &another){
    if(&another == this) return *this;
    this->Clear();
    for(auto iterator_temp = another.Begin(); iterator_temp != another.End(); ++iterator_temp)
        this->Insert(*iterator_temp);
    return *this;
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMap<Key,Value,Hash,Pred>& UnorderedMap<Key,Value,Hash,Pred>::operator=(UnorderedMap &&another){
    if(&another == this) return *this;
    this->Clear();
    element_size_ = another.element_size_;
    bucket_count_ = another.bucket_count_;
    hash_func_ = another.hash_func_;
    equal_func_ = another.equal_func_;
    buckets_pointer_ = another.buckets_pointer_;

    another.Initialize(bucket_count_,hash_func_,equal_func_);
    return *this;
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMap<Key,Value,Hash,Pred>::~UnorderedMap<Key,Value,Hash,Pred>(){
    this->ReleaseResource();
}

template <typename Key,typename Value,typename Hash,typename Pred>
void UnorderedMap<Key,Value,Hash,Pred>::Clear() noexcept{
    this->ReleaseResource();
    this->Initialize();
}


}
#endif
