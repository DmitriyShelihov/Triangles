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
		bool point_belongs(Point point) {
			if (!point.valid())
				return false;
			Segment seg(point1, point2);

			if (!seg.point_belongs_same_segment_line(point))
				return false;
			return ((point1.x <= point.x && point.x <= point2.x &&
					 point1.y <= point.y && point.y <= point2.y &&
				  	 point1.z <= point.z && point.z <= point2.x) ||
			   		(point1.x >= point.x && point.x >= point2.x &&
			         point1.y >= point.y && point.y >= point2.y &&
			         point1.z >= point.z && point.z >= point2.z));
		}
		Point intersection_with_segment_on_plane(Segment seg2) {		//segments are considered to be on the same plane
			Point answer {};
			if (!seg2.valid())
				return answer;

			Line line(point1, point2);
			printf("Line in segment intersection:\n");
			line.print();
			Segment seg1(point1, point2);
			Point point_intersect = seg2.intersection_with_line_on_plane(line);

			if (!point_intersect.valid())
				return answer;
			if (seg2.point_belongs(point_intersect))
				return point_intersect;
			return answer;
		}
		bool belongs_to_line(Line line) {
			if (!line.valid() || !point1.valid() || !point2.valid())
				return false;
			return (line.point_belongs_line(point1) && line.point_belongs_line(point2));
		}
};

