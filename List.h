#ifndef LIST_H
#define LIST_H
#include <initializer_list>
#include <iostream>
namespace sablin{
	
template <typename T>
class List;

namespace dzerzhinsky{	
	
namespace lenin{

template <typename T>
class ListNode{
public:
	T 		*element_pointer_ = nullptr;
	ListNode<T> *last_node_ 	  = nullptr;
	ListNode<T> *next_node_ 	  = nullptr;
public:
	ListNode() = default;
	ListNode(const ListNode&) 			 = delete;
	ListNode(ListNode&&)    			 = delete;
	ListNode& operator=(const ListNode&) = delete;
	ListNode& operator=(ListNode&&) 	 = delete;
	~ListNode();
};

template <typename T>
ListNode<T>::~ListNode(){
	if(element_pointer_ != nullptr)
		delete element_pointer_;
	element_pointer_ = nullptr;
}

template <typename T>
class ListIteratorBase{
private:
    ListNode<T> *node_pointer_;
public:
    ListIteratorBase() : node_pointer_(nullptr){}
    ListIteratorBase(const ListIteratorBase&) = default;
    ListIteratorBase& operator=(const ListIteratorBase&) = default;
    ListIteratorBase& operator=(ListIteratorBase&&) = default;
    virtual ~ListIteratorBase();

    void set_node_pointer(ListNode<T>*);
    ListNode<T>* get_node_pointer() const;

    virtual void StepNext()=0;
    virtual void StepLast()=0;
};

template <typename T>
ListIteratorBase<T>::~ListIteratorBase(){
    node_pointer_ = nullptr;
}

template <typename T>
void ListIteratorBase<T>::set_node_pointer(ListNode<T> *node_pointer){
    node_pointer_ = node_pointer;
}

template <typename T>
ListNode<T>* ListIteratorBase<T>::get_node_pointer() const{
    return node_pointer_;
}

template <typename T>
class ListIteratorPositive : public ListIteratorBase<T>{
public:
	ListIteratorPositive(ListNode<T>*);
	ListIteratorPositive(const ListIteratorPositive&);
	ListIteratorPositive(ListIteratorPositive&&);
	ListIteratorPositive& operator=(const ListIteratorPositive&);
	ListIteratorPositive& operator=(ListIteratorPositive&&);
	~ListIteratorPositive() = default;
	
    void StepNext() override;
    void StepLast() override;
};

template <typename T>
ListIteratorPositive<T>::ListIteratorPositive(ListNode<T> *node_pointer){
    this->set_node_pointer(node_pointer);
}

template <typename T>
ListIteratorPositive<T>::ListIteratorPositive(const ListIteratorPositive &another){
	this->set_node_pointer(another.get_pointer());
}

template <typename T>
ListIteratorPositive<T>::ListIteratorPositive(ListIteratorPositive &&another){
    this->set_node_pointer(another.get_node_pointer());
    another.set_pointer(nullptr);
}

template <typename T>
ListIteratorPositive<T>& ListIteratorPositive<T>::operator=(const ListIteratorPositive &another){
    if(this == &another) return *this;
    this->set_node_pointer(another.get_node_pointer());
    return *this;
}

template <typename T>
ListIteratorPositive<T>& ListIteratorPositive<T>::operator=(ListIteratorPositive &&another){
	if(this == &another) return *this;
    this->set_node_pointer(another.get_node_pointer());
    another.set_node_pointer(nullptr);
    return *this;
} 

template <typename T>
void ListIteratorPositive<T>::StepNext(){
    ListNode<T>* node_pointer_temp = this->get_node_pointer();
    if(node_pointer_temp == nullptr)
        throw new std::runtime_error("StepNext Wrong!");
    node_pointer_temp = node_pointer_temp->next_node_;
    this->set_node_pointer(node_pointer_temp);
}

template <typename T>
void ListIteratorPositive<T>::StepLast(){
    ListNode<T>* node_pointer_temp = this->get_node_pointer();
    if(node_pointer_temp == nullptr)
        throw new std::runtime_error("StepLast Wrong!");
    node_pointer_temp = node_pointer_temp->last_node_;
    this->set_node_pointer(node_pointer_temp);
}

template <typename T>
class ListIteratorNegative : public ListIteratorBase<T>{
public:
	ListIteratorNegative(ListNode<T>*);
	ListIteratorNegative(const ListIteratorNegative&);
	ListIteratorNegative(ListIteratorNegative&&);
	ListIteratorNegative& operator=(const ListIteratorNegative&);
	ListIteratorNegative& operator=(ListIteratorNegative&&);
	~ListIteratorNegative() = default;	
	
    void StepNext() override;
    void StepLast() override;
};

template <typename T>
ListIteratorNegative<T>::ListIteratorNegative(ListNode<T> *node_pointer){
    this->set_node_pointer(node_pointer);
}
	
template <typename T>
ListIteratorNegative<T>::ListIteratorNegative(const ListIteratorNegative &another){
	this->set_node_pointer(another.get_node_pointer());
}

template <typename T>
ListIteratorNegative<T>::ListIteratorNegative(ListIteratorNegative &&another){
	this->set_node_pointer(another.get_node_pointer());
	another.set_node_pointer(nullptr);
}

template <typename T>
void ListIteratorNegative<T>::StepNext(){
    ListNode<T> *temp_node_pointer = this->get_node_pointer();
    if(temp_node_pointer == nullptr)
        throw new std::runtime_error("StepNext Wrong!");
    temp_node_pointer = temp_node_pointer->last_node_;
    this->set_node_pointer(temp_node_pointer);
}

template <typename T>
void ListIteratorNegative<T>::StepLast(){
    ListNode<T> *temp_node_pointer = this->get_node_pointer();
    if(temp_node_pointer == nullptr)
        throw new std::runtime_error("StepLast Wrong!");
    temp_node_pointer = temp_node_pointer->next_node_;
    this->set_node_pointer(temp_node_pointer);
}
}

template <typename T>
class ListIterator{
    friend class List<T>;
    template <typename TYPE>
    friend bool operator==(const ListIterator<TYPE>&,const ListIterator<TYPE>&);
    template <typename TYPE>
    friend bool operator!=(const ListIterator<TYPE>&,const ListIterator<TYPE>&);
private:
    lenin::ListIteratorBase<T> *list_iterator_base_pointer_;
public:
    ListIterator();
    ListIterator(const ListIterator&);
    ListIterator(ListIterator&&);
    ListIterator& operator=(const ListIterator&);
    ListIterator& operator=(ListIterator&&);
    ~ListIterator();

