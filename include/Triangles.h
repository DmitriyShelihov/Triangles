#pragma once 
#include <iostream>
#include <cmath>

const long double eps = 1e-10;

int compare_double(const double a, const double b) {
	if (std::fabs(a-b) < eps)
		return 0;
	if (a-b > eps)
		return 1;
	return 2;
}

#include "Point.h"
#include "Line.h"
#include "Plane.h"
#include "Segment.h"

struct Triangle_vert {
	Point p1;
	Point p2;
	Point p3;
};

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
		Triangle () {}
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
		bool degen() {
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
		Triangle_vert get_triangle_vert() {
			return {point1, point2, point3};
		}
		bool is_point() {					//is Triangle a point
			return (point1.equal(point2) && point1.equal(point3));
		}
		bool point_inside(Point point) {			//point and triangle on the same plane
			Line line1(point1, point);
			Line line2(point2, point);
			Line line3(point3, point);
			
			Segment seg1(point2, point3);
			Segment seg2(point1, point3);
			Segment seg3(point1, point2);

			Point p1 = seg1.intersection_with_line_on_plane(line1);
			Point p2 = seg2.intersection_with_line_on_plane(line2);
			Point p3 = seg3.intersection_with_line_on_plane(line3);

			if ((p1.valid() && point.central_point(point1, p1)) ||
				(p2.valid() && point.central_point(point2, p2)) ||
				(p3.valid() && point.central_point(point3, p3))) {
				return true;
			}
			return false;
		}
		bool point_belongs(Point p) {
			Triangle T(point1, point2, point3);
			Triangle_sides sides = T.get_triangle_sides();
			Plane pl = T.plane();
			if (!pl.point_belongs(p))
				return false;
			return (sides.seg1.point_belongs(p) || sides.seg2.point_belongs(p) || sides.seg3.point_belongs(p) || T.point_inside(p));
		}

		bool triangle_intersection(Triangle second) {
			Triangle first(point1, point2, point3);
			if (!second.degen() && first.degen()) {
				Plane plane = second.plane();
				if (first.is_point()) {
					return second.point_belongs(point1);
				}
				if (point1.central_point(point2, point3)) {
					Segment seg(point2, point3);
					Line line(point2, point3);
					Point intersection = plane.intersection_with_line(line);
					return seg.point_belongs(intersection);
				}
				if (point2.central_point(point1, point3)) {
                	Segment seg(point1, point3);
                    Line line(point1, point3);
                    Point intersection = plane.intersection_with_line(line);
                    return seg.point_belongs(intersection);
				}
                Segment seg(point1, point2);
                Line line(point1, point2);
                Point intersection = plane.intersection_with_line(line);
                return seg.point_belongs(intersection); 
			} else if (second.degen() && !first.degen()) {
				Triangle_vert vert = second.get_triangle_vert();
				Point point4 = vert.p1; Point point5 = vert.p2; Point point6 = vert.p3;

				Plane plane = first.plane();
                if (second.is_point()) {
                	return first.point_belongs(point4);
                }
                if (point4.central_point(point5, point6)) {
                    Segment seg(point5, point6);
                    Line line(point5, point6);
                    Point intersection = plane.intersection_with_line(line);
                    return seg.point_belongs(intersection);
                }
                if (point5.central_point(point4, point6)) {
                    Segment seg(point4, point6);
                    Line line(point4, point6);
                    Point intersection = plane.intersection_with_line(line);
                    return seg.point_belongs(intersection);
                }
                Segment seg(point4, point5);
                Line line(point4, point5);
                Point intersection = plane.intersection_with_line(line);
                return seg.point_belongs(intersection);
			} else if (second.degen() && first.degen()) {
				Triangle_vert vert = second.get_triangle_vert();
				Point point4 = vert.p1; Point point5 = vert.p2; Point point6 = vert.p3;
				
				if (!first.is_point() && !second.is_point()) {	
					Segment seg1 = get_largest_segment(point1, point2, point3);
					Segment seg2 = get_largest_segment(point4, point5, point6);
					if (!point1.equal(point2))
						Line line(point1, point2);
					else if (!point1.equal(point3))
						Line line(point1, point3);
					else if (!point2.equal(point3))
						Line line(point2, point3);
					//TODO
				}
				//TODO
			}
			
			Plane plane1(point1, point2, point3);
			Plane plane2 = second.plane();
			Line line = plane1.plane_intersection(plane2);
			
			//debug
			printf("The line of intersection two triangle planes:");
			line.print();
			printf("\n");
			//debug_end

			Segment segment1(point1, point2);
			Segment segment2(point2, point3);
            Segment segment3(point1, point3);
			Triangle_sides sides = second.get_triangle_sides();
			Triangle_vert vertexies = second.get_triangle_vert();
			Point point4 = vertexies.p1;
			Point point5 = vertexies.p2;
			Point point6 = vertexies.p3;
			
			if (!line.valid()) {//planes are parallel or equal
			
				if (plane1.equal(plane2)) {				//equal
					if ((segment1.intersection_with_segment_on_plane(sides.seg1)).valid() || 
						(segment1.intersection_with_segment_on_plane(sides.seg2)).valid() ||
						(segment1.intersection_with_segment_on_plane(sides.seg3)).valid() ||
						(segment2.intersection_with_segment_on_plane(sides.seg1)).valid() ||
						(segment2.intersection_with_segment_on_plane(sides.seg2)).valid() ||
						(segment2.intersection_with_segment_on_plane(sides.seg3)).valid() || 
						(segment3.intersection_with_segment_on_plane(sides.seg1)).valid() ||
						(segment3.intersection_with_segment_on_plane(sides.seg2)).valid() ||
						(segment3.intersection_with_segment_on_plane(sides.seg3)).valid()) {
							return true;
					} 
					if (second.point_inside(point1) && second.point_inside(point2) && second.point_inside(point3)) {
						return true;
					}
					return false;
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
			
			if (line.point_belongs_line(point1) && !line.point_belongs_line(point2) && !line.point_belongs_line(point3)) {
 				k++;
 				mas[0] = point1;
 				if (inter2.valid()){
					k++;
					mas[1] = inter2;
 				}
            } else if (line.point_belongs_line(point2) && !line.point_belongs_line(point1) && !line.point_belongs_line(point3)) {
				k++;
				mas[0] = point2;
				if (inter3.valid()) {
					k++;
					mas[1] = inter3;
				}
            } else if (line.point_belongs_line(point3) && !line.point_belongs_line(point1) && !line.point_belongs_line(point2)) {
				k++;
				mas[0] = point3;
				if (inter1.valid()) {
					k++;
					mas[1] = inter1;
				}
			} else {
				if (inter1.valid()){mas[k] = inter1; k++;}
             	if (inter2.valid()){mas[k] = inter2; k++;}
             	if (inter3.valid()){mas[k] = inter3; k++;}
			}
			
			if (line.point_belongs_line(point4) && !line.point_belongs_line(point5) && !line.point_belongs_line(point6)) {
                 mas[k] = point4;
                 k++;
                 if (inter5.valid()){
                     mas[k] = inter5;
                     k++;
                 }
             } else if (line.point_belongs_line(point5) && !line.point_belongs_line(point4) && !line.point_belongs_line(point6)) {
                 mas[k] = point5;
                 k++;
                 if (inter6.valid()) {
                     mas[k] = inter6;
                     k++;
                 }
             } else if (line.point_belongs_line(point6) && !line.point_belongs_line(point4) && !line.point_belongs_line(point5)) {
                 mas[k] = point6;
                 k++;
                 if (inter4.valid()) {
                     mas[k] = inter4;
                     k++;
                 }
             } else {
                 if (inter4.valid()){mas[k] = inter4; k++;}
                 if (inter5.valid()){mas[k] = inter5; k++;}
                 if (inter6.valid()){mas[k] = inter6; k++;}
             }
			
			//debug
			printf("k = %d\nPoints are:", k);
			for (int i = 0; i < k; i++)
				mas[i].print();
			printf("\n");
			//debug end

			if (!segment1.belongs_to_line(line) && !segment2.belongs_to_line(line) && !segment3.belongs_to_line(line) &&
                !sides.seg1.belongs_to_line(line) && !sides.seg2.belongs_to_line(line) && !sides.seg3.belongs_to_line(line)) {
				if (k == 4) {
					if (!mas[0].equal(mas[1]) && !mas[0].equal(mas[2]) && !mas[0].equal(mas[3])				 
				 	&& !mas[1].equal(mas[2]) && !mas[1].equal(mas[3]) && !mas[2].equal(mas[3])) {		//4 different points of intersection
						//debug

						printf("Segment doesnt belong line, k = 4, point are not equal\n");
						//debug end
						if ((mas[0].central_point(mas[2], mas[3]) && mas[1].central_point(mas[2], mas[3])) ||
					    	(mas[2].central_point(mas[0], mas[1]) && mas[3].central_point(mas[0], mas[1])) ||
					    	(mas[0].central_point(mas[2], mas[3]) && mas[3].central_point(mas[0], mas[1])) ||
					    	(mas[0].central_point(mas[2], mas[3]) && mas[2].central_point(mas[0], mas[1])) ||
					   	 	(mas[1].central_point(mas[2], mas[3]) && mas[3].central_point(mas[0], mas[1])) ||
					    	(mas[1].central_point(mas[2], mas[3]) && mas[2].central_point(mas[0], mas[1])))
							return true;
						return false;
					}
					return true;													//some of points belonged to different triangles are equal
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
							Point new_mas[4];
							if (mas[0].equal(mas[1])){
								new_mas[0] = mas[0];
								new_mas[1] = mas[2];
							} else {
								new_mas[0] = mas[0];
								new_mas[1] = mas[1];
							}
							if (mas[3].equal(mas[4])){
                                new_mas[2] = mas[3];
                                new_mas[3] = mas[5];
                            } else {
                                new_mas[2] = mas[3];
                                new_mas[3] = mas[4];
                            }
                            if (new_mas[0].central_point(new_mas[2], new_mas[3]) || new_mas[1].central_point(new_mas[2], new_mas[3]) || 
                               (new_mas[2].central_point(new_mas[0], new_mas[1]) && new_mas[3].central_point(new_mas[0], new_mas[1])) ||
                               (new_mas[0].central_point(new_mas[2], new_mas[3]) && new_mas[1].central_point(new_mas[2], new_mas[3]))) {
								return true;
                            }
                            return false;
						}
						return true;
					} else if (k == 5) {
						if (!mas[0].equal(mas[3]) && !mas[0].equal(mas[4]) && 
                        	!mas[1].equal(mas[3]) && !mas[1].equal(mas[4]) && 
                            !mas[2].equal(mas[3]) && !mas[2].equal(mas[4])) {
								
							Point new_mas[4];

							if (mas[0].equal(mas[1])){
                            	new_mas[0] = mas[0];
                                new_mas[1] = mas[2];
                            } else {
                                new_mas[0] = mas[0];
                                new_mas[1] = mas[1];
                            }
							new_mas[2] = mas[3];
							new_mas[3] = mas[4];
							
							if (new_mas[0].central_point(new_mas[2], new_mas[3]) || new_mas[1].central_point(new_mas[2], new_mas[3]) || 
                            	(new_mas[2].central_point(new_mas[0], new_mas[1]) && new_mas[3].central_point(new_mas[0], new_mas[1])) ||
                                (new_mas[0].central_point(new_mas[2], new_mas[3]) && new_mas[1].central_point(new_mas[2], new_mas[3]))) {
                                return true;
                          	}
                          	return false;
						}
						return true;
					} else if (k == 4) {
						if (!mas[0].equal(mas[3]) && !mas[1].equal(mas[3]) && !mas[2].equal(mas[3])){
							Point new_mas[3];
                            if (mas[0].equal(mas[1])){
                            	new_mas[0] = mas[0];
                                new_mas[1] = mas[2];
                            } else {
                                new_mas[0] = mas[0];
                                new_mas[1] = mas[1];
                            }
                            new_mas[2] = mas[3];
                            if (new_mas[2].central_point(new_mas[0], new_mas[1]))
                            	return true;
                            return false;
						}
						return true;
					} else {
						return false;
					}
				}
			 else {		//side of second triangle is on the line
				if (k == 5) {
					if (!mas[2].equal(mas[0]) && !mas[2].equal(mas[1]) && 
                        !mas[3].equal(mas[0]) && !mas[3].equal(mas[1]) && 
                        !mas[4].equal(mas[0]) && !mas[4].equal(mas[1])) {
							
						Point new_mas[4];
						if (mas[2].equal(mas[3])){
                            new_mas[2] = mas[2];
                            new_mas[3] = mas[4];
                        } else {
                            new_mas[2] = mas[2];
                            new_mas[3] = mas[3];
                        }
						new_mas[0] = mas[0];
						new_mas[1] = mas[1];
							
						if (new_mas[0].central_point(new_mas[2], new_mas[3]) || new_mas[1].central_point(new_mas[2], new_mas[3]) || 
                           (new_mas[2].central_point(new_mas[0], new_mas[1]) && new_mas[3].central_point(new_mas[0], new_mas[1])) ||
                           (new_mas[0].central_point(new_mas[2], new_mas[3]) && new_mas[1].central_point(new_mas[2], new_mas[3]))) {
                           return true;
                        }
                        return false;
					}
					return true;
				} else if (k == 4) {
						if (!mas[1].equal(mas[0]) && !mas[2].equal(mas[0]) && !mas[3].equal(mas[0])){
							Point new_mas[3];
                            if (mas[1].equal(mas[2])){
                            	new_mas[1] = mas[1];
                                new_mas[2] = mas[3];
                            } else {
                                new_mas[1] = mas[1];
                                new_mas[2] = mas[2];
                            }
                            new_mas[0] = mas[0];
                            if (new_mas[0].central_point(new_mas[1], new_mas[2]))
                            	return true;
                            return false;
						}
						return true;
					} else {
						return false;
					}
				}
			}
		}
};

