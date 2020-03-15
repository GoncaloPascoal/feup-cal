/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
	double minDistance = MAX_DOUBLE;
	Point p1, p2;

	for (size_t i = 0; i < vp.size(); ++i) {
	    for (size_t j = i + 1; j < vp.size(); ++j) {
	        double distance = vp.at(i).distance(vp.at(j));

	        if (distance < minDistance) {
	            minDistance = distance;
	            p1 = vp.at(i);
	            p2 = vp.at(j);
	        }
	    }
	}

	return Result(minDistance, p1, p2);
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	double minDistance = MAX_DOUBLE;
	Point p1, p2;

	sortByX(vp, 0, vp.size() - 1);

	double distance;

    for (size_t i = 0; i < vp.size(); ++i) {
        for (size_t j = i + 1; j < vp.size(); ++j) {
            if (abs(vp.at(i).x - vp.at(j).x) > minDistance) {
                break;
            } else if ((distance = vp.at(i).distance(vp.at(j))) < minDistance) {
                minDistance = distance;
                p1 = vp.at(i);
                p2 = vp.at(j);
            }
        }
    }

	return Result(minDistance, p1, p2);
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res) {
    double dist;

	for (int i = left; i <= right; ++i) {
	    for (int j = i + 1; j <= right; ++j) {
	        if (abs(vp.at(i).y - vp.at(j).y) > res.dmin) {
	            break;
	        }
	        else if ((dist = vp.at(i).distance(vp.at(j))) < res.dmin) {
	            res.dmin = dist;
	            res.p1 = vp.at(i);
	            res.p2 = vp.at(j);
	        }
	    }
	}
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
	// Base case of two points
	if (right - left == 1) {
	    return Result(vp.at(left).distance(vp.at(right)), vp.at(left), vp.at(left));
	}

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	if (left == right) {
	    return Result();
	}

	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	int leftEnd = left + (right - left) / 2, rightBegin = left + (right - left) / 2 + 1;

	Result leftRes = np_DC(vp, left, leftEnd, numThreads);
	Result rightRes = np_DC(vp, rightBegin, right, numThreads);

	// Select the best solution from left and right
	Result res = leftRes.dmin < rightRes.dmin ? leftRes : rightRes;

	// Determine the strip area around middle point
	double stripX = (vp.at(leftEnd).x + vp.at(rightBegin).x) / 2;
	int stripLeft = left, stripRight = right;

	for (int i = leftEnd; i >= left; --i) {
	    if (abs(stripX - vp.at(i).x) > res.dmin) {
	        stripLeft = i - 1;
            break;
	    }
	}

    for (int i = rightBegin; i <= right; ++i) {
        if (abs(stripX - vp.at(i).x) > res.dmin) {
            stripRight = i - 1;
            break;
        }
    }

	// Order points in strip area by Y coordinate
	sortByY(vp, stripLeft, stripRight);

	// Calculate nearest points in strip area (using npByY function)
	npByY(vp, stripLeft, stripRight, res);

	// Reorder points in strip area back by X coordinate
	sortByX(vp, stripLeft, stripRight);

	return res;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num) {
	numThreads = num;
}

/**
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() - 1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/**
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() - 1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
