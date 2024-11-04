#pragma once

class Point {
	public:
		double x = NAN;
		double y = NAN;
		double z = NAN;
		Point () {}		
		Point (double _x, double _y, double _z) 
			: x(_x), y(_y), z(_z) {}
		void print() {
			std::cout << "{" << x << ", "  << y << ", " << z << "}"; 
		}
		bool valid() {
			return !(std::isnan(x) || std::isnan(y) || std::isnan(z));
		}
		bool equal(Point rhs) {
			if (!rhs.valid() || !(this->valid()))
				return false;
			return (compare_double(x, rhs.x) == 0 && compare_double(y, rhs.y) == 0 && compare_double(z, rhs.z) == 0);
		}
		bool central_point(Point point1, Point point2) {			//3 points considered to be on the same line and different
			Point point(x, y, z);
			if (!point1.valid() || !point2.valid() || !point.valid())
				return false;
			return ((compare_double(std::fabs(x-point2.x), std::fabs(point1.x-point2.x)) == 0 ||
                   compare_double(std::fabs(x-point2.x), std::fabs(point1.x-point2.x)) == 2) &&
                  (compare_double(std::fabs(x-point1.x), std::fabs(point1.x-point2.x)) == 0 ||
                   compare_double(std::fabs(x-point1.x), std::fabs(point1.x-point2.x)) == 2) &&
                  (compare_double(std::fabs(y-point2.y), std::fabs(point1.y-point2.y)) == 0 ||
                   compare_double(std::fabs(y-point2.y), std::fabs(point1.y-point2.y)) == 2) &&
                  (compare_double(std::fabs(y-point1.y), std::fabs(point1.y-point2.y)) == 0 ||
                   compare_double(std::fabs(y-point1.y), std::fabs(point1.y-point2.y)) == 2) &&
                  (compare_double(std::fabs(z-point2.z), std::fabs(point1.z-point2.z)) == 0 ||
                   compare_double(std::fabs(z-point2.z), std::fabs(point1.z-point2.z)) == 2) &&
                  (compare_double(std::fabs(z-point1.z), std::fabs(point1.z-point2.z)) == 0 ||
                   compare_double(std::fabs(z-point1.z), std::fabs(point1.z-point2.z)) == 2));
		}
};
