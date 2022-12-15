#ifndef LIST_H
#define LIST_H
#include <initializer_list>
#include <iostream>
namespace sablin{
	
template <typename T>
class List;

namespace valerij{	
	
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
class ListPositiveIterator{
	template <typename TYPE>
	friend bool operator==(const ListPositiveIterator<TYPE>&,const ListPositiveIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator!=(const ListPositiveIterator<TYPE>&,const ListPositiveIterator<TYPE>&);
	
	template <typename TYPE>
	friend class sablin::List;
private:
	ListNode<T> *node_pointer_;
public:
	ListPositiveIterator(ListNode<T>*);
	ListPositiveIterator(const ListPositiveIterator&);
	ListPositiveIterator(ListPositiveIterator&&);
	ListPositiveIterator& operator=(const ListPositiveIterator&);
	ListPositiveIterator& operator=(ListPositiveIterator&&);
	~ListPositiveIterator();
	
	T& operator*() const;
	T* operator->() const;
	
	ListPositiveIterator<T>& operator++();
	ListPositiveIterator<T>& operator--();
	ListPositiveIterator<T>  operator++(int);
	ListPositiveIterator<T>  operator--(int);
};

template <typename T>
ListPositiveIterator<T>::ListPositiveIterator(ListNode<T> *node_pointer):
	node_pointer_(node_pointer) {}

template <typename T>
ListPositiveIterator<T>::ListPositiveIterator(const ListPositiveIterator &another){
	node_pointer_ = another.node_pointer_;
}

template <typename T>
ListPositiveIterator<T>::ListPositiveIterator(ListPositiveIterator &&another){
	node_pointer_ = another.node_pointer_;
	another.node_pointer_ = nullptr;
}

template <typename T>
ListPositiveIterator<T>& ListPositiveIterator<T>::operator=(const ListPositiveIterator &another){
	if(this == &another) return *this;
	node_pointer_ = another.node_pointer_;
}

template <typename T>
ListPositiveIterator<T>& ListPositiveIterator<T>::operator=(ListPositiveIterator &&another){
	if(this == &another) return *this;
	node_pointer_ = another.node_pointer_;
	another.node_pointer_ = nullptr;
} 

template <typename T>
ListPositiveIterator<T>::~ListPositiveIterator(){
	node_pointer_ = nullptr;
}

template <typename T>
T& ListPositiveIterator<T>::operator*() const{
	return *node_pointer_->element_pointer_;
}

template <typename T>
T* ListPositiveIterator<T>::operator->() const{
	return & this->operator*();
}

template <typename T>
ListPositiveIterator<T>& ListPositiveIterator<T>::operator++(){
	node_pointer_ = node_pointer_->next_node_;
	return *this;
}

template <typename T>
ListPositiveIterator<T>& ListPositiveIterator<T>::operator--(){
	node_pointer_ = node_pointer_->last_node_;
	return *this;
}

template <typename T>
ListPositiveIterator<T> ListPositiveIterator<T>::operator++(int){
	ListPositiveIterator temp(node_pointer_);
	node_pointer_ = node_pointer_->next_node_;
	return temp;
}

template <typename T>
ListPositiveIterator<T> ListPositiveIterator<T>::operator--(int){
	ListPositiveIterator temp(node_pointer_);
	node_pointer_ = node_pointer_->last_node_;
	return temp;
}

template <typename T>
class ListNegativeIterator{
	template <typename TYPE>
	friend bool operator==(const ListNegativeIterator<TYPE>&,const ListNegativeIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator!=(const ListNegativeIterator<TYPE>&,const ListNegativeIterator<TYPE>&);
	
	template <typename TYPE>
	friend class sablin::List;
private:
	ListNode<T> *node_pointer_;
public:
	ListNegativeIterator(ListNode<T>*);
	ListNegativeIterator(const ListNegativeIterator&);
	ListNegativeIterator(ListNegativeIterator&&);
	ListNegativeIterator& operator=(const ListNegativeIterator&);
	ListNegativeIterator& operator=(ListNegativeIterator&&);
	~ListNegativeIterator();	
	
	T& operator*() const;
	T* operator->() const;
	
	ListNegativeIterator<T>& operator++();
	ListNegativeIterator<T>& operator--();
	ListNegativeIterator<T>  operator++(int);
	ListNegativeIterator<T>  operator--(int);
};

template <typename T>
ListNegativeIterator<T>::ListNegativeIterator(ListNode<T> *node_pointer):
	node_pointer_(node_pointer) {}
	
template <typename T>
ListNegativeIterator<T>::ListNegativeIterator(const ListNegativeIterator &another){
	node_pointer_ = another.node_pointer_;
}

template <typename T>
ListNegativeIterator<T>::ListNegativeIterator(ListNegativeIterator &&another){
	node_pointer_ = another.node_pointer_;
	another.node_pointer_ = nullptr;
}

template <typename T>
ListNegativeIterator<T>& ListNegativeIterator<T>::operator=(const ListNegativeIterator &another){
	if(this == &another) return *this;
	node_pointer_ = another.node_pointer_;
}

template <typename T>
ListNegativeIterator<T>& ListNegativeIterator<T>::operator=(ListNegativeIterator &&another){
	if(this == &another) return *this;
	node_pointer_ = another.node_pointer_;
	another.node_pointer_ = nullptr;
} 

template <typename T>
ListNegativeIterator<T>::~ListNegativeIterator(){
	node_pointer_ = nullptr;
}

template <typename T>
T& ListNegativeIterator<T>::operator*() const{
	return *node_pointer_->element_pointer_;
}

template <typename T>
T* ListNegativeIterator<T>::operator->() const{
	return & this->operator*();
}

template <typename T>
ListNegativeIterator<T>& ListNegativeIterator<T>::operator++(){
	node_pointer_ = node_pointer_->last_node_;
	return *this;
}

template <typename T>
ListNegativeIterator<T>& ListNegativeIterator<T>::operator--(){
	node_pointer_ = node_pointer_->next_node_;
	return *this;
}

template <typename T>
ListNegativeIterator<T> ListNegativeIterator<T>::operator++(int){
	ListNegativeIterator temp(node_pointer_);
	node_pointer_ = node_pointer_->last_node_;
	return temp;
}

template <typename T>
ListNegativeIterator<T> ListNegativeIterator<T>::operator--(int){
	ListNegativeIterator temp(node_pointer_);
	node_pointer_ = node_pointer_->next_node_;
	return temp;
}

template <typename T>
bool operator==(const ListPositiveIterator<T> &rhs,const ListPositiveIterator<T> &lhs){
	return rhs.node_pointer_ == lhs.node_pointer_;
}

template <typename T>
bool operator!=(const ListPositiveIterator<T> &rhs,const ListPositiveIterator<T> &lhs){
	return rhs.node_pointer_ != lhs.node_pointer_;
}

template <typename T>
bool operator==(const ListNegativeIterator<T> &rhs,const ListNegativeIterator<T> &lhs){
	return rhs.node_pointer_ == lhs.node_pointer_;
}

template <typename T>
bool operator!=(const ListNegativeIterator<T> &rhs,const ListNegativeIterator<T> &lhs){
	return rhs.node_pointer_ != lhs.node_pointer_;
}

}

template <typename T>
class List{
public:
	typedef T 	   						     element_type;
	typedef size_t 						     number_type;
	typedef valerij::ListPositiveIterator<T> positive_iterator;
	typedef valerij::ListNegativeIterator<T> negative_iterator;
	
