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

#include "Segment.h"

int main() {
	Point p1(0,6,0);
	Point p2(7,0,0);
	Point p3(2,1,0);
	Point p4(1,2,0);
	Point p5(1,1,0);
	Point p6(0,0,0);
		
	Segment seg1(p1, p2);
	Segment seg2(p1, p6);
	Segment seg3(p2, p6);
	Segment segment1(p3, p4);
	Segment segment2(p4, p5);
	Segment segment3(p3, p5);
    seg2.intersection_with_segment_on_plane(segment3).print();
    printf("\n");
    Point point_x(0, 1, 0);
    std::cout << segment3.point_belongs(point_x);
	
}
