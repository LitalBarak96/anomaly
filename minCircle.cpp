//#include <iostream>
//#include <vector>
//#include <stdlib.h>
//#include <time.h>
//#include <math.h>
//#include "minCircle.h"
//
//vector<Point> vecR;
//float distanc(const Point& pointa, const Point& pointb){
//    return sqrt(pow(pointa.x - pointb.x, 2)
//                + pow(pointa.y - pointb.y, 2));
//
//}

//
//}
//Point circle_center(float bx, float by,float cx, float cy){
//    float first = bx * bx + by * by;
//    float sec = cx * cx + cy * cy;
//    float third = bx * cy - by * cx;
//    return { static_cast<float>(((cy * first - by * sec) / (2 * third))),
//             static_cast<float>((bx * sec - cx * first) / (2 * third)) };
//}
//
//Circle trespoint(const Point& ponpon1, const Point& ponpon2, const Point& ponpon3){
//    Point I = circle_center(ponpon2.x - ponpon1.x, ponpon2.y - ponpon1.y,
//                                ponpon3.x - ponpon1.x, ponpon3.y - ponpon1.y);
//
//    I.x += ponpon1.x;
//    I.y += ponpon1.y;
//    return { I, (distanc(I, ponpon1)) };
//}
//Circle dospoint(const Point& ponpon1, const Point& ponpon2){
//    Point C = { static_cast<float>((ponpon1.x + ponpon2.x) / 2.0), static_cast<float>((ponpon1.y + ponpon2.y) / 2.0) };
//
//    // Set the radius to be half the distance AB
//    return { C, static_cast<float>(distanc(ponpon1, ponpon2) / 2.0) };
//}
//bool vaildcircle(const Circle& butt, const vector<Point>& buttP){
//    for (const Point& p : buttP)
//        if (!inornot(butt, p))
//            return false;
//    return true;
//}
//
//
//Circle findMinCircle(Point** points,size_t size){
//    vector<Point> vecpoints;
//    Point temp(0,0);
//    for( int i = 0; i < size; i++){
//        temp = *points[i];
//        vecpoints.push_back(temp);
//    }
//// from point vector from given points
//    if (size == 0 || vecR.size() == 3) {
//        if (vecR.size() == 0)
//            return Circle(Point(0,0), 0);
//        if (vecR.size() == 1)
//            return Circle(vecR.at(0), 0);
//        if (vecR.size() == 2)
//            return dospoint(vecR.at(0), vecR.at(1));
//        for (int j = 0; j < 3; j++){
//            for(int k = j + 1; k < 3; k++){
//                Circle round = dospoint(vecR.at(j),vecR.at(k));
//                if (vaildcircle(round,vecR))
//                    return round;
//
//
//            }
//        }
// return trespoint(vecR.at(0), vecR.at(1), vecR.at(2));
//    }
//
//// אחרי שעשינו את מה שהיה צריך לעשותת צריך לרוקן אותו כי הגענו לקצה,לא בטוחה איפה להכניס את זה אבל חשוב שזה יקרה
//
//        // ברגע שעשינו פה return  זה מוחק את השורות הבאות
//    int randomi = rand() % size;
//    Point outpoint = vecpoints.at(randomi);
//    swap(vecpoints.at(randomi), vecpoints.at(size - 1));
//    Point** p =new Point*[size -1];
//    for (int m = 0; m < size -1; m++)
//    {
//        p[m] = new Point(vecpoints.at(m));
//    }
//    Circle again = findMinCircle(p, size -1 );
//    if(inornot(again, outpoint)) {
//        return again;
//    }
//    vecR.push_back(outpoint);
//    return findMinCircle(p, size -1 );
//}



