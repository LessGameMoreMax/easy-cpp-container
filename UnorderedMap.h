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
    bool Add(const Key&,Value&);
    bool Add(Key&&,Value&&);
    UnorderedMapListNode<Key,Value>* Find(const Key&);
    bool Erase(const Key&);
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
bool UnorderedMapList<Key,Value,Pred>::Add(const Key &key,Value &value){
    if(head_pointer_ == nullptr){
        head_pointer_ = new UnorderedMapListNode<Key,Value>(key,value);
        return true;
    }
    UnorderedMapListNode<Key,Value> *temp_pointer = head_pointer_;
    while(temp_pointer->next_node_ != nullptr){
       if(equal_func_(temp_pointer->element_pointer_->first,key)){
           temp_pointer->element_pointer_->second = value;
           return false;
       } 
       temp_pointer = temp_pointer->next_node_;
    }
    if(equal_func_(temp_pointer->element_pointer_->first,key)){
        temp_pointer->element_pointer_->second = value;
        return false;
    }
    temp_pointer->next_node_ = new UnorderedMapListNode<Key,Value>(key,value);
    return true;
}

template <typename Key,typename Value,typename Pred>
bool UnorderedMapList<Key,Value,Pred>::Add(Key &&key,Value &&value){
    if(head_pointer_ == nullptr){
        head_pointer_ = new UnorderedMapListNode<Key,Value>(std::move(key),std::move(value));
        return true;
    }
    UnorderedMapListNode<Key,Value> *temp_pointer = head_pointer_;
    while(temp_pointer->next_node_ != nullptr){
       if(equal_func_(temp_pointer->element_pointer_->first,key)){
           temp_pointer->element_pointer_->second = std::move(value);
           return false;
       } 
       temp_pointer = temp_pointer->next_node_;
    }
    if(equal_func_(temp_pointer->element_pointer_->first,key)){
        temp_pointer->element_pointer_->second = std::move(value);
        return false;
    }
    temp_pointer->next_node_ = new UnorderedMapListNode<Key,Value>(std::move(key),std::move(value));
    return true;
}

template <typename Key,typename Value,typename Pred>
UnorderedMapListNode<Key,Value>* UnorderedMapList<Key,Value,Pred>::Find(const Key &key){
    UnorderedMapListNode<Key,Value> *temp_pointer = head_pointer_;
    while(temp_pointer != nullptr){
        if(equal_func_(temp_pointer->element_pointer_->first,key))
            return temp_pointer;
        temp_pointer = temp_pointer->next_node_;
    }
    return nullptr;
}

template <typename Key,typename Value,typename Pred>
bool UnorderedMapList<Key,Value,Pred>::Erase(const Key &key){
    if(head_pointer_ == nullptr) return false;
    UnorderedMapListNode<Key,Value> *temp_pointer = head_pointer_;
    while(temp_pointer->next_node_ != nullptr){
        if(equal_func_(temp_pointer->next_node_->element_pointer_->first,key)){
            UnorderedMapListNode<Key,Value> *temp_next_pointer = temp_pointer->next_node_;
            temp_pointer->next_node_ = temp_next_pointer->next_node_;
            delete temp_next_pointer;
            return true;
        }
        temp_pointer = temp_pointer->next_node_;
    }
    if(equal_func_(head_pointer_->element_pointer_->first,key)){
        temp_pointer = head_pointer_;
        head_pointer_ = head_pointer_->next_node_;
        delete temp_pointer;
        return true;
    }
    return false;
}

template <typename Key,typename Value,typename Hash,typename Pred>
class UnorderedMapIteratorPositive{
private:
    UnorderedMapListNode<Key,Value>   *node_pointer_;
    UnorderedMap<Key,Value,Hash,Pred> *unordered_map_pointer_;   
    size_t                            bucket_index_;  
public:
    UnorderedMapIteratorPositive(UnorderedMap<Key,Value,Hash,Pred>*,UnorderedMapListNode<Key,Value> *node_poitner = nullptr,
            size_t bucket_index = -1);
    UnorderedMapIteratorPositive(const UnorderedMapIteratorPositive&) = default;
    UnorderedMapIteratorPositive& operator=(const UnorderedMapIteratorPositive&) = default;
    UnorderedMapIteratorPositive& operator=(UnorderedMapIteratorPositive&) = default;
    ~UnorderedMapIteratorPositive() = default;
    
