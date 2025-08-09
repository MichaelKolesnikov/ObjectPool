#include <gtest/gtest.h>
#include <ObjectPool.h>

class Dummy
{
public:
    int value = 0;
    Dummy() = default;
};

TEST(ObjectPoolTest, GetAndRelease)
{
    ObjectPool<Dummy> pool;

    Dummy *obj1 = pool.get();
    ASSERT_NE(obj1, nullptr);
    obj1->value = 42;

    EXPECT_EQ(pool.size(), 1);

    pool.release(obj1);
    EXPECT_EQ(pool.size(), 1);

    Dummy *obj2 = pool.get();
    EXPECT_EQ(obj1, obj2);
    EXPECT_EQ(obj2->value, 42);
}

TEST(ObjectPoolTest, ReserveIncreasesSize)
{
    ObjectPool<Dummy> pool;

    pool.reserveObjects(5);
    EXPECT_GE(pool.size(), 5);

    pool.reserveObjects(3);
    EXPECT_GE(pool.size(), 5);
}

TEST(ObjectPoolTest, ClearEmptiesPool)
{
    ObjectPool<Dummy> pool;

    pool.reserveObjects(3);
    EXPECT_GE(pool.size(), 3);

    pool.clear();
    EXPECT_EQ(pool.size(), 0);

    Dummy *obj = pool.get();
    EXPECT_NE(obj, nullptr);
    pool.release(obj);
}