    ListIterator<T>& operator++();
    ListIterator<T>& operator--();
    ListIterator<T> operator++(int);
    ListIterator<T> operator--(int);

    T& operator*() const;
    T* operator->() const;
};

template <typename T>
ListIterator<T>::ListIterator():
    list_iterator_base_pointer_(nullptr){}

template <typename T>
ListIterator<T>::ListIterator(const ListIterator &another){
    if(another.list_iterator_base_pointer_ == nullptr){
        list_iterator_base_pointer_ = nullptr;
        return;
    }
    if(typeid(*(another.list_iterator_base_pointer_)) == typeid(lenin::ListIteratorPositive<T>))
        list_iterator_base_pointer_ = new lenin::ListIteratorPositive<T>(another.list_iterator_base_pointer_->get_node_pointer());
    else if(typeid(*(another.list_iterator_base_pointer_)) == typeid(lenin::ListIteratorNegative<T>))
        list_iterator_base_pointer_ = new lenin::ListIteratorNegative<T>(another.list_iterator_base_pointer_->get_node_pointer());
    else
        throw new std::runtime_error("Construct Wrong Owing to Wrong Type!");
}

template <typename T>
ListIterator<T>::ListIterator(ListIterator &&another){
    if(another.list_iterator_base_pointer_ == nullptr){
        list_iterator_base_pointer_ = nullptr;
        return;
    }
    list_iterator_base_pointer_ = another.list_iterator_base_pointer_;
    another.list_iterator_base_pointer_ = nullptr;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator=(const ListIterator &another){
    if(this == &another) return *this;

    lenin::ListIteratorBase<T> *temp_pointer = nullptr;
    if(another.list_iterator_base_pointer_ == nullptr)
        temp_pointer = nullptr;
    else if(typeid(*(another.list_iterator_base_pointer_)) == typeid(lenin::ListIteratorPositive<T>))
        temp_pointer = new lenin::ListIteratorPositive<T>(another.list_iterator_base_pointer_->get_node_pointer());
    else if(typeid(*(another.list_iterator_base_pointer_)) == typeid(lenin::ListIteratorNegative<T>))
        temp_pointer = new lenin::ListIteratorNegative<T>(another.list_itertator_base_pointer_->get_node_pointer());
    else
        throw new std::runtime_error("Construct Wrong Owing to Wrong Type!");

    if(list_iterator_base_pointer_ != nullptr)
        delete list_iterator_base_pointer_;

    list_iterator_base_pointer_ = temp_pointer;
    return *this;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator=(ListIterator &&another){
    if(this == &another) return *this;
    if(list_iterator_base_pointer_ != nullptr)
        delete list_iterator_base_pointer_;
    list_iterator_base_pointer_ = another.list_iterator_base_pointer_;
    another.list_iterator_base_pointer_ = nullptr;
    return *this;
}

template <typename T>
ListIterator<T>::~ListIterator(){
    if(list_iterator_base_pointer_ != nullptr)
        delete list_iterator_base_pointer_;
    list_iterator_base_pointer_ = nullptr;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator++(){
    if(list_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    list_iterator_base_pointer_->StepNext();
    return *this;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator--(){
    if(list_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    list_iterator_base_pointer_->StepLast();
    return *this;
}

template <typename T>
ListIterator<T> ListIterator<T>::operator++(int){
    if(list_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator");
    ListIterator temp(*this);
    list_iterator_base_pointer_->StepNext();
    return temp;
}

template <typename T>
ListIterator<T> ListIterator<T>::operator--(int){
    if(list_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator");
    ListIterator temp(*this);
    list_iterator_base_pointer_->StepLast();
    return temp;
}

template <typename T>
T& ListIterator<T>::operator*() const{
    if(list_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    lenin::ListNode<T> *temp_node_pointer = list_iterator_base_pointer_->get_node_pointer();
    if(temp_node_pointer == nullptr)
        throw new std::runtime_error("NULL Node!");
    return *(temp_node_pointer->element_pointer_);
}

template <typename T>
T* ListIterator<T>::operator->() const{
    if(list_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    lenin::ListNode<T> *temp_node_pointer = list_iterator_base_pointer_->get_node_pointer();
    if(temp_node_pointer == nullptr)
        throw new std::runtime_error("NULL Node!");
    return temp_node_pointer->element_pointer_;
}

template <typename T>
bool operator==(const ListIterator<T> &lhs,const ListIterator<T> &rhs){
    if(lhs.list_iterator_base_pointer_ != nullptr && rhs.list_iterator_base_pointer_ != nullptr){
        if(typeid(*(lhs.list_iterator_base_pointer_)) == typeid(*(rhs.list_iterator_base_pointer_)))
            return lhs.list_iterator_base_pointer_->get_node_pointer() == rhs.list_iterator_base_pointer_->get_node_pointer();
        else
            return false;
    }else if(lhs.list_iterator_base_pointer_ == nullptr && rhs.list_iterator_base_pointer_ == nullptr){
        return true;
    }else{
        return false;
    }
}

template <typename T>
bool operator!=(const ListIterator<T> &lhs,const ListIterator<T> &rhs){
    return !(lhs == rhs);
}

}
template <typename T>
class List{
public:
	typedef T 	   						     element_type;
	typedef size_t 						     number_type;
	typedef dzerzhinsky::ListIterator<T>     iterator;
	
	//Debug--------------------------------------------------------
	void DebugPrint(){
		std::cout << "element_size_ : " << element_size_ << std::endl;
		for(dzerzhinsky::lenin::ListNode<T> *temp = head_node_;temp != tail_node_;temp = temp->next_node_)
			std::cout << *temp->element_pointer_ << std::endl;
		if(tail_node_ != nullptr) std::cout << *tail_node_->element_pointer_ << std::endl;
	}
	//Debug--------------------------------------------------------
private:
	number_type                   element_size_;
	dzerzhinsky::lenin::ListNode<T> 	  *head_node_;
	dzerzhinsky::lenin::ListNode<T> 	  *tail_node_;
	
	dzerzhinsky::lenin::ListNode<T>      *beyond_head_node_;
	dzerzhinsky::lenin::ListNode<T>	  *beyond_tail_node_;
	
	void Initialize();
	void ReleaseResource();

    iterator InsertPositive(const iterator,const T&);
	iterator InsertPositive(const iterator,const number_type,const T&);
	template <typename Iterator>
	iterator InsertPositive(const iterator,const Iterator,const Iterator);
	
	iterator ErasePositive(const iterator);
	iterator ErasePositive(const iterator,const iterator);
	
	iterator InsertNegative(const iterator,const T&);
	iterator InsertNegative(const iterator,const number_type,const T&);
	template <typename Iterator>
	iterator InsertNegative(const iterator,const Iterator,const Iterator);
	
	iterator EraseNegative(const iterator);
	iterator EraseNegative(const iterator,const iterator);

public:
	List();
	explicit List(const number_type,const T&);
	explicit List(std::initializer_list<T>);
	template <typename Iterator>
	explicit List(const Iterator,const Iterator);
	
	List(const List&);
	List(List&&);
	
	List& operator=(const List&);
	List& operator=(List&&);
	
	~List();

	void Clear() noexcept;
	
	iterator Begin()  noexcept;
	iterator End()    noexcept;
	iterator RBegin() noexcept;
	iterator REnd()   noexcept;
	
	bool IsEmpty() const;
	number_type Size() const;
	
	T Front() const;
	T Back() const;
	
	void Assign(const number_type,const T&);
	template <typename Iterator>
	void Assign(const Iterator,const Iterator);
	void Assign(std::initializer_list<T>);
	
	void PushFront(const T&);
	void PushFront(T&&);
	
	void PopFront();
	
	void PushBack(const T&);
	void PushBack(T&&);
	
	void PopBack();
	
	iterator Insert(const iterator,const T&);
	iterator Insert(const iterator,const number_type,const T&);
	template <typename Iterator>
	iterator Insert(const iterator,const Iterator,const Iterator);
	
	iterator Erase(const iterator);
	iterator Erase(const iterator,const iterator);
};

template <typename T>
void List<T>::Initialize(){
	element_size_ = 0;
	beyond_head_node_ = new dzerzhinsky::lenin::ListNode<T>();
	beyond_tail_node_ = new dzerzhinsky::lenin::ListNode<T>();
	head_node_ = nullptr;
	tail_node_ = nullptr;
	beyond_head_node_->next_node_ = beyond_tail_node_;
	beyond_tail_node_->last_node_ = beyond_head_node_;
}

template <typename T>
void List<T>::ReleaseResource(){
	while(beyond_head_node_ != nullptr){
		dzerzhinsky::lenin::ListNode<T> *temp = beyond_head_node_;
		beyond_head_node_ = beyond_head_node_->next_node_;
		delete temp;
	}
	head_node_ = tail_node_ = beyond_head_node_ = beyond_tail_node_ = nullptr;
	element_size_ = 0;
}

template <typename T>
List<T>::List() { Initialize();}

template <typename T>
List<T>::List(const number_type size,const T &element){
	if(size == 0) throw new std::runtime_error("Size Wrong ---- List(size,element)");
	this->Initialize();
	for(number_type i = 0;i != size; ++i){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(element);
		if(i == 0){
			head_node_ = temp_node;
			tail_node_ = temp_node;
			beyond_head_node_->next_node_ = head_node_;
			head_node_->last_node_ = beyond_head_node_;
			beyond_tail_node_->last_node_ = tail_node_;
			tail_node_->next_node_ = beyond_tail_node_;
		}else{
			tail_node_->next_node_ = temp_node;
			temp_node->last_node_  = tail_node_;
			tail_node_ = temp_node;
			tail_node_->next_node_ = beyond_tail_node_;
			beyond_tail_node_->last_node_ = tail_node_;
		}
	}
	element_size_ = size;
}

template <typename T>
List<T>::List(std::initializer_list<T> list){
	number_type size = list.size();
	if(size == 0) throw new std::runtime_error("Size Wrong ----- List(initializer_list)");
	this->Initialize();
	for(number_type i = 0;i != size; ++i){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(*(list.begin() + i));
		if(i == 0){
			head_node_ = temp_node;
			tail_node_ = temp_node;
			beyond_head_node_->next_node_ = head_node_;
			head_node_->last_node_ = beyond_head_node_;
			beyond_tail_node_->last_node_ = tail_node_;
			tail_node_->next_node_ = beyond_tail_node_;
		}else{
			tail_node_->next_node_ = temp_node;
			temp_node->last_node_  = tail_node_;
			tail_node_ = temp_node;
			tail_node_->next_node_ = beyond_tail_node_;
			beyond_tail_node_->last_node_ = tail_node_;
		}
	}
	element_size_ = size;
}

template <typename T>
template <typename Iterator>
List<T>::List(const Iterator first_iterator,const Iterator second_iterator){
	for(Iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator)	
		++element_size_;
	
	this->Initialize();
	
	for(Iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(*temp_iterator);
		if(temp_iterator == first_iterator){
			head_node_ = temp_node;
			tail_node_ = temp_node;
			beyond_head_node_->next_node_ = head_node_;
			head_node_->last_node_ = beyond_head_node_;
			beyond_tail_node_->last_node_ = tail_node_;
			tail_node_->next_node_ = beyond_tail_node_;
		}else{
			tail_node_->next_node_ = temp_node;
			temp_node->last_node_  = tail_node_;
			tail_node_ = temp_node;
			tail_node_->next_node_ = beyond_tail_node_;
			beyond_tail_node_->last_node_ = tail_node_;
		}
	}
}

template <typename T>
List<T>::List(const List<T> &another){
	this->Initialize();
	element_size_ = another.element_size_;
	for(dzerzhinsky::lenin::ListNode<T> *temp = another.beyond_tail_node_->next_node_;
			temp != another.beyond_tail_node_;temp = temp->next_node_){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(*(temp->element_pointer_));
		if(temp == another.head_node_){
			head_node_ = temp_node;
			tail_node_ = temp_node;
			beyond_head_node_->next_node_ = head_node_;
			head_node_->last_node_ = beyond_head_node_;
			beyond_tail_node_->last_node_ = tail_node_;
			tail_node_->next_node_ = beyond_tail_node_;
		}else{
			tail_node_->next_node_ = temp_node;
			temp_node->last_node_  = tail_node_;
			tail_node_ = temp_node;
			tail_node_->next_node_ = beyond_tail_node_;
			beyond_tail_node_->last_node_ = tail_node_;
		}
	}
}

template <typename T>
List<T>::List(List<T> &&another){
	element_size_ = another.element_size_;
	head_node_ = another.head_node_;
	tail_node_ = another.tail_node_;
	beyond_head_node_ = another.beyond_head_node_;
	beyond_tail_node_ = another.beyond_tail_node_;
	
	another.Initialize();
}

template <typename T>
List<T>& List<T>::operator=(const List &another){
	if(&another == this) return *this;
	this->Clear();
	element_size_ = another.element_size_;
	for(dzerzhinsky::lenin::ListNode<T> *temp = another.beyond_tail_node_->next_node_;
		temp != another.beyond_tail_node_;temp = temp->next_node_){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(*(temp->element_pointer_));
		if(temp == another.head_node_){
			head_node_ = temp_node;
			tail_node_ = temp_node;
			beyond_head_node_->next_node_ = head_node_;
			head_node_->last_node_ = beyond_head_node_;
			beyond_tail_node_->last_node_ = tail_node_;
			tail_node_->next_node_ = beyond_tail_node_;
		}else{
			tail_node_->next_node_ = temp_node;
			temp_node->last_node_  = tail_node_;
			tail_node_ = temp_node;
			tail_node_->next_node_ = beyond_tail_node_;
			beyond_tail_node_->last_node_ = tail_node_;
		}
	}
	return *this;
}

template <typename T>
List<T>& List<T>::operator=(List &&another){
	if(&another == this) return *this;
	this->Clear();
	element_size_ = another.element_size_;
	head_node_ = another.head_node_;
	tail_node_ = another.tail_node_;
	beyond_head_node_ = another.beyond_head_node_;
	beyond_tail_node_ = another.beyond_tail_node_;
	
	another.Initialize();
	return *this;
}

template <typename T>
List<T>::~List<T>(){
	this->ReleaseResource();
}

template <typename T>
void List<T>::Clear() noexcept {
	this->ReleaseResource();
	this->Initialize();
}

template <typename T>
typename List<T>::iterator List<T>::Begin() noexcept{
    dzerzhinsky::ListIterator<T> temp;
    temp.list_iterator_base_pointer_ = new dzerzhinsky::lenin::ListIteratorPositive<T>(head_node_);
    return temp;
}

template <typename T>
typename List<T>::iterator List<T>::End() noexcept{
    dzerzhinsky::ListIterator<T> temp;
    if(tail_node_ == nullptr) temp.list_iterator_base_pointer_ = new dzerzhinsky::lenin::ListIteratorPositive<T>(nullptr);
    else                      temp.list_iterator_base_pointer_ = new dzerzhinsky::lenin::ListIteratorPositive<T>(beyond_tail_node_);
    return temp;
}

template <typename T>
typename List<T>::iterator List<T>::RBegin() noexcept{
    dzerzhinsky::ListIterator<T> temp;
    temp.list_iterator_base_pointer_ = new dzerzhinsky::lenin::ListIteratorNegative<T>(tail_node_);
    return temp;
}

template <typename T>
typename List<T>::iterator List<T>::REnd() noexcept{
    dzerzhinsky::ListIterator<T> temp;
    if(head_node_ == nullptr) temp.list_iterator_base_pointer_ = new dzerzhinsky::lenin::ListIteratorNegative<T>(nullptr);
    else                      temp.list_iterator_base_pointer_ = new dzerzhinsky::lenin::ListIteratorNegative<T>(beyond_head_node_);
    return temp;
}

template <typename T>
bool List<T>::IsEmpty() const{
	return head_node_ == nullptr;
}

template <typename T>
typename List<T>::number_type List<T>::Size() const{
	return element_size_;
}

template <typename T>
T List<T>::Front() const{
	return *(head_node_->element_pointer_);
}

template <typename T>
T List<T>::Back() const{
	return *(tail_node_->element_pointer_);
}

template <typename T>
void List<T>::Assign(const number_type size,const T &element){
	if(size == 0) throw new std::runtime_error("Size Wrong ---- Assign(size,element)");
	this->Clear();
	for(number_type i = 0;i != size; ++i){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(element);
		if(i == 0){
			head_node_ = temp_node;
			tail_node_ = temp_node;
			beyond_head_node_->next_node_ = head_node_;
			head_node_->last_node_ = beyond_head_node_;
			beyond_tail_node_->last_node_ = tail_node_;
			tail_node_->next_node_ = beyond_tail_node_;
		}else{
			tail_node_->next_node_ = temp_node;
			temp_node->last_node_  = tail_node_;
			tail_node_ = temp_node;
			tail_node_->next_node_ = beyond_tail_node_;
			beyond_tail_node_->last_node_ = tail_node_;
		}
	}
	element_size_ = size;
}

template <typename T>
void List<T>::Assign(std::initializer_list<T> list){
	number_type size = list.size();
	if(size == 0) throw new std::runtime_error("Size Wrong ----- List(initializer_list)");
	this->Clear();
	for(number_type i = 0;i != size; ++i){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(*(list.begin() + i));
		if(i == 0){
			head_node_ = temp_node;
			tail_node_ = temp_node;
			beyond_head_node_->next_node_ = head_node_;
			head_node_->last_node_ = beyond_head_node_;
			beyond_tail_node_->last_node_ = tail_node_;
			tail_node_->next_node_ = beyond_tail_node_;
		}else{
			tail_node_->next_node_ = temp_node;
			temp_node->last_node_  = tail_node_;
			tail_node_ = temp_node;
			tail_node_->next_node_ = beyond_tail_node_;
			beyond_tail_node_->last_node_ = tail_node_;
		}
	}
	element_size_ = size;
}

template <typename T>
template <typename Iterator>
void List<T>::Assign(const Iterator first_iterator,const Iterator second_iterator){
	for(Iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator)	
		++element_size_;
	this->Clear();
	
	for(Iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(*temp_iterator);
		if(temp_iterator == first_iterator){
			head_node_ = temp_node;
			tail_node_ = temp_node;
			beyond_head_node_->next_node_ = head_node_;
			head_node_->last_node_ = beyond_head_node_;
			beyond_tail_node_->last_node_ = tail_node_;
			tail_node_->next_node_ = beyond_tail_node_;
		}else{
			tail_node_->next_node_ = temp_node;
			temp_node->last_node_  = tail_node_;
			tail_node_ = temp_node;
			tail_node_->next_node_ = beyond_tail_node_;
			beyond_tail_node_->last_node_ = tail_node_;
		}
	}	
}

template <typename T>
void List<T>::PushFront(const T &element){
	++element_size_;
	if(head_node_ == nullptr){
		head_node_ = new dzerzhinsky::lenin::ListNode<T>();
		head_node_->element_pointer_ = new T(element);
		tail_node_ = head_node_;
		head_node_->last_node_ = beyond_head_node_;
		head_node_->next_node_ = beyond_tail_node_;
		beyond_head_node_->next_node_ = head_node_;
		beyond_tail_node_->last_node_ = head_node_;
		return;
	}
	
	dzerzhinsky::lenin::ListNode<T>* temp = new dzerzhinsky::lenin::ListNode<T>();
	temp->element_pointer_ = new T(element);
	head_node_->last_node_ = temp;
	temp->next_node_ = head_node_;
	temp->last_node_ = beyond_head_node_;
	beyond_head_node_->next_node_ = temp;
	head_node_ = temp;
}

template <typename T>
void List<T>::PushFront(T &&element){
	++element_size_;
	if(head_node_ == nullptr){
		head_node_ = new dzerzhinsky::lenin::ListNode<T>();
		head_node_->element_pointer_ = new T(std::move(element));
		tail_node_ = head_node_;
		head_node_->last_node_ = beyond_head_node_;
		head_node_->next_node_ = beyond_tail_node_;
		beyond_head_node_->next_node_ = head_node_;
		beyond_tail_node_->last_node_ = head_node_;
		return;
	}
	
	dzerzhinsky::lenin::ListNode<T>* temp = new dzerzhinsky::lenin::ListNode<T>();
	temp->element_pointer_ = new T(std::move(element));
	head_node_->last_node_ = temp;
	temp->next_node_ = head_node_;
	temp->last_node_ = beyond_head_node_;
	beyond_head_node_->next_node_ = temp;
	head_node_ = temp;
}

template <typename T>
void List<T>::PopFront(){
	if(head_node_ == nullptr)
		throw new std::runtime_error("No Element ---- PopFront()");
	
	if(element_size_ == 1) {this->Clear(); return;}
	
	--element_size_;
	head_node_ = head_node_->next_node_;
	delete head_node_->last_node_;
	head_node_->last_node_ = beyond_head_node_;
	beyond_head_node_->next_node_ = head_node_;
}

template <typename T>
void List<T>::PushBack(const T &element){
	if(head_node_ == nullptr){
		this->PushFront(element);
		return;
	}
	++element_size_;
	
	dzerzhinsky::lenin::ListNode<T>* temp = new dzerzhinsky::lenin::ListNode<T>();
	temp->element_pointer_ = new T(element);
	tail_node_->next_node_ = temp;
	temp->last_node_ = tail_node_;
	tail_node_ = temp;
	temp->next_node_ = beyond_tail_node_;
	beyond_tail_node_->last_node_ = temp;
}

template <typename T>
void List<T>::PushBack(T &&element){
	if(head_node_ == nullptr){
		this->PushFront(std::move(element));
		return;
	}
	++element_size_;
	
	dzerzhinsky::lenin::ListNode<T>* temp = new dzerzhinsky::lenin::ListNode<T>();
	temp->element_pointer_ = new T(std::move(element));
	tail_node_->next_node_ = temp;
	temp->last_node_ = tail_node_;
	tail_node_ = temp;
	temp->next_node_ = beyond_tail_node_;
	beyond_tail_node_->last_node_ = temp;
}

template <typename T>
void List<T>::PopBack(){
	if(tail_node_ == nullptr)
		throw new std::runtime_error("No Element ---- PopFront()");
	
	if(element_size_ == 1) {this->Clear(); return;}
	
	--element_size_;
	tail_node_ = tail_node_->last_node_;
	delete tail_node_->next_node_;
	tail_node_->next_node_ = beyond_tail_node_;
	beyond_tail_node_->last_node_ = tail_node_;
}

template <typename T>
typename List<T>::iterator List<T>::InsertPositive(const iterator var_iterator,
										   const T &element){
	if(var_iterator == this->End()){PushBack(element); return (--this->End());}
	if(var_iterator == this->Begin()){PushFront(element);return this->Begin();}
	
	++element_size_;
	dzerzhinsky::lenin::ListNode<T> *temp_pointer = var_iterator.list_iterator_base_pointer_->get_node_pointer()->last_node_;
	dzerzhinsky::lenin::ListNode<T> *temp = new dzerzhinsky::lenin::ListNode<T>();
	temp->element_pointer_ = new T(element);
	temp->last_node_ = temp_pointer;
	temp->next_node_ = temp_pointer->next_node_;
	temp_pointer->next_node_->last_node_ = temp;
	temp_pointer->next_node_ = temp;
    return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorPositive<T>(temp_pointer->next_node_));
}

template <typename T>
typename List<T>::iterator List<T>::InsertPositive(const iterator iterator,
													const size_t size,const T &element){
	if(size == 0) throw new std::runtime_error("Wrong Size ---- Insert(iter,size,element)");
	
	element_size_ += size;
	dzerzhinsky::lenin::ListNode<T> *head_temp = nullptr;
	dzerzhinsky::lenin::ListNode<T> *tail_temp = nullptr;
	
	for(number_type i = 0;i != size; ++i){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(element);
		if(i == 0){
			head_temp = temp_node;
			tail_temp = temp_node;
		}else{
			tail_temp->next_node_ = temp_node;
			temp_node->last_node_  = tail_temp;
			tail_temp = temp_node;
		}
	}
	
	if(head_node_ == nullptr){
		head_node_ = head_temp;
		tail_node_ = tail_temp;
		head_node_->last_node_ = beyond_head_node_;
		beyond_head_node_->next_node_ = head_node_;
		tail_node_->next_node_ = beyond_tail_node_;
		beyond_tail_node_->last_node_ = tail_node_;
		return this->Begin();
	}
	
	if(iterator == this->Begin()){
		head_node_->last_node_ = tail_temp;
		tail_temp->next_node_ = head_node_;
		head_node_ = head_temp;
		head_node_->last_node_ = beyond_head_node_;
		beyond_head_node_->next_node_ = head_node_;
		return this->Begin();
	}
	
	if(iterator == this->End()){
		tail_node_->next_node_ = head_temp;
		head_temp->last_node_ = tail_node_;
		tail_node_ = tail_temp;
		tail_node_->next_node_ = beyond_tail_node_;
		beyond_tail_node_->last_node_ = tail_node_;
		return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorPositive<T>(head_temp));
	}
	
	dzerzhinsky::lenin::ListNode<T> *temp_pointer = iterator.node_pointer_->last_node_;
	tail_temp->next_node_ = temp_pointer->next_node_;
	temp_pointer->next_node_->last_node_ = tail_temp;
	head_temp->last_node_ = temp_pointer;
	temp_pointer->next_node_ = head_temp;
	return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorPositive<T>(temp_pointer->next_node_));
}

template <typename T>
template <typename Iterator>
typename List<T>::iterator List<T>::InsertPositive(const iterator iterator,
													const Iterator first_iterator,
													const Iterator second_iterator){
	number_type size = 0;
	for(Iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator)
		++size;
	if(size == 0) throw new std::runtime_error("Wrong Iterator ---- Insert(iterator,iterator)");
	
	element_size_ += size;
	dzerzhinsky::lenin::ListNode<T> *head_temp = nullptr;
	dzerzhinsky::lenin::ListNode<T> *tail_temp = nullptr;
	
	Iterator temp_iterator = first_iterator;
	for(number_type i = 0;i != size; ++i){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(*(temp_iterator++));
		if(i == 0){
			head_temp = temp_node;
			tail_temp = temp_node;
		}else{
			tail_temp->next_node_ = temp_node;
			temp_node->last_node_  = tail_temp;
			tail_temp = temp_node;
		}
	}
	
	if(head_node_ == nullptr){
		head_node_ = head_temp;
		tail_node_ = tail_temp;
		head_node_->last_node_ = beyond_head_node_;
		beyond_head_node_->next_node_ = head_node_;
		tail_node_->next_node_ = beyond_tail_node_;
		beyond_tail_node_->last_node_ = tail_node_;
		return this->Begin();
	}
	
	if(iterator == this->Begin()){
		head_node_->last_node_ = tail_temp;
		tail_temp->next_node_ = head_node_;
		head_node_ = head_temp;
		head_node_->last_node_ = beyond_head_node_;
		beyond_head_node_->next_node_ = head_node_;
		return this->Begin();
	}
	
	if(iterator == this->End()){
		tail_node_->next_node_ = head_temp;
		head_temp->last_node_ = tail_node_;
		tail_node_ = tail_temp;
		tail_node_->next_node_ = beyond_tail_node_;
		beyond_tail_node_->last_node_ = tail_node_;
		return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorPositive<T>(head_temp));
	}
	
	dzerzhinsky::lenin::ListNode<T> *temp_pointer = iterator.node_pointer_->last_node_;
	tail_temp->next_node_ = temp_pointer->next_node_;
	temp_pointer->next_node_->last_node_ = tail_temp;
	head_temp->last_node_ = temp_pointer;
	temp_pointer->next_node_ = head_temp;
	return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorPositive<T>(temp_pointer->next_node_));
}

template <typename T>
typename List<T>::iterator List<T>::ErasePositive(const iterator iterator){
	if(iterator == this->End())
		throw new std::runtime_error("Wrong Position ---- Erase(iterator)");
	
	if(iterator == this->Begin()) {PopFront(); return this->Begin();}
	if(iterator == --this->End()) {PopBack(); return this->End();}
	
	--element_size_;
	
	dzerzhinsky::lenin::ListNode<T> *temp_pointer = iterator.node_pointer_->last_node_;
	temp_pointer->next_node_->next_node_->last_node_ = temp_pointer;
	temp_pointer->next_node_ = temp_pointer->next_node_->next_node_;
	delete iterator.node_pointer_;
	return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorPositive<T>(temp_pointer->next_node_));
}

template <typename T>
typename List<T>::iterator List<T>::ErasePositive(const iterator first_iterator,
												   const iterator second_iterator){
	number_type size = 0;
	for(iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator)
		++size;
	if(size == 0) throw new std::runtime_error("Wrong Iterator ---- Erase(iterator,iterator)");
	
	if(first_iterator == this->Begin() && second_iterator == this->End()){
		this->Clear();
		return this->End();
	}
	
	element_size_ -= size;
	dzerzhinsky::lenin::ListNode<T> *head_temp = nullptr;
	dzerzhinsky::lenin::ListNode<T> *tail_temp = nullptr;
	
	
	if(first_iterator == this->Begin()){
		tail_temp = second_iterator.node_pointer_->last_node_;
		head_temp = head_node_;
		head_node_ = second_iterator.node_pointer_;
		head_node_->last_node_ = beyond_head_node_;
		beyond_head_node_->next_node_ = head_node_;
		tail_temp->next_node_ = nullptr;
	}else if(second_iterator == this->End()){
		head_temp = first_iterator.node_pointer_;
		tail_temp = second_iterator.node_pointer_->last_node_;
		tail_node_ = head_temp->last_node_;
		tail_node_->next_node_ = beyond_tail_node_;
		beyond_tail_node_->last_node_ = tail_node_;
		tail_temp->next_node_ = nullptr;
	}else{
		head_temp = first_iterator.node_pointer_;
		tail_temp = second_iterator.node_pointer_->last_node_;
		head_temp->last_node_->next_node_ = tail_temp->next_node_;
		tail_temp->next_node_->last_node_ = head_temp->last_node_;
		tail_temp->next_node_ = nullptr;
	}
	
	while(head_temp != nullptr){
		if(head_temp->next_node_ != nullptr){
			head_temp = head_temp->next_node_;
			delete head_temp->last_node_;
		}else{
			delete head_temp;
			head_temp = nullptr;
		}
	}
	tail_temp = nullptr;
	
	return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorPositive<T>(second_iterator.node_pointer_));
}

template <typename T>
typename List<T>::iterator List<T>::InsertNegative(const iterator iterator,
													const T &element){
	if(iterator == this->RBegin()){PushBack(element);return this->RBegin();}
	if(iterator == this->REnd()){PushFront(element); return (--this->REnd());}
	
	++element_size_;
	dzerzhinsky::lenin::ListNode<T> *temp_pointer = iterator.node_pointer_->next_node_;
	dzerzhinsky::lenin::ListNode<T> *temp = new dzerzhinsky::lenin::ListNode<T>();
	temp->element_pointer_ = new T(element);
	temp->next_node_ = temp_pointer;
	temp->last_node_ = temp_pointer->last_node_;
	temp_pointer->last_node_->next_node_ = temp;
	temp_pointer->last_node_ = temp;
	return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorNegative<T>(temp_pointer->last_node_));
}

template <typename T>
typename List<T>::iterator List<T>::InsertNegative(const iterator iterator,
													const size_t size,const T &element){
	if(size == 0) throw new std::runtime_error("Wrong Size ---- Insert(iter,size,element)");
	
	element_size_ += size;
	dzerzhinsky::lenin::ListNode<T> *head_temp = nullptr;
	dzerzhinsky::lenin::ListNode<T> *tail_temp = nullptr;
	
	for(number_type i = 0;i != size; ++i){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(element);
		if(i == 0){
			head_temp = temp_node;
			tail_temp = temp_node;
		}else{
			tail_temp->last_node_ = temp_node;
			temp_node->next_node_  = tail_temp;
			tail_temp = temp_node;
		}
	}
	
	if(head_node_ == nullptr){
		head_node_ = tail_temp;
		tail_node_ = head_temp;
		head_node_->last_node_ = beyond_head_node_;
		beyond_head_node_->next_node_ = head_node_;
		tail_node_->next_node_ = beyond_tail_node_;
		beyond_tail_node_->last_node_ = tail_node_;
		return this->RBegin();
	}
	
	if(iterator == this->RBegin()){
		tail_node_->next_node_ = tail_temp;
		tail_temp->last_node_ = tail_node_;
		tail_node_ = head_temp;
		tail_node_->next_node_ = beyond_tail_node_;
		beyond_tail_node_->last_node_ = tail_node_;
		return this->RBegin();
	}
	
	if(iterator == this->REnd()){
		head_node_->last_node_ = head_temp;
		head_temp->next_node_ = head_node_;
		head_node_ = tail_temp;
		head_node_->last_node_ = beyond_head_node_;
		beyond_head_node_->next_node_ = head_node_;
		return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorNegative<T>(head_temp));
	}
	
	dzerzhinsky::lenin::ListNode<T> *temp_pointer = iterator.node_pointer_->next_node_;
	tail_temp->last_node_ = temp_pointer->last_node_;
	temp_pointer->last_node_->next_node_ = tail_temp;
	head_temp->next_node_ = temp_pointer;
	temp_pointer->last_node_ = head_temp;
	return dzerzhinsky::ListIterator<T>(dzerzhinsky::lenin::ListIteratorNegative<T>(temp_pointer->last_node_));
}

template <typename T>
template <typename Iterator>
typename List<T>::iterator List<T>::InsertNegative(const iterator iterator,
													const Iterator first_iterator,
													const Iterator second_iterator){
	number_type size = 0;
	for(Iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator)
		++size;
	
	if(size == 0) throw new std::runtime_error("Wrong Iterator ---- Insert(iterator,iterator)");
	
	element_size_ += size;
	dzerzhinsky::lenin::ListNode<T> *head_temp = nullptr;
	dzerzhinsky::lenin::ListNode<T> *tail_temp = nullptr;
	
	Iterator temp_iterator = first_iterator;
	for(number_type i = 0;i != size; ++i){
		dzerzhinsky::lenin::ListNode<T> *temp_node = new dzerzhinsky::lenin::ListNode<T>();
		temp_node->element_pointer_ = new T(*(temp_iterator++));
		if(i == 0){
			head_temp = temp_node;
			tail_temp = temp_node;
		}else{
			tail_temp->last_node_ = temp_node;
			temp_node->next_node_  = tail_temp;
			tail_temp = temp_node;
		}
	}
	
	if(head_node_ == nullptr){
		head_node_ = tail_temp;
		tail_node_ = head_temp;
		head_node_->last_node_ = beyond_head_node_;
		beyond_head_node_->next_node_ = head_node_;
		tail_node_->next_node_ = beyond_tail_node_;
		beyond_tail_node_->last_node_ = tail_node_;
		return this->RBegin();
	}
	
	if(iterator == this->RBegin()){
		tail_node_->next_node_ = tail_temp;
		tail_temp->last_node_ = tail_node_;
		tail_node_ = head_temp;
		tail_node_->next_node_ = beyond_tail_node_;
		beyond_tail_node_->last_node_ = tail_node_;
		return this->RBegin();
	}
	
	if(iterator == this->REnd()){
		head_node_->last_node_ = head_temp;
		head_temp->next_node_ = head_node_;
		head_node_ = tail_temp;
		head_node_->last_node_ = beyond_head_node_;
		beyond_head_node_->next_node_ = head_node_;
		return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorNegative<T>(head_temp));
	}
	
