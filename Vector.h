#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <initializer_list>
namespace sablin{
	
template <typename T>
class Vector;

namespace valerij{

template <typename T>
class VectorPositiveIterator{
	template <typename TYPE>
	friend bool operator==(const VectorPositiveIterator<TYPE>&,const VectorPositiveIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator!=(const VectorPositiveIterator<TYPE>&,const VectorPositiveIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator<=(const VectorPositiveIterator<TYPE>&,const VectorPositiveIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator>=(const VectorPositiveIterator<TYPE>&,const VectorPositiveIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator<(const VectorPositiveIterator<TYPE>&,const VectorPositiveIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator>(const VectorPositiveIterator<TYPE>&,const VectorPositiveIterator<TYPE>&);
	template <typename TYPE>
	friend int32_t operator-(const VectorPositiveIterator<TYPE>&,const VectorPositiveIterator<TYPE>&);
private:
	T *pointer_;
public:
	VectorPositiveIterator(T*);
	VectorPositiveIterator(const VectorPositiveIterator&);
	VectorPositiveIterator(VectorPositiveIterator&&);
	VectorPositiveIterator& operator=(const VectorPositiveIterator&);
	VectorPositiveIterator& operator=(VectorPositiveIterator&&);
	~VectorPositiveIterator();
	
	T& operator*() const;
	T* operator->() const;
	
	VectorPositiveIterator<T>& operator++();
	VectorPositiveIterator<T>& operator--();
	VectorPositiveIterator<T>  operator++(int);
	VectorPositiveIterator<T>  operator--(int);
	
	VectorPositiveIterator<T>& operator+=(const int32_t&);
	VectorPositiveIterator<T>& operator-=(const int32_t&);
	VectorPositiveIterator<T> operator+(const int32_t&);
	VectorPositiveIterator<T> operator-(const int32_t&);
	
	VectorPositiveIterator<T>& operator+=(const size_t&);
	VectorPositiveIterator<T>& operator-=(const size_t&);
	VectorPositiveIterator<T> operator+(const size_t&);
	VectorPositiveIterator<T> operator-(const size_t&);
};

template <typename T>
VectorPositiveIterator<T>::VectorPositiveIterator(T *pointer):
	pointer_(pointer) {}
	
template <typename T>
VectorPositiveIterator<T>::VectorPositiveIterator(const VectorPositiveIterator &another){
	pointer_ = another.pointer_;
}

template <typename T>
VectorPositiveIterator<T>::VectorPositiveIterator(VectorPositiveIterator &&another){
	pointer_ = another.pointer_;
	another.pointer_ = nullptr;
}

template <typename T>
VectorPositiveIterator<T>& VectorPositiveIterator<T>::operator=(const VectorPositiveIterator &another){
	if(this == &another) return *this;
	pointer_ = another.pointer_;
}

template <typename T>
VectorPositiveIterator<T>& VectorPositiveIterator<T>::operator=(VectorPositiveIterator &&another){
	if(this == &another) return *this;
	pointer_ = another.pointer_;
	another.pointer_ = nullptr;
}

template <typename T>
VectorPositiveIterator<T>::~VectorPositiveIterator(){
	pointer_ = nullptr;
}

template <typename T>
T& VectorPositiveIterator<T>::operator*() const{
	return *pointer_;
}

template <typename T>
T* VectorPositiveIterator<T>::operator->() const{
	return & this->operator*();
}

template <typename T>
VectorPositiveIterator<T>& VectorPositiveIterator<T>::operator++(){
	++pointer_;
	return *this;
}

template <typename T>
VectorPositiveIterator<T>& VectorPositiveIterator<T>::operator--(){
	--pointer_;
	return *this;
}

template <typename T>
VectorPositiveIterator<T> VectorPositiveIterator<T>::operator++(int){
	VectorPositiveIterator temp(pointer_);
	++pointer_;
	return temp;
}

template <typename T>
VectorPositiveIterator<T> VectorPositiveIterator<T>::operator--(int){
	VectorPositiveIterator temp(pointer_);
	--pointer_;
	return temp;
}

template <typename T>
VectorPositiveIterator<T>& VectorPositiveIterator<T>::operator+=(const int32_t &difference){
	pointer_ += difference;
	return *this;
}

template <typename T>
VectorPositiveIterator<T>& VectorPositiveIterator<T>::operator-=(const int32_t &difference){
	pointer_ -= difference;
	return *this;
}

template <typename T>
VectorPositiveIterator<T> VectorPositiveIterator<T>::operator+(const int32_t &difference){
	VectorPositiveIterator<T> temp(*this);
	temp += difference;
	return temp;
}

template <typename T>
VectorPositiveIterator<T> VectorPositiveIterator<T>::operator-(const int32_t &difference){
	VectorPositiveIterator<T> temp(*this);
	temp -= difference;
	return temp;
}

template <typename T>
VectorPositiveIterator<T>& VectorPositiveIterator<T>::operator+=(const size_t &difference){
	pointer_ += difference;
	return *this;
}

template <typename T>
VectorPositiveIterator<T>& VectorPositiveIterator<T>::operator-=(const size_t &difference){
	pointer_ -= difference;
	return *this;
}

template <typename T>
VectorPositiveIterator<T> VectorPositiveIterator<T>::operator+(const size_t &difference){
	VectorPositiveIterator<T> temp(*this);
	temp += difference;
	return temp;
}

template <typename T>
VectorPositiveIterator<T> VectorPositiveIterator<T>::operator-(const size_t &difference){
	VectorPositiveIterator<T> temp(*this);
	temp -= difference;
	return temp;
}

template <typename T>
bool operator==(const VectorPositiveIterator<T> &lhs,const VectorPositiveIterator<T> &rhs){
	return lhs.pointer_ == rhs.pointer_;
}

template <typename T>
bool operator!=(const VectorPositiveIterator<T> &lhs,const VectorPositiveIterator<T> &rhs){
	return lhs.pointer_ != rhs.pointer_;
}

template <typename T>
bool operator<=(const VectorPositiveIterator<T> &lhs,const VectorPositiveIterator<T> &rhs){
	return lhs.pointer_ <= rhs.pointer_;
}

template <typename T>
bool operator>=(const VectorPositiveIterator<T> &lhs,const VectorPositiveIterator<T> &rhs){
	return lhs.pointer_ >= rhs.pointer_;
}

template <typename T>
bool operator<(const VectorPositiveIterator<T> &lhs,const VectorPositiveIterator<T> &rhs){
	return lhs.pointer_ < rhs.pointer_;
}

template <typename T>
bool operator>(const VectorPositiveIterator<T> &lhs,const VectorPositiveIterator<T> &rhs){
	return lhs.pointer_ > rhs.pointer_;
}

template <typename T>
int32_t operator-(const VectorPositiveIterator<T> &lhs,const VectorPositiveIterator<T> &rhs){
	return lhs.pointer_ - rhs.pointer_;
}

template <typename T>
class VectorNegativeIterator{
	template <typename TYPE>
	friend bool operator==(const VectorNegativeIterator<TYPE>&,const VectorNegativeIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator!=(const VectorNegativeIterator<TYPE>&,const VectorNegativeIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator<=(const VectorNegativeIterator<TYPE>&,const VectorNegativeIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator>=(const VectorNegativeIterator<TYPE>&,const VectorNegativeIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator<(const VectorNegativeIterator<TYPE>&,const VectorNegativeIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator>(const VectorNegativeIterator<TYPE>&,const VectorNegativeIterator<TYPE>&);
	template <typename TYPE>
	friend int32_t operator-(const VectorNegativeIterator<TYPE>&,const VectorNegativeIterator<TYPE>&);
private:
	T *pointer_;
public:
	VectorNegativeIterator(T*);
	VectorNegativeIterator(const VectorNegativeIterator&);
	VectorNegativeIterator(VectorNegativeIterator&&);
	VectorNegativeIterator& operator=(const VectorNegativeIterator&);
	VectorNegativeIterator& operator=(VectorNegativeIterator&&);
	~VectorNegativeIterator();
	
	T& operator*() const;
	T* operator->() const;
	
	VectorNegativeIterator<T>& operator++();
	VectorNegativeIterator<T>& operator--();
	VectorNegativeIterator<T>  operator++(int);
	VectorNegativeIterator<T>  operator--(int);
	
	VectorNegativeIterator<T>& operator+=(const int32_t&);
	VectorNegativeIterator<T>& operator-=(const int32_t&);
	VectorNegativeIterator<T> operator+(const int32_t&);
	VectorNegativeIterator<T> operator-(const int32_t&);
	
	VectorNegativeIterator<T>& operator+=(const size_t&);
	VectorNegativeIterator<T>& operator-=(const size_t&);
	VectorNegativeIterator<T> operator+(const size_t&);
	VectorNegativeIterator<T> operator-(const size_t&);
};

template <typename T>
VectorNegativeIterator<T>::VectorNegativeIterator(T *pointer):
	pointer_(pointer) {}
	
template <typename T>
VectorNegativeIterator<T>::VectorNegativeIterator(const VectorNegativeIterator &another){
	pointer_ = another.pointer_;
}

template <typename T>
VectorNegativeIterator<T>::VectorNegativeIterator(VectorNegativeIterator &&another){
	pointer_ = another.pointer_;
	another.pointer_ = nullptr;
}

template <typename T>
VectorNegativeIterator<T>& VectorNegativeIterator<T>::operator=(const VectorNegativeIterator &another){
	if(this == &another) return *this;
	pointer_ = another.pointer_;
}

template <typename T>
VectorNegativeIterator<T>& VectorNegativeIterator<T>::operator=(VectorNegativeIterator &&another){
	if(this == &another) return *this;
	pointer_ = another.pointer_;
	another.pointer_ = nullptr;
}

template <typename T>
VectorNegativeIterator<T>::~VectorNegativeIterator(){
	pointer_ = nullptr;
}

template <typename T>
T& VectorNegativeIterator<T>::operator*() const{
	return *pointer_;
}

template <typename T>
T* VectorNegativeIterator<T>::operator->() const{
	return & this->operator*();
}

template <typename T>
VectorNegativeIterator<T>& VectorNegativeIterator<T>::operator++(){
	--pointer_;
	return *this;
}

template <typename T>
VectorNegativeIterator<T>& VectorNegativeIterator<T>::operator--(){
	++pointer_;
	return *this;
}

template <typename T>
VectorNegativeIterator<T> VectorNegativeIterator<T>::operator++(int){
	VectorNegativeIterator temp(pointer_);
	--pointer_;
	return temp;
}

template <typename T>
VectorNegativeIterator<T> VectorNegativeIterator<T>::operator--(int){
	VectorNegativeIterator temp(pointer_);
	++pointer_;
	return temp;
}

template <typename T>
VectorNegativeIterator<T>& VectorNegativeIterator<T>::operator+=(const int32_t &difference){
	pointer_ -= difference;
	return *this;
}

template <typename T>
VectorNegativeIterator<T>& VectorNegativeIterator<T>::operator-=(const int32_t &difference){
	pointer_ += difference;
	return *this;
}

template <typename T>
VectorNegativeIterator<T> VectorNegativeIterator<T>::operator+(const int32_t &difference){
	VectorNegativeIterator<T> temp(*this);
	temp += difference;
	return temp;
}

template <typename T>
VectorNegativeIterator<T> VectorNegativeIterator<T>::operator-(const int32_t &difference){
	VectorNegativeIterator<T> temp(*this);
	temp -= difference;
	return temp;
}

template <typename T>
VectorNegativeIterator<T>& VectorNegativeIterator<T>::operator+=(const size_t &difference){
	pointer_ -= difference;
	return *this;
}

template <typename T>
VectorNegativeIterator<T>& VectorNegativeIterator<T>::operator-=(const size_t &difference){
	pointer_ += difference;
	return *this;
}

template <typename T>
VectorNegativeIterator<T> VectorNegativeIterator<T>::operator+(const size_t &difference){
	VectorNegativeIterator<T> temp(*this);
	temp += difference;
	return temp;
}

template <typename T>
VectorNegativeIterator<T> VectorNegativeIterator<T>::operator-(const size_t &difference){
	VectorNegativeIterator<T> temp(*this);
	temp -= difference;
	return temp;
}

template <typename T>
bool operator==(const VectorNegativeIterator<T> &lhs,const VectorNegativeIterator<T> &rhs){
	return lhs.pointer_ == rhs.pointer_;
}

template <typename T>
bool operator!=(const VectorNegativeIterator<T> &lhs,const VectorNegativeIterator<T> &rhs){
	return lhs.pointer_ != rhs.pointer_;
}

template <typename T>
bool operator<=(const VectorNegativeIterator<T> &lhs,const VectorNegativeIterator<T> &rhs){
	return lhs.pointer_ >= rhs.pointer_;
}

template <typename T>
bool operator>=(const VectorNegativeIterator<T> &lhs,const VectorNegativeIterator<T> &rhs){
	return lhs.pointer_ <= rhs.pointer_;
}

template <typename T>
bool operator>(const VectorNegativeIterator<T> &lhs,const VectorNegativeIterator<T> &rhs){
	return lhs.pointer_ < rhs.pointer_;
}

template <typename T>
bool operator<(const VectorNegativeIterator<T> &lhs,const VectorNegativeIterator<T> &rhs){
	return lhs.pointer_ > rhs.pointer_;
}

template <typename T>
int32_t operator-(const VectorNegativeIterator<T> &lhs,const VectorNegativeIterator<T> &rhs){
	return rhs.pointer_ - lhs.pointer_;
}
	
}

template <typename T>
class Vector{
public:
	typedef T 								   element_type;
	typedef size_t 							   number_type;
	typedef valerij::VectorPositiveIterator<T> positive_iterator;
	typedef valerij::VectorNegativeIterator<T> negative_iterator;
private:
	number_type allocated_size_;
	number_type element_size_;
	std::allocator<T> allocator_;
	T *head_pointer_;
	T *tail_pointer_;
	
	void Initialize();
	void ReleaseResource();
	
	void EnlargeMemory();
	void ReduceMemory();
public:
	Vector() : allocated_size_(0),element_size_(0),
			   head_pointer_(nullptr),tail_pointer_(nullptr){}
	explicit Vector(std::initializer_list<T>);
	template <typename Iterator>
	explicit Vector(const Iterator,const Iterator);
	explicit Vector(const number_type,const T&);
	
	Vector(const Vector&);
	Vector(Vector&&);
	
	Vector& operator=(const Vector&);
	Vector& operator=(Vector&&);
	
	~Vector();
	
	//Debug--------------------------------------
	void DebugPrint(){
		std::cout << "allocated_size_ : " << allocated_size_ << std::endl;
		std::cout << "element_size_ L " << element_size_ << std::endl;
		std::cout << "ELEMENT IS : " << std::endl;
		for(number_type i = 0;i != element_size_; ++i)
			std::cout << *(head_pointer_ + i) << " ";
		std::cout << std::endl;
	}
	//Debug--------------------------------------
	
	positive_iterator Begin() noexcept;
	positive_iterator End() noexcept;
	negative_iterator RBegin() noexcept;
	negative_iterator REnd() noexcept;
	
	bool IsEmpty() const {return element_size_ == 0;}
	
	T operator[](const number_type index) const {return *(head_pointer_+index);}
	T At(const number_type) const;
	T Front() const {return *(head_pointer_);}
	T Back() const {return *(tail_pointer_);}
	
	void Assign(const number_type&,const T&);
	void Assign(std::initializer_list<T>);
	template <typename Iterator>
	void Assign(const Iterator,const Iterator);
	
	void PushBack(const T&);
	void PushBack(T&&);
	
	T PopBack();
	
	positive_iterator Insert(positive_iterator,const T&);
	positive_iterator Insert(positive_iterator,const number_type,const T&);
	template <typename Iterator>
	positive_iterator Insert(positive_iterator,const Iterator,const Iterator);
	
	positive_iterator Erase(positive_iterator);
	positive_iterator Erase(positive_iterator,positive_iterator);
	
	negative_iterator Insert(negative_iterator,const T&);
	negative_iterator Insert(negative_iterator,const number_type,const T&);
	template <typename Iterator>
	negative_iterator Insert(negative_iterator,const Iterator,const Iterator);
	
	negative_iterator Erase(negative_iterator);
	negative_iterator Erase(negative_iterator,negative_iterator);
	
	void Clear() noexcept;
};

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list){
	number_type list_size = list.size();
	if(list_size == 0){
		head_pointer_ = tail_pointer_ = nullptr;
		element_size_ = allocated_size_ = 0;
		return;
	}
	
	allocated_size_ = list_size * 2;
	element_size_ = list_size;
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_ - 1;
	for(size_t i = 0;i != list_size; ++i)
		allocator_.construct(head_pointer_ + i,std::move(*(list.begin() + i)));
}

template <typename T>
template <typename Iterator>
Vector<T>::Vector(const Iterator iterator_first,const Iterator iterator_second){
	size_t size = 0;
	for(Iterator iterator_temp = iterator_first;iterator_temp != iterator_second;++iterator_temp)
		++size;
	
	allocated_size_ = size * 2;
	element_size_ = size;
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = tail_pointer_ + element_size_ - 1;
	
	Iterator iterator_temp = iterator_first;
	for(size_t i = 0; i != size; ++i)
		allocator_.construct(head_pointer_ + i, *(iterator_temp++));
}

template <typename T>
Vector<T>::Vector(const number_type size,const T &element){
	if(size == 0) throw new std::runtime_error("Size Wrong ---- Vector(size,element)");
	
	allocated_size_ = size * 2;
	element_size_ = size;
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_ - 1;
	
	for(int32_t i = 0; i != size; ++i)
		allocator_.construct(head_pointer_ + i, element);
}

template <typename T>
Vector<T>::Vector(const Vector &another){
	element_size_ = another.element_size_;
	allocated_size_ = another.allocatefd_size_;
	
	if(allocated_size_ = 0){
		head_pointer_ = tail_pointer_ = nullptr;
		return;
	}
	
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_ - 1;
	
	for(size_t i = 0;i != element_size_; ++i)
		allocator_.construct(head_pointer_ + i, *(another.head_pointer_ + i));
}

template <typename T>
Vector<T>::Vector(Vector &&another){
	element_size_ = another.element_size_;
	allocated_size_ = another.allocated_size_;
	head_pointer_ = another.head_pointer_;
	tail_pointer_ = another.tail_pointer_;
	allocator_ = std::move(another.allocator_);
	
	another.Initialize();
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &another){
	if(this == &another) return *this;
	
	this->Clear();
	element_size_ = another.element_size_;
	allocated_size_ = another.allocated_size_;
	if(allocated_size_ == 0) {return *this;}
	
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_ - 1;
	
	for(size_t i = 0; i != element_size_; ++i)
		allocator_.construct(head_pointer_ + i,*(another.head_pointer + i));
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &&another){
	if(this == &another) return *this;
	this->Clear();
	
	element_size_ = another.element_size_;
	allocated_size_ = another.allocated_size_;
	head_pointer_ = another.head_pointer_;
	tail_pointer_ = another.tail_pointer_;
	allocator_ = std::move(another.allocator_);
	
	another.Initialize();
	return *this;
}

template <typename T>
Vector<T>::~Vector(){
	ReleaseResource();
}

template <typename T>
void Vector<T>::Initialize(){
	element_size_ = 0;
	allocated_size_ = 0;
	head_pointer_ = nullptr;
	tail_pointer_ = nullptr;
	allocator_ = std::allocator<T>();
}

template <typename T>
void Vector<T>::ReleaseResource(){
	if(allocated_size_ == 0) return;
	for(number_type i = 0;i != element_size_; ++i)
		allocator_.destroy(head_pointer_ + i);
	allocator_.deallocate(head_pointer_,allocated_size_);
}

template <typename T>
void Vector<T>::Clear() noexcept {
	ReleaseResource();
	Initialize();
}

template <typename T>
void Vector<T>::EnlargeMemory(){
	number_type temp_allocated_size = allocated_size_ * 2;
	number_type temp_element_size = element_size_;
	T *temp_head_pointer = allocator_.allocate(temp_allocated_size);
	for(size_t i = 0; i != element_size_; ++i)
		allocator_.construct(temp_head_pointer + i,std::move(*(head_pointer_ + i)));
	this->ReleaseResource();
	allocated_size_ = temp_allocated_size;
	element_size_ = temp_element_size;
	head_pointer_ = temp_head_pointer;
	tail_pointer_ = head_pointer_ + element_size_ - 1;
}

template <typename T>
void Vector<T>::ReduceMemory(){
	number_type temp_allocated_size = allocated_size_ / 2;
	number_type temp_element_size = element_size_;
	T *temp_head_pointer = allocator_.allocate(temp_allocated_size);
	for(size_t i = 0;i != element_size_; ++i)
		allocator_.construct(temp_head_pointer + i,std::move(*(head_pointer_ + i)));
	this->ReleaseResource();
	allocated_size_ = temp_allocated_size;
	element_size_ = temp_element_size;
	head_pointer_ = temp_head_pointer;
	tail_pointer_ = head_pointer_ + element_size_ - 1;
}

template <typename T>
T Vector<T>::At(const number_type index) const{
	if(index >= element_size_)
		throw new std::runtime_error("Wrong Index Beyond ---- At()");
	return *(head_pointer_ + index);
}

template <typename T>
typename Vector<T>::positive_iterator Vector<T>::Begin() noexcept{
	return valerij::VectorPositiveIterator<T>(head_pointer_);
}

template <typename T>
typename Vector<T>::positive_iterator Vector<T>::End() noexcept{
	if(tail_pointer_ == nullptr) return valerij::VectorPositiveIterator<T>(nullptr);
	return valerij::VectorPositiveIterator<T>(tail_pointer_ + 1);
}

template <typename T>
typename Vector<T>::negative_iterator Vector<T>::RBegin() noexcept{
	return valerij::VectorNegativeIterator<T>(tail_pointer_);
}

template <typename T>
typename Vector<T>::negative_iterator Vector<T>::REnd() noexcept{
	if(head_pointer_ == nullptr) return valerij::VectorNegativeIterator<T>(nullptr);
	return valerij::VectorNegativeIterator<T>(head_pointer_ - 1);
}

template <typename T>
void Vector<T>::Assign(const number_type &size,const T &element){
	if(size == 0) return;
	this->Clear();
	
	element_size_ = size;
	allocated_size_ = size * 2;
	
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_ - 1;
	
	for(size_t i = 0; i != element_size_; ++i)
		allocator_.construct(head_pointer_ + i, element);
}

template <typename T>
void Vector<T>::Assign(std::initializer_list<T> list){
	number_type list_size = list.size();
	this->Clear();
	if(list_size == 0){ return;}
	
	allocated_size_ = list_size * 2;
	element_size_ = list_size;
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_ - 1;
	for(size_t i = 0;i != list_size; ++i)
		allocator_.construct(head_pointer_ + i,std::move(*(list.begin() + i)));
}

template <typename T>
template <typename Iterator>
void Vector<T>::Assign(const Iterator iterator_first,const Iterator iterator_second){
	size_t size = 0;
	for(Iterator iterator_temp = iterator_first;iterator_temp != iterator_second;++iterator_temp)
		++size;
	
	this->Clear();
	
	allocated_size_ = size * 2;
	element_size_ = size;
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = tail_pointer_ + element_size_ - 1;
	
	Iterator iterator_temp = iterator_first;
	for(size_t i = 0; i != size; ++i)
		allocator_.construct(head_pointer_ + i, *(iterator_temp++));	
}

template <typename T>
void Vector<T>::PushBack(const T &element){
	if(allocated_size_ == 0){this->Assign(1,element); return;}
	allocator_.construct(++tail_pointer_,element);
	if((++element_size_) == allocated_size_) EnlargeMemory();
}

template <typename T>
void Vector<T>::PushBack(T &&element){
	if(allocated_size_ == 0){this->Assign(1,element); return;}
	allocator_.construct(++tail_pointer_,std::move(element));
	if((++element_size_) == allocated_size_) EnlargeMemory();
}

template <typename T>
T Vector<T>::PopBack(){
	if(element_size_ == 0)
		throw new std::runtime_error("No element ---- PopBack()");
	T temp_element = std::move(*(tail_pointer_--));
	if(element_size_ == 1) {this->Clear(); return temp_element;}
	if(element_size_ <= allocated_size_ / 4) ReduceMemory();
	return temp_element;
}

template <typename T>
typename Vector<T>::positive_iterator Vector<T>::Insert(positive_iterator iterator,
													    const T &element){	
	if(allocated_size_ == 0) {PushBack(element); return this->Begin();}
	
	int32_t difference = iterator - this->Begin();
	if(difference < 0) throw new std::runtime_error("Wrong Iterator Position ----Insert(iterator,element)");
	allocator_construct(++tail_pointer_,element);
	++element_size_;
	for(int32_t i = element_size_ - 1;i != difference; --i)
		*(head_pointer_ + i) = std::move(*(head_pointer_ + i - 1));
	*(head_pointer_ + difference) = element;
	if(element_size_ == allocated_size_) EnlargeMemory();
	return this->Begin() + difference;
}

template <typename T>
typename Vector<T>::positive_iterator Vector<T>::Insert(positive_iterator iterator,
														const number_type size,const T &element){
	if(size == 0) throw new std::runtime_error("Wrong Insert Number ---- Insert(iterator,size,element)");
	if(allocated_size_ == 0){this->Assgin(size,element); return this->Begin();}
	
	int32_t difference = iterator - this->Begin();
	if(difference < 0) throw new std::runtime_error("Wrong Iterator Position ----Insert()");
	while(allocated_size_ <= size + element_size_) EnlargeMemory();
	
	if(element_size_ - difference >= size){
		for(size_t i = 0;i != size; ++i)
			allocator_.construct(tail_pointer_ + i + 1,std::move(*(tail_pointer_ -size + i + 1)));
		tail_pointer_ += size;
		for(size_t i = 0;i != element_size_ - size - difference; ++i)
			*(tail_pointer_ - size - i) = std::move(*(tail_pointer_ - 2*size - i));
		for(size_t i = 0;i != size; ++i)
			*(head_pointer_ + i + difference) = element;
		element_size_ += size;
		return (this->Begin() + difference);	
	}
	
	for(size_t i = 0;i != element_size_ - difference; ++i)
		allocator_.construct(tail_pointer_ + size - i,std::move(*(tail_pointer_ - i)));
	for(size_t i = 0;i != size-element_size_ + difference; ++i)
		allocator_.construct(tail_pointer_ + 1 + i,element);
	tail_pointer_ += size;
	for(size_t i = 0;i != element_size_ - difference; ++i)
		*(head_pointer_ + i + difference) = element;
	element_size_ += size;
	return this->Begin() + difference;
}

template <typename T>
template <typename Iterator>
typename Vector<T>::positive_iterator Vector<T>::Insert(positive_iterator iterator,
													    const Iterator iterator_first,const Iterator iterator_second){
	size_t size = 0;
	for(Iterator iterator_temp = iterator_first;iterator_temp != iterator_second; ++iterator_temp)
		++size;
	
	if(allocated_size_ == 0){this->Assign(iterator_first,iterator_second); return this->Begin();}
	
	int32_t difference = iterator - this->Begin();
	if(difference < 0) throw new std::runtime_error("Wrong Iterator Position ----Insert()");
	while(allocated_size_ <= size + element_size_) EnlargeMemory();
	
	if(element_size_ - difference >= size){
		for(size_t i = 0;i != size; ++i)
			allocator_.construct(tail_pointer_ + i + 1,std::move(*(tail_pointer_ -size + i + 1)));
		tail_pointer_ += size;
		for(size_t i = 0;i != element_size_ - size - difference; ++i)
			*(tail_pointer_ - size - i) = std::move(*(tail_pointer_ - 2*size - i));
		size_t i = 0;
		Iterator iterator_temp = iterator_first;
		while(iterator_temp != iterator_second)
			*(head_pointer_ + (i++) + difference) = *(iterator_temp++);
		element_size_ += size;
		return (this->Begin() + difference);	
	}
	
	for(size_t i = 0;i != element_size_ - difference; ++i)
		allocator_.construct(tail_pointer_ + size - i,std::move(*(tail_pointer_ - i)));
	tail_pointer_ += size;
	Iterator iterator_temp = iterator_second;
	for(size_t i = 0;i != size-element_size_ + difference; ++i)
		allocator_.construct(tail_pointer_ - i - element_size_ + difference,*(--iterator_temp));
	iterator_temp = iterator_first;
	for(size_t i = 0;i != element_size_ - difference; ++i)
		*(head_pointer_ + i + difference) = *(iterator_temp++);
	element_size_ += size;
	return this->Begin() + difference;
}

template <typename T>
typename Vector<T>::positive_iterator Vector<T>::Erase(positive_iterator iterator){
	if(element_size_ == 0) throw new std::runtime_error("No Element -----Erase(iterator)");
	if(element_size_ == 1 && iterator == this->Begin()){ this->Clear(); return this->Begin();}
	
	int32_t difference = iterator - this->Begin();
	if(difference < 0 || difference >= static_cast<int32_t>(element_size_))
		throw new std::runtime_error("Wrong Iterator Position ----Erase(iterator)");
	
	--element_size_;
	for(size_t i = static_cast<size_t>(difference);i != element_size_; ++i)
		*(head_pointer_ + i) = std::move(*(head_pointer_ + i + 1));
	allocator_.destroy(tail_pointer_--);
	if(element_size_ <= allocated_size_ / 4) ReduceMemory();
	return this->Begin() + difference;
}

template <typename T>
typename Vector<T>::positive_iterator Vector<T>::Erase(positive_iterator iterator_first,
													   positive_iterator iterator_second){
	int32_t first_difference = iterator_first - this->Begin();
	int32_t second_difference = iterator_second - this->Begin();
	if(first_difference >= second_difference || first_difference < 0 || second_difference <= 0)
		throw new std::runtime_error("Wrong Iterator Position ---- Erase(iterator,iterator)");
	
	size_t size = static_cast<size_t>(second_difference) - static_cast<size_t>(first_difference);
	for(size_t i = 0;i != element_size_ - second_difference; ++i)
		*(head_pointer_ + first_difference + i) = std::move(*(head_pointer_ + second_difference + i));
	for(size_t i = 0;i != size; ++i)
		allocator_.destroy(tail_pointer_--);
	element_size_ -= size;
	while(element_size_ <= allocated_size_ / 4) ReduceMemory();
	return this->Begin() + first_difference;
}

template <typename T>
typename Vector<T>::negative_iterator Vector<T>::Insert(negative_iterator iterator,
														const T &element){	
	if(allocated_size_ == 0) {PushBack(element); return this->RBegin();}
	
	int32_t difference = iterator - this->RBegin();
	if(difference < 0) throw new std::runtime_error("Wrong Iterator Position ----Insert(iterator,element)");
	allocator_construct(++tail_pointer_,element);
	++element_size_;
	for(int32_t i = 0;i != difference; ++i)
		*(tail_pointer_ - i) = std::move(*(tail_pointer_ - i - 1));
	*(tail_pointer_ - difference) = element;
	if(element_size_ == allocated_size_) EnlargeMemory();
	return this->RBegin() + difference;
}

template <typename T>
typename Vector<T>::negative_iterator Vector<T>::Insert(negative_iterator iterator,
														const number_type size,const T &element){
	if(size == 0) throw new std::runtime_error("Wrong Insert Number ---- Insert(iterator,size,element)");
	if(allocated_size_ == 0){this->Assgin(size,element); return this->RBegin();}
	
	int32_t difference = iterator - this->RBegin();
	if(difference < 0) throw new std::runtime_error("Wrong Iterator Position ----Insert()");
	while(allocated_size_ <= size + element_size_) EnlargeMemory();
	
	if(difference >= size){
		for(size_t i = 0;i != size; ++i)
			allocator_.construct(tail_pointer_ + i + 1,std::move(*(tail_pointer_ - size + i + 1)));
		tail_pointer_ += size;
		for(size_t i = 0;i != difference - size; ++i)
			*(tail_pointer_ - size - i) = std::move(*(tail_pointer_ - 2*size - i));
		for(size_t i = 0;i != size; ++i)
			*(tail_pointer_ - i - difference) = element;
		element_size_ += size;
		return (this->RBegin() + difference);	
	}
	
	for(size_t i = 0;i != difference; ++i)
		allocator_.construct(tail_pointer_ + size - i,std::move(*(tail_pointer_ - i)));
	for(size_t i = 0;i != size - difference; ++i)
		allocator_.construct(tail_pointer_ + 1 + i,element);
	tail_pointer_ += size;
	for(size_t i = 0;i != difference; ++i)
		*(tail_pointer_ - i - size) = element;
	element_size_ += size;
	return this->RBegin() + difference;
}

template <typename T>
template <typename Iterator>
typename Vector<T>::negative_iterator Vector<T>::Insert(negative_iterator iterator,
														const Iterator iterator_first,const Iterator iterator_second){
	size_t size = 0;
	for(Iterator iterator_temp = iterator_first;iterator_temp != iterator_second; ++iterator_temp)
		++size;
	
	if(allocated_size_ == 0){this->Assign(iterator_first,iterator_second); return this->RBegin();}
	
	int32_t difference = iterator - this->RBegin();
	if(difference < 0) throw new std::runtime_error("Wrong Iterator Position ----Insert()");
	while(allocated_size_ <= size + element_size_) EnlargeMemory();

	if(static_cast<size_t>(difference) >= size){
		for(size_t i = 0;i != size; ++i)
			allocator_.construct(tail_pointer_ + i + 1,std::move(*(tail_pointer_ - size + i + 1)));
		tail_pointer_ += size;
		for(size_t i = 0;i != difference - size; ++i)
			*(tail_pointer_ - size - i) = std::move(*(tail_pointer_ - 2*size - i));
		size_t i = 0;
		Iterator iterator_temp = iterator_first;
		while(iterator_temp != iterator_second)
			*(tail_pointer_ - (i++) - difference) = *(iterator_temp++);
		element_size_ += size;
		return (this->RBegin() + difference);	
	}
	
	for(size_t i = 0;i != static_cast<size_t>(difference); ++i)
		allocator_.construct(tail_pointer_ + size - i,std::move(*(tail_pointer_ - i)));
	Iterator iterator_temp = iterator_first;
	for(size_t i = 0;i != size - difference; ++i)
		allocator_.construct(tail_pointer_ + size - difference - i,*(iterator_temp++));
	for(size_t i = 0;i != static_cast<size_t>(difference); ++i)
		*(tail_pointer_ - i) = *(iterator_temp++);
	tail_pointer_ += size;
	element_size_ += size;
	return this->RBegin() + difference;
}

template <typename T>
typename Vector<T>::negative_iterator Vector<T>::Erase(negative_iterator iterator){
	if(element_size_ == 0) throw new std::runtime_error("No Element -----Erase(iterator)");
	if(element_size_ == 1 && iterator == this->RBegin()){ this->Clear(); return this->RBegin();}
	
	int32_t difference = iterator - this->RBegin();
	if(difference < 0 || difference >= static_cast<int32_t>(element_size_))
		throw new std::runtime_error("Wrong Iterator Position ----Erase(iterator)");
	
	--element_size_;
	for(size_t i = static_cast<size_t>(difference);i != 0; --i)
		*(tail_pointer_ - i) = std::move(*(tail_pointer_ - i + 1));
	allocator_.destroy(tail_pointer_--);
	if(element_size_ <= allocated_size_ / 4) ReduceMemory();
	return this->RBegin() + difference;
}

template <typename T>
typename Vector<T>::negative_iterator Vector<T>::Erase(negative_iterator iterator_first,
													   negative_iterator iterator_second){
	int32_t first_difference = iterator_first - this->RBegin();
	int32_t second_difference = iterator_second - this->RBegin();
	if(first_difference >= second_difference || first_difference < 0 || second_difference <= 0)
		throw new std::runtime_error("Wrong Iterator Position ---- Erase(iterator,iterator)");
	
	size_t size = static_cast<size_t>(second_difference) - static_cast<size_t>(first_difference);
	for(size_t i = 0;i != static_cast<size_t>(first_difference); ++i)
		*(tail_pointer_ - second_difference + i + 1) = std::move(*(tail_pointer_ - first_difference + i + 1));
	for(size_t i = 0;i != size; ++i)
		allocator_.destroy(tail_pointer_--);
	element_size_ -= size;
	while(element_size_ <= allocated_size_ / 4) ReduceMemory();
	return this->RBegin() + first_difference;
}



}
#endif
