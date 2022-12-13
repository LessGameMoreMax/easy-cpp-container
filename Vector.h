#ifndef VECTOR_H
#define VECTOR_H
#include <initializer_list>
#include <memory>

//Debug------------------------
#include <iostream>
//Debug------------------------

namespace sablin{

//Iteartor Class==============Begin============================
template <typename T>
class VectorIterator{
	template <typename TYPE>
	friend bool operator==(const VectorIterator<TYPE>&,const VectorIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator!=(const VectorIterator<TYPE>&,const VectorIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator<=(const VectorIterator<TYPE>&,const VectorIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator>=(const VectorIterator<TYPE>&,const VectorIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator<(const VectorIterator<TYPE>&,const VectorIterator<TYPE>&);
	template <typename TYPE>
	friend bool operator>(const VectorIterator<TYPE>&,const VectorIterator<TYPE>&);
	template <typename TYPE>
	friend int32_t operator-(const VectorIterator<TYPE>&,const VectorIterator<TYPE>&);
protected:
	T *pointer_ = nullptr;
public:
	VectorIterator<T>* temp_pointer = nullptr;
	VectorIterator() : pointer_(nullptr){}
	VectorIterator(T *pointer) : pointer_(pointer) {}
	VectorIterator(const VectorIterator&);
	VectorIterator(VectorIterator&&);
	VectorIterator& operator=(const VectorIterator&);
	VectorIterator& operator=(VectorIterator&&);
	virtual ~VectorIterator();

	T& operator*() const;
	T* operator->() const;
	
	virtual VectorIterator<T>& operator++() = 0;
	virtual VectorIterator<T>& operator--() = 0;
	
	virtual VectorIterator<T>& operator++(int) = 0;
	virtual VectorIterator<T>& operator--(int) = 0;
	
	virtual VectorIterator<T>& operator+=(const int32_t&) = 0;
	virtual VectorIterator<T>& operator-=(const int32_t&) = 0;
	
	virtual VectorIterator<T>& operator+(const int32_t&) = 0;
	virtual VectorIterator<T>& operator-(const int32_t&) = 0;
	
	virtual VectorIterator<T>& operator+=(const size_t&) = 0;
	virtual VectorIterator<T>& operator-=(const size_t&) = 0;
	
	virtual VectorIterator<T>& operator+(const size_t&) = 0;
	virtual VectorIterator<T>& operator-(const size_t&) = 0;
};

template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator &other):
	pointer_(other.pointer_){}
	
template <typename T>
VectorIterator<T>::VectorIterator(VectorIterator &&other):
								  pointer_(std::move(other.pointer_)){
	other.pointer_ = nullptr;
	if(other.temp_pointer != nullptr) delete other.temp_pointer;
	other.temp_pointer = nullptr;
}
	
template <typename T>
VectorIterator<T>& VectorIterator<T>::operator=(const VectorIterator &other){
	if(this == &other) return *this;
	pointer_ = other.pointer_;
	if(temp_pointer != nullptr) delete temp_pointer;
	//Attention!
	temp_pointer = nullptr;
	return *this;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator=(VectorIterator &&other){
	if(this == &other) return *this;
	VectorIterator<T>::operator=(std::move(other));
	pointer_ = other.pointer_;
	other.pointer_ = nullptr;
	if(temp_pointer != nullptr) delete temp_pointer;
	//Attention!
	temp_pointer = nullptr;
	
	if(other.temp_pointer != nullptr) delete other.temp_pointer;
	other.temp_pointer = nullptr;
	return *this;
}

template <typename T>
VectorIterator<T>::~VectorIterator<T>(){
	pointer_ = nullptr;
	if(temp_pointer != nullptr) delete temp_pointer;
	temp_pointer = nullptr;
}

template <typename T>
bool operator==(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
	return lhs.pointer_ == rhs.pointer_;
}

template <typename T>
bool operator!=(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
	return lhs.pointer_ != rhs.pointer_;
}

template <typename T>
T& VectorIterator<T>::operator*() const{
	return *pointer_;	
}

template <typename T>
T* VectorIterator<T>::operator->() const{
	return & this->operator*();
}

template <typename T>
class PositiveIterator : public VectorIterator<T>{
public:
	PositiveIterator() : VectorIterator<T>(){}
	PositiveIterator(T *pointer) : VectorIterator<T>(pointer) {}
	PositiveIterator(const PositiveIterator&) = default;
	PositiveIterator(PositiveIterator&&) = default;
	PositiveIterator& operator=(const PositiveIterator&) = default;
	PositiveIterator& operator=(PositiveIterator&&) = default;
	~PositiveIterator() override = default;
	
	VectorIterator<T>& operator++() override;
	VectorIterator<T>& operator--() override;
	VectorIterator<T>& operator++(int) override;
	VectorIterator<T>& operator--(int) override;
	VectorIterator<T>& operator+=(const int32_t&) override;
	VectorIterator<T>& operator-=(const int32_t&) override;
	
	VectorIterator<T>& operator+(const int32_t&) override;
	VectorIterator<T>& operator-(const int32_t&) override;
	
	VectorIterator<T>& operator+=(const size_t&) override;
	VectorIterator<T>& operator-=(const size_t&) override;
	
	VectorIterator<T>& operator+(const size_t&) override;
	VectorIterator<T>& operator-(const size_t&) override;
	
};

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator++(){
	++VectorIterator<T>::pointer_;
	return *this;
}

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator--(){
	--VectorIterator<T>::pointer_;
	return *this;
}

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator++(int){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new PositiveIterator(*this);
	++*this;
	return (*VectorIterator<T>::temp_pointer);
}

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator--(int){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new PositiveIterator(*this);
	--*this;
	return (*VectorIterator<T>::temp_pointer);
} 

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator+=(const int32_t &difference){
	VectorIterator<T>::pointer_ += difference;
	return *this;
}

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator-=(const int32_t &difference){
	VectorIterator<T>::pointer_ -= difference;
	return *this;
}

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator+(const int32_t &difference){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new PositiveIterator(*this);
	(*VectorIterator<T>::temp_pointer) += difference;
	return (*VectorIterator<T>::temp_pointer);
}

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator-(const int32_t &difference){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new PositiveIterator(*this);
	(*VectorIterator<T>::temp_pointer) -= difference;
	return (*VectorIterator<T>::temp_pointer);
}

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator+=(const size_t &difference){
	VectorIterator<T>::pointer_ += difference;
	return *this;
}

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator-=(const size_t &difference){
	VectorIterator<T>::pointer_ -= difference;
	return *this;
}

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator+(const size_t &difference){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new PositiveIterator(*this);
	(*VectorIterator<T>::temp_pointer) += difference;
	return (*VectorIterator<T>::temp_pointer);
}

template <typename T>
VectorIterator<T>& PositiveIterator<T>::operator-(const size_t &difference){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new PositiveIterator(*this);
	(*VectorIterator<T>::temp_pointer) -= difference;
	return (*VectorIterator<T>::temp_pointer);
}


template <typename T>
class NegativeIterator : public VectorIterator<T>{
public:
	NegativeIterator() : VectorIterator<T>(){}
	NegativeIterator(T *pointer) : VectorIterator<T>(--pointer) {}
	NegativeIterator(const NegativeIterator&) = default;
	NegativeIterator(NegativeIterator&&) = default;
	NegativeIterator& operator=(const NegativeIterator&) = default;
	NegativeIterator& operator=(NegativeIterator&&) = default;
	~NegativeIterator() override = default;
	
	VectorIterator<T>& operator++() override;
	VectorIterator<T>& operator--() override;
	VectorIterator<T>& operator++(int) override;
	VectorIterator<T>& operator--(int) override;
	VectorIterator<T>& operator+=(const int32_t&) override;
	VectorIterator<T>& operator-=(const int32_t&) override;
	
	VectorIterator<T>& operator+(const int32_t&) override;
	VectorIterator<T>& operator-(const int32_t&) override;
	
	VectorIterator<T>& operator+=(const size_t&) override;
	VectorIterator<T>& operator-=(const size_t&) override;
	
	VectorIterator<T>& operator+(const size_t&) override;
	VectorIterator<T>& operator-(const size_t&) override;
};

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator++(){
	--VectorIterator<T>::pointer_;
	return *this;
}
template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator--(){
	++VectorIterator<T>::pointer_;
	return *this;
}

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator++(int){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new NegativeIterator(*this);
	++*this;
	return (*VectorIterator<T>::temp_pointer);
}

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator--(int){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new NegativeIterator(*this);
	--*this;
	return (*VectorIterator<T>::temp_pointer);
}

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator+=(const int32_t &different){
	VectorIterator<T>::pointer_ -= different;
	return *this;
}

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator-=(const int32_t &different){
	VectorIterator<T>::pointer_ += different;
	return *this;
}

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator+(const int32_t &difference){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new NegativeIterator(*this);
	(*VectorIterator<T>::temp_pointer) += difference;
	return (*VectorIterator<T>::temp_pointer);
}

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator-(const int32_t &difference){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new NegativeIterator(*this);
	(*VectorIterator<T>::temp_pointer) -= difference;
	return (*VectorIterator<T>::temp_pointer);
}

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator+=(const size_t &different){
	VectorIterator<T>::pointer_ -= different;
	return *this;
}

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator-=(const size_t &different){
	VectorIterator<T>::pointer_ += different;
	return *this;
}

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator+(const size_t &difference){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new NegativeIterator(*this);
	(*VectorIterator<T>::temp_pointer) += difference;
	return (*VectorIterator<T>::temp_pointer);
}

template <typename T>
VectorIterator<T>& NegativeIterator<T>::operator-(const size_t &difference){
	if(VectorIterator<T>::temp_pointer != nullptr) delete VectorIterator<T>::temp_pointer;
	VectorIterator<T>::temp_pointer = new NegativeIterator(*this);
	(*VectorIterator<T>::temp_pointer) -= difference;
	return (*VectorIterator<T>::temp_pointer);
}

//Not Member Function, so use RTTI to imitate virtual functions!
//RTTI!
//Compare operator=====================Begin=======================
template <typename T>
bool operator<=(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
	if(typeid(lhs) == typeid(PositiveIterator<T>) && typeid(rhs) == typeid(PositiveIterator<T>))
		return (lhs.pointer_ - rhs.pointer_) <= 0;
	
	if(typeid(lhs) == typeid(NegativeIterator<T>) && typeid(rhs) == typeid(NegativeIterator<T>))
		return (lhs.pointer_ - rhs.pointer_) >= 0;
	
	throw new std::runtime_error("Wrong Compare Type!----operator<=");
}

template <typename T>
bool operator>=(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
	if(typeid(lhs) == typeid(PositiveIterator<T>) && typeid(rhs) == typeid(PositiveIterator<T>))
		return (lhs.pointer_ - rhs.pointer_) >= 0;
	
	if(typeid(lhs) == typeid(NegativeIterator<T>) && typeid(rhs) == typeid(NegativeIterator<T>))
		return (lhs.pointer_ - rhs.pointer_) <= 0;
	
	throw new std::runtime_error("Wrong Compare Type!----operator>=");
}

template <typename T>
bool operator<(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
	if(typeid(lhs) == typeid(PositiveIterator<T>) && typeid(rhs) == typeid(PositiveIterator<T>))
		return (lhs.pointer_ - rhs.pointer_) < 0;
	
	if(typeid(lhs) == typeid(NegativeIterator<T>) && typeid(rhs) == typeid(NegativeIterator<T>))
		return (lhs.pointer_ - rhs.pointer_) > 0;
	
	throw new std::runtime_error("Wrong Compare Type!----operator<");
}

template <typename T>
bool operator>(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
	if(typeid(lhs) == typeid(PositiveIterator<T>) && typeid(rhs) == typeid(PositiveIterator<T>))
		return (lhs.pointer_ - rhs.pointer_) > 0;
	
	if(typeid(lhs) == typeid(NegativeIterator<T>) && typeid(rhs) == typeid(NegativeIterator<T>))
		return (lhs.pointer_ - rhs.pointer_) < 0;
	
	throw new std::runtime_error("Wrong Compare Type!----operator>");
}

template <typename T>
int32_t operator-(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
	if(typeid(lhs) == typeid(PositiveIterator<T>) && typeid(rhs) == typeid(PositiveIterator<T>))
		return lhs.pointer_ - rhs.pointer_;
	
	if(typeid(lhs) == typeid(NegativeIterator<T>) && typeid(rhs) == typeid(NegativeIterator<T>))
		return rhs.pointer_ - lhs.pointer_;
	
	throw new std::runtime_error("Wrong Mius Type!----operator-");
}

//Vector Part========================================Begin=================================================
template <typename T>
class Vector{
public:
	typedef T 		element_type;
	typedef size_t  number_type;
	//Virtaul need!
	typedef VectorIterator<T>& iterator_type;
private:
	number_type allocated_size_;
	number_type element_size_;
	std::allocator<T> allocator_;
	T *head_pointer_;
	T *tail_pointer_;
	
	VectorIterator<T> *begin_pointer_ = nullptr;
	VectorIterator<T> *end_pointer_ = nullptr;
	VectorIterator<T> *rbegin_pointer_ = nullptr;
	VectorIterator<T> *rend_pointer_ = nullptr;
	VectorIterator<T> *return_pointer_ = nullptr;
	
	void ReleaseMemory();
	void ReleaseIterator(bool);
	void ReleaseReturnIterator();
	
	void EnlargeMemory();
	void ReduceMemory();
	
	int32_t GetDifference(iterator_type&);
	iterator_type ReturnBegin(iterator_type&) noexcept;
public:
	Vector():allocated_size_(0),element_size_(0),head_pointer_(nullptr),tail_pointer_(nullptr){}
	explicit Vector(std::initializer_list<T>&&);
	//User must make sure the order of iterator and the same container
	template <typename Iterator>
	explicit Vector(Iterator&,Iterator&);
	explicit Vector(const int32_t,const T&);
//	explicit Vector(const int32_t); Deleted!
	
	Vector(const Vector&);
	Vector(Vector&&);
	
	Vector& operator=(const Vector&);
	Vector& operator=(Vector&&);
	
	~Vector();

	//Debug---------------------
	void DebugPrint(){
		std::cout << "allocated_size_ : " << allocated_size_ << std::endl;
		std::cout << "element_size_ : " << element_size_ << std::endl;
		std::cout << "ELEMENT IS : " << std::endl;
		for(number_type i = 0;i != element_size_;++i)
			std::cout << *(head_pointer_ + i) << " ";
		std::cout << std::endl;
	}
	//Debug---------------------
	
//Iterators===============Begin========================

	iterator_type Begin() noexcept;
	iterator_type End() noexcept;
	//Privide the reverse Iterator!	
	iterator_type RBegin() noexcept;
	iterator_type REnd() noexcept;
	
//Capacity================Begin=========================
	size_t get_element_size() const {return element_size_;}
	size_t get_allocated_size() const {return allocated_size_;}
	bool IsEmpty() const {return element_size_ == 0;}
//Element access============Begin=========================
	T operator[](const number_type index) const {return *(head_pointer_+index);}
	T At(const number_type) const;
	T Front() const {return *(head_pointer_);}
	T Back() const {return *(tail_pointer_-1);}
//Modifiers=================Begin===========================
	void Assign(const number_type&,const T&);
	void Assign(std::initializer_list<T>&&);
	template <typename Iterator>
	void Assign(Iterator&,Iterator&);
	
	void PushBack(const T&);
	void PushBack(T&&);
	
	T PopBack();
	
	iterator_type Insert(iterator_type,const T&);
	iterator_type Insert(iterator_type,const number_type,const T&);
	template <typename Iterator>
	iterator_type Insert(iterator_type,Iterator&,Iterator&);
	
	iterator_type Erase(iterator_type);
	iterator_type Erase(iterator_type,iterator_type);
	
	void Clear() noexcept;
};


//Construct Functions======Begin==================================
template <typename T>
Vector<T>::Vector(std::initializer_list<T> &&list){
	typename std::initializer_list<T>::size_type list_size = list.size();
	//If initializer list is empty,return immediately after initialize.
	if(list_size == 0){
		head_pointer_ = tail_pointer_ = nullptr;
		element_size_ = allocated_size_ = 0;
		return;
	}
	
	//If intializer list is not empty,allocate the memory.
	allocated_size_ = list_size * 2;
	element_size_ = list_size;
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_;
	
	for(size_t i = 0;i != list_size;++i)
		allocator_.construct(head_pointer_ + i,std::move(*(list.begin() + i)));
}

template <typename T>
template <typename Iterator>
Vector<T>::Vector(Iterator &iterator_first,Iterator &iterator_second){
	//primer judge but do not identity the truth
	if(iterator_first >= iterator_second)
		throw new std::runtime_error("Wrong Iterator Position ----Vector Constructor"); 
	
	size_t iterator_length = iterator_second-iterator_first;
	//Keep the rule of cpp
	allocated_size_ = iterator_length * 2;
	element_size_ = iterator_length;
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_;
	//Just Copy the element
	//This way can makesure that if the pointer is from the different container,
	//the construct data is wrong nor consume all resource
	for(size_t i = 0;i != iterator_length;++i)
		allocator_.construct(head_pointer_ + i,*(iterator_first + i));
}

template <typename T>
Vector<T>::Vector(const int32_t size,const T &element){
	if(size < 0) throw new std::runtime_error("Size Wrong ----Vector Constructor");
	
	allocated_size_ = size * 2;
	element_size_ = size;
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_;
	
	for(int32_t i = 0;i != size;++i)
		allocator_.construct(head_pointer_ + i, element);
}

//Copy Constructor===================Begin==============================
template <typename T>
Vector<T>::Vector(const Vector &another){
	element_size_ = another.element_size_;
	allocated_size_ = another.allocated_size_;
	//if memory size is zero
	if(allocated_size_ == 0){
		head_pointer_ = tail_pointer_ = nullptr;
		return;
	}
	//if memory size if not zero,allocator the memory
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_;
	//Copy the data
	for(size_t i = 0;i != element_size_;++i)
		allocator_.construct(head_pointer_ + i,*(another.head_pointer_ + i));
}

//Move Constructor===================Begin===============================
template <typename T>
Vector<T>::Vector(Vector &&another){
	element_size_ = another.element_size_;
	allocated_size_ = another.allocated_size_;
	head_pointer_ = another.head_pointer_;
	tail_pointer_ = another.tail_pointer_;
	//Don't Forget the allocator!
	allocator_ = std::move(another.allocator_);
	//Preseve the Moved Object won't release the resource!!!
	another.element_size_ = another.allocated_size_ = 0;
	another.head_pointer_ = another.tail_pointer_ = nullptr;
	another.ReleaseIterator(true);
}

//Copy Assaginment==================Begin================================
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &another){
	//Check out the self assaginment!
	if(this == &another) return *this;
	
	//Release the previous resource!
	ReleaseMemory();
	ReleaseIterator(true);
	
	//Construct again!
	element_size_ = another.element_size_;
	allocated_size_ = another.allocated_size_;
	//if memory size is zero
	if(allocated_size_ == 0){return *this;}
	//if memory size if not zero,allocator the memory
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_;
	//Copy the data
	for(size_t i = 0;i != element_size_;++i)
		allocator_.construct(head_pointer_ + i,*(another.head_pointer_ + i));
	return *this;
} 

//Move Assaginment===================Begin==============================
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &&another){
	//Check out the self assaginment!
	if(this == &another) return *this;
	
	//Release the previous resource!
	ReleaseMemory();
	ReleaseIterator(true);
	
	//Move the resource! 
	element_size_ = another.element_size_;
	allocated_size_ = another.allocated_size_;
	head_pointer_ = another.head_pointer_;
	tail_pointer_ = another.tail_pointer_;
	//Don't Forget the allocator!
	allocator_ = std::move(another.allocator_);
	//Preseve the Moved Object won't release the resource When it destruct!!!
	another.element_size_ = another.allocated_size_ = 0;
	another.head_pointer_ = another.tail_pointer_ = nullptr;
	another.ReleaseIterator(true);
	return *this;
}

//Destructor Function==============Begin================================
template <typename T>
Vector<T>::~Vector(){
	ReleaseMemory();
	ReleaseIterator(true);
}

//Private Functions=================Begin===============================
template <typename T>
void Vector<T>::ReleaseMemory(){
	if(allocated_size_ == 0) return;
	for(number_type i = 0;i != element_size_;++i)
		allocator_.destroy(head_pointer_ + i);
	allocator_.deallocate(head_pointer_,allocated_size_);
	
	head_pointer_ = tail_pointer_ = nullptr;
	element_size_ = allocated_size_ = 0;
}

template <typename T>
void Vector<T>::ReleaseIterator(bool release_return_iterator){
	if(begin_pointer_ != nullptr) delete begin_pointer_;
	begin_pointer_ = nullptr;
	if(end_pointer_ != nullptr) delete end_pointer_;
	end_pointer_ = nullptr;
	if(rbegin_pointer_ != nullptr) delete rbegin_pointer_;
	rbegin_pointer_ = nullptr;
	if(rend_pointer_ != nullptr) delete rend_pointer_;
	rend_pointer_ = nullptr;
	if(release_return_iterator) ReleaseReturnIterator();
}

template <typename T>
void Vector<T>::ReleaseReturnIterator(){
	if(return_pointer_ != nullptr) delete return_pointer_;
	return_pointer_ = nullptr;
}

template <typename T>
void Vector<T>::EnlargeMemory(){
	//Not Assume Element Size Is Allocated Size 1/2
	ReleaseIterator(false);
	number_type temp_allocated_size = allocated_size_ * 2;
	number_type temp_element_size = element_size_;
	T *temp_head_pointer = allocator_.allocate(temp_allocated_size);
	for(size_t i = 0;i != element_size_;++i)
		allocator_.construct(temp_head_pointer + i,std::move(*(head_pointer_ + i)));
	ReleaseMemory();
	
	allocated_size_ = temp_allocated_size;
	element_size_ = temp_element_size;
	head_pointer_ = temp_head_pointer;
	tail_pointer_ = head_pointer_ + element_size_;
}

template <typename T>
void Vector<T>::ReduceMemory(){
	ReleaseIterator(false);
	number_type temp_allocated_size = allocated_size_ / 2;
	number_type temp_element_size = element_size_;
	T *temp_head_pointer = allocator_.allocate(temp_allocated_size);
	for(size_t i = 0;i != element_size_;++i)
		allocator_.construct(temp_head_pointer + i,std::move(*(head_pointer_ + i)));
	ReleaseMemory();
	
	allocated_size_ = temp_allocated_size;
	element_size_ = temp_element_size;
	head_pointer_ = temp_head_pointer;
	tail_pointer_ = head_pointer_ + element_size_;
}

template <typename T>
int32_t Vector<T>::GetDifference(Vector<T>::iterator_type &iterator){
	//Not Use the Position of begin iterator!
	VectorIterator<T> *temp_begin_pointer = new PositiveIterator(head_pointer_); 
	int32_t difference = *temp_begin_pointer - iterator;
	delete temp_begin_pointer;
	return (-difference);
}

template <typename T>
typename Vector<T>::iterator_type Vector<T>::ReturnBegin(iterator_type &iterator) noexcept{
	VectorIterator<T> *temp = nullptr;
	if(return_pointer_ != nullptr)
		temp = return_pointer_->temp_pointer;
	if(temp != &iterator) delete return_pointer_;
	return_pointer_ = new PositiveIterator(head_pointer_);	
	return (*return_pointer_);
}

//Public Functions====================Begin=============================
template <typename T>
T Vector<T>::At(const number_type index) const{
	if(index >= element_size_)
		throw new std::runtime_error("Wrong Index Beyond ---- At()");
	return *(head_pointer_ + index);
}

template <typename T>
typename Vector<T>::iterator_type Vector<T>::Begin() noexcept{
	if(begin_pointer_ != nullptr) delete begin_pointer_;
	begin_pointer_ = new PositiveIterator(head_pointer_);
	return (*begin_pointer_);
}

template <typename T>
typename Vector<T>::iterator_type Vector<T>::End() noexcept{
	if(end_pointer_ != nullptr) delete end_pointer_;
	end_pointer_ = new PositiveIterator(tail_pointer_);
	return (*end_pointer_);
}

template <typename T>
typename Vector<T>::iterator_type Vector<T>::RBegin() noexcept{
	if(rbegin_pointer_ != nullptr) delete rbegin_pointer_;
	rbegin_pointer_ = new NegativeIterator(tail_pointer_);
	return (*rbegin_pointer_);
}

template <typename T>
typename Vector<T>::iterator_type Vector<T>::REnd() noexcept{
	if(rend_pointer_ != nullptr) delete rend_pointer_;
	rend_pointer_ = new NegativeIterator(head_pointer_);
	return (*rend_pointer_);
}

template <typename T>
void Vector<T>::Assign(const number_type &size,const T &element){
	if(size == 0) return;
	ReleaseIterator(true);
	ReleaseMemory();
	
	element_size_ = size;
	allocated_size_ = size * 2;
	
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_;
	
	for(size_t i = 0;i != element_size_;++i)
		allocator_.construct(head_pointer_ + i, element);
}

template <typename T>
void Vector<T>::Assign(std::initializer_list<T> &&list){
	typename std::initializer_list<T>::size_type list_size = list.size();

	ReleaseIterator(true);
	ReleaseMemory();
	
	//If initializer list is empty,return immediately after initialize.
	if(list_size == 0){
		head_pointer_ = tail_pointer_ = nullptr;
		element_size_ = allocated_size_ = 0;
		return;
	}
	
	//If intializer list is not empty,allocate the memory.
	allocated_size_ = list_size * 2;
	element_size_ = list_size;
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_;
	
	for(size_t i = 0;i != list_size;++i)
		allocator_.construct(head_pointer_ + i,std::move(*(list.begin() + i)));
}

template <typename T>
template <typename Iterator>
void Vector<T>::Assign(Iterator &iterator_first,Iterator &iterator_second){
	//primer judge but do not identity the truth
	if(iterator_first >= iterator_second)
		throw new std::runtime_error("Wrong Iterator Position ----Assign!"); 
	
	ReleaseIterator(true);
	ReleaseMemory();
	
	size_t iterator_length = iterator_second-iterator_first;
	//Keep the rule of cpp
	allocated_size_ = iterator_length * 2;
	element_size_ = iterator_length;
	head_pointer_ = allocator_.allocate(allocated_size_);
	tail_pointer_ = head_pointer_ + element_size_;
	//Just Copy the element
	//This way can makesure that if the pointer is from the different container,
	//the construct data is wrong nor consume all resource
	for(size_t i = 0;i != iterator_length;++i)
		allocator_.construct(head_pointer_ + i,*(iterator_first + i));
}

template <typename T>
void Vector<T>::PushBack(const T &element){
	if(allocated_size_ == 0){ this->Assign(1,element); return;}
	ReleaseIterator(true);
	allocator_.construct(tail_pointer_++,element);
	if((++element_size_) == allocated_size_) EnlargeMemory();
}

template <typename T>
void Vector<T>::PushBack(T &&element){
	if(allocated_size_ == 0) { this->Assign(1,std::move(element)); return;}
	ReleaseIterator(false);
	allocator_.construct(tail_pointer_++,std::move(element));
	if((++element_size_) == allocated_size_) EnlargeMemory();
}

template <typename T>
T Vector<T>::PopBack(){
	ReleaseIterator(true);
	if(element_size_ == 0) throw new std::runtime_error("No element! ----PopBack()");
	T temp_element = std::move(*(--tail_pointer_));
	allocator_.destroy(tail_pointer_);
	--element_size_;
	if(element_size_ == 0){ReleaseMemory(); return temp_element;}
	if(element_size_ <= allocated_size_/4) { ReduceMemory();}
	return temp_element;
}

template <typename T>
typename Vector<T>::iterator_type Vector<T>::Insert(iterator_type iterator,
													const T &element){
	
	if(allocated_size_ == 0) {PushBack(element); return this->ReturnBegin(iterator);}
	
	int32_t difference = GetDifference(iterator);
	if(difference < 0) throw new std::runtime_error("Wrong Iterator Position! ----Insert()");
	ReleaseIterator(false);
	allocator_.construct(tail_pointer_++,element);
	++element_size_;
	for(int32_t i = element_size_ - 1;i != difference;--i)
		*(head_pointer_ + i) = std::move(*(head_pointer_ + i - 1));
	*(head_pointer_ + difference) = element;
	if(element_size_ == allocated_size_) EnlargeMemory();
	return (this->ReturnBegin(iterator) + difference);
}

template <typename T>
typename Vector<T>::iterator_type Vector<T>::Insert(iterator_type iterator,
													const number_type n,const T &element){
	
	if(n == 0) throw new std::runtime_error("Wrong Insert Number ---- Insert");
	
	if(allocated_size_ == 0) {
		allocated_size_ = n * 2;
		element_size_ = n;
		head_pointer_ = allocator_.allocate(allocated_size_);
		tail_pointer_ = head_pointer_ + element_size_;
		for(size_t i = 0;i != element_size_;++i)
			allocator_.construct(head_pointer_ + i, element);
		return this->ReturnBegin(iterator);
	}
	
	int32_t difference = GetDifference(iterator);
	if(difference < 0) throw new std::runtime_error("Wrong Iterator Position! ----Insert()");
	ReleaseIterator(false);
	while(allocated_size_ <= n + element_size_) EnlargeMemory();
	
	if(element_size_ - difference >= n){
		for(size_t i = 0;i != n; ++i)
			allocator_.construct(tail_pointer_ + i,std::move(*(tail_pointer_ - n + i)));
		tail_pointer_ += n;
		for(size_t i = 0;i != element_size_ - n - difference; ++i)
			*(tail_pointer_ - n - i - 1) = std::move(*(tail_pointer_ - 2*n - 1 - i));
		for(size_t i = 0;i != n; ++i)
			*(head_pointer_ + i + difference) = element;
		element_size_ += n;
		return (this->ReturnBegin(iterator) + difference);	
	}
	
	for(size_t i = 0;i != element_size_ - difference; ++i)
		allocator_.construct(tail_pointer_ + n - 1 - i,std::move(*(tail_pointer_ - 1 - i)));
	for(size_t i = 0;i != n - element_size_ + difference; ++i)
		allocator_.construct(tail_pointer_ + i, element);
	tail_pointer_ += n;
	for(size_t i = 0;i != element_size_ - difference; ++i)
		*(head_pointer_ + i + difference) = element;
	element_size_ += n;
	return (this->ReturnBegin(iterator) + difference);
}

template <typename T>
template <typename Iterator>
typename Vector<T>::iterator_type Vector<T>::Insert(iterator_type iterator,
										Iterator &iterator_first,Iterator &iterator_second){
	int32_t n = iterator_second - iterator_first;
	if(n <= 0) throw new std::runtime_error("Wrong Insert Iterator ---- Insert");
	
	if(allocated_size_ == 0) {
		allocated_size_ = n * 2;
		element_size_ = n;
		head_pointer_ = allocator_.allocate(allocated_size_);
		tail_pointer_ = head_pointer_ + element_size_;
		size_t i = 0;
		while(iterator_first != iterator_second)
			allocator_.construct(head_pointer_ + (i++),*(iterator_first++));
		return this->ReturnBegin(iterator);
	}
	
	int32_t difference = GetDifference(iterator);
	if(difference < 0) throw new std::runtime_error("Wrong Iterator Position! ----Insert()");
	ReleaseIterator(false);
	while(allocated_size_ <= n + element_size_) EnlargeMemory();
	
	if(element_size_ - difference >= static_cast<size_t>(n)){
		for(int32_t i = 0;i != n; ++i)
			allocator_.construct(tail_pointer_ + i,std::move(*(tail_pointer_ - n + i)));
		tail_pointer_ += n;
		for(size_t i = 0;i != element_size_ - n - difference; ++i)
			*(tail_pointer_ - n - i - 1) = std::move(*(tail_pointer_ - 2*n - 1 - i));
		size_t i = 0;
		while(iterator_first != iterator_second)
			*(head_pointer_ + (i++) + difference) = *(iterator_first++);
		element_size_ += n;
		return (this->ReturnBegin(iterator) + difference);	
	}
	
	for(size_t i = 0;i != element_size_ - difference; ++i)
		allocator_.construct(tail_pointer_ + n - 1 - i,std::move(*(tail_pointer_ - 1 - i)));
	tail_pointer_ += n;
	for(size_t i = 0;i != n - element_size_ + difference; ++i)
		allocator_.construct(tail_pointer_ - i - element_size_ + difference - 1, *(--iterator_second));
	for(size_t i = 0;i != element_size_ - difference; ++i)
		*(head_pointer_ + i + difference) = *(iterator_first++);
	element_size_ += n;
	return (this->ReturnBegin(iterator) + difference);
}

template <typename T>
typename Vector<T>::iterator_type Vector<T>::Erase(iterator_type iterator){
	if(element_size_ == 0) throw new std::runtime_error("Wrong! No element---- Erase()");
	if(element_size_ == 1){ 
		ReleaseIterator(false);
		ReleaseMemory();
		return this->ReturnBegin(iterator);
	}
	
	int32_t difference = GetDifference(iterator);
	if(difference < 0 || difference >= static_cast<int32_t>(element_size_))
		throw new std::runtime_error("Wrong Iterator Position! ----Erase()");
	ReleaseIterator(false);
	
	--element_size_;
	for(size_t i = static_cast<size_t>(difference);i != element_size_; ++i)
		*(head_pointer_ + i) = std::move(*(head_pointer_ + i + 1));
	allocator_.destroy(--tail_pointer_);
	if(element_size_ <= allocated_size_/4) ReduceMemory();
	return (this->ReturnBegin(iterator) + difference);
}

template <typename T>
typename Vector<T>::iterator_type Vector<T>::Erase(iterator_type iterator_first,
												   iterator_type iterator_second){
	int32_t first_difference = GetDifference(iterator_first);
	int32_t second_difference = GetDifference(iterator_second);
	if(first_difference >= second_difference || first_difference < 0 || second_difference <= 0)
		throw new std::runtime_error("Wrong Iterator Position! ----Erase()");
	
	size_t n = static_cast<size_t>(second_difference) - static_cast<size_t>(first_difference);
	for(size_t i = 0;i != element_size_ - second_difference; ++i)
		*(head_pointer_ + first_difference + i) = std::move(*(head_pointer_ + second_difference + i));
	for(size_t i = 0;i != n; ++i)
		allocator_.destroy(--tail_pointer_);
	element_size_ -= n;
	while(element_size_ <= allocated_size_ / 4) ReduceMemory();
	return (this->ReturnBegin(iterator_first) + first_difference);
}

template <typename T>
void Vector<T>::Clear() noexcept{
	ReleaseIterator(true);
	ReleaseMemory();
}

}
#endif