	dzerzhinsky::lenin::ListNode<T> *temp_pointer = iterator.node_pointer_->next_node_;
	tail_temp->last_node_ = temp_pointer->last_node_;
	temp_pointer->last_node_->next_node_ = tail_temp;
	head_temp->next_node_ = temp_pointer;
	temp_pointer->last_node_ = head_temp;
	return dzerzhinsky::ListIterator<T>(dzerzhinsky::lenin::ListIteratorNegative<T>(temp_pointer->last_node_));
}

template <typename T>
typename List<T>::iterator List<T>::EraseNegative(const iterator iterator){
	if(iterator == this->REnd())
		throw new std::runtime_error("Wrong Position ---- Erase(iterator)");
	
	if(iterator == this->RBegin()) {PopBack(); return this->RBegin();}
	if(iterator == --this->REnd()) {PopFront(); return this->REnd();}
	
	--element_size_;
	
	dzerzhinsky::lenin::ListNode<T> *temp_pointer = iterator.node_pointer_->next_node_;
	temp_pointer->last_node_->last_node_->next_node_ = temp_pointer;
	temp_pointer->last_node_ = temp_pointer->last_node_->last_node_;
	delete iterator.node_pointer_;
	return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorNegative<T>(temp_pointer->last_node_));
}

template <typename T>
typename List<T>::iterator List<T>::EraseNegative(const iterator first_iterator,
												   const iterator second_iterator){
	number_type size = 0;
	for(iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator)
		++size;
	if(size == 0) throw new std::runtime_error("Wrong Iterator ---- Erase(iterator,iterator)");
	
	if(first_iterator == this->RBegin() && second_iterator == this->REnd()){
		this->Clear();
		return this->REnd();
	}
	
	element_size_ -= size;
	dzerzhinsky::lenin::ListNode<T> *head_temp = nullptr;
	dzerzhinsky::lenin::ListNode<T> *tail_temp = nullptr;
	
	
	if(first_iterator == this->RBegin()){
		head_temp = second_iterator.node_pointer_->next_node_;
		tail_temp = tail_node_;
		tail_temp->next_node_ = nullptr;
		tail_node_ = second_iterator.node_pointer_;
		tail_node_->next_node_ = beyond_tail_node_;
		beyond_tail_node_->last_node_ = tail_node_;
	}else if(second_iterator == this->REnd()){
		tail_temp = first_iterator.node_pointer_;
		head_temp = head_node_;
		head_node_ = tail_temp->next_node_;
		tail_temp->next_node_ = nullptr;
		head_node_->last_node_ = beyond_head_node_;
		beyond_head_node_->next_node_ = head_node_;
	}else{
		head_temp = second_iterator.node_pointer_->next_node_;
		tail_temp = first_iterator.node_pointer_;
		head_temp->last_node_->next_node_ = tail_temp->next_node_;
		tail_temp->next_node_->last_node_ = head_temp->last_node_;
		tail_temp->next_node_ = nullptr;
	}
	
	while(head_temp != nullptr){
		if(head_temp->next_node_ != nullptr){
			head_temp = head_temp->next_node_;
			delete head_temp->last_node_;
		}else{
			delete head_temp;
			head_temp = nullptr;
		}
	}
	
	return dzerzhinsky::ListIterator<T>(new dzerzhinsky::lenin::ListIteratorNegative<T>(second_iterator.node_pointer_));
}

