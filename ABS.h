#pragma once
#include <iostream>

using namespace std;

template <typename T>
class ABS
{
    float _scaleFactor;
    unsigned int _maxCapacity;
    unsigned int _size;
    T* _array;
    unsigned int total_resizes;

public:

    //----- Cons/Destr -----//

    ABS();
    ABS(int capacity);
    ABS(int capacity, float scale_factor);
    ~ABS();

    //----- Copy/Assign -----//

    ABS(const ABS& d);
    ABS& operator=(const ABS& d);

    //----- Mutate -----//

    void push(T data);
    T pop();

    //----- Access -----//

    T peek();
    T* getData();
    unsigned int getSize();
    unsigned int getMaxCapacity();
    unsigned int getTotalResizes();
};

//----- Construction/Destruction -----//

template <typename T>
ABS<T>::ABS()
{
    _scaleFactor = 2.0;
    _maxCapacity = 1;
    _size = 0;
    _array = new T[_maxCapacity];
    total_resizes = 0;
}

template <typename T>
ABS<T>::ABS(int capacity)
{
    _scaleFactor = 2.0;
    _maxCapacity = capacity;
    _size = 0;
    _array = new T[_maxCapacity];
    total_resizes = 0;
}

template <typename T>
ABS<T>::ABS(int capacity, float scale_factor)
{
    _scaleFactor = scale_factor;
    _maxCapacity = capacity;
    _size = 0;
    _array = new T[_maxCapacity];
    total_resizes = 0;
}

template <typename T>
ABS<T>::~ABS()
{
    delete[] _array;
}

//----- Mutate -----//

template <typename T>
void ABS<T>::push(T data)
{
    if (_size == _maxCapacity)
    {
        // resize
        _maxCapacity = _maxCapacity * _scaleFactor;
        total_resizes++;
        T* tempArray = new T[_maxCapacity];

        for (unsigned int i = 0; i < _size; i++)
        {
            tempArray[i] = _array[i];
        }
        delete[] _array;
        _array = tempArray;
    }
    // shift data
    _array[_size] = data;
    ++_size;
}

template<typename T>
T ABS<T>::pop()
{
    if (_size == 0)
    {
        throw runtime_error("An error has occurred.");
    }
    else
    {
        T popped = _array[_size - 1];

        if ((((float)(_size - 1) / (float)(_maxCapacity)) < (1.0 / (float)(_scaleFactor))))
        {
            _maxCapacity = _maxCapacity / _scaleFactor;
            _size--;
            total_resizes++;
            T* tempArray = new T[_maxCapacity];

            for (unsigned int i = 0; i < _size; i++)
            {
                tempArray[i] = _array[i];
            }
            delete[] _array;
            _array = tempArray;

            return popped;
        }
        else
        {
            _size--;
            return popped;
        }
    }
}

//----- Access -----//

template<typename T>
T ABS<T>::peek()
{
    if (_size == 0)
    {
        throw runtime_error("An error has occurred.");
    }
    else
    {
        return _array[_size - 1];
    }
}

template <typename T>
T* ABS<T>::getData()
{
    return _array;
}

template <typename T>
unsigned int ABS<T>::getSize()
{
    return _size;
}

template <typename T>
unsigned int ABS<T>::getMaxCapacity()
{
    return _maxCapacity;
}

template <typename T>
unsigned int ABS<T>::getTotalResizes()
{
    return total_resizes;
}

