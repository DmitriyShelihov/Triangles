#include <gtest/gtest.h>
#include "Triangles.h"

::testing::AssertionResult DOUBLE_EQ(double d1, double d2)
{
  	if (compare_double(d1, d2) == 0)
      	return ::testing::AssertionSuccess();
    else
      	return ::testing::AssertionFailure(); 
}

class PointValidTest: public ::testing::Test {
	public:
		bool ans1_ref = 1;
		bool ans2_ref = 0;
	protected:
		bool ans1;
		bool ans2;
	void SetUp() {
		Point p1(1, 2, 3);
		Point p2{};
		
		ans1 = p1.valid();
		ans2 = p2.valid();
	}
};

TEST_F(PointValidTest, test1) {
	ASSERT_EQ(ans1, ans1_ref);
	ASSERT_EQ(ans2, ans2_ref);
}

class PointEqualTest: public ::testing::Test {
	public:
		bool ans1_ref = 1;
		bool ans2_ref = 0;
	protected:
		bool ans1;
		bool ans2;
	void SetUp() {
		Point p1(1, 2, 3);
		Point p2(1.0000000000000000123, 2.0000000000000000000213, 3.0000000000000000000214);
		Point p3{};
		ans1 = p1.equal(p2);
		ans2 = p1.equal(p3);
	}
};

TEST_F(PointEqualTest, test2) {
	ASSERT_EQ(ans1, ans1_ref);
	ASSERT_EQ(ans2, ans2_ref);
}

class PointCentral_pointTest: public ::testing::Test {
	public:
		bool ans1_ref;
		bool ans2_ref;
	protected:
		bool ans1;
		bool ans2;
	
	void SetUp() {
		Point p1(1, 3, 3);
		Point p2(2, 2, 4);
		Point p3(1.5, 2.5, 3.9);

		p3.central_point(p1, p2);
		p1.central_point(p2, p3);
	}
};

TEST_F(PointCentral_pointTest, test3) {
	ASSERT_EQ(ans1, ans1_ref);
	ASSERT_EQ(ans2, ans2_ref);
}

class LineValidTest: public ::testing::Test {
	public: 
		bool ref_ans1 = 1;
		bool ref_ans2 = 0;
	protected: 
		bool ans1;
		bool ans2;
	
	void SetUp() {
		Point p1(1, 4, 3);
		Point p2(1, 1, 3);
		Line line1(p1, p2);
		
		Point p3{};
		Line line2(p1, p3);
		
		ans1 = line1.valid();
		ans2 = line2.valid();
	}
};

TEST_F(LineValidTest, test4) {
	ASSERT_EQ(ans1, ref_ans1);
	ASSERT_EQ(ans2, ref_ans2);
}

class LinePoint_belongsTest: public ::testing::Test {
	public:
		bool ref_ans1 = 1;
		bool ref_ans2 = 0;
	protected:
		bool ans1;
		bool ans2; 
	void SetUp() {
		Point p1(1, 1, 1);
		Point p2(2, 2, 2);
		Line line(p1, p2);
		
		Point p3(3, 3, 3);
		Point p4(-1, 1, 1);
		
		ans1 = line.point_belongs(p3);
		ans2 = line.point_belongs(p4);
	}
};

TEST_F(LinePoint_belongsTest, test5) {
	ASSERT_EQ(ans1, ref_ans1);
	ASSERT_EQ(ans2, ref_ans2);
}

class Line_A_B_C_Test: public ::testing::Test {
	public:
		double a_ref = 5;
		double b_ref = 3;
		double c_ref = -1;
	protected:
		double a;
		double b;
		double c;
	void SetUp() {
		Point p1(1, 1, 1);
		Point p2(6, 4, 0);
		Line line(p1, p2);

		a = line.a();
		b = line.b();
		c = line.c();
	}
};

TEST_F(Line_A_B_C_Test, test6) {
	EXPECT_TRUE(DOUBLE_EQ(a, a_ref));
	EXPECT_TRUE(DOUBLE_EQ(b, b_ref));
	EXPECT_TRUE(DOUBLE_EQ(c, c_ref));
}

::testing::AssertionResult POINTS_EQ(Point p1, Point p2)
{
	if (p1.equal(p2))
		return ::testing::AssertionSuccess();
	else
		return ::testing::AssertionFailure();
}

class LineStart_pointTest : public ::testing::Test {
	public:
		Point p_ref = {100, 100, 100};
	protected:
		Point p;

	void SetUp() {
		Point p1(100, 100, 100);
		Point p2(200, 200, 0);
		Line line(p1, p2);
		
		p = line.start_point();
	}
};

TEST_F(LineStart_pointTest, test7) {
	EXPECT_TRUE(POINTS_EQ(p_ref, p));
}

class LineIs_lines_parallelTest : public ::testing::Test {
	public:
		bool ans1_ref = 1;
		bool ans2_ref = 0;
		bool ans3_ref = 0;
	protected:
		bool ans1;
		bool ans2;
		bool ans3;

