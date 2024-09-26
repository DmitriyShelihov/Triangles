#pragma once 

int compare_double(double a, double b) {
	if (std::fabs(a-b) < DBL_EPSILON * fmax(fabs(a), fabs(b)))
		return 0;
	if (a > b)
		return 1;
	return 2;
}

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

};

class Segment {
	private:
		Point point1;
		Point point2;
	public:
		Snippet (Point _point1, Point _point2) 
			: point1(_point1), point2(_point2) {}
		double length () {
			return std::sqrt(std::pow(point1.x-point2.x, 2) + std::pow(point1.y-point2.y, 2) + std::pow(point1.z-point2.z, 2));
		}
		
		bool valid() {
			return point1.valid() && point2.valid();
		}
		void print() {
			std::cout << "Segment { ";
			point1.print();
			std::cout << ", ";
			point2.print();
			std::cout << " }";
		}
		bool point_belongs_segment(Point point) {
			return (point.x-point1.x) * (point2.y-point1.y) == (point.y-point1.y) * (point2.x-point1.x) &&
				   (point.y-point1.y) * (point2.z-point1.z) == (point.z-point1.z) * (point2.y-point1.y) &&
				   (point.x-point1.x) * (point2.z-point1.z) == (point.z-point1.z) * (point2.x-point1.x) &&
				   std::fabs(point.x-point2.x) <= std::fabs(point1.x-point2.x) && 
				   std::fabs(point.x-point1.x) <= std::fabs(point1.x-point2.x) &&
				   std::fabs(point.y-point2.y) <= std::fabs(point1.y-point2.y) &&
				   std::fabs(point.y-point1.y) <= std::fabs(point1.y-point2.y) &&
				   std::fabs(point.z-point2.z) <= std::fabs(point1.z-point2.z) &&
				   std::fabs(point.z-point1.z) <= std::fabs(point1.z-point2.z);
		}
		bool point_belongs_same_segment_line(Point point) {
			return (point.x-point1.x) * (point2.y-point1.y) == (point.y-point1.y) * (point2.x-point1.x) &&
                   (point.y-point1.y) * (point2.z-point1.z) == (point.z-point1.z) * (point2.y-point1.y) &&
                   (point.x-point1.x) * (point2.z-point1.z) == (point.z-point1.z) * (point2.x-point1.x);
		}
	
}

class Triangle {	
	private: 
		Point point1;
		Point point2;
		Point point3;
	public:
		Triangle (Point _point1, Point _point2, Point _point3) 
			: point1(_point1), point2(_point2), point3(_point3) {}
		bool valid() {
			return point1.valid() && point2.valid() && point3.valid() && !point1.equal(point2) && !point1.equal(point3) && !point3.equal(point2);
		}
		void print() {
			std::cout << "Triangle { ";
			point1.print();
			std::cout << ", ";
			point2.print();
			std::cout << ", ";
			point3.print();
			std::cout << " }";
		}
		bool degenerate_triangle() {
			Segment side (point1, point2);
			return side.point_belongs_same_segment_line(Point point3); 
		}
}

class Line {
	private:
		Point point1;
		Point point2;
	public:
		Line (Point _point1, Point _point2) 
			: point1(_point1), point2(_point2) {}
		bool valid() {
			return point1.valid() && point2.valid() && !point1.equal(point2);
		}
		void print() {
			std::cout << "Line { ";
			point1.print();
			std::cout << ", ";
			point2.print();
			std::cout << " }";
		}
		bool point_belongs_line(Point point) {
        	return (point.x-point1.x) * (point2.y-point1.y) == (point.y-point1.y) * (point2.x-point1.x) &&
                   (point.y-point1.y) * (point2.z-point1.z) == (point.z-point1.z) * (point2.y-point1.y) &&
                   (point.x-point1.x) * (point2.z-point1.z) == (point.z-point1.z) * (point2.x-point1.x);
        }

}

class Plane {
	private:
		Point point1;
		Point point2;
		Point point3;
	public:
		Plane (Point _point1, Point _point2, Point _point3)
			: point1(_point1), point2(_point2), point3(_point3) {}
		bool valid() {
			Line line (point1, point2);
			return point1.valid() && point2.valid() && point3.valid() && line.point_belongs_line(point3);
		}
		void print() {
         	std::cout << "Plane { ";
          	point1.print();
          	std::cout << ", ";
          	point2.print();
          	std::cout << ", ";
          	point3.print();
          	std::cout << " }";
		}
		
		double A() {
			return point3.z * (point2.y-point1.y) + point1.z * (point3.y-point2.y) + point2.z * (point1.y-point3.y);
		}

		double B() {
			return point3.z * (point1.x-point2.x) + point1.z * (point2.x-point3.x) + point2.z * (point3.x-point1.x);
		}

		double C() {
			return (point3.y * (point2.x-point1.x) + point1.y * (point3.x-point2.x) + point2.y * (point1.x-point3.x);
		}
		
		double D() {
			return point1.x * point2.y * point3.z + point1.y * point3.x * point2.z + point2.x * point3.y * point1.z -
                   point1.y * point2.x * point3.z - point3.y * point1.x * point2.z - point1.z * point2.y * point3.x;
		}

		Line plane_intersection(Plane plane2) {
			Plane plane1 (point1, point2, point3);
			double A1 = plane1.A(); double A2 = plane2.A();
			double B1 = plane1.B(); double B2 = plane2.B();
			double C1 = plane1.C(); double C2 = plane2.C();
			double D1 = plane1.D(); double D2 = plane2.D();
			Point point_1 {};
			Point point_2 {};
			
			double N1 = B1 * C2 - C1 * B2;				//line direction vector
			double N2 = C1 * A2 - A1 * C2;				
			double N3 = A1 * B2 - B1 * A2;

			if (compare_double(A1, 0) == 0) {
				if (compare_double(A2, 0) == 0) {
					if (compare_double(B1, 0) == 0) {
						if (compare_double(B2, 0) != 0) {		//planes are not parallel
							point_1.z = -D2/C2;
							point_1.y = -(C1 * point_1.z + D1)/B1;
							point_1.x = 0;
						}
					}
					else if (compare_double(B1*C2, B2 * C1) != 0) {
						point_1.x = 0;
						point_1.y = (D2*C1-D1*C2)/(B1*C2-B2*C1);
						point_1.z = (D1*B2-B1*D2)/(B1*C2-B2*C1);
					}	
				}
				else {
					if (compare_double(B1, 0) == 0) {
						point_1.z = -D1/C1;
						point_1.y = 0;
						point_1.x = -(C2*point_1.z + D2)/A2;
					}
					else {
						point_1.z = 0;
						point_1.y = -D1/B1;
						point_1.x = -(B2*point_1.y + D2)/A2;
					}
				}
			}
			else if (compare_double(B2*A1-B1*A2, 0) != 0){
				point_1.z = 0;
				point_1.y = (D1*A2-D2*A1)/(B2*A1-B1*A2);
				point_1.x = -(B1*point_1.y+D1)/A1;
			}
			else if (compare_double(A1*C2-C1*A2, 0) != 0) {
				point_1.z = (D1*A2-D2*A1)/(A1*C2-C1*A2);
				point_1.y = 0;
				point_1.x = -(C1*z+D1)/A1;
			}
			
			if (point_1.valid()) {
				point_2.x = point_1.x + N1;
				point_2.y = point_1.y + N2;
				point_2.z = point_1.z + N3;
			}
			
			Line line (point_1, point_2);
			return line;
		}
	
		
}
