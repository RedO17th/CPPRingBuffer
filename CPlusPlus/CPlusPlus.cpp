#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

template <class T>
class BaseRingBuffer
{
public:

    BaseRingBuffer(T index, T capacity)
    {
        SetIndex(index);

        this->capacity = capacity;

        pRing = new T[capacity];
    }

    ~BaseRingBuffer()
    {
        currentIndex = 0;
        nextIndex = 0;
        capacity = 0;

        delete pRing;
        pRing = nullptr;
    }

    virtual bool Add(T value) { return true; }

    virtual void DeleteTheNumberOfItems(int number)
    {
        if (number == 0)
            return;

        if (number >= capacity)
        {
            Clear();
            return;
        }

        int prevIndx = currentIndex;
        int capacityCopy = capacity;
        for (int i = 0; i < number; i++)
        {
            prevIndx = prevIndx == 0 ? --capacityCopy : --prevIndx;
            *(pRing + prevIndx) = 0;
        }
    }

    virtual void Show()
    {
        cout << "---Space---" << endl;
        for (int i = 0; i < capacity; i++)
            cout << *(pRing + i) << endl;
    }

protected:

    T* pRing = nullptr;

    T currentIndex = 0;
    T nextIndex = 0;
    T capacity = 0;

    virtual void SetIndex(int index)
    {
        if (index < 0) index = 0;

        nextIndex = index >= capacity ? 0 : index;
    }

    virtual int GetIndex()
    {
        if (nextIndex == 0 || nextIndex == capacity)
            nextIndex = 0;

        return nextIndex;
    }

    virtual void Clear()
    {
        for (int i = 0; i < capacity; i++)
            pRing[i] = 0;
    }
};

template <class T>
class LoopedRingBuffer : public BaseRingBuffer<T>
{
public:
    LoopedRingBuffer(T index, T capacity) : BaseRingBuffer<T>(index, capacity) { }

    bool Add(T value) override
    {
        this->currentIndex = this->GetIndex();
        this->pRing[this->currentIndex] = value;

        this->nextIndex++;

        return BaseRingBuffer<T>::Add(value);
    }
};

/*
class UnLoopedRingBuffer : public BaseRingBuffer
{
public:
    UnLoopedRingBuffer(int index, int capacity) : BaseRingBuffer(index, capacity) { }

    bool Add(int value) override
    {
        if (FreeCellIsExists() == false)
            return false;

        pRing[currentIndex] = value;
        nextIndex++;

        return BaseRingBuffer::Add(value);
    }

protected:

    bool FreeCellIsExists()
    {
        nextIndex = nextIndex == capacity ? 0 : nextIndex;

        bool result = SearchFromIndex(nextIndex);

        if (result == false)
            result = SearchFromIndex(0);

        return result;
    }

    bool SearchFromIndex(int index)
    {
        bool result = false;
        for (int i = index; i < capacity; i++)
        {
            if (*(pRing + i) == 0)
            {
                currentIndex = i;
                result = truse;
                break;
            }
        }

        return result;
    }
};

class FirstRingBuffer : public LoopedRingBuffer
{
public:
    FirstRingBuffer(int index, int capacity) : LoopedRingBuffer(index, capacity) { }
};

class SecondRingBuffer : public UnLoopedRingBuffer
{
public:
    SecondRingBuffer(int index, int capacity) : UnLoopedRingBuffer(index, capacity) { }
};
*/

int main()
{
    /*
    //Uncomment the required option for the test

    //First option
    //Init and Add three item with data overwriting
    cout << "First option ..." << endl;
    BaseRingBuffer *iBuffer = new FirstRingBuffer(0, 3);
    iBuffer->Add(11);
    iBuffer->Add(22);
    iBuffer->Add(33);
    iBuffer->Show();
    //Remove one item before current position
    iBuffer->DeleteTheNumberOfItems(1);
    iBuffer->Show();
    //Add next item with data overwriting
    iBuffer->Add(44);
    iBuffer->Show();
    delete iBuffer;
    iBuffer = nullptr;
    */

    /*
    //Second option
    //Init and Add five item without data overwriting
    cout << endl;
    cout << "Second option ..." << endl;
    BaseRingBuffer *unLoopedBuffer = new SecondRingBuffer(2, 5);
    unLoopedBuffer->Add(1);
    unLoopedBuffer->Add(2);
    unLoopedBuffer->Add(3);
    unLoopedBuffer->Show();

    unLoopedBuffer->Add(4);
    unLoopedBuffer->Add(5);
    unLoopedBuffer->Show();

    //If the addition occurred correctly, then display the result
    if(unLoopedBuffer->Add(6))
        unLoopedBuffer->Show();
    else
    {
        //otherwise, free up a few seats
        unLoopedBuffer->DeleteTheNumberOfItems(3);
        unLoopedBuffer->Show();
    }

    unLoopedBuffer->Add(6);
    unLoopedBuffer->Add(7);
    unLoopedBuffer->Add(8);
    unLoopedBuffer->Show();

    if(unLoopedBuffer->Add(9))
        unLoopedBuffer->Show();
    else
    {
        unLoopedBuffer->DeleteTheNumberOfItems(1);
        unLoopedBuffer->Show();
    }

    unLoopedBuffer->Add(9);
    unLoopedBuffer->Show();

    delete unLoopedBuffer;
    unLoopedBuffer = nullptr;
    */

    BaseRingBuffer<int>* a = new LoopedRingBuffer<int>(0, 5);
    a->Add(1);
    a->Add(2);
    a->Add(3);
    a->Show();

    return 0;
}
