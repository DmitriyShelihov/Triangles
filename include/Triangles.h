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
			Triangle_sides sides = second.get_triangle_sides();	

			if (!line.valid()) {						//planes are parallel or equal
				if (plane1.equal(plane2)) {

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
			Point inter4 = sides.seg1.intersection_with_line_on_plane(line);
			Point inter5 = sides.seg2.intersection_with_line_on_plane(line);
			Point inter6 = sides.seg3.intersection_with_line_on_plane(line);

			int k = 0;
			Point mas[6];
			
			if (inter1.valid()){mas[k] = inter1; k++;}
			if (inter2.valid()){mas[k] = inter2; k++;}
			if (inter3.valid()){mas[k] = inter3; k++;}
			if (inter4.valid()){mas[k] = inter4; k++;}
			if (inter5.valid()){mas[k] = inter5; k++;}
			if (inter6.valid()){mas[k] = inter6; k++;}
			
			if (!segment1.belongs_to_line(line) && !segment2.belongs_to_line(line) && !segment3.belongs_to_line(line) &&
                !sides.seg1.belongs_to_line(line) && !sides.seg2.belongs_to_line(line) && !sides.seg3.belongs_to_line(line)) {

				if (k == 4) {
					if (!mas[0].equal(mas[1]) && !mas[0].equal(mas[2]) && !mas[0].equal(mas[3])				 
				 	&& !mas[1].equal(mas[2]) && !mas[1].equal(mas[3]) && !mas[2].equal(mas[3]) {		//4 different points of intersection
					
						if ((mas[0].central_point(mas[2], mas[3]) == 0 && mas[1].central_point(mas[2], mas[3]) == 0) ||
					    	(mas[2].central_point(mas[0], mas[1]) == 0 && mas[3].central_point(mas[0], mas[1]) == 0) ||
					    	(mas[0].central_point(mas[2], mas[3]) == 0 && mas[3].central_point(mas[0], mas[1]) == 0) ||
					    	(mas[0].central_point(mas[2], mas[3]) == 0 && mas[2].central_point(mas[0], mas[1]) == 0) ||
					   	 	(mas[1].central_point(mas[2], mas[3]) == 0 && mas[3].central_point(mas[0], mas[1]) == 0) ||
					    	(mas[1].central_point(mas[2], mas[3]) == 0 && mas[2].central_point(mas[0], mas[1]) == 0))
			
							return true;
						return false;
					}
					return true;			//some of points belonged to different triangles are equal
				} else if (k == 3) {
					if (!mas[0].equal(mas[1]) && !mas[1].equal(mas[2]) && !mas[0].equal(mas[2])) {
						if ((mas[0].equal(inter1) && mas[1].equal(inter2)) ||
							(mas[0].equal(inter1) && mas[1].equal(inter3)) ||
							(mas[0].equal(inter2) && mas[1].equal(inter3))) {			//two from 3 points belongs to 1 triangle
							if (mas[2].central_point(mas[0], mas[1]))
								return true;
							return false;
						}
						if (mas[0].central_point(mas[1], mas[2]))
							return true;
						return false;
					}
					return true;
				} else if (k == 2) {
					if (!mas[0].equal(mas[1])) 
						return false;
					return true;
				} else {
					return false;
				}
			} else {			//one side of the triangle belongs to line
				if (segment1.belongs_to_line(line) || segment2.belongs_to_line(line) || segment3.belongs_to_line(line)) {	//=>first triangle
					if (k == 6) {
						if (!mas[0].equal(mas[3]) && !mas[0].equal(mas[4]) && !mas[0].equal(mas[5]) &&
							!mas[1].equal(mas[3]) && !mas[1].equal(mas[4]) && !mas[1].equal(mas[5]) &&
							!mas[2].equal(mas[3]) && !mas[2].equal(mas[4]) && !mas[2].equal(mas[5])) {
							//TODO where we have 4 different points
						}
						
					}
				}
			}


		}
};

