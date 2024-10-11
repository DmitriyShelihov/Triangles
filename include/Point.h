#pragma once

class Point {
	public:
		double x = NAN;
		double y = NAN;
		double z = NAN;
		Point () {}		
		Point (double _x, double _y, double _z) 
			: x(_x), y(_y), z(_z) {}
		double radius() {
			return std::sqrt(x*x + y*y + z*z);
		}
		void print() {
			std::cout << "{" << x << ", "  << y << ", " << z << "}"; 
		}
		bool valid() {
			return !(std::isnan(x) || std::isnan(y) || std::isnan(z));
		}
		bool equal(const Point rhs) {
			return (compare_double(x, rhs.x) == 0 && compare_double(y, rhs.y) == 0 && compare_double(z, rhs.z) == 0);
		}
		int central_point(Point p1, Point p2) {			//3 points considered to be on the same line and different
			if (((compare_double(p1.x, x) == 0 || compare_double(p1.x, x) == 2) && (compare_double(x, p2.x) == 0 || compare_double(x, p2.x) == 2) &&
				 (compare_double(p1.y, y) == 0 || compare_double(p1.y, y) == 2) && (compare_double(y, p2.y) == 0 || compare_double(y, p2.y) == 2) &&
				 (compare_double(p1.z, z) == 0 || compare_double(p1.z, z) == 2) && (compare_double(z, p2.z) == 0 || compare_double(z, p2.z) == 2)) ||
				((compare_double(p1.x, x) == 0 || compare_double(p1.x, x) == 1) && (compare_double(x, p2.x) == 0 || compare_double(x, p2.x) == 1) &&
				 (compare_double(p1.y, y) == 0 || compare_double(p1.y, y) == 1) && (compare_double(y, p2.y) == 0 || compare_double(y, p2.y) == 1) &&
	   			 (compare_double(p1.z, z) == 0 || compare_double(p1.z, z) == 1) && (compare_double(z, p2.z) == 0 || compare_double(z, p2.z) == 1))) {			
				return 0;
			}
			if (((compare_double(x, p1.x) == 0 || compare_double(x, p1.x) == 2) && (compare_double(p1.x, p2.x) == 0 || compare_double(p1.x, p2.x) == 2) &&
                  (compare_double(y, p1.y) == 0 || compare_double(y, p1.y) == 2) && (compare_double(p1.y, p2.y) == 0 || compare_double(p1.y, p2.y) == 2) &&
                  (compare_double(z, p1.z) == 0 || compare_double(z, p1.z) == 2) && (compare_double(p1.z, p2.z) == 0 || compare_double(p1.z, p2.z) == 2)) ||
                 ((compare_double(x, p1.x) == 0 || compare_double(x, p1.x) == 1) && (compare_double(p1.x, p2.x) == 0 || compare_double(p1.x, p2.x) == 1) &&
                  (compare_double(y, p1.y) == 0 || compare_double(y, p1.y) == 1) && (compare_double(p1.y, p2.y) == 0 || compare_double(p1.y, p2.y) == 1) &&
                  (compare_double(z, p1.z) == 0 || compare_double(z, p1.z) == 1) && (compare_double(p1.z, p2.z) == 0 || compare_double(p1.z, p2.z) == 1))) {
                 return 1;
          	}
         	return 2;
		}
};
