#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <initializer_list>
namespace sablin{
	
template <typename T>
class Vector;

namespace dzerzhinsky{

namespace lenin{

template <typename T>
class VectorIteratorBase{
private:
    T *pointer_;
public:
    VectorIteratorBase() : pointer_(nullptr){}
    VectorIteratorBase(const VectorIteratorBase&) = default;
    VectorIteratorBase& operator=(const VectorIteratorBase&) = default;
    VectorIteratorBase& operator=(VectorIteratorBase&&) = default;
    virtual ~VectorIteratorBase();
    
    void set_pointer(T*);
    T* get_pointer() const;

    virtual void SelfAdd(int32_t)=0;
    virtual void SelfMinus(int32_t)=0;
};

template <typename T>
VectorIteratorBase<T>::~VectorIteratorBase(){
    pointer_ = nullptr;
}

template <typename T>
void VectorIteratorBase<T>::set_pointer(T *pointer){
    pointer_ = pointer;
}

template <typename T>
T* VectorIteratorBase<T>::get_pointer() const{
    return pointer_;
}

template <typename T>
class VectorIteratorPositive : public VectorIteratorBase<T>{
public:
    VectorIteratorPositive(T*);
    VectorIteratorPositive(const VectorIteratorPositive&);
    VectorIteratorPositive(VectorIteratorPositive&&);
    VectorIteratorPositive& operator=(const VectorIteratorPositive&);
    VectorIteratorPositive& operator=(VectorIteratorPositive&&);
    ~VectorIteratorPositive() = default;

    void SelfAdd(int32_t) override;
    void SelfMinus(int32_t) override;
};

template <typename T>
VectorIteratorPositive<T>::VectorIteratorPositive(T *pointer){
    this->set_pointer(pointer);
}

template <typename T>
VectorIteratorPositive<T>::VectorIteratorPositive(const VectorIteratorPositive &another){
    this->set_pointer(another.get_pointer());
}

template <typename T>
VectorIteratorPositive<T>::VectorIteratorPositive(VectorIteratorPositive &&another){
    this->set_pointer(another.get_pointer());
    another.set_pointer(nullptr);
}

template <typename T>
VectorIteratorPositive<T>& VectorIteratorPositive<T>::operator=(const VectorIteratorPositive &another){
    if(this == &another) return *this;
    this->set_pointer(another.get_pointer());
    return *this;
}

template <typename T>
VectorIteratorPositive<T>& VectorIteratorPositive<T>::operator=(VectorIteratorPositive &&another){
    if(this == &another) return *this;
    this->set_pointer(another.get_pointer());
    another.set_pointer(nullptr);
    return *this;
}

template <typename T>
void VectorIteratorPositive<T>::SelfAdd(int32_t difference){
    T* pointer_temp = this->get_pointer();
    pointer_temp += difference;
    this->set_pointer(pointer_temp);
}

template <typename T>
void VectorIteratorPositive<T>::SelfMinus(int32_t difference){
    T* pointer_temp = this->get_pointer();
    pointer_temp -= difference;
    this->set_pointer(pointer_temp);
}

template <typename T>
class VectorIteratorNegative : public VectorIteratorBase<T>{
public:
    VectorIteratorNegative(T*);
    VectorIteratorNegative(const VectorIteratorNegative&);
    VectorIteratorNegative(VectorIteratorNegative&&);
    VectorIteratorNegative& operator=(const VectorIteratorNegative&);
    VectorIteratorNegative& operator=(VectorIteratorNegative&&);
    ~VectorIteratorNegative() = default;

