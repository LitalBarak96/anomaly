#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "minCircle.h"

vector<Point> vecR;
float distanc(const Point& pointa, const Point& pointb){
    return sqrt(pow(pointa.x - pointb.x, 2)
                + pow(pointa.y - pointb.y, 2));

}
bool inornot(const Circle& circle, const Point& point){
    return distanc(circle.center,point)<=circle.radius;

}
Point circle_center(float bx, float by,float cx, float cy){
    float first = bx * bx + by * by;
    float sec = cx * cx + cy * cy;
    float third = bx * cy - by * cx;
    return { static_cast<float>(((cy * first - by * sec) / (2 * third))),
             static_cast<float>((bx * sec - cx * first) / (2 * third)) };
}

Circle trespoint(const Point& ponpon1, const Point& ponpon2, const Point& ponpon3){
    Point I = circle_center(ponpon2.x - ponpon1.x, ponpon2.y - ponpon1.y,
                                ponpon3.x - ponpon1.x, ponpon3.y - ponpon1.y);

    I.x += ponpon1.x;
    I.y += ponpon1.y;
    return { I, (distanc(I, ponpon1)) };
}
Circle dospoint(const Point& ponpon1, const Point& ponpon2){
    Point C = { static_cast<float>((ponpon1.x + ponpon2.x) / 2.0), static_cast<float>((ponpon1.y + ponpon2.y) / 2.0) };

    // Set the radius to be half the distance AB
    return { C, static_cast<float>(distanc(ponpon1, ponpon2) / 2.0) };
}
bool vaildcircle(const Circle& butt, const vector<Point>& buttP){
    for (const Point& p : buttP)
        if (!inornot(butt, p))
            return false;
    return true;
}


Circle findMinCircle(Point** points,size_t size){
    vector<Point> vecpoints;
    Point temp(0,0);
    for( int i = 0; i < size; i++){
        temp = *points[i];
        vecpoints.push_back(temp);
    }
// from point vector from given points
    if (size == 0 || vecR.size() == 3) {
        if (vecR.size() == 0)
            return Circle(Point(0,0), 0);
        if (vecR.size() == 1)
            return Circle(vecR.at(0), 0);
        if (vecR.size() == 2)
            return dospoint(vecR.at(0), vecR.at(1));
        for (int j = 0; j < 3; j++){
            for(int k = j + 1; k < 3; k++){
                Circle round = dospoint(vecR.at(j),vecR.at(k));
                if (vaildcircle(round,vecR))
                    return round;


            }
        }
 return trespoint(vecR.at(0), vecR.at(1), vecR.at(2));
    }
    
// אחרי שעשינו את מה שהיה צריך לעשותת צריך לרוקן אותו כי הגענו לקצה,לא בטוחה איפה להכניס את זה אבל חשוב שזה יקרה
    
        // ברגע שעשינו פה return  זה מוחק את השורות הבאות
    int randomi = rand() % size;
    Point outpoint = vecpoints.at(randomi);
    swap(vecpoints.at(randomi), vecpoints.at(size - 1));
    Point** p =new Point*[size -1];
    for (int m = 0; m < size -1; m++)
    {
        p[m] = new Point(vecpoints.at(m));
    }
    Circle again = findMinCircle(p, size -1 );
    if(inornot(again, outpoint)) {
        return again;
    }
    vecR.push_back(outpoint);
    return findMinCircle(p, size -1 );
}