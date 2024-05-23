#include <iterator>
#include <stdexcept>

template <typename T>
class DynamicArray
{
private:
    unsigned capacity;
    unsigned current_size;
    T **elements;

    void initialize(unsigned from);
    void expand();

public:
    DynamicArray(unsigned initialCapacity = 5);
    ~DynamicArray();

    T &operator[](int index);

    void add(const T &element);
    void remove(int index);
    unsigned size() const;
    void clear();

    // Iterator typedefs
    typedef T* iterator;
    typedef const T* const_iterator;

    // Iterator functions
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};

template <typename T>
DynamicArray<T>::DynamicArray(unsigned initialCapacity)
    : capacity(initialCapacity), current_size(0)
{
    this->elements = new T *[this->capacity];
    initialize(0);
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    clear();
    delete[] this->elements;
}

template <typename T>
void DynamicArray<T>::initialize(unsigned from)
{
    for (unsigned i = from; i < this->capacity; ++i)
    {
        this->elements[i] = nullptr;
    }
}

template <typename T>
void DynamicArray<T>::expand()
{
    this->capacity *= 2;
    T **temp = new T *[this->capacity];
    for (unsigned i = 0; i < this->current_size; ++i)
    {
        temp[i] = this->elements[i];
    }
    delete[] this->elements;
    this->elements = temp;
    initialize(this->current_size);
}

template <typename T>
T &DynamicArray<T>::operator[](int index)
{
    if (index < 0 || static_cast<unsigned>(index) >= this->current_size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return *this->elements[index];
}

template <typename T>
void DynamicArray<T>::add(const T &element)
{
    if (this->current_size >= this->capacity)
    {
        expand();
    }
    this->elements[this->current_size++] = new T(element);
}

template <typename T>
void DynamicArray<T>::remove(int index)
{
    if (index < 0 || static_cast<unsigned>(index) >= this->current_size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    delete this->elements[index];

    if (index != this->current_size - 1)
    {
        this->elements[index] = this->elements[this->current_size - 1];
    }
    this->elements[--this->current_size] = nullptr;
}

template <typename T>
unsigned DynamicArray<T>::size() const
{
    return this->current_size;
}

template <typename T>
void DynamicArray<T>::clear()
{
    for (unsigned i = 0; i < this->current_size; ++i)
    {
        delete this->elements[i];
        this->elements[i] = nullptr;
    }
    this->current_size = 0;
}

template <typename T>
typename DynamicArray<T>::iterator DynamicArray<T>::begin() {
    return *this->elements; 
}

template <typename T>
typename DynamicArray<T>::iterator DynamicArray<T>::end() {
    return *(this->elements + this->current_size); 
}


template <typename T>
typename DynamicArray<T>::const_iterator DynamicArray<T>::begin() const {
    return *this->elements;
}

template <typename T>
typename DynamicArray<T>::const_iterator DynamicArray<T>::end() const {
    return *(this->elements + this->current_size);
}

