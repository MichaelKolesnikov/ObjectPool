#include <iostream>
#include <vector>
#include <ObjectPool.h>

using namespace std;

int main()
{
    ObjectPool<int> pool;
    pool.reserveObjects(3);
    std::vector<int *> v;
    for (int _ = 0; _ < 4; ++_)
    {
        v.push_back(pool.get());
    }

    for (auto p : v)
    {
        pool.release(p);
    }
    cout << pool.size() << endl;
}