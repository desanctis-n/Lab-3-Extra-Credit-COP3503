#pragma once
#include <iostream>

using namespace std;

template <typename T>
class ABQ
{
    float _scaleFactor;
    unsigned int _maxCapacity;
    unsigned int _size;
    T* _array;
    unsigned int total_resizes;

public:

    //----- Cons/Destr -----//

    ABQ();
    ABQ(int capacity);
    ABQ(int capacity, float scale_factor);
    ~ABQ();

    //----- Copy/Assign -----//

    ABQ(const ABQ& d);
    ABQ& operator=(const ABQ& d);

    //----- Mutate -----//

    void enqueue(T data);
    T dequeue();

    //----- Access -----//

    T peek();
    T* getData();
    unsigned int getSize();
    unsigned int getMaxCapacity();
    unsigned int getTotalResizes();
};

//----- Construction/Destruction -----//

template <typename T>
ABQ<T>::ABQ()
{
    _scaleFactor = 2.0f;
    _maxCapacity = 1;
    _size = 0;
    _array = new T[_maxCapacity];
    total_resizes = 0;
}

template <typename T>
ABQ<T>::ABQ(int capacity)
{
    _scaleFactor = 2.0;
    _maxCapacity = capacity;
    _size = 0;
    _array = new T[_maxCapacity];
    total_resizes = 0;
}

template <typename T>
ABQ<T>::ABQ(int capacity, float scale_factor)
{
    _scaleFactor = scale_factor;
    _maxCapacity = capacity;
    _size = 0;
    _array = new T[_maxCapacity];
    total_resizes = 0;
}

template <typename T>
ABQ<T>::~ABQ()
{
    delete[] _array;
}

//----- Mutate -----//

template <typename T>
void ABQ<T>::enqueue(T data)
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
T ABQ<T>::dequeue()
{
    if (_size == 0)
    {
        throw runtime_error("An error has occurred.");
    }
    else
    {
        T dequeued = _array[0];

        if ((((float)(_size - 1) / (float)(_maxCapacity)) < (1.0 / (float)(_scaleFactor))))
        {
            _maxCapacity = _maxCapacity / _scaleFactor;
            _size--;
            total_resizes++;
            T* tempArray = new T[_maxCapacity];

            for (unsigned int i = 0; i < _size; i++)
            {
                tempArray[i] = _array[i + 1];
            }
            delete[] _array;
            _array = tempArray;

            return dequeued;
        }
        else
        {
            _size--;
            T* tempArray = new T[_maxCapacity];

            for (unsigned int i = 0; i < _size; i++)
            {
                tempArray[i] = _array[i + 1];
            }
            delete[] _array;
            _array = tempArray;

            return dequeued;
        }
    }
}

//----- Access -----//

template<typename T>
T ABQ<T>::peek()
{
    if (_size == 0)
    {
        throw runtime_error("An error has occurred.");
    }
    else
    {
        return _array[0];
    }
}

template <typename T>
T* ABQ<T>::getData()
{
    return _array;
}

template <typename T>
unsigned int ABQ<T>::getSize()
{
    return _size;
}

template <typename T>
unsigned int ABQ<T>::getMaxCapacity()
{
    return _maxCapacity;
}

template <typename T>
unsigned int ABQ<T>::getTotalResizes()
{
    return total_resizes;
}

