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
	Point p1(0,0,0);
	Point p2(1,0,0);
	Point p3(0,0,0);
	Point p4(0,1,0);
	
	Segment seg1(p1, p2);
	Segment seg2(p3, p4);
	
	Point res = seg1.intersection_with_segment_on_plane(seg2);
	res.print();
}
