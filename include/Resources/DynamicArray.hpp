#include <stdexcept>
#include <vector>

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
    DynamicArray(const DynamicArray &other);
    ~DynamicArray();

    T &operator[](int index);
    void operator=(const DynamicArray &other);

    void add(const T &element);
    void remove(int index);
    unsigned size() const;
    void clear();

    // Iterator typedefs
    typedef T **iterator;
    typedef const T **const_iterator;

    // Iterator functions
    iterator begin() { return elements; }
    iterator end() { return elements + current_size; }
    const_iterator begin() const { return elements; }
    const_iterator end() const { return elements + current_size; }
};

template <typename T>
DynamicArray<T>::DynamicArray(unsigned initialCapacity)
    : capacity(initialCapacity), current_size(0)
{
    elements = new T *[capacity];
    initialize(0);
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &other)
    : capacity(other.capacity), current_size(other.current_size)
{
    elements = new T *[capacity];
    for (unsigned i = 0; i < current_size; ++i)
    {
        elements[i] = new T(*other.elements[i]);
    }
    initialize(current_size);
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    clear();
    delete[] elements;
}

template <typename T>
void DynamicArray<T>::initialize(unsigned from)
{
    for (unsigned i = from; i < capacity; ++i)
    {
        elements[i] = nullptr;
    }
}

template <typename T>
void DynamicArray<T>::expand()
{
    capacity *= 2;
    T **temp = new T *[capacity];
    for (unsigned i = 0; i < current_size; ++i)
    {
        temp[i] = elements[i];
    }
    delete[] elements;
    elements = temp;
    initialize(current_size);
}

template <typename T>
T &DynamicArray<T>::operator[](int index)
{
    if (index < 0 || static_cast<unsigned>(index) >= current_size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return *elements[index];
}

template <typename T>
void DynamicArray<T>::operator=(const DynamicArray &other)
{
    if (this == &other)
    {
        return;
    }
    clear();
    delete[] elements;
    capacity = other.capacity;
    current_size = other.current_size;
    elements = new T *[capacity];
    for (unsigned i = 0; i < current_size; ++i)
    {
        elements[i] = new T(*other.elements[i]);
    }
    initialize(current_size);
}

template <typename T>
void DynamicArray<T>::add(const T &element)
{
    if (current_size >= capacity)
    {
        expand();
    }
    elements[current_size++] = new T(element);
}

template <typename T>
void DynamicArray<T>::remove(int index)
{
    if (index < 0 || static_cast<unsigned>(index) >= current_size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    delete elements[index];

    if (index != current_size - 1)
    {
        elements[index] = elements[current_size - 1];
    }
    elements[--current_size] = nullptr;
}

template <typename T>
unsigned DynamicArray<T>::size() const
{
    return current_size;
}

template <typename T>
void DynamicArray<T>::clear()
{
    for (unsigned i = 0; i < current_size; ++i)
    {
        delete elements[i];
        elements[i] = nullptr;
    }
    current_size = 0;
}
