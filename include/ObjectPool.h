#pragma once
#include <vector>
#include <unordered_set>

template <class T>
class ObjectPool
{
    std::vector<T *> freeObjects;
    std::unordered_set<T *> takenObjects;

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
        freeObjects.reserve(freeObjects.size() + missingObjectsNumber);
        while (missingObjectsNumber--)
        {
            freeObjects.push_back(new T());
        }
    }
    T *get() // ~ O(1)
    {
        if (freeObjects.empty())
        {
            freeObjects.push_back(new T());
        }
        T *ptrToReturn = freeObjects.back();
        freeObjects.pop_back();

        takenObjects.insert(ptrToReturn);
        return ptrToReturn;
    }
    void release(T *ptr) // ~ O(1)
    {
        auto it = takenObjects.find(ptr);
        if (it == takenObjects.end())
        {
            return;
        }
        takenObjects.erase(it);
        freeObjects.push_back(ptr);
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
