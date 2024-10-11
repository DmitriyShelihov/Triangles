#pragma once

#include "Point.h"

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