    void SelfAdd(int32_t) override;
    void SelfMinus(int32_t) override;
};

template <typename T>
VectorIteratorNegative<T>::VectorIteratorNegative(T *pointer){
    this->set_pointer(pointer);
}

template <typename T>
VectorIteratorNegative<T>::VectorIteratorNegative(const VectorIteratorNegative &another){
    this->set_pointer(another.get_pointer());
}

template <typename T>
VectorIteratorNegative<T>::VectorIteratorNegative(VectorIteratorNegative &&another){
    this->set_pointer(another.get_pointer());
    another.set_pointer(nullptr);
}

template <typename T>
VectorIteratorNegative<T>& VectorIteratorNegative<T>::operator=(const VectorIteratorNegative &another){
    if(this == &another) return *this;
    this->set_pointer(another.get_pointer());
    return *this;
}

template <typename T>
VectorIteratorNegative<T>& VectorIteratorNegative<T>::operator=(VectorIteratorNegative &&another){
    if(this == &another) return *this;
    this->set_pointer(another.get_pointer());
    another.set_pointer(nullptr);
    return *this;
}

template <typename T>
void VectorIteratorNegative<T>::SelfAdd(int32_t difference){
    T* temp_pointer = this->get_pointer();
    temp_pointer -= difference;
    this->set_pointer(temp_pointer);
}

template <typename T>
void VectorIteratorNegative<T>::SelfMinus(int32_t difference){
    T* temp_pointer = this->get_pointer();
    temp_pointer += difference;
    this->set_pointer(temp_pointer);
}
}

template <typename T>
class VectorIterator{
    friend class Vector<T>;
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
private:
    lenin::VectorIteratorBase<T> *vector_iterator_base_pointer_;
public:
    VectorIterator();
    VectorIterator(const VectorIterator&);
    VectorIterator(VectorIterator&&);
    VectorIterator& operator=(const VectorIterator&);
    VectorIterator& operator=(VectorIterator&&);
    ~VectorIterator();

    VectorIterator<T>& operator++();
    VectorIterator<T>& operator--();
    VectorIterator<T> operator++(int);
    VectorIterator<T> operator--(int);

    VectorIterator<T>& operator+=(const int32_t&);
    VectorIterator<T>& operator-=(const int32_t&);
    VectorIterator<T> operator+(const int32_t&);
    VectorIterator<T> operator-(const int32_t&);

