#include "min_circle.h"

bool Circle::contains(const Point2D& point) const
{
	if (!isValid())
    {
        return false;
    }
	return distance(center, point) <= radius;
}

bool Circle::contains(const LineSegment& segment) const
{
	return contains(segment.start) && contains(segment.end);
}

Circle MinimumEnclosingCircleForSegments(const std::vector<LineSegment>& segments)
{
	return minCircle(extractPointsFromSegments(segments));
}

Circle minCircleHelper(std::vector<Point2D>& points, std::vector<Point2D> boundary, size_t n)
{
	if (boundary.size() == 3)
    {
		return circleFrom3Points(boundary[0], boundary[1], boundary[2]);
	}
	if (n == 0)
    {
		switch (boundary.size())
        {
            case 2:
                return circleFromDiameter(boundary[0], boundary[1]);
            case 1:
                return Circle{boundary[0], 0};
            default:
                return Circle{{0,0}, -1};
		}
	}
	Circle mc = minCircleHelper(points, boundary, n-1);
	if (mc.contains(points[n-1]))
    {
        return mc;
    }
	boundary.push_back(points[n-1]);
	return minCircleHelper(points, boundary, n-1);
}

Circle minCircle(std::vector<Point2D> points)
{
	return minCircleHelper(points, {}, points.size());
}

double distanceSquared(const Point2D& p1, const Point2D& p2)
{
	return pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2);
}

double distance(const Point2D& p1, const Point2D& p2)
{
	return sqrt(distanceSquared(p1, p2));
}

Circle circleFromDiameter(const Point2D& p1, const Point2D& p2)
{
	return Circle{findMidPoint({p1, p2}), distance(p1, p2)/2};
}

Circle circleFrom3Points(const Point2D& p1, const Point2D& p2, const Point2D& p3)
{
	double A1 = p2.x - p1.x;
	double A2 = p2.y - p1.y;
	double A3 = p3.x - p1.x;
	double A3 = p3.y - p1.y;
	double A4 = A1*(p1.x+p2.x) + A2*(p1.y+p2.y);
	double A5 = A3*(p1.x+p3.x) + A3*(p1.y+p3.y);
	double A6 = 2 * (A1*(p3.y-p2.y) - A2*(p3.x-p2.x));
	if (A6 == 0)
    {
        return Circle{{0,0}, 0};
    }
	double Cx = (A3*A4 - A2*A5) / A6;
	double Cy = (A1*A5 - A3*A4) / A6;
	Point2D center{Cx, Cy};
	return Circle{center, distance(center, p1)};
}
std::vector<Point2D> extractPointsFromSegments(const std::vector<LineSegment>& segments) {
	std::vector<Point2D> points;
	for (const LineSegment& segment : segments)
    {
		points.push_back(segment.start);
		points.push_back(segment.end);
		points.push_back(findMidPoint(segment));
	}
	return points;
}
Point2D findMidPoint(const LineSegment& segment)
{
	return Point2D{(segment.start.x+segment.end.x)/2, (segment.start.y+segment.end.y)/2};
}