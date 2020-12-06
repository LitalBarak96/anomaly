
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    float mypers=0;
    int myMostcorFeatur=0;
    vector<vector<float>>mytablevector=ts.getthetable();
    int sizeofcolom=mytablevector[1].size();//כמה עמודות יש
    for (int j = 0;j<sizeofcolom;j++){//לולאה על זה שאנחנו בודקים
        float theFirst [mytablevector.size()];// המערך שאליו בודקים הראשון
        float theOthers [mytablevector.size()];// המערך שבודקים אליו
        std::copy(mytablevector.at(j).begin(), mytablevector.at(j).end(), theFirst);//העתקה של הוקטור לתוך המערך
        for (int i=j+1;i<sizeofcolom;i++ ){// בודקת בלולאה הזו על כל השאר ולא צריך לבדוק אחורה,מקווה שזה לא יעשה שגיאה של יציאה מגבולות
            std::copy(mytablevector.at(i).begin(), mytablevector.at(i).end(), theOthers);
            if (mypers<abs(pearson(theFirst,theOthers,sizeofcolom))){
                mypers=abs(pearson(theFirst,theOthers,sizeofcolom));// בערך מוחלט
                myMostcorFeatur=i;  //   אני מחזיקה את הערך
            }


        }


}





	// TODO Auto-generated destructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub

}