	//Debug--------------------------------------------------------
	void DebugPrint(){
		std::cout << "element_size_ : " << element_size_ << std::endl;
		for(valerij::ListNode<T> *temp = head_node_;temp != tail_node_;temp = temp->next_node_)
			std::cout << *temp->element_pointer_ << std::endl;
		if(tail_node_ != nullptr) std::cout << *tail_node_->element_pointer_ << std::endl;
	}
	//Debug--------------------------------------------------------
private:
	number_type                element_size_;
	valerij::ListNode<T> 	  *head_node_;
	valerij::ListNode<T> 	  *tail_node_;
	
	valerij::ListNode<T>      *beyond_head_node_;
	valerij::ListNode<T>	  *beyond_tail_node_;
	
	void Initialize();
	void ReleaseResource();
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
	
	positive_iterator Begin()  noexcept;
	positive_iterator End()    noexcept;
	negative_iterator RBegin() noexcept;
	negative_iterator REnd()   noexcept;
	
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
	
	positive_iterator Insert(const positive_iterator,const T&);
	positive_iterator Insert(const positive_iterator,const number_type,const T&);
	template <typename Iterator>
	positive_iterator Insert(const positive_iterator,const Iterator,const Iterator);
	
	positive_iterator Erase(const positive_iterator);
	positive_iterator Erase(const positive_iterator,const positive_iterator);
	