//#ifndef MINCIRCLE_H_
//#define MINCIRCLE_H_
//
//#include <iostream>
//#include <vector>
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
//#include <math.h>
//#include "minCircle.h"
//#include "anomaly_detection_util.h"
//
//using namespace std;
//
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
//float dist(Point a, Point b){
//    float x2=(a.x-b.x)*(a.x-b.x);
//    float y2=(a.y-b.y)*(a.y-b.y);
//    return sqrt(x2+y2);
//}
//
//Circle from2points(Point a,Point b){
//    float x=(a.x+b.x)/2;
//    float y=(a.y+b.y)/2;
//    float r=dist(a,b)/2;
//    return Circle(Point(x,y),r);
//}
//
//
//
//Circle from3Points(Point a, Point b, Point c){
//    // find the circumcenter of the triangle a,b,c
//    // find the circumcenter of the triangle a,b,c
//
//    Point mAB((a.x+b.x)/2 , (a.y+b.y)/2); // mid point of line AB
//    float slopAB = (b.y - a.y) / (b.x - a.x); // the slop of AB
//    float pSlopAB = - 1/slopAB; // the perpendicular slop of AB
//    // pSlop equation is:
//    // y - mAB.y = pSlopAB * (x - mAB.x) ==> y = pSlopAB * (x - mAB.x) + mAB.y
//
//    Point mBC((b.x+c.x)/2 , (b.y+c.y)/2); // mid point of line BC
//    float slopBC = (c.y - b.y) / (c.x - b.x); // the slop of BC
//    float pSlopBC = - 1/slopBC; // the perpendicular slop of BC
//    // pSlop equation is:
//    // y - mBC.y = pSlopBC * (x - mBC.x) ==> y = pSlopBC * (x - mBC.x) + mBC.y
//
//    /*
//    pSlopAB * (x - mAB.x) + mAB.y = pSlopBC * (x - mBC.x) + mBC.y
//    pSlopAB*x - pSlopAB*mAB.x + mAB.y = pSlopBC*x - pSlopBC*mBC.x + mBC.y
//
//    x*(pSlopAB - pSlopBC) = - pSlopBC*mBC.x + mBC.y + pSlopAB*mAB.x - mAB.y
//    x = (- pSlopBC*mBC.x + mBC.y + pSlopAB*mAB.x - mAB.y) / (pSlopAB - pSlopBC);
//
//    */
//
//    float x = (- pSlopBC*mBC.x + mBC.y + pSlopAB*mAB.x - mAB.y) / (pSlopAB - pSlopBC);
//    float y = pSlopAB * (x - mAB.x) + mAB.y;
//    Point center(x,y);
//    float R=dist(center,a);
//
//    return Circle(center,R);
//}
//
//Circle trivial(vector<Point>& P){
//    if(P.size()==0)
//        return Circle(Point(0,0),0);
//    else if(P.size()==1)
//        return Circle(P[0],0);
//    else if (P.size()==2)
//        return from2points(P[0],P[1]);
//
//    // maybe 2 of the points define a small circle that contains the 3ed point
//    Circle c=from2points(P[0],P[1]);
//    if(dist(P[2],c.center)<=c.radius)
//        return c;
//    c=from2points(P[0],P[2]);
//    if(dist(P[1],c.center)<=c.radius)
//        return c;
//    c=from2points(P[1],P[2]);
//    if(dist(P[0],c.center)<=c.radius)
//        return c;
//    // else find the unique circle from 3 points
//    return from3Points(P[0],P[1],P[2]);
//}
//
//
///*
//algorithm welzl
//    input: Finite sets P and R of points in the plane |R|<= 3.
//    output: Minimal disk enclosing P with R on the boundary.
//
//    if P is empty or |R| = 3 then
//        return trivial(R)
//    choose p in P (randomly and uniformly)
//    D := welzl(P - { p }, R)
//    if p is in D then
//        return D
//
//    return welzl(P - { p }, R U { p })
// */
//
//
//Circle welzl(Point** P,vector<Point> R, size_t n){
//    if(n==0 || R.size()==3){
//        return trivial(R);
//    }
//
//    // remove random point p
//    // swap is more efficient than remove
//    //srand (time(NULL));
//    int i=rand()%n;
//    Point p(P[i]->x,P[i]->y);
//    swap(P[i],P[n-1]);
//
//    Circle c=welzl(P,R,n-1);
//
//    if(dist(p,c.center)<=c.radius)
//        return c;
//
//    R.push_back(p);
//
//    return welzl(P,R,n-1);
//}
//
//Circle findMinCircle(Point** points,size_t size){
//    return welzl(points,{},size);
//}
//