	void SetUp() {
		Point p1(1, 1, 1);
		Point p2(2, 2, 2);

		Point p3(0, 2, 1);
		Point p4(1, 3, 2);

		Line l1(p1, p2);
		Line l2(p3, p4);
		Line l3(p1, p3);
	
		ans1 = l1.is_lines_parallel(l2);
		ans2 = l2.is_lines_parallel(l3);
		ans3 = l1.is_lines_parallel(l3);
	}
};

TEST_F(LineIs_lines_parallelTest, test8) {
	ASSERT_EQ(ans1, ans1_ref);
	ASSERT_EQ(ans2, ans2_ref);
	ASSERT_EQ(ans3, ans3_ref);
}

class LinePoint_distance_to_lineTest : public ::testing::Test {
	public: 
		double h_ref = 326.4077145670543;	
	protected:
		double h;
	void SetUp() {
		Point p(435.2, 34.5, -2738.4);
		Point p1(1.123, 1.235, -24.5);
		Point p2(0, 0, 0);
		
		Line l(p1, p2);
		h = l.point_distance_to_line(p);
	}
};

TEST_F(LinePoint_distance_to_lineTest, test9) {
	EXPECT_TRUE(DOUBLE_EQ(h, h_ref));
}

class PlaneValidTest : public ::testing::Test {
	public: 
		bool ans1_ref = 0;
		bool ans2_ref = 0;
		bool ans3_ref = 1;
	protected:
		bool ans1;
		bool ans2;
		bool ans3;
	
	void SetUp() {
		Point p1{};
		Point p2(1, 1, 1);
		Point p3(2, 2, 2);
		Point p4(3, 3, 3);
		Point p5(1, 2, 3);

		Plane plane1(p1, p2, p3);
		Plane plane2(p2, p3, p4);
		Plane plane3(p2, p3, p5);
		
		ans1 = plane1.valid(); 
		ans2 = plane2.valid();
		ans3 = plane3.valid();
	}
};

TEST_F(PlaneValidTest, test10) {
	ASSERT_EQ(ans1, ans1_ref);
	ASSERT_EQ(ans2, ans2_ref);
	ASSERT_EQ(ans3, ans3_ref);
}

class Plane_A_B_C_D_Test : public ::testing::Test {
	public:
		double A_ref = -27.04640417720;
		double B_ref = 16.625852160;
		double C_ref = 19.749747320;
		double D_ref = -122.84044432984;
	protected:
		double A;
		double B;
		double C;
		double D;

	void SetUp() {
		Point p1(1.13, 3.14, 5.124);
		Point p2(1.45, 0.1444, 8.084);
		Point p3(7.1847, 8.1784, 9.174187);
		
		Plane p(p1, p2, p3);
		A = p.A(); B = p.B(); C = p.C(); D = p.D();
	}
};

TEST_F(Plane_A_B_C_D_Test, test11) {
	EXPECT_TRUE(DOUBLE_EQ(A, A_ref));
	EXPECT_TRUE(DOUBLE_EQ(B, B_ref));
	EXPECT_TRUE(DOUBLE_EQ(C, C_ref));
	EXPECT_TRUE(DOUBLE_EQ(D, D_ref));
} 

class PlanePoint_belongsTest : public ::testing::Test {
	public:
		bool ans1_ref = 1;	
		bool ans2_ref = 0;
	protected:
		bool ans1;
		bool ans2;
	
	void SetUp() {
		Point p1(0, 0, 0);	
		Point p2(1, 1, 1);
		Point p3(1, 0, 0);
		Plane p(p1, p2, p3);

		Point p4(2, 2, 2);
		ans1 = p.point_belongs(p4);
		Point p5(100, 100, 101);
		ans2 = p.point_belongs(p5);
	}
};

TEST_F(PlanePoint_belongsTest, test12) {
	ASSERT_EQ(ans1, ans1_ref);
	ASSERT_EQ(ans2, ans2_ref);
}

class PlaneEqualTest : public ::testing::Test {
	public:
		bool ans1_ref = 1;
		bool ans2_ref = 0;
	protected:
		bool ans1;
		bool ans2;
	void SetUp() {
		Point p1(0, 0, 0);
		Point p2(1, 1, 1);
		Point p3(1, 0, 0);
		Plane plane1(p1, p2, p3);

		Point p4(2, 2, 2);
		Point p5(2, 0, 0);
		Point p6(3, 3, 3);
		Plane plane2(p4, p5, p6);

		Point p7(-1, -1, -1);
		Point p8(1, 1, 1);
		Point p9(100, 100, 101);
		Plane plane3(p7, p8, p9);
		
		ans1 = plane1.equal(plane2);
		ans2 = plane2.equal(plane3);
	}
};

TEST_F(PlaneEqualTest, test13) {
	ASSERT_EQ(ans1, ans1_ref);
	ASSERT_EQ(ans2, ans2_ref);
}

