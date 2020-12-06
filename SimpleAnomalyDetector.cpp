
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){

    vector<vector<float>>mytablevector=ts.getthetable();
    vector<string>myfeaturename=ts.getfeaturs();
    int sizeofcolom=mytablevector[1].size();//כמה עמודות יש
    int matthatcheckcorelation[sizeofcolom][2];
    for (int j = 0;j<sizeofcolom;j++){//לולאה על זה שאנחנו בודקים
        float theFirst [mytablevector.size()];// המערך שאליו בודקים הראשון
        float theOthers [mytablevector.size()];// המערך שבודקים אליו
            for (int m =0 ;m<mytablevector.size();m++){//יצירת המערך
                theFirst[m]=mytablevector[m][j];
            }
        float mypers=0;
        int myMostcorFeaturi=0;
        int i=(j+1);
       while(i<sizeofcolom){// בודקת בלולאה הזו על כל השאר ולא צריך לבדוק אחורה,מקווה שזה לא יעשה שגיאה של יציאה מגבולות
            for (int k = 0; k < mytablevector.size(); k++) {    // זה יוצר את המערך השני
                theOthers[k]=mytablevector[k][i];   //   k זה המיקום בשורה
            }
            if (mypers<abs(pearson(theFirst,theOthers,sizeofcolom))){
                mypers=abs(pearson(theFirst,theOthers,sizeofcolom));// בערך מוחלט
                if(mypers>0.9){
                    cf.push_back(correlatedFeatures());
                    cf[j].corrlation = mypers;
                    cf[j].feature1=
                    myMostcorFeaturi=i;

                }

            }

            i++;
        }
//       matthatcheckcorelation[j][0]=j;
//       matthatcheckcorelation[j][1]=myMostcorFeaturi;



}





	// TODO Auto-generated destructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub

}