//#endif /* MINCIRCLE_H_ */
//


#include "minCircle.h"
#include <iostream>
#include "minCircle.h"
#include <algorithm>
#include <assert.h>
#include <vector>
#include <cmath>
#include <stdlib.h>

using namespace std;


//Calculates the distance between two points
float distance(const Point &a, const Point &b) {
    return sqrt(pow(a.x - b.x, 2)
                + pow(a.y - b.y, 2));
}
//Checks if the point is inside the circle
bool if_point_in_sphere(const Circle &c, const Point &p) {
    return distance(c.center, p) <= c.radius;
}
//Creates a vector of points
vector<Point> creating_vector_of_points(Point **points, size_t size) {
    vector<Point> pts;
    for (int i = 0; i < size; ++i) {
        pts.push_back(*points[i]);
    }
    return pts;
}
//Calculate the center of a circle for three points
Point center_of_Circle_from_3_Points(vector<Point> v) {
    Point p1 = v[0];
    Point p2 = v[1];
    Point p3 = v[2];
    float m_a = (p2.y - p1.y) / (p2.x - p1.x);
    float m_b = (p3.y - p2.y) / (p3.x - p2.x);
    float x1 = (m_a * m_b) * (p1.y - p3.y);
    float x2 = m_b * (p1.x + p2.x);
    float x3 = m_a * (p2.x + p3.x);
    float x = (x1 + x2 - x3) / (2 * (m_b - m_a));
    float y1 = (-1 / m_a) * (x - ((p1.x + p2.x) / 2));
    float y2 = (p1.y + p2.y) / 2;
    float y = y1 + y2;
    Point p(x, y);
    return p;
}
//A function that returns the center of the circle and its radius in a trivial case
Circle trivial(const vector<Point> v, int size) {
    Point p (0,0);
    Circle c(p,0);
    switch (size) {
        case 0: {
            Point p(0, 0);
            Circle c(p, 0);
            return c;
        }
        case 1: {
            Circle c(v[0], 0);
            return c;
        }
        case 2: {
            float x = (v[0].x + v[1].x) / 2;
            float y = (v[0].y + v[1].y) / 2;
            Point p(x, y);
            float radius = distance(v[0], v[1]) / 2;
            Circle c(p, radius);
            return c;
        }
        case 3: {
            Point p = center_of_Circle_from_3_Points(v);
            float r = distance(p, v[0]);
            Circle c(p, r);
            return c;
        }
        default:
            cout << "trivial is only for less than 3 points" << endl;
    }
}

bool inornot(const Circle& circle, const Point& point){
    return distance(circle.center,point)<=circle.radius;
}
//Welzl's algorithm
Circle welzl( vector<Point> &pts, size_t size, vector<Point> r) {
    if (size<=0 || r.size() == 3) {
        return trivial(r,r.size());
    }
    int i = rand() % size;
    Point p = pts[i];
    swap(pts[i], pts[size - 1]);

    Circle d = welzl(pts, size-1, r);
    if (if_point_in_sphere(d, p)) {
        return d;
    }
    r.push_back(p);
    return welzl(pts, size - 1, r);
}
//Returns the minimum circle that contains all the points
Circle findMinCircle(Point **points, size_t size) {
    vector<Point> r;
    vector<Point> pts;
    pts = creating_vector_of_points(points, size);
    Circle final_circle = welzl(pts, size, r);
    return final_circle;
}
