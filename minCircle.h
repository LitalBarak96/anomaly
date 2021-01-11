//#ifndef MINCIRCLE_H_
//#define MINCIRCLE_H_
//
//#include <iostream>
//#include <vector>
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
//#include "anomaly_detection_util.h"
//
//using namespace std;
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
//
//bool inornot(const Circle& bigO, const Point& alpha);
//
//float distance(Point a, Point b);
//
//Circle from2points(Point a,Point b);
//
//Point circumcenter(Point b, Point c);
//
//Circle from3Points(Point a, Point b, Point c);
//
//Circle trivial(vector<Point>& P);
//
//Circle welzl(Point** P,vector<Point> R, size_t n);Circle findMinCircle(Point** points,size_t size);
//
//#endif /* MINCIRCLE_H_ */


//#ifndef MINCIRCLE_H_
//#define MINCIRCLE_H_
//
//#include <iostream>
//#include <vector>
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
//#include "anomaly_detection_util.h"
//
//using namespace std;
//
//
//
//
//
//class Circle{
//public:
//    Point center;
//    float radius;
//    Circle(Point c,float r):center(c),radius(r){}
//};
//// --------------------------------------
//
//
//bool inornot(const Circle& bigO, const Point& alpha);
//
//float dist(Point a, Point b);
//
//Circle from2points(Point a,Point b);
//
//Point circumcenter(Point b, Point c);
//
//Circle from3Points(Point a, Point b, Point c);
//
//Circle trivial(vector<Point>& P);
//
//Circle welzl(Point** P,vector<Point> R, size_t n);Circle findMinCircle(Point** points,size_t size);
//
//#endif /* MINCIRCLE_H_ */
//





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
	Circle(Point c,float r):center(c),radius(r){}
    Circle():center(0,0),radius(0){}
};



bool inornot(const Circle& bigO, const Point& alpha);

float distance(const Point &a, const Point &b);

bool if_point_in_sphere(const Circle &c, const Point &p);

vector<Point> creating_vector_of_points(Point **points, size_t size);

Point center_of_Circle_from_3_Points(vector<Point> v);

Circle trivial(const vector<Point> v, int size);

Circle welzl( vector<Point> &pts, size_t size, vector<Point> r);

Circle findMinCircle(Point **points, size_t size);


#endif /* MINCIRCLE_H_ */