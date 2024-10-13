#pragma once

#include "Point.h"
#include "Line.h"

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
			return point1.valid() && point2.valid() && !point1.equal(point2);
		}
		void print() {
			std::cout << "Segment { ";
			point1.print();
			std::cout << ", ";
			point2.print();
			std::cout << " }";
		}
		bool point_belongs(Point point) {
			if (!point1.valid() || !point2.valid() || !point.valid())
				return false;
			return compare_double((point.x-point1.x) * (point2.y-point1.y), (point.y-point1.y) * (point2.x-point1.x)) == 0 &&
				   compare_double((point.y-point1.y) * (point2.z-point1.z), (point.z-point1.z) * (point2.y-point1.y)) == 0 &&
				   compare_double((point.x-point1.x) * (point2.z-point1.z), (point.z-point1.z) * (point2.x-point1.x)) == 0 &&
				   point.central_point(point1, point2);
		}
		bool point_belongs_same_segment_line(Point point) {
			if (!point1.valid() || !point2.valid() || !point.valid())
				return false;
			return compare_double((point.x-point1.x) * (point2.y-point1.y), (point.y-point1.y) * (point2.x-point1.x)) == 0 &&
                   compare_double((point.y-point1.y) * (point2.z-point1.z), (point.z-point1.z) * (point2.y-point1.y)) == 0 &&
                   compare_double((point.x-point1.x) * (point2.z-point1.z), (point.z-point1.z) * (point2.x-point1.x)) == 0;
		}
		Point intersection_with_line_on_plane (Line line) {							//Line and segment are considered to be on the same plane
			Point intersection {};
			if (!line.valid() || !point1.valid() || !point2.valid())
				return intersection;

			double a = line.a();
			double b = line.b();
			double c = line.c();
			
			Point point0 = line.start_point();

			double h = line.point_distance_to_line(point1);
			
			Segment segment(point1, point2);

			double l = segment.length();
			
			double A = std::sqrt(a*a+b*b+c*c);

			double cos_alpha = ((point2.x-point1.x)*a + (point2.y-point1.y)*b + (point2.z-point1.z)*c)/(l*A);

			if (compare_double(cos_alpha, 1) == 0 || compare_double(cos_alpha, -1) == 0) {		//segment and line are parallel
				if (line.point_belongs(point1))
					return point1;								//segment belongs to line
				else
					return intersection;						//segment and line are parallel and there is no intersection
			}
			double r = h/(std::sqrt(1-cos_alpha*cos_alpha));

			intersection.x = point1.x + (point2.x-point1.x)*r/l;
			intersection.y = point1.y + (point2.y-point1.y)*r/l;
			intersection.z = point1.z + (point2.z-point1.z)*r/l;
			
			if (line.point_belongs(intersection) && segment.point_belongs(intersection))
				return intersection;
			intersection.x = point1.x - (point2.x-point1.x)*r/l;
            intersection.y = point1.y - (point2.y-point1.y)*r/l;
            intersection.z = point1.z - (point2.z-point1.z)*r/l;
			
			if (line.point_belongs(intersection) && segment.point_belongs(intersection))
				return intersection;

			Point default_p {};
			return default_p;			//segment does not cross the line	
		}
		Point intersection_with_segment_on_plane(Segment seg2) {		//segments are considered to be on the same plane
			Point answer {};
			Segment seg1(point1, point2);
			if (!seg2.valid() || !seg1.valid())
				return answer;

			Line line(point1, point2);
			
			Point point_intersect = seg2.intersection_with_line_on_plane(line);

			if (!point_intersect.valid())
				return answer;
			if (seg1.point_belongs(point_intersect))
				return point_intersect;
			return answer;
		}
		bool belongs_to_line(Line line) {
			if (!line.valid() || !point1.valid() || !point2.valid())
				return false;
			return (line.point_belongs(point1) && line.point_belongs(point2));
		}
		bool belongs_one_plane(Line line) {
			Segment seg(point1, point2);
			if (!line.valid() || !seg.valid())
				return false;
			Plane p (line, point1);
			if (p.valid()) {
				return p.point_belongs(point2);
			}			//=> point1 belongs line
			return true;
		}
};

Segment get_largest_segment(Point p1, Point p2, Point p3) {
	if (p1.central_point(p2, p3)) {
		Segment seg(p2, p3);
		return seg;
	}
	if (p2.central_point(p1, p3)) {
		Segment seg(p1, p3);
		return seg;
	}
	Segment seg(p1, p2);
	return seg;
	
}

