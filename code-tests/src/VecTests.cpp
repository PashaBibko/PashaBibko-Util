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

    PB_TEST(PBU_VectorTests, VecAdd)
    {
        /* Vec += Vec */
        Vec3i a1(1, 2, 3);
        Vec3i b1(3, 3, 4);
        a1 += b1;
        PB_EXPECT_EQL(a1, Vec3i(4, 5, 7));

        /* Vec += Item */
        Vec3i a2(45, 50, 55);
        a2 += 5;
        PB_EXPECT_EQL(a2, Vec3i(50, 55, 60));

        /* Vec = Vec + Vec */
        Vec3i a3(33, 44, 55);
        Vec3i b3(22, 44, 66);
        Vec3i c3 = a3 + b3;
        PB_EXPECT_EQL(c3, Vec3i(55, 88, 121));

        /* Vec = Vec + Item */
        Vec3i a4(24, 46, 68);
        Vec3i b4 = a4 + 2;
        PB_EXPECT_EQL(b4, Vec3i(26, 48, 70));

        /* Vec = Item + Vec */
        Vec3i a5(13, 15, 17);
        Vec3i b5 = 3 + a5;
        PB_EXPECT_EQL(b5, Vec3i(16, 18, 20));
    }

    PB_TEST(PBU_VectorTests, VecSub)
    {
        /* Vec -= Vec */
        Vec3i a1(4, 5, 6);
        Vec3i b1(3, 4, 6);
        a1 -= b1;
        PB_EXPECT_EQL(a1, Vec3i(1, 1, 0));

        /* Vec -= Item */
        Vec3i a2(66, 77, 88);
        a2 -= 11;
        PB_EXPECT_EQL(a2, Vec3i(55, 66, 77));

        /* Vec = Vec - Vec */
        Vec3i a3(35, 40 , 45);
        Vec3i b3(5, 10, 10);
        Vec3i c3 = a3 - b3;
        PB_EXPECT_EQL(c3, Vec3i(30, 30, 35));

        /* Vec = Vec - Item */
        Vec3i a4(44, 45, 46);
        Vec3i b4 = a4 - 12;
        PB_EXPECT_EQL(b4, Vec3i(32, 33, 34));

        /* Vec = Item - Vec */
        Vec3i a5(22, 54, 29);
        Vec3i b5 = 100 - a5;
        PB_EXPECT_EQL(b5, Vec3i(78, 46, 71));
    }

    PB_TEST(PBU_VectorTests, VecMul)
    {
        /* Vec *= Vec */
        Vec3i a1(3, 4, 5);
        Vec3i b1(6, 5, 4);
        a1 *= b1;
        PB_EXPECT_EQL(a1, Vec3i(18, 20, 20));

        /* Vec *= Item */
        Vec3i a2(6, 7, 8);
        a2 *= 3;
        PB_EXPECT_EQL(a2, Vec3i(18, 21, 24));

        /* Vec = Vec * Vec */
        Vec3i a3(8, 9, 10);
        Vec3i b3(11, 12, 10);
        Vec3i c3 = a3 * b3;
        PB_EXPECT_EQL(c3, Vec3i(88, 108, 100));

        /* Vec = Vec * Item */
        Vec3i a4(10, 20, 30);
        Vec3i b4 = a4 * 5;
        PB_EXPECT_EQL(b4, Vec3i(50, 100, 150));

        /* Vec = Item * Vec */
        Vec3i a5(12, 15, 20);
        Vec3i b5 = 5 * a5;
        PB_EXPECT_EQL(b5, Vec3i(60, 75, 100));
    }

    PB_TEST(PBU_VectorTests, VecDiv)
    {
        /* Vec /= Vec */
        Vec3i a1(24, 35, 48);
        Vec3i b1(6, 7, 8);
        Vec3i c1 = a1 / b1;
        PB_EXPECT_EQL(c1, Vec3i(4, 5, 6));

        /* Vec /= Item */
        Vec3i a2(22, 88, 99);
        a2 /= 11;
        PB_EXPECT_EQL(a2, Vec3i(2, 8, 9));

        /* Vec = Vec / Vec */
        Vec3i a3(56, 80, 90);
        Vec3i b3(8, 4, 90);
        Vec3i c3 = a3 / b3;
        PB_EXPECT_EQL(c3, Vec3i(7, 20, 1));

        /* Vec = Vec / Item */
        Vec3i a4(50, 55, 60);
        Vec3i b4 = a4 / 5;
        PB_EXPECT_EQL(b4, Vec3i(10, 11, 12));

        /* Vec = Item / Vec */
        Vec3i a5(2, 3, 4);
        Vec3i b5 = 24 / a5;
        PB_EXPECT_EQL(b5, Vec3i(12, 8, 6));
    }
};
