//// ID1	ID2
//
//#ifndef MINCIRCLE_H_
//#define MINCIRCLE_H_
//#include <vector>
//#include <iostream>
//#include "anomaly_detection_util.h"
//using namespace std;
//
//// ------------ DO NOT CHANGE -----------
//
//class Circle{
//public:
//    Point center;
//    float radius;
//    Circle():center(0,0),radius(0){};
//    Circle(Point c,float r):center(c),radius(r){}
//};
//// --------------------------------------
//
//// implement
//Circle findMinCircle(Point** points,size_t size);
//// is a point inside a circle
//bool inornot(const Circle& bigO, const Point& alpha);
////smallest circle that intersects 2 points and the center by assuming the center is between the points
//Circle dospoint(const Point& ponpon1, const Point& ponpon2);
////find the center of 3 points
//Point circle_center(double bx, double by,double cx, double cy);
////return a unique circle that intersects three points
//Circle trespoint(const Point& ponpon1, const Point& ponpon2, const Point& ponpon3);
////check whether a circle encloses the given points
//bool vaildcircle(const Circle& butt, const vector<Point>& buttP);
////return the euclidean distance
//float distanc(const Point& a, const Point& b);
//
//
//
//
//#endif /* MINCIRCLE_H_ */



#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;

class Circle{
public:
    Point center;
    float radius;
    Circle():center(0,0),radius(0){};
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------


bool inornot(const Circle& bigO, const Point& alpha);

float dist(Point a, Point b);

Circle from2points(Point a,Point b);

Point circumcenter(Point b, Point c);

Circle from3Points(Point a, Point b, Point c);

Circle trivial(vector<Point>& P);

Circle welzl(Point** P,vector<Point> R, size_t n);Circle findMinCircle(Point** points,size_t size);

#endif /* MINCIRCLE_H_ */