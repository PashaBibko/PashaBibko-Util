#include <Util.h>

PB_TEST_GROUP(PBU_VectorTests);

namespace PashaBibko::Util::CodeTests
{
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
};
