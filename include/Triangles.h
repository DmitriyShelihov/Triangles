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

#include "Point.h"
#include "Line.h"
#include "Plane.h"
#include "Segment.h"

struct Triangle_sides {
	Segment seg1;
	Segment seg2;
	Segment seg3;
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
		Triangle_sides get_triangle_sides() {
			Segment seg1(point1, point2);
			Segment seg2(point2, point3);
			Segment seg3(point1, point3);
			return {seg1, seg2, seg3};
		}
		bool triangle_intersection(Triangle second) {
			Plane plane1(point1, point2, point3);
			Plane plane2 = second.plane();
			Line line = plane1.plane_intersection(plane2);

			Segment segment1(point1, point2);
			Segment segment2(point2, point3);
            Segment segment3(point1, point3);


			if (!line.valid()) {						//planes are parallel or equal
				if (plane1.equal(plane2)) {
					printf("At the equal planes\n");
					Triangle_sides sides = second.get_triangle_sides();
					sides.seg1.print();
					sides.seg2.print();
					sides.seg3.print();
					segment1.print();
					segment2.print();
					segment3.print();
					return ((segment1.intersection_with_segment_on_plane(sides.seg1)).valid() || 
							(segment1.intersection_with_segment_on_plane(sides.seg2)).valid() ||
							(segment1.intersection_with_segment_on_plane(sides.seg3)).valid() ||
							(segment2.intersection_with_segment_on_plane(sides.seg1)).valid() ||
							(segment2.intersection_with_segment_on_plane(sides.seg2)).valid() ||
							(segment2.intersection_with_segment_on_plane(sides.seg3)).valid() || 
							(segment3.intersection_with_segment_on_plane(sides.seg1)).valid() ||
							(segment3.intersection_with_segment_on_plane(sides.seg2)).valid() ||
							(segment3.intersection_with_segment_on_plane(sides.seg3)).valid());
				}
				else {
					return false;
				}
			}
		
			Point inter1 = segment1.intersection_with_line_on_plane(line);
			Point inter2 = segment2.intersection_with_line_on_plane(line);
			Point inter3 = segment3.intersection_with_line_on_plane(line);

			return (inter1.valid() || inter2.valid() || inter3.valid());
		}
};

