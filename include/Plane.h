#pragma once

#include "Point.h"
#include "Line.h"

class Plane {
	private:
		Point point1;
		Point point2;
		Point point3;
	public:
		Plane (Point _point1, Point _point2, Point _point3)
			: point1(_point1), point2(_point2), point3(_point3) {}
		Plane (Line line, Point point) {
			point1 = point1;
			point2 = line.start_point();
			point3.x = point2.x + line.a();
			point3.y = point2.y + line.b();
			point3.z = point2.z + line.c();
		}
		bool valid() {
			Line line (point1, point2);
			return point1.valid() && point2.valid() && point3.valid() && line.point_belongs(point3);
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
			return -(point1.x * point2.y * point3.z + point1.y * point3.x * point2.z + point2.x * point3.y * point1.z -
                   point1.y * point2.x * point3.z - point3.y * point1.x * point2.z - point1.z * point2.y * point3.x);
		}
		bool point_belongs(Point p) {
			if (!p.valid())
				return false;
			Plane pl(point1, point2, point3);
			double A = pl.A(); double B = pl.B(); double C = pl.C(); double D = pl.D();
			return (compare_double(A*p.x + B*p.y + C*p.z + D, 0) == 0);
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
        Point intersection_with_line(Line line) {
			Point intersection {};
			
			
			if (!point1.valid() || !point2.valid() || !point3.valid() || !line.valid())
				return intersection;
			double A = (*this).A(); double B = (*this).B(); double C = (*this).C(); double D = (*this).D();
			
			double a = line.a(); double b = line.b(); double c = line.c();
			
			Point point1 = line.start_point();
			if ((*this).point_belongs(point1))
				return point1;
			double mod_vec_l = std::sqrt(a*a + b*b + c*c);
			double mod_vec_p = std::sqrt(A*A + B*B + C*C);

			double cos_alpha = (a*A+b*B+c*C)/(mod_vec_l*mod_vec_p);
			if (compare_double(cos_alpha, 0) == 0)				//line and plane are parallel
				return intersection;
			double h = std::fabs(A*point1.x + B*point1.y + C*point1.z + D)/mod_vec_p;
			double x = h/cos_alpha;
			
			intersection.x = (a*x)/mod_vec_l + point1.x;
			intersection.y = (b*x)/mod_vec_l + point1.y;
			intersection.z = (c*x)/mod_vec_l + point1.z;
			
			if ((*this).point_belongs(intersection))
				return intersection;
			intersection.x = (-a*x)/mod_vec_l + point1.x;
			intersection.y = (-b*x)/mod_vec_l + point1.y;
			intersection.z = (-c*x)/mod_vec_l + point1.z;
			
			return intersection;
     	}        
};
