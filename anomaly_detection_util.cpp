/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */

#include <math.h>
#include "anomaly_detection_util.h"
// פונקציה של חישוב ממוצע
float avg(float* x, int size){
    float sum = 0;
    for (int i=0;i<size;i++){
        sum=sum+x[i];
    }
    float Avg = sum/size;

	return Avg;
}

// returns the variance of X and Y
float var(float* x, int size){
    float sigma=x[0];//? לצרף או לשים אפס,אם גודל האוכלוסיה הוא 1 האם המיו הוא 0 או 1
    for(int i =1;i<=size;i++){//לולאה למיו
        sigma =sigma+x[i];// מקווה שזה בסדר,לבדוק את זה אחרי זה ,מבחינת פוינטרים אם זה עושה בעיה
    }
    //אני יכולה
    float mew = (sigma/size);//בין 2 INT התוצואה תיתן 0 כי זה קטן מ 1 לכן היה אפשר להמיר ל FLOAT או לוותר לגמרי על ה ה1
    // אני מבינה שיש דרך ליעול מכתיבת שתי לולאות אבל זה ממש מוזר
    float myVarSum=0;
    for(int i =0;i<size;i++){//סיגמא לVAR
        myVarSum=myVarSum+((x[i]-mew)*(x[i]-mew));

    }
    float Var=myVarSum/size;


	return Var;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float sigmaX=x[0];
    for(int i =1;i<=size;i++){//לולאה למיו
        sigmaX =sigmaX+x[i];
    }
    float MewX =sigmaX/size;

    float sigmaY=y[0];
    for(int i =1;i<=size;i++){//לולאה למיו
        sigmaY =sigmaY+y[i];
    }
    float MewY =sigmaY/size;

    float sigmaXY=sigmaX+sigmaY;
    for(int i =0;i<size;i++){//לולאה למיו
        sigmaXY =sigmaXY+x[i]+y[i];
    }
    float MewXY =sigmaXY/size;
    float COV = MewXY - MewX*MewY;
	return COV;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    float MyCOV =cov(x,y,size);
    float Sig =sqrt(var(x,size));
   float Pearson = MyCOV/Sig;
	return Pearson;
}

// performs a linear regression and returns the line equation
//כמה הערות,מדובר על מערכים ששלחנו ולכן אני שולחת שוב מערך וכל הבלבול שהיה קודם היה מיותר
Line linear_reg(Point** points, int size){

    // יוצרת מערך מאופס
    float myXp[size];
    float myYp[size];
    //יוצרת מערך
    for(int i=0;i<size;i++){
      myXp[i]= points[i]->x;
        myYp[i]= points[i]->y;
    }
    //יוצרת ממוצע
  float avgX= avg(myXp,size);
  float avgY= avg(myYp,size);

    // חישוב של A ושל B לפי הנוסחא
    float a = cov(myXp,myYp,size)/var(myXp,size);
    float b=avgY-a*avgX;
	return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    Line l=linear_reg(points,size);
    

	return 0;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	return 0;
}