    T& operator*() const;
    T* operator->() const;
};

template <typename T>
VectorIterator<T>::VectorIterator():
vector_iterator_base_pointer_(nullptr){}

template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator &another){
    if(another.vector_iterator_base_pointer_ == nullptr){
        vector_iterator_base_pointer_ = nullptr;
        return;
    }
    if(typeid(*(another.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorPositive<T>))
        vector_iterator_base_pointer_ = new lenin::VectorIteratorPositive<T>(another.vector_iterator_base_pointer_->get_pointer());
    else if(typeid(*(another.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorNegative<T>))
        vector_iterator_base_pointer_ = new lenin::VectorIteratorNegative<T>(another.vector_iterator_base_pointer_->get_pointer());
    else
        throw new std::runtime_error("Construct Wrong Owing to Wrong Type!");
}

template <typename T>
VectorIterator<T>::VectorIterator(VectorIterator &&another){
    if(another.vector_iterator_base_pointer_ == nullptr){
        vector_iterator_base_pointer_ = nullptr;
        return;
    }
    vector_iterator_base_pointer_ = another.vector_iterator_base_pointer_;
    another.vector_iterator_base_pointer_ = nullptr;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator=(const VectorIterator &another){
    if(this == &another) return *this;

    lenin::VectorIteratorBase<T> *temp_pointer = nullptr;
    if(another.vector_iterator_base_pointer_ == nullptr)
        temp_pointer = nullptr;
    else if(typeid(*(another.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorPositive<T>))
        temp_pointer = new lenin::VectorIteratorPositive<T>(another.vector_iterator_base_pointer_->get_pointer());
    else if(typeid(*(another.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorNegative<T>))
        temp_pointer = new lenin::VectorIteratorNegative<T>(another.vector_iterator_base_pointer_->get_pointer());
    else
        throw new std::runtime_error("Construct Wrong Owing to Wrong Type!");

    if(vector_iterator_base_pointer_ != nullptr)
        delete vector_iterator_base_pointer_;

    vector_iterator_base_pointer_ = temp_pointer;
    return *this;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator=(VectorIterator &&another){
    if(this == &another) return *this;
    if(vector_iterator_base_pointer_ != nullptr)
        delete vector_iterator_base_pointer_;
    vector_iterator_base_pointer_ = another.vector_iterator_base_pointer_;
    another.vector_iterator_base_pointer_ = nullptr;
    return *this;
}

template <typename T>
VectorIterator<T>::~VectorIterator(){
    if(vector_iterator_base_pointer_ != nullptr)
        delete vector_iterator_base_pointer_;
    vector_iterator_base_pointer_ = nullptr;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator++(){
    if(vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    vector_iterator_base_pointer_->SelfAdd(1);
    return *this;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator--(){
    if(vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    vector_iterator_base_pointer_->SelfMinus(1);
    return *this;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int){
    if(vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    VectorIterator temp(*this);
    vector_iterator_base_pointer_->SelfAdd(1);
    return temp;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator--(int){
    if(vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    VectorIterator temp(*this);
    vector_iterator_base_pointer_->SelfMinus(1);
    return temp;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator+=(const int32_t &difference){
    if(vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator");
    vector_iterator_base_pointer_.SelfAdd(difference);
    return *this;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator-=(const int32_t &difference){
    if(vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator");
    vector_iterator_base_pointer_.SelfMinus(difference);
    return *this;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator+(const int32_t &difference){
    VectorIterator<T> temp(*this);
    temp += difference;
    return temp;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator-(const int32_t &difference){
    VectorIterator<T> temp(*this);
    temp -= difference;
    return temp;
}

template <typename T>
T& VectorIterator<T>::operator*() const{
    if(vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    return *(vector_iterator_base_pointer_->get_pointer());
}

template <typename T>
T* VectorIterator<T>::operator->() const{
    if(vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    return vector_iterator_base_pointer_->get_pointer();
}

template <typename T>
bool operator==(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
    if(lhs.vector_iterator_base_pointer_ != nullptr && rhs.vector_iterator_base_pointer_ != nullptr){
        if(typeid(*(lhs.vector_iterator_base_pointer_)) == typeid(*(rhs.vector_iterator_base_pointer_)))
            return lhs.vector_iterator_base_pointer_->get_pointer() == rhs.vector_iterator_base_pointer_->get_pointer();
        else
            return false;
    }else if(lhs.vector_iterator_base_pointer_ == nullptr && rhs.vector_iterator_base_pointer_ == nullptr){
        return true;
    }else{
        return false;
    }
}

template <typename T>
bool operator!=(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
    return !(lhs == rhs); 
}

template <typename T>
bool operator<=(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
    if(lhs.vector_iterator_base_pointer_ != nullptr && rhs.vector_iterator_base_pointer_ != nullptr){
        if(typeid(*(lhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorPositive<T>) &&
           typeid(*(rhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorPositive<T>))
                return lhs.vector_iterator_base_pointer_->get_pointer() <= rhs.vector_iterator_base_pointer_->get_pointer();
        else if(typeid(*(lhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorNegative<T>) &&
                typeid(*(rhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorNegative<T>))
                    return lhs.vector_iterator_base_pointer_->get_pointer() >= rhs.vector_iterator_base_pointer_->get_pointer();
        else
            throw new std::runtime_error("Wrong Iterator Type Comparsion!");
    }else if(lhs.vector_iterator_base_pointer_ == nullptr && rhs.vector_iterator_base_pointer_ == nullptr){
        return true;
    }else if(lhs.vector_iterator_base_pointer_ == nullptr && rhs.vector_iterator_base_pointer_ != nullptr){
        return true;
    }else{
        return false;
    }
}

template <typename T>
bool operator>=(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
    return lhs == rhs || !(lhs <= rhs);
}

template <typename T>
bool operator<(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
    if(lhs.vector_iterator_base_pointer_ != nullptr && rhs.vector_iterator_base_pointer_ != nullptr){
        if(typeid(*(lhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorPositive<T>) &&
           typeid(*(rhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorPositive<T>))
                return lhs.vector_iterator_base_pointer_->get_pointer() < rhs.vector_iterator_base_pointer_->get_pointer();
        else if(typeid(*(lhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorNegative<T>) &&
                typeid(*(rhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorNegative<T>))
                    return lhs.vector_iterator_base_pointer_->get_pointer() > rhs.vector_iterator_base_pointer_->get_pointer();
        else
            throw new std::runtime_error("Wrong Iterator Type Comparsion!");
    }else if(lhs.vector_iterator_base_pointer_ == nullptr && rhs.vector_iterator_base_pointer_ != nullptr){
        return true;
    }else{
        return false;
    }
}

template <typename T>
bool operator>(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
    return !(lhs <= rhs);
}

template <typename T>
int32_t operator-(const VectorIterator<T> &lhs,const VectorIterator<T> &rhs){
    if(lhs.vector_iterator_base_pointer_ != nullptr && rhs.vector_iterator_base_pointer_ != nullptr){
        if(typeid(*(lhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorPositive<T>) &&
           typeid(*(rhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorPositive<T>))
                return lhs.vector_iterator_base_pointer_->get_pointer() - rhs.vector_iterator_base_pointer_->get_pointer();
        else if(typeid(*(lhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorNegative<T>) &&
                typeid(*(rhs.vector_iterator_base_pointer_)) == typeid(lenin::VectorIteratorNegative<T>))
                    return rhs.vector_iterator_base_pointer_->get_pointer() - lhs.vector_iterator_base_pointer_->get_pointer();
        else
            throw new std::runtime_error("Wrong Type Comparsion!");
    }else if(lhs.vector_iterator_base_pointer_ == nullptr && rhs.vector_iterator_base_pointer_ == nullptr){
        return 0;
    }else{
        throw new std::runtime_error("Wrong Type Comparsion!");
    }
}

}

template <typename T>
class Vector{
public:
	typedef T 								   element_type;
	typedef size_t 							   number_type;
	typedef dzerzhinsky::VectorIterator<T>     iterator;
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

	iterator InsertPositive(iterator,const T&);
	iterator InsertPositive(iterator,const number_type,const T&);
	template <typename Iterator>
	iterator InsertPositive(iterator,const Iterator,const Iterator);
	
	iterator ErasePositive(iterator);
	iterator ErasePositive(iterator,iterator);

    iterator InsertNegative(iterator,const T&);
    iterator InsertNegative(iterator,const number_type,const T&);
    template <typename Iterator>
    iterator InsertNegative(iterator,const Iterator,const Iterator);

    iterator EraseNegative(iterator);
    iterator EraseNegative(iterator,iterator);
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
	
	iterator Begin() noexcept;
	iterator End() noexcept;
	iterator RBegin() noexcept;
	iterator REnd() noexcept;
	
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
	
	iterator Insert(iterator,const T&);
	iterator Insert(iterator,const number_type,const T&);
	template <typename Iterator>
	iterator Insert(iterator,const Iterator,const Iterator);
	
	iterator Erase(iterator);
	iterator Erase(iterator,iterator);
	
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
	
	if(allocated_size_ == 0){
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
typename Vector<T>::iterator Vector<T>::Begin() noexcept{
    dzerzhinsky::VectorIterator<T> temp;
    temp.vector_iterator_base_pointer_ = new dzerzhinsky::lenin::VectorIteratorPositive<T>(head_pointer_);
    return temp;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::End() noexcept{
    dzerzhinsky::VectorIterator<T> temp;
	if(tail_pointer_ == nullptr) temp.vector_iterator_base_pointer_ = new dzerzhinsky::lenin::VectorIteratorPositive<T>(nullptr);
    else                         temp.vector_iterator_base_pointer_ = new dzerzhinsky::lenin::VectorIteratorPositive<T>(tail_pointer_+1);
    return temp;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::RBegin() noexcept{
    dzerzhinsky::VectorIterator<T> temp;
    temp.vector_iterator_base_pointer_ = new dzerzhinsky::lenin::VectorIteratorNegative<T>(tail_pointer_);
    return temp;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::REnd() noexcept{
    dzerzhinsky::VectorIterator<T> temp;
	if(head_pointer_ == nullptr) temp.vector_iterator_base_pointer_ = new dzerzhinsky::lenin::VectorIteratorNegative<T>(nullptr);
    else                         temp.vector_iterator_base_pointer_ = new dzerzhinsky::lenin::VectorIteratorNegative<T>(head_pointer_ - 1);
	return temp;
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
typename Vector<T>::iterator Vector<T>::Insert(iterator var_iterator,
                                               const T &element){
    if(var_iterator.vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    else if(typeid(*(var_iterator.vector_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::VectorIteratorPositive<T>))
        return InsertPositive(var_iterator,element);
    else
        return InsertNegative(var_iterator,element);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::Insert(iterator var_iterator,
                                               const number_type size,const T &element){
    if(var_iterator.vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    else if(typeid(*(var_iterator.vector_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::VectorIteratorPositive<T>))
        return InsertPositive(var_iterator,size,element);
    else
        return InsertNegative(var_iterator,size,element);
}

template <typename T>
template <typename Iterator>
typename Vector<T>::iterator Vector<T>::Insert(iterator var_iterator,
                                               const Iterator iterator_first,
                                               const Iterator iterator_second){
    if(var_iterator.vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    else if(typeid(*(var_iterator.vector_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::VectorIteratorPositive<T>))
        return InsertPositive(var_iterator,iterator_first,iterator_second);
    else
        return InsertNegative(var_iterator,iterator_first,iterator_second);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::Erase(iterator var_iterator){
    if(var_iterator.vector_iterator_base_pointer_ == nullptr)
        throw new std::runtime_error("NULL Iterator!");
    else if(typeid(*(var_iterator.vector_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::VectorIteratorPositive<T>))
        return ErasePositive(var_iterator);
    else
        return EraseNegative(var_iterator);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::Erase(iterator iterator_first,
                                              iterator iterator_second){
    if(iterator_first.vector_iterator_base_pointer_ == nullptr ||
       iterator_second.vector_iterator_base_pointer_ == nullptr)
            throw new std::runtime_error("NULL Iterator!");
    else if(typeid(*(iterator_first.vector_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::VectorIteratorPositive<T>) &&
            typeid(*(iterator_second.vector_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::VectorIteratorPositive<T>))
        return ErasePositive(iterator_first,iterator_second);
    else if(typeid(*(iterator_first.vector_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::VectorIteratorNegative<T>) &&
            typeid(*(iterator_second.vector_iterator_base_pointer_)) ==
            typeid(dzerzhinsky::lenin::VectorIteratorNegative<T>))
        return EraseNegative(iterator_first,iterator_second);
    else
        throw new std::runtime_error("Wrong Iterator Type!");
}


template <typename T>
typename Vector<T>::iterator Vector<T>::InsertPositive(iterator var_iterator,
													    const T &element){	
	if(allocated_size_ == 0) {PushBack(element); return this->Begin();}
	
	int32_t difference = var_iterator - this->Begin();
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
typename Vector<T>::iterator Vector<T>::InsertPositive(iterator var_iterator,
											   const number_type size,const T &element){
	if(size == 0) throw new std::runtime_error("Wrong Insert Number ---- Insert(iterator,size,element)");
	if(allocated_size_ == 0){this->Assgin(size,element); return this->Begin();}
	
	int32_t difference = var_iterator - this->Begin();
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
typename Vector<T>::iterator Vector<T>::InsertPositive(iterator var_iterator,
													   const Iterator iterator_first,const Iterator iterator_second){
	size_t size = 0;
	for(Iterator iterator_temp = iterator_first;iterator_temp != iterator_second; ++iterator_temp)
		++size;
	
	if(allocated_size_ == 0){this->Assign(iterator_first,iterator_second); return this->Begin();}
	
	int32_t difference = var_iterator - this->Begin();
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
typename Vector<T>::iterator Vector<T>::ErasePositive(iterator var_iterator){
	if(element_size_ == 0) throw new std::runtime_error("No Element -----Erase(iterator)");
	if(element_size_ == 1 && var_iterator == this->Begin()){ this->Clear(); return this->Begin();}
	
	int32_t difference = var_iterator - this->Begin();
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
typename Vector<T>::iterator Vector<T>::ErasePositive(iterator iterator_first,
													  iterator iterator_second){
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
typename Vector<T>::iterator Vector<T>::InsertNegative(iterator var_iterator,
														const T &element){	
	if(allocated_size_ == 0) {PushBack(element); return this->RBegin();}
	
	int32_t difference = var_iterator - this->RBegin();
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
typename Vector<T>::iterator Vector<T>::InsertNegative(iterator var_iterator,
													   const number_type size,const T &element){
	if(size == 0) throw new std::runtime_error("Wrong Insert Number ---- Insert(iterator,size,element)");
	if(allocated_size_ == 0){this->Assgin(size,element); return this->RBegin();}
	
	int32_t difference = var_iterator - this->RBegin();
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
typename Vector<T>::iterator Vector<T>::InsertNegative(iterator var_iterator,
														const Iterator iterator_first,const Iterator iterator_second){
	size_t size = 0;
	for(Iterator iterator_temp = iterator_first;iterator_temp != iterator_second; ++iterator_temp)
		++size;
	
	if(allocated_size_ == 0){this->Assign(iterator_first,iterator_second); return this->RBegin();}
	
	int32_t difference = var_iterator - this->RBegin();
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
typename Vector<T>::iterator Vector<T>::EraseNegative(iterator var_iterator){
	if(element_size_ == 0) throw new std::runtime_error("No Element -----Erase(iterator)");
	if(element_size_ == 1 && var_iterator == this->RBegin()){ this->Clear(); return this->RBegin();}
	
	int32_t difference = var_iterator - this->RBegin();
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
typename Vector<T>::iterator Vector<T>::EraseNegative(iterator iterator_first,
													  iterator iterator_second){
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