	negative_iterator Insert(const negative_iterator,const T&);
	negative_iterator Insert(const negative_iterator,const number_type,const T&);
	template <typename Iterator>
	negative_iterator Insert(const negative_iterator,const Iterator,const Iterator);
	
	negative_iterator Erase(const negative_iterator);
	negative_iterator Erase(const negative_iterator,const negative_iterator);
	
};

template <typename T>
void List<T>::Initialize(){
	element_size_ = 0;
	beyond_head_node_ = new valerij::ListNode<T>();
	beyond_tail_node_ = new valerij::ListNode<T>();
	head_node_ = nullptr;
	tail_node_ = nullptr;
	beyond_head_node_->next_node_ = beyond_tail_node_;
	beyond_tail_node_->last_node_ = beyond_head_node_;
}

template <typename T>
void List<T>::ReleaseResource(){
	while(beyond_head_node_ != nullptr){
		valerij::ListNode<T> *temp = beyond_head_node_;
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
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
	for(valerij::ListNode<T> *temp = another.beyond_tail_node_->next_node_;
			temp != another.beyond_tail_node_;temp = temp->next_node_){
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
	for(valerij::ListNode<T> *temp = another.beyond_tail_node_->next_node_;
		temp != another.beyond_tail_node_;temp = temp->next_node_){
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
typename List<T>::positive_iterator List<T>::Begin() noexcept{
	return valerij::ListPositiveIterator<T>(head_node_); 
}

template <typename T>
typename List<T>::positive_iterator List<T>::End() noexcept{
	return valerij::ListPositiveIterator<T>(beyond_tail_node_);
}

template <typename T>
typename List<T>::negative_iterator List<T>::RBegin() noexcept{
	return valerij::ListNegativeIterator<T>(tail_node_);
}

template <typename T>
typename List<T>::negative_iterator List<T>::REnd() noexcept{
	return valerij::ListNegativeIterator<T>(beyond_head_node_);
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
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
		head_node_ = new valerij::ListNode<T>();
		head_node_->element_pointer_ = new T(element);
		tail_node_ = head_node_;
		head_node_->last_node_ = beyond_head_node_;
		head_node_->next_node_ = beyond_tail_node_;
		beyond_head_node_->next_node_ = head_node_;
		beyond_tail_node_->last_node_ = head_node_;
		return;
	}
	
	valerij::ListNode<T>* temp = new valerij::ListNode<T>();
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
		head_node_ = new valerij::ListNode<T>();
		head_node_->element_pointer_ = new T(std::move(element));
		tail_node_ = head_node_;
		head_node_->last_node_ = beyond_head_node_;
		head_node_->next_node_ = beyond_tail_node_;
		beyond_head_node_->next_node_ = head_node_;
		beyond_tail_node_->last_node_ = head_node_;
		return;
	}
	
	valerij::ListNode<T>* temp = new valerij::ListNode<T>();
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
	
	valerij::ListNode<T>* temp = new valerij::ListNode<T>();
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
	
	valerij::ListNode<T>* temp = new valerij::ListNode<T>();
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
typename List<T>::positive_iterator List<T>::Insert(const positive_iterator iterator,
													const T &element){
	if(iterator == this->End()){PushBack(element); return valerij::ListPositiveIterator(tail_node_);}
	if(iterator == this->Begin()){PushFront(element);return valerij::ListPositiveIterator(head_node_);}
	
	++element_size_;
	valerij::ListNode<T> *temp_pointer = iterator.node_pointer_->last_node_;
	valerij::ListNode<T> *temp = new valerij::ListNode<T>();
	temp->element_pointer_ = new T(element);
	temp->last_node_ = temp_pointer;
	temp->next_node_ = temp_pointer->next_node_;
	temp_pointer->next_node_->last_node_ = temp;
	temp_pointer->next_node_ = temp;
	return valerij::ListPositiveIterator<T>(temp_pointer->next_node_);
}

template <typename T>
typename List<T>::positive_iterator List<T>::Insert(const positive_iterator iterator,
													const size_t size,const T &element){
	if(size == 0) throw new std::runtime_error("Wrong Size ---- Insert(iter,size,element)");
	
	element_size_ += size;
	valerij::ListNode<T> *head_temp = nullptr;
	valerij::ListNode<T> *tail_temp = nullptr;
	
	for(number_type i = 0;i != size; ++i){
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
		return valerij::ListPositiveIterator<T>(head_temp);
	}
	
	valerij::ListNode<T> *temp_pointer = iterator.node_pointer_->last_node_;
	tail_temp->next_node_ = temp_pointer->next_node_;
	temp_pointer->next_node_->last_node_ = tail_temp;
	head_temp->last_node_ = temp_pointer;
	temp_pointer->next_node_ = head_temp;
	return valerij::ListPositiveIterator<T>(temp_pointer->next_node_);
}

template <typename T>
template <typename Iterator>
typename List<T>::positive_iterator List<T>::Insert(const positive_iterator iterator,
													const Iterator first_iterator,
													const Iterator second_iterator){
	number_type size = 0;
	for(Iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator)
		++size;
	
	element_size_ += size;
	valerij::ListNode<T> *head_temp = nullptr;
	valerij::ListNode<T> *tail_temp = nullptr;
	
	Iterator temp_iterator = first_iterator;
	for(number_type i = 0;i != size; ++i){
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
		return valerij::ListPositiveIterator<T>(head_temp);
	}
	
	valerij::ListNode<T> *temp_pointer = iterator.node_pointer_->last_node_;
	tail_temp->next_node_ = temp_pointer->next_node_;
	temp_pointer->next_node_->last_node_ = tail_temp;
	head_temp->last_node_ = temp_pointer;
	temp_pointer->next_node_ = head_temp;
	return valerij::ListPositiveIterator<T>(temp_pointer->next_node_);
}

template <typename T>
typename List<T>::positive_iterator List<T>::Erase(const positive_iterator iterator){
	if(iterator == this->End())
		throw new std::runtime_error("Wrong Position ---- Erase(positive_iterator)");
	
	if(iterator == this->Begin()) {PopFront(); return this->Begin();}
	if(iterator == --this->End()) {PopBack(); return this->End();}
	
	--element_size_;
	
	valerij::ListNode<T> *temp_pointer = iterator.node_pointer_->last_node_;
	temp_pointer->next_node_->next_node_->last_node_ = temp_pointer;
	temp_pointer->next_node_ = temp_pointer->next_node_->next_node_;
	delete iterator.node_pointer_;
	return valerij::ListPositiveIterator<T>(temp_pointer->next_node_);
}

template <typename T>
typename List<T>::positive_iterator List<T>::Erase(const positive_iterator first_iterator,
												   const positive_iterator second_iterator){
	number_type size = 0;
	for(positive_iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator)
		++size;
	
	if(first_iterator == this->Begin() && second_iterator == this->End()){
		this->Clear();
		return this->End();
	}
	
	element_size_ -= size;
	valerij::ListNode<T> *head_temp = nullptr;
	valerij::ListNode<T> *tail_temp = nullptr;
	
	
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
	
	return valerij::ListPositiveIterator<T>(second_iterator.node_pointer_);
}

template <typename T>
typename List<T>::negative_iterator List<T>::Insert(const negative_iterator iterator,
													const T &element){
	if(iterator == this->RBegin()){PushBack(element);return this->RBegin();}
	if(iterator == this->REnd()){PushFront(element); return this->REnd();}
	
	++element_size_;
	valerij::ListNode<T> *temp_pointer = iterator.node_pointer_->next_node_;
	valerij::ListNode<T> *temp = new valerij::ListNode<T>();
	temp->element_pointer_ = new T(element);
	temp->next_node_ = temp_pointer;
	temp->last_node_ = temp_pointer->last_node_;
	temp_pointer->last_node_->next_node_ = temp;
	temp_pointer->last_node_ = temp;
	return valerij::ListNegativeIterator<T>(temp_pointer->last_node_);
}

template <typename T>
typename List<T>::negative_iterator List<T>::Insert(const negative_iterator iterator,
													const size_t size,const T &element){
	if(size == 0) throw new std::runtime_error("Wrong Size ---- Insert(iter,size,element)");
	
	element_size_ += size;
	valerij::ListNode<T> *head_temp = nullptr;
	valerij::ListNode<T> *tail_temp = nullptr;
	
	for(number_type i = 0;i != size; ++i){
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
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
		return valerij::ListNegativeIterator<T>(head_temp);
	}
	
	valerij::ListNode<T> *temp_pointer = iterator.node_pointer_->next_node_;
	tail_temp->last_node_ = temp_pointer->last_node_;
	temp_pointer->last_node_->next_node_ = tail_temp;
	head_temp->next_node_ = temp_pointer;
	temp_pointer->last_node_ = head_temp;
	return valerij::ListNegativeIterator<T>(temp_pointer->last_node_);
}

template <typename T>
template <typename Iterator>
typename List<T>::negative_iterator List<T>::Insert(const negative_iterator iterator,
													const Iterator first_iterator,
													const Iterator second_iterator){
	number_type size = 0;
	for(Iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator)
		++size;
	
	element_size_ += size;
	valerij::ListNode<T> *head_temp = nullptr;
	valerij::ListNode<T> *tail_temp = nullptr;
	
	Iterator temp_iterator = first_iterator;
	for(number_type i = 0;i != size; ++i){
		valerij::ListNode<T> *temp_node = new valerij::ListNode<T>();
		temp_node->element_pointer_ = new T(*(first_iterator++));
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
		return valerij::ListNegativeIterator<T>(head_temp);
	}
	
	valerij::ListNode<T> *temp_pointer = iterator.node_pointer_->next_node_;
	tail_temp->last_node_ = temp_pointer->last_node_;
	temp_pointer->last_node_->next_node_ = tail_temp;
	head_temp->next_node_ = temp_pointer;
	temp_pointer->last_node_ = head_temp;
	return valerij::ListNegativeIterator<T>(temp_pointer->last_node_);
}

template <typename T>
typename List<T>::negative_iterator List<T>::Erase(const negative_iterator iterator){
	if(iterator == this->REnd())
		throw new std::runtime_error("Wrong Position ---- Erase(negative_iterator)");
	
	if(iterator == this->RBegin()) {PopBack(); return this->RBegin();}
	if(iterator == --this->REnd()) {PopFront(); return this->REnd();}
	
	--element_size_;
	
	valerij::ListNode<T> *temp_pointer = iterator.node_pointer_->next_node_;
	temp_pointer->last_node_->last_node_->next_node_ = temp_pointer;
	temp_pointer->last_node_ = temp_pointer->last_node_->last_node_;
	delete iterator.node_pointer_;
	return valerij::ListNegativeIterator<T>(temp_pointer->last_node_);
}

template <typename T>
typename List<T>::negative_iterator List<T>::Erase(const negative_iterator first_iterator,
												   const negative_iterator second_iterator){
	number_type size = 0;
	for(negative_iterator temp_iterator = first_iterator;temp_iterator != second_iterator;++temp_iterator)
		++size;
	
	if(first_iterator == this->RBegin() && second_iterator == this->REnd()){
		this->Clear();
		return this->REnd();
	}
	
	element_size_ -= size;
	valerij::ListNode<T> *head_temp = nullptr;
	valerij::ListNode<T> *tail_temp = nullptr;
	
	
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
	
	return valerij::ListNegativeIterator<T>(second_iterator.node_pointer_);
}


	
}

#endif
