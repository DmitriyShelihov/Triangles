#pragma once 

#include <iostream>
#include <cmath>

#define DBL_EPSILON 2.2204460492503131e-016

int compare_double(double a, double b) {
	if (std::fabs(a-b) <= DBL_EPSILON*std::fabs(std::max(a, b)))
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
        double a() {
			return point2.x-point1.x;
        }
        double b() {
			return point2.y-point1.y;
        }
        double c() {
			return point2.z-point1.z;
        }
        Point start_point() {
			return point1;
        }

        bool is_lines_parallel(Line line_1) {
        	Line line_2(point1, point2);
			double a1 = line_1.a(); double a2 = line_2.a();
			double b1 = line_1.b(); double b2 = line_2.b();
			double c1 = line_1.c(); double c2 = line_2.c();
			
			if (compare_double(a2, 0) == 0 && compare_double(a1, 0) == 0) {
				if (compare_double(b2, 0) == 0 && compare_double(b1, 0) == 0) 
					return 1;
				else if (compare_double(b2, 0) != 0 && compare_double(b1, 0) != 0) {
					if (compare_double(c1, b1*c2/b2) == 0)
						return 1;
					else
						return 0;
				}
				else
					return 0;
			}
			else if (compare_double(a2, 0) != 0 && compare_double(a1, 0) != 0) {
				if (compare_double(b1, b2*a1/a2) == 0 && compare_double(c1, c2*a1/a2) == 0)
					return 1;
				else
					return 0;
			}
			return 0;
  		}
  		double point_distance_to_line(Point point){
            double x_0 = point1.x;
            double y_0 = point1.y;
            double z_0 = point1.z;

            double a = point2.x-point1.x;
            double b = point2.y-point1.y;
 			double c = point2.z-point1.z;

            return std::sqrt((std::pow((y_0-point.y)*c-(z_0-point.z)*b, 2) + 
            	   std::pow(c*(x_0-point.x)-a*(z_0-point.z), 2) + 
            	   std::pow((x_0-point.x)*b-a*(y_0-point.y), 2))/(a*a+b*b+c*c));
     	}	
};

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
			return point3.y * (point2.x-point1.x) + point1.y * (point3.x-point2.x) + point2.y * (point1.x-point3.x);
		}
		
		double D() {
			return point1.x * point2.y * point3.z + point1.y * point3.x * point2.z + point2.x * point3.y * point1.z -
                   point1.y * point2.x * point3.z - point3.y * point1.x * point2.z - point1.z * point2.y * point3.x;
		}

		bool equal(Plane plane) {
			double A = plane.A(), B = plane.B(), C = plane.C(), D = plane.D();
			return (compare_double(A*point1.x + B*point1.y + C*point1.z + D, 0) == 0 &&
				    compare_double(A*point2.x + B*point2.y + C*point2.z + D, 0) == 0 &&
				    compare_double(A*point3.x + B*point3.y + C*point3.z + D, 0) == 0);
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
							point_1.z = -D1/C1;
							point_1.y = -(C2 * point_1.z + D2)/B2;
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
				point_1.x = -(C1*point_1.z+D1)/A1;
			}
			
			if (point_1.valid()) {
				point_2.x = point_1.x + N1;
				point_2.y = point_1.y + N2;
				point_2.z = point_1.z + N3;
			}
			
			Line line (point_1, point_2);
			return line;
		}
	
		
};

class Segment {
	private:
		Point point1;
		Point point2;
	public:
		Segment (Point _point1, Point _point2) 
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
		Point intersection_with_line_on_plane (Line line) {							//Line and segment are considered to be on the same plane
			double a = line.a();
			double b = line.b();
			double c = line.c();
			
			Point point0 = line.start_point();
			Point intersection {};

			double h = line.point_distance_to_line(point1);
				
			Segment segment(point1, point2);

			double l = segment.length();
			
			double A = std::sqrt(a*a+b*b+c*c);

			double cos_alpha = ((point2.x-point1.x)*a + (point2.y-point1.y)*b + (point2.z-point1.z)*c)/(l*A);

			if (compare_double(cos_alpha, 1) == 0 || compare_double(cos_alpha, -1) == 0) {		//segment and line are parallel
				if (line.point_belongs_line(point1))
					return point1;								//segment belongs to line
				else
					return intersection;						//segment and line are parallel and there is no intersection
			}
			double r = h/(std::sqrt(1-cos_alpha*cos_alpha));

			intersection.x = point1.x + (point2.x-point1.x)*r/l;
			intersection.y = point1.y + (point2.y-point1.y)*r/l;
			intersection.z = point1.z + (point2.z-point1.z)*r/l;
			
			if (line.point_belongs_line(intersection))
				return intersection;
			else {
				Point default_p {};
				return default_p;			//segment does not cross the line
			}	
		}
	
};

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
			return side.point_belongs_same_segment_line(point3); 
		}
		Plane plane() {
			Plane plane(point1, point2, point3);
			return plane;
		}
		bool triangle_intersection(Triangle second) {
			Plane plane1(point1, point2, point3);
			Plane plane2 = second.plane();
			Line line = plane1.plane_intersection(plane2);

			if (!line.valid()) {						//planes are parallel or equal
				if (plane1.equal(plane2)) {
														//TODO
				}
				else {
					return false;
				}
			}
			
			Segment segment1(point1, point2);
			Segment segment2(point2, point3);
			Segment segment3(point1, point3);

			Point inter1 = segment1.intersection_with_line_on_plane(line);
			Point inter2 = segment2.intersection_with_line_on_plane(line);
			Point inter3 = segment3.intersection_with_line_on_plane(line);

			return (inter1.valid() || inter2.valid() || inter3.valid());
		}
};