class PlaneIntersectionTest : public ::testing::Test {
    public:
        Point p1_ref = {0, 0, 0};
        Point p2_ref = {3, 3, 0};
    protected:
    	Point p1_ans;
    	Point p2_ans;
    void SetUp() {
        Point p1(0, 0, 0);
        Point p2(1, 1, 1);
        Point p3(1, 1, 0);
        Point p4(0, 0, 0);
        Point p5(1, 1, 0);
        Point p6(2, 5, 0);

        Plane plane1(p1, p2, p3);
        Plane plane2(p4, p5, p6);

        Line line_ans = plane1.plane_intersection(plane2);
        
        p1_ans = line_ans.start_point();
        p2_ans = {p1_ans.x + line_ans.a(), p1_ans.y + line_ans.b(), p1_ans.z + line_ans.c()};
    }
};
 
TEST_F(PlaneIntersectionTest, test14) {
	EXPECT_TRUE(POINTS_EQ(p1_ref, p1_ans));
	EXPECT_TRUE(POINTS_EQ(p2_ref, p2_ans));
}

class PlaneIntersection_with_lineTest : public ::testing::Test {
	public:
		Point p_ref = {0.5, 0.5, 0};
	protected:
		Point p_ans;
	void SetUp() {
		Point p1(0, 0, 0);
		Point p2(1, 1, 1);
		Point p3(1, 1, 0);

		Point p4(1, 0, 0);
		Point p5(0, 1, 0);

		Plane p(p1, p2, p3);
		Line l(p4, p5);
		p_ans = p.intersection_with_line(l);
	}
};

TEST_F(PlaneIntersection_with_lineTest, test15) {
	EXPECT_TRUE(POINTS_EQ(p_ref, p_ans));
}

class TriangleValidTest : public ::testing::Test {
	public:
		bool ans1_ref = 1;
		bool ans2_ref = 0;
	protected:
		bool ans1;
		bool ans2;
	void SetUp() {
		Point p1(0, 0, 0);
		Point p2(1, 0, 0);
		Point p3(0, 1, 0);
		Point p4{};
		
		Triangle T1(p1, p2, p3);
		Triangle T2(p2, p3, p4);
		ans1 = T1.valid();
		ans2 = T2.valid();
	}
};

TEST_F(TriangleValidTest, test16) {
	ASSERT_EQ(ans1, ans1_ref);
	ASSERT_EQ(ans2, ans2_ref);
}

class TriangleDegenTest : public ::testing::Test {
	public:
		bool ans1_ref = 1;
		bool ans2_ref = 0;
	protected:
		bool ans1;
		bool ans2;
	void SetUp() {
		Point p1(0, 0, 0);
		Point p2(1, 1, 1);
		Point p3(2, 2, 2);
		Point p4(1, 2, 3);

		Triangle T1(p1, p2, p3);
		Triangle T2(p2, p3, p4);
		ans1 = T1.degen();
		ans2 = T2.degen();
	}
};

TEST_F(TriangleDegenTest, test17) {
	ASSERT_EQ(ans1_ref, ans1);
	ASSERT_EQ(ans2_ref, ans2);
}

class TriangleIs_pointTest : public ::testing::Test {
	public:
		bool ans1_ref = 1;
		bool ans2_ref = 0;
	protected:
		bool ans1;
		bool ans2;
	void SetUp() {
		Point p1(0, 0, 0);
		Point p2(0, 0, 0.0000000000000000009);
		Point p3(0.000000000000000000000009, 0, 0);
		Point p4(1, 1, 1);

		Triangle T1(p1, p2, p3);
		Triangle T2(p2, p3, p4);
		ans1 = T1.is_point();
		ans2 = T2.is_point();
	}
};

TEST_F(TriangleIs_pointTest, test18) {
	ASSERT_EQ(ans1_ref, ans1);
	ASSERT_EQ(ans2_ref, ans2);
}

class TrianglePoint_insideTest : public ::testing::Test {
	public:
		bool ans1_ref = 1;
		bool ans2_ref = 0;
	protected:
		bool ans1;
		bool ans2;
	void SetUp() {
		Point p1(0, 0, 0);
		Point p2(2, 0, 0);
		Point p3(0, 2, 0);
		Point p4(1, 1, 0);
		Point p5(2, 2, 0);

		Triangle T(p1, p2, p3);
		ans1 = T.point_inside(p4);
		ans2 = T.point_inside(p5);
	}
};
 
TEST_F(TrianglePoint_insideTest, test19) {
    ASSERT_EQ(ans1_ref, ans1);
    ASSERT_EQ(ans2_ref, ans2);
}

class TrianglePoint_belongsTest : public ::testing::Test {
	public:
		bool ans1_ref = 1;
		bool ans2_ref = 0;
	protected:
		bool ans1;
		bool ans2;
	void SetUp() {
		Point p1(0, 0, 0);
		Point p2(0, 2, 0);
		Point p3(2, 0, 0);        
		Point p4(0.5, 0.0000000000000009, 0);
		Point p5(1.00001, 1.000001, 0);

		Triangle T(p1, p2, p3);
        ans1 = T.point_belongs(p4);
        ans2 = T.point_belongs(p5);
	}
};

TEST_F(TrianglePoint_belongsTest, test20) {
	ASSERT_EQ(ans1_ref, ans1);
	ASSERT_EQ(ans2_ref, ans2);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}


