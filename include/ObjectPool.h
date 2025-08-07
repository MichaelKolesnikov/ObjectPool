#pragma once
#include <set>

template <class T>
class ObjectPool
{
    std::set<T *> freeObjects;
    std::set<T *> takenObjects;

public:
    ObjectPool() // O(1)
    {
    }
    ~ObjectPool() // O(N)
    {
        clear();
    }
    void reserve(size_t n) // O(n)
    {
        if (size() >= n)
        {
            return;
        }
        int missingObjectsNumber = n - size();
        while (missingObjectsNumber--)
        {
            freeObjects.insert(new T());
        }
    }
    T *get() // O(log(N))
    {
        if (freeObjects.empty())
        {
            freeObjects.insert(new T());
        }
        auto it = freeObjects.begin();
        T *ptrToReturn = *it;
        freeObjects.erase(it);

        takenObjects.insert(ptrToReturn);
        return ptrToReturn;
    }
    void release(T *ptr) // O(log(N))
    {
        freeObjects.insert(ptr);
        takenObjects.erase(ptr);
    }
    void clear() // O(N)
    {
        for (T *ptr : freeObjects)
        {
            delete ptr;
        }
        for (T *ptr : takenObjects)
        {
            delete ptr;
        }
        freeObjects.clear();
        takenObjects.clear();
    }
    size_t size() // O(1)
    {
        return freeObjects.size() + takenObjects.size();
    }
};
