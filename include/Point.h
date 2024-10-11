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
			if ((p1.x <= x && x <= p2.x &&
				 p1.y <= y && y <= p2.y &&
				 p1.z <= z && z <= p2.z) ||
				(p1.x >= x && x >= p2.x &&
                 p1.y >= y && y >= p2.y &&
                 p1.z >= z && z >= p2.z))
			
				return 0;
			if ((x <= p1.x && p1.x <= p2.x &&
                 y <= p1.y && p1.y <= p2.y &&
                 z <= p1.z && p1.z <= p2.z) ||
                (x >= p1.x && p1.x >= p2.x &&
                 y >= p1.y && p1.y >= p2.y &&
                 z >= p1.z && p1.z >= p2.z))
                 
                 return 1;
         	return 2;
		}
};