    void set_node_pointer(UnorderedMapListNode<Key,Value>*);
    UnorderedMapListNode<Key,Value>* get_node_pointer() const;
    size_t get_bucket_index() const;
    void set_bucket_index(size_t);
    UnorderedMap<Key,Value,Hash,Pred>* get_unordered_map_pointer() const;

    void StepNext();
};

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMapIteratorPositive<Key,Value,Hash,Pred>::UnorderedMapIteratorPositive(UnorderedMap<Key,Value,Hash,Pred> *unordered_map_pointer,
        UnorderedMapListNode<Key,Value> *node_pointer,size_t bucket_index){
    unordered_map_pointer_ = unordered_map_pointer;
    if(bucket_index == -1){
        node_pointer_ = nullptr;
        bucket_index_ = unordered_map_pointer_->BucketCount() - 1;
        return;
    }
    node_pointer_ = node_pointer;
    bucket_index_ = bucket_index;
}

template <typename Key,typename Value,typename Hash,typename Pred>
void UnorderedMapIteratorPositive<Key,Value,Hash,Pred>::set_node_pointer(UnorderedMapListNode<Key,Value> *node_pointer){
    node_pointer_ = node_pointer;
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMapListNode<Key,Value>* UnorderedMapIteratorPositive<Key,Value,Hash,Pred>::get_node_pointer() const{
    return node_pointer_;
}

template <typename Key,typename Value,typename Hash,typename Pred>
void UnorderedMapIteratorPositive<Key,Value,Hash,Pred>::set_bucket_index(size_t bucket_index){
    bucket_index_ = bucket_index;
}

template <typename Key,typename Value,typename Hash,typename Pred>
size_t UnorderedMapIteratorPositive<Key,Value,Hash,Pred>::get_bucket_index() const{
    return bucket_index_;
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMap<Key,Value,Hash,Pred>* UnorderedMapIteratorPositive<Key,Value,Hash,Pred>::get_unordered_map_pointer() const{
    return unordered_map_pointer_;
}

template <typename Key,typename Value,typename Hash,typename Pred>
void UnorderedMapIteratorPositive<Key,Value,Hash,Pred>::StepNext(){
    if(node_pointer_ == nullptr) throw new std::runtime_error("StepNext Wrong!");
    node_pointer_ = node_pointer_->next_node_;
    if(node_pointer_ != nullptr) return;
    for(size_t i = bucket_index_ + 1;i != unordered_map_pointer_->BucketCount(); ++i){
        auto temp_pointer = unordered_map_pointer_->GetBucketBeginNode(i);
        if(temp_pointer != nullptr){
           node_pointer_ = temp_pointer;
           bucket_index_ = i;
           return;
        }
    }
    bucket_index_ = unordered_map_pointer_->BucketCount() - 1;
}
}

template <typename Key,typename Value,typename Hash,typename Pred>
class UnorderedMapIterator{
    friend class UnorderedMap<Key,Value,Hash,Pred>;
    template <typename K,typename V,typename H,typename P>
    friend bool operator==(const UnorderedMapIterator<K,V,H,P>&,const UnorderedMapIterator<K,V,H,P>&);
    template <typename K,typename V,typename H,typename P>
    friend bool operator!=(const UnorderedMapIterator<K,V,H,P>&,const UnorderedMapIterator<K,V,H,P>&);
private:
    lenin::UnorderedMapIteratorPositive<Key,Value,Hash,Pred> *unordered_map_iterator_pointer_;
public:
    UnorderedMapIterator();
    UnorderedMapIterator(const UnorderedMapIterator&);
    UnorderedMapIterator(UnorderedMapIterator&&);
    UnorderedMapIterator& operator=(const UnorderedMapIterator&);
    UnorderedMapIterator& operator=(UnorderedMapIterator&&);
    ~UnorderedMapIterator();

    UnorderedMapIterator<Key,Value,Hash,Pred>& operator++();
    UnorderedMapIterator<Key,Value,Hash,Pred> operator++(int);

    Pair<Key,Value>& operator*() const;
    Pair<Key,Value>* operator->() const;
};

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMapIterator<Key,Value,Hash,Pred>::UnorderedMapIterator():
    unordered_map_iterator_pointer_(nullptr){}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMapIterator<Key,Value,Hash,Pred>::UnorderedMapIterator(const UnorderedMapIterator &another){
    if(another.unordered_map_iterator_pointer_ == nullptr){
        unordered_map_iterator_pointer_ = nullptr;
        return;
    }
    unordered_map_iterator_pointer_ = 
        new lenin::UnorderedMapIteratorPositive<Key,Value,Hash,Pred>(another.unordered_map_iterator_pointer_->get_unordered_map_pointer(),
                another.unordered_map_iterator_pointer_->get_node_pointer(),another.unordered_map_iterator_pointer_->get_bucket_index());
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMapIterator<Key,Value,Hash,Pred>::UnorderedMapIterator(UnorderedMapIterator &&another){
    if(another.unordered_map_iterator_pointer_ == nullptr){
        unordered_map_iterator_pointer_ = nullptr;
        return;
    }
    unordered_map_iterator_pointer_ = another.unordered_map_iterator_pointer_;
    another.unordered_map_iterator_pointer_ = nullptr;
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMapIterator<Key,Value,Hash,Pred>& UnorderedMapIterator<Key,Value,Hash,Pred>::operator=(const UnorderedMapIterator &another){
    if(this == &another) return *this;
    if(unordered_map_iterator_pointer_ != nullptr) delete unordered_map_iterator_pointer_;
    if(another.unordered_map_iterator_pointer_ == nullptr){
        unordered_map_iterator_pointer_ = nullptr;
        return *this;
    }

    unordered_map_iterator_pointer_ = 
        new lenin::UnorderedMapIteratorPositive<Key,Value,Hash,Pred>(another.unordered_map_iterator_pointer_->get_unordered_map_pointer(),
                another.unordered_map_iterator_pointer_->get_node_pointer(),another.unordered_map_iterator_pointer_->get_bucket_index());
    return *this;
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMapIterator<Key,Value,Hash,Pred>& UnorderedMapIterator<Key,Value,Hash,Pred>::operator=(UnorderedMapIterator &&another){
    if(this == &another) return *this;
    if(unordered_map_iterator_pointer_ != nullptr) delete unordered_map_iterator_pointer_;
    unordered_map_iterator_pointer_ = another.unordered_map_iterator_pointer_;
    another.unordered_map_iterator_pointer_ = nullptr;
    return *this;
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMapIterator<Key,Value,Hash,Pred>::~UnorderedMapIterator(){
    if(unordered_map_iterator_pointer_ != nullptr)
        delete unordered_map_iterator_pointer_;
    unordered_map_iterator_pointer_ = nullptr;
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMapIterator<Key,Value,Hash,Pred>& UnorderedMapIterator<Key,Value,Hash,Pred>::operator++(){
    if(unordered_map_iterator_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    unordered_map_iterator_pointer_->StepNext();
    return *this;
}

template <typename Key,typename Value,typename Hash,typename Pred>
UnorderedMapIterator<Key,Value,Hash,Pred> UnorderedMapIterator<Key,Value,Hash,Pred>::operator++(int){
    if(unordered_map_iterator_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator");
    UnorderedMapIterator temp(*this);
    unordered_map_iterator_pointer_->StepNext();
    return temp;
}

template <typename Key,typename Value,typename Hash,typename Pred>
Pair<Key,Value>& UnorderedMapIterator<Key,Value,Hash,Pred>::operator*() const{
    if(unordered_map_iterator_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    lenin::UnorderedMapListNode<Key,Value> *temp_node_pointer = unordered_map_iterator_pointer_->get_node_pointer();
    if(temp_node_pointer == nullptr){
        if(unordered_map_iterator_pointer_->get_unordered_map_pointer()->BucketCount()
                ==(unordered_map_iterator_pointer_->get_bucket_index()+1)){
                    throw new std::runtime_error("Iterator Beyond!");
                }else{
                    throw new std::runtime_error("NULL Node!");
                }
    }
    return *(temp_node_pointer->element_pointer_);
}

template <typename Key,typename Value,typename Hash,typename Pred>
Pair<Key,Value>* UnorderedMapIterator<Key,Value,Hash,Pred>::operator->() const{
    if(unordered_map_iterator_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    lenin::UnorderedMapListNode<Key,Value> *temp_node_pointer = unordered_map_iterator_pointer_->get_node_pointer();
    if(temp_node_pointer == nullptr){
        if(unordered_map_iterator_pointer_->get_unordered_map_pointer()->BucketCount()
                ==(unordered_map_iterator_pointer_->get_bucket_index()+1)){
                    throw new std::runtime_error("Iterator Beyond!");
                }else{
                    throw new std::runtime_error("NULL Node!");
                }
    }
    return temp_node_pointer->element_pointer_;
}

template <typename Key,typename Value,typename Hash,typename Pred>
bool operator==(const UnorderedMapIterator<Key,Value,Hash,Pred> &lhs,const UnorderedMapIterator<Key,Value,Hash,Pred> &rhs){
    if(lhs.unordered_map_iterator_pointer_ != nullptr && rhs.unordered_map_iterator_pointer_ != nullptr){
        return lhs.unordered_map_iterator_pointer_->get_bucket_index()==rhs.unordered_map_iterator_pointer_->get_bucket_index()
                    && lhs.unordered_map_iterator_pointer_->get_node_pointer()==rhs.unordered_map_iterator_pointer_->get_node_pointer();
    }else if(lhs.unordered_map_iterator_pointer_ == nullptr && rhs.unordered_map_iterator_pointer_ == nullptr){
        return true;
    }else{
        return false;
    }
}

template <typename Key,typename Value,typename Hash,typename Pred>
bool operator!=(const UnorderedMapIterator<Key,Value,Hash,Pred> &lhs,const UnorderedMapIterator<Key,Value,Hash,Pred> &rhs){
    return !(lhs == rhs);
}


}

template <typename Key,typename Value,typename Hash = std::hash<Key>,typename Pred = sablin::EqualTo<Key>>
class UnorderedMap{
    friend class dzerzhinsky::lenin::UnorderedMapIteratorPositive<Key,Value,Hash,Pred>;
public:
    typedef Key                                                    key_type;
    typedef Value                                                  mapped_type;
    typedef sablin::Pair<const key_type,mapped_type>               value_type;
    typedef size_t                                                 number_type;
    typedef Hash                                                   hasher;
    typedef Pred                                                   key_equal;
    typedef dzerzhinsky::UnorderedMapIterator<Key,Value,Hash,Pred> iterator;

    //Debug--------------------------
    void PrintAll(){
        std::cout << "Element_Size is : " << element_size_ << std::endl;
        std::cout << "Bucket_Count is : " << bucket_count_ << std::endl;
        for(size_t i = 0;i != bucket_count_; ++i){
            std::cout << "Bucket Index : " << i << std::endl;
            if(buckets_pointer_[i] == nullptr){
                std::cout << "NULL" << std::endl;
                continue;
            }
            auto temp_pointer = buckets_pointer_[i]->get_head_pointer();
            while(temp_pointer != nullptr){
                std::cout << "First: " << temp_pointer->element_pointer_->first;
                std::cout << " Second: " << temp_pointer->element_pointer_->second;
                std::cout << "---";
                temp_pointer = temp_pointer->next_node_;
            }
            std::cout << std::endl;
        }
    }
    //Debug--------------------------
private:
    number_type element_size_;
    number_type bucket_count_;
    hasher      hash_func_;
    key_equal   equal_func_;
    dzerzhinsky::lenin::UnorderedMapList<Key,Value,Pred> **buckets_pointer_;
private:
    void Initialize(number_type,const hasher&,const key_equal&);
    void ReleaseResource();
    dzerzhinsky::lenin::UnorderedMapListNode<Key,Value>* GetBucketBeginNode(number_type) const;
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

    iterator Begin(number_type bucket_index = 0) noexcept;
    iterator End() noexcept;
    iterator End(number_type) noexcept;

    number_type BucketCount() const noexcept; 

    bool IsEmpty() const;
    number_type Size() const;

    iterator Find(const key_type&);

    mapped_type& At(const key_type&);
    const mapped_type& At(const key_type&) const;

    iterator Insert(const Pair<Key,Value>&);
    iterator Insert(Pair<Key,Value>&&);
    template <typename Iterator>
    void Insert(Iterator,Iterator);
    void Insert(std::initializer_list<Pair<Key,Value>>);

    bool Erase(const key_type&);
    iterator Erase(const iterator&);
    iterator Erase(const iterator&,const iterator&);
};

template <typename Key,typename Value,typename Hash,typename Pred>
void UnorderedMap<Key,Value,Hash,Pred>::Initialize(number_type bucket_count,const hasher& hash_func,
        const key_equal& equal_func){
    element_size_ = 0;
    bucket_count_ = bucket_count;
    hash_func_ = hash_func;
    equal_func_ = equal_func;
    buckets_pointer_ = new dzerzhinsky::lenin::UnorderedMapList<Key,Value,Pred>*[bucket_count_];
    for(number_type i = 0; i != bucket_count_; ++i)
        buckets_pointer_[i] = nullptr;
}

template <typename Key,typename Value,typename Hash,typename Pred>
void UnorderedMap<Key,Value,Hash,Pred>::ReleaseResource(){
    for(number_type i = 0;i != bucket_count_; ++i)
        if(buckets_pointer_[i] != nullptr) delete buckets_pointer_[i];
    delete [] buckets_pointer_;
    element_size_ = 0;
    buckets_pointer_ = nullptr;
    bucket_count_ = 0;
}

template <typename Key,typename Value,typename Hash,typename Pred>
dzerzhinsky::lenin::UnorderedMapListNode<Key,Value>* UnorderedMap<Key,Value,Hash,Pred>::GetBucketBeginNode(number_type bucket_index) const{
    if(buckets_pointer_[bucket_index] == nullptr) return nullptr;
    return buckets_pointer_[bucket_index]->get_head_pointer();
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
    number_type bucket_count = bucket_count_;
    const hasher hash_func = hash_func_;
    const key_equal equal_func = equal_func_; 
    this->ReleaseResource();
    this->Initialize(bucket_count,hash_func,equal_func);
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::number_type UnorderedMap<Key,Value,Hash,Pred>::BucketCount() const noexcept{
    return bucket_count_;
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::iterator UnorderedMap<Key,Value,Hash,Pred>::Begin(number_type bucket_index) noexcept{
    if(buckets_pointer_ == nullptr) throw new std::runtime_error("NULL Buckets!");
    if(bucket_index >= bucket_count_) throw new std::runtime_error("Wrong Bucket!");
    dzerzhinsky::UnorderedMapIterator<Key,Value,Hash,Pred> temp;
    temp.unordered_map_iterator_pointer_ = new dzerzhinsky::lenin::UnorderedMapIteratorPositive<Key,Value,Hash,Pred>(this);
    for(number_type i = bucket_index; i != bucket_count_; ++i){
        dzerzhinsky::lenin::UnorderedMapListNode<Key,Value>* temp_node_pointer = GetBucketBeginNode(i);
        if(temp_node_pointer != nullptr){
            temp.unordered_map_iterator_pointer_->set_bucket_index(i);
            temp.unordered_map_iterator_pointer_->set_node_pointer(temp_node_pointer);
            return temp; } }
    return temp;
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::iterator UnorderedMap<Key,Value,Hash,Pred>::End() noexcept{
    return End(bucket_count_ - 1);
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::iterator UnorderedMap<Key,Value,Hash,Pred>::End(number_type bucket_index) noexcept{
    if(buckets_pointer_ == nullptr) throw new std::runtime_error("NULL Buckets!");
    if(bucket_index >= bucket_count_) throw new std::runtime_error("Wrong Bucket!");
    dzerzhinsky::UnorderedMapIterator<Key,Value,Hash,Pred> temp;
    temp.unordered_map_iterator_pointer_ = new dzerzhinsky::lenin::UnorderedMapIteratorPositive<Key,Value,Hash,Pred>(this);
    if(bucket_index == bucket_count_ - 1) return temp;
    for(number_type i = bucket_index + 1; i != bucket_count_; ++i){
        dzerzhinsky::lenin::UnorderedMapListNode<Key,Value>* temp_node_pointer = GetBucketBeginNode(i);
        if(temp_node_pointer != nullptr){
            temp.unordered_map_iterator_pointer_->set_bucket_index(i);
            temp.unordered_map_iterator_pointer_->set_node_pointer(temp_node_pointer);
            return temp;
        }
    }
    return temp;
}

template <typename Key,typename Value,typename Hash,typename Pred>
bool UnorderedMap<Key,Value,Hash,Pred>::IsEmpty() const{
    return element_size_ == 0;
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::number_type UnorderedMap<Key,Value,Hash,Pred>::Size() const{
    return element_size_;
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::iterator UnorderedMap<Key,Value,Hash,Pred>::Find(const key_type &key){
    dzerzhinsky::UnorderedMapIterator<Key,Value,Hash,Pred> temp;
    temp.unordered_map_iterator_pointer_ = new dzerzhinsky::lenin::UnorderedMapIteratorPositive<Key,Value,Hash,Pred>(this);
    for(number_type i = 0; i != bucket_count_; ++i){
        if(buckets_pointer_[i] != nullptr){
            dzerzhinsky::lenin::UnorderedMapListNode<Key,Value> *temp_node = buckets_pointer_[i]->Find(key);
            if(temp_node != nullptr){
                temp.unordered_map_iterator_pointer_->set_bucket_index(i);
                temp.unordered_map_iterator_pointer_->set_node_pointer(temp_node);
                return temp;
            }
        }
    }
    return temp;
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::mapped_type& UnorderedMap<Key,Value,Hash,Pred>::At(const key_type &key){
   auto iter = Find(key);
   if(iter == End()) throw new std::runtime_error("No Such Key!");
   return iter->second;
}

template <typename Key,typename Value,typename Hash,typename Pred>
const typename UnorderedMap<Key,Value,Hash,Pred>::mapped_type& UnorderedMap<Key,Value,Hash,Pred>::At(const key_type &key) const{
   auto iter = Find(key);
   if(iter == End()) throw new std::runtime_error("No Such Key!");
   return iter->second;
}

template <typename Key,typename Value,typename Hash,typename Pred>
template <typename Iterator>
void UnorderedMap<Key,Value,Hash,Pred>::Insert(Iterator iterator_first,Iterator iterator_second){
    for(Iterator iterator_temp = iterator_first;iterator_temp != iterator_second; ++iterator_temp)
        Insert(*iterator_temp);
}

template <typename Key,typename Value,typename Hash,typename Pred>
void UnorderedMap<Key,Value,Hash,Pred>::Insert(std::initializer_list<Pair<Key,Value>> list){
    number_type size = list.size();
    if(size == 0) return;
    for(number_type i = 0;i != size; ++i)
        this->Insert(*(list.begin() + i));
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::iterator UnorderedMap<Key,Value,Hash,Pred>::Insert(const Pair<Key,Value> &insert_pair){
    number_type hash_index = hash_func_(insert_pair.first) % bucket_count_;
    if(buckets_pointer_[hash_index] == nullptr)
        buckets_pointer_[hash_index] = new dzerzhinsky::lenin::UnorderedMapList<Key,Value,Pred>();
    element_size_ += buckets_pointer_[hash_index]->Add(insert_pair.first,insert_pair.second);
    dzerzhinsky::UnorderedMapIterator<Key,Value,Hash,Pred> temp;
    temp.unordered_map_iterator_pointer_ = new dzerzhinsky::lenin::UnorderedMapIteratorPositive<Key,Value,Hash,Pred>(this,
            buckets_pointer_[hash_index]->Find(insert_pair.first),hash_index);
    return temp;
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::iterator UnorderedMap<Key,Value,Hash,Pred>::Insert(Pair<Key,Value> &&insert_pair){
    number_type hash_index = hash_func_(insert_pair.first) % bucket_count_;
    if(buckets_pointer_[hash_index] == nullptr)
        buckets_pointer_[hash_index] = new dzerzhinsky::lenin::UnorderedMapList<Key,Value,Pred>();
    element_size_ += buckets_pointer_[hash_index]->Add(std::move(insert_pair.first),std::move(insert_pair.second));
    dzerzhinsky::UnorderedMapIterator<Key,Value,Hash,Pred> temp;
    temp.unordered_map_iterator_pointer_ = new dzerzhinsky::lenin::UnorderedMapIteratorPositive<Key,Value,Hash,Pred>(this,
            buckets_pointer_[hash_index]->Find(insert_pair.first),hash_index);
    return temp;
}

template <typename Key,typename Value,typename Hash,typename Pred>
bool UnorderedMap<Key,Value,Hash,Pred>::Erase(const key_type &key){
    for(number_type i = 0; i != bucket_count_; ++i){
        if(buckets_pointer_[i] != nullptr && buckets_pointer_[i]->Erase(key)){
            --element_size_;
            if(buckets_pointer_[i]->get_head_pointer() == nullptr){
                delete buckets_pointer_[i];
                buckets_pointer_[i] = nullptr;
            }
            return true;
        }
    } 
    return false;
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::iterator UnorderedMap<Key,Value,Hash,Pred>::Erase(const iterator &iterator_target){
    auto iterator_result = iterator_target;  
    ++iterator_result;
    buckets_pointer_[iterator_target.unordered_map_iterator_pointer_->get_bucket_index()]->Erase(iterator_target->first);
    auto pointer = buckets_pointer_[iterator_target.unordered_map_iterator_pointer_->get_bucket_index()]->get_head_pointer();
    if(pointer == nullptr){
        delete buckets_pointer_[iterator_target.unordered_map_iterator_pointer_->get_bucket_index()];
        buckets_pointer_[iterator_target.unordered_map_iterator_pointer_->get_bucket_index()] = nullptr;
    }
    --element_size_;
    return iterator_result;
}

template <typename Key,typename Value,typename Hash,typename Pred>
typename UnorderedMap<Key,Value,Hash,Pred>::iterator UnorderedMap<Key,Value,Hash,Pred>::Erase(const iterator &iterator_first,
        const iterator &iterator_second){
    auto iterator_temp = iterator_first;
    while(iterator_temp != iterator_second){
        auto iterator_temp_temp = iterator_temp;
        ++iterator_temp_temp;
        buckets_pointer_[iterator_temp.unordered_map_iterator_pointer_->get_bucket_index()]->Erase(iterator_temp->first);
        auto pointer = buckets_pointer_[iterator_temp.unordered_map_iterator_pointer_->get_bucket_index()]->get_head_pointer();
        if(pointer == nullptr){
            delete buckets_pointer_[iterator_temp.unordered_map_iterator_pointer_->get_bucket_index()];
            buckets_pointer_[iterator_temp.unordered_map_iterator_pointer_->get_bucket_index()] = nullptr;
        }
        iterator_temp = iterator_temp_temp;
        --element_size_;
    }
    return iterator_second;
}

}
#endif