template <typename T>
typename List<T>::iterator List<T>::Insert(iterator var_iterator,
                                               const T &element){
    if(var_iterator.list_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    else if(typeid(*(var_iterator.list_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::ListIteratorPositive<T>))
        return InsertPositive(var_iterator,element);
    else
        return InsertNegative(var_iterator,element);
}

template <typename T>
typename List<T>::iterator List<T>::Insert(iterator var_iterator,
                                               const number_type size,const T &element){
    if(var_iterator.list_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    else if(typeid(*(var_iterator.list_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::ListIteratorPositive<T>))
        return InsertPositive(var_iterator,size,element);
    else
        return InsertNegative(var_iterator,size,element);
}

template <typename T>
template <typename Iterator>
typename List<T>::iterator List<T>::Insert(iterator var_iterator,
                                               const Iterator iterator_first,
                                               const Iterator iterator_second){
    if(var_iterator.list_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    else if(typeid(*(var_iterator.list_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::ListIteratorPositive<T>))
        return InsertPositive(var_iterator,iterator_first,iterator_second);
    else
        return InsertNegative(var_iterator,iterator_first,iterator_second);
}

template <typename T>
typename List<T>::iterator List<T>::Erase(iterator var_iterator){
    if(var_iterator.list_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    else if(typeid(*(var_iterator.list_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::ListIteratorPositive<T>))
        return ErasePositive(var_iterator);
    else
        return EraseNegative(var_iterator);
}

template <typename T>
typename List<T>::iterator List<T>::Erase(iterator iterator_first,
                                              iterator iterator_second){
    if(iterator_first.list_iterator_base_pointer_ == nullptr ||
       iterator_second.list_iterator_base_pointer_ == nullptr)
            throw new std::runtime_error("NULL Iterator!");
    else if(typeid(*(iterator_first.list_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::ListIteratorPositive<T>) &&
            typeid(*(iterator_second.list_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::ListIteratorPositive<T>))
        return ErasePositive(iterator_first,iterator_second);
    else if(typeid(*(iterator_first.list_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::ListIteratorNegative<T>) &&
            typeid(*(iterator_second.list_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::ListIteratorNegative<T>))
        return EraseNegative(iterator_first,iterator_second);
    else
        throw new std::runtime_error("Wrong Iterator Type!");
}

}

#endif
