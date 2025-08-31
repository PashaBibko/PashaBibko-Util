#include <Util.h>

PB_TEST_GROUP(PBU_VectorTests);

namespace PashaBibko::Util::CodeTests
{
    PB_TEST(PBU_VectorTests, VecConstructors)
    {
        /* Default constructor */
        Vec2i a;
        PB_EXPECT_EQL(a.x, 0);
        PB_EXPECT_EQL(a.y, 0);

        /* Single item constructor */
        Vec2i b(56);
        PB_EXPECT_EQL(b.x, 56);
        PB_EXPECT_EQL(b.y, 56);

        /* Multi-item constructor */
        Vec2i c(23117, 333);
        PB_EXPECT_EQL(c.x, 23117);
        PB_EXPECT_EQL(c.y, 333);
    }

    PB_TEST(PBU_VectorTests, Vec2_Aliases)
    {
        Vec2f v(4.0f);

        PB_EXPECT_EQL(v.x, 4);
        PB_EXPECT_EQL(v.y, 4);

        v[0] = 53;
        v[1] = 217;

        PB_EXPECT_EQL(v.x, 53);
        PB_EXPECT_EQL(v.y, 217);

        v.x = 7.4f;
        v.y = 9.7f;

        PB_EXPECT_EQL(v.x, 7.4f);
        PB_EXPECT_EQL(v.y, 9.7f);
    }

    PB_TEST(PBU_VectorTests, Vec3_Aliases)
    {
        Vec3f v(4983.0f);

        PB_EXPECT_EQL(v.x, 4983.0f);
        PB_EXPECT_EQL(v.y, 4983.0f);
        PB_EXPECT_EQL(v.z, 4983.0f);

        v[0] = 234;
        v[1] = 206;
        v[2] = 691;

        PB_EXPECT_EQL(v.x, 234);
        PB_EXPECT_EQL(v.y, 206);
        PB_EXPECT_EQL(v.z, 691);

        v.x = 756;
        v.y = 928;
        v.z = 256;

        PB_EXPECT_EQL(v.r, 756);
        PB_EXPECT_EQL(v.g, 928);
        PB_EXPECT_EQL(v.b, 256);
    }

    PB_TEST(PBU_VectorTests, Vec4_Aliases)
    {
        Vec4f v(5393.0f);

        PB_EXPECT_EQL(v.x, 5393.0f);
        PB_EXPECT_EQL(v.y, 5393.0f);
        PB_EXPECT_EQL(v.z, 5393.0f);
        PB_EXPECT_EQL(v.w, 5393.0f);

        v[0] = 254;
        v[1] = 534;
        v[2] = 349;
        v[3] = 435;

        PB_EXPECT_EQL(v.x, 254);
        PB_EXPECT_EQL(v.y, 534);
        PB_EXPECT_EQL(v.z, 349);
        PB_EXPECT_EQL(v.w, 435);

        v.x = 423;
        v.y = 534;
        v.z = 434;
        v.w = 503;

        PB_EXPECT_EQL(v.r, 423);
        PB_EXPECT_EQL(v.g, 534);
        PB_EXPECT_EQL(v.b, 434);
        PB_EXPECT_EQL(v.a, 503);
    }

    PB_TEST(PBU_VectorTests, VecIterator)
    {
        /* Non - const iterator */
        Util::Vec<10, int> vecA(0, 1, 2, 3, 45, 6, 7, 8, 9, 11);
        int arrA[] = { 0, 1, 2, 3, 45, 6, 7, 8, 9, 11 };

        std::size_t indexA = 0;
        for (int& item : vecA)
        {
            PB_EXPECT_EQL(item, arrA[indexA]);
            indexA++;
        }

        /* Const iterator */
        Util::Vec<10, int> vecB(6, 7, 2, 3, 1, 1, 7, 4, 2, 0);
        int arrB[] = { 6, 7, 2, 3, 1, 1, 7, 4, 2, 0 };

        std::size_t indexB = 0;
        for (const int& item : vecB)
        {
            PB_EXPECT_EQL(item, arrB[indexB]);
            indexB++;
        }
    }

    PB_TEST(PBU_VectorTests, VecEql)
    {
        Vec4i a(1, 2, 3, 4);
        Vec4i b(5, 6, 7, 8);
        Vec4i c(1, 2, 3, 4);
        Vec4i d(5, 6, 9, 8);

        PB_EXPECT_FALSE(a == b);
        PB_EXPECT_FALSE(b == d);

        PB_EXPECT_TRUE(a == c);
    }

    PB_TEST(PBU_VectorTests, VecNEql)
    {
        Vec4i a(1, 2, 3, 4);
        Vec4i b(1, 2, 5, 4);
        Vec4i c(5, 6, 7, 8);
        Vec4i d(5, 6, 7, 8);

        PB_EXPECT_TRUE(a != b);
        PB_EXPECT_TRUE(a != c);

        PB_EXPECT_FALSE(c != d);
    }
};
