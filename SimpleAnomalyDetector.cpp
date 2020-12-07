
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    vector<vector<float>>mytablevector=ts.getthetable();
    int sizeoftable=int(mytablevector.size());
    vector<string>myfeaturename=ts.getfeaturs();
    int sizeofcolom=mytablevector[1].size()-1;//כמה עמודות יש
    int matthatcheckcorelation[sizeofcolom][2];
    for (int j = 0;j<sizeofcolom;j++){//לולאה על זה שאנחנו בודקים
        float theFirst [sizeoftable];// המערך שאליו בודקים הראשון
        float theOthers [sizeoftable];// המערך שבודקים אליו
            for (int m =0 ;m<sizeoftable;m++){//יצירת המערך
                theFirst[m]=mytablevector[m][j];
            }
        float mypers=0;
        int myMostcorFeaturi=0;
        int i=(j+1);
       while(i<sizeofcolom){// בודקת בלולאה הזו על כל השאר ולא צריך לבדוק אחורה,מקווה שזה לא יעשה שגיאה של יציאה מגבולות
            for (int k = 0; k < sizeoftable; k++) {    // זה יוצר את המערך השני
                theOthers[k]=mytablevector[k][i];   //   k זה המיקום בשורה
            }
            if (mypers<abs(pearson(theFirst,theOthers,sizeofcolom))){
                mypers=abs(pearson(theFirst,theOthers,sizeofcolom));// בערך מוחלט
                myMostcorFeaturi=i;
            }

            i++;
        }
        if(mypers>0.9){
            Point** arrayofPointformaxi = new Point*[sizeoftable];
            for (int k = 0; k < sizeoftable; k++) {
               // I ו J הם הטורים שלי,להבנתי ג'יי זה איקס ו איי זה וואי אני מסתכלת על פי השורה הנוכחית והטור שמצאתי שהם מקסימלים
                arrayofPointformaxi[k]=new Point(mytablevector[k][j],mytablevector[k][myMostcorFeaturi]);
            }
            Line myLine = linear_reg(arrayofPointformaxi,sizeoftable);
            float myMaxdev=0;// אנחנו רוצים למצוא זה שיתן לנו מקסימלי
            for (int k = 0; k < sizeoftable; k++) {
                if (myMaxdev<dev(*arrayofPointformaxi[k],myLine)) {
                    myMaxdev = dev(*arrayofPointformaxi[k], myLine);// אני רוצה את הערך שנמצא במיקום הזה
                }
            }


            // את זה לעשות אחרי שיצרתי את לינאר רג
            cf.push_back(correlatedFeatures());
            cf[j].corrlation = mypers;
            cf[j].feature1=myfeaturename.at(i);
            cf[j].feature2=myfeaturename.at(j);
            cf[j].lin_reg=myLine;
            cf[j].threshold=myMaxdev;



        }
       matthatcheckcorelation[j][0]=j;
       matthatcheckcorelation[j][1]=myMostcorFeaturi;



}





	// TODO Auto-generated destructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub

}

