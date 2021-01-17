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
    int mycorliationnumberoftimes =0;
    int sizeofcolom=mytablevector[1].size();//כמה עמודות יש

    for (int j = 0;j<sizeofcolom;j++){//לולאה על זה שאנחנו בודקים
        float theFirst [sizeoftable];// המערך שאליו בודקים הראשון
        float theOthers [sizeoftable];// המערך שבודקים אליו
        for (int m =0 ;m<sizeoftable;m++){//יצירת המערך
            theFirst[m]=mytablevector[m][j];
        }
        float mypers=0;
        int myMostcorFeaturi=0;
        int z=j+1;
        while(z<sizeofcolom){  // בודקת בלולאה הזו על כל השאר ולא צריך לבדוק אחורה,מקווה שזה לא יעשה שגיאה של יציאה מגבולות
            for (int k = 0; k < sizeoftable; k++) {    // זה יוצר את המערך השני
                theOthers[k] = mytablevector[k][z];   //   k זה המיקום בשורה
            }
            float checkpears=pearson(theFirst,theOthers,sizeoftable);
            if (mypers<checkpears){
                mypers=checkpears;// בערך מוחלט
                myMostcorFeaturi=z;
            }


            z++;
        }




        if((mypers>stof(CorthreshSimple)&&(myMostcorFeaturi>j)) || (mypers <stof(CorthreshSimple) && mypers >0.5)){// לשים לב שעשיתי פשוט גדול ממנו ,כאילו אם עברתי עליו כבר זה אומר שבוודאות בעתיד ה"משלים שלו" כבר שייך לו ולא נמצא אחד אחר
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
            cf[mycorliationnumberoftimes].corrlation = mypers;
            cf[mycorliationnumberoftimes].feature1=myfeaturename.at(j);
            cf[mycorliationnumberoftimes].feature2=myfeaturename.at(myMostcorFeaturi);
            cf[mycorliationnumberoftimes].lin_reg=myLine;

            if (mypers>stof(CorthreshSimple)){
                cf[mycorliationnumberoftimes].typeofdata = "linear";
                cf[mycorliationnumberoftimes].threshold = myMaxdev*1.1;

            }
            else if(mypers<stof(CorthreshSimple) && mypers>0.5) {
                cf[mycorliationnumberoftimes].typeofdata = "circle";
                cf[mycorliationnumberoftimes].circle=findMinCircle(arrayofPointformaxi,sizeoftable);
                cf[mycorliationnumberoftimes].threshold=findMinCircle(arrayofPointformaxi,sizeoftable).radius*1.1;
            }
            mycorliationnumberoftimes++;




        }


    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){

    vector<vector<float>>myTable=ts.getthetable();
    int table_size=int(myTable.size());
    vector<string>feature_name=ts.getfeaturs();
    int size_of_colom=myTable[1].size();
    vector<correlatedFeatures>corelatfeature=getNormalModel();
    int corlatefeatur_size=corelatfeature.size();
    int indexfeature2=0;
    int indexfeature1=0;
    vector<AnomalyReport>MyAnomlyReport;
    for (int i = 0; i <corlatefeatur_size ; i++) {// הלולאה הגדולה שעוברת על כל הפיצרים
        auto it = std::find(feature_name.begin(), feature_name.end(), corelatfeature.at(i).feature1);
        if (it != feature_name.end()) {
            indexfeature1 = it - feature_name.begin();
        }
        auto itf2 = std::find(feature_name.begin(), feature_name.end(), corelatfeature.at(i).feature2);
        if (itf2 != feature_name.end()) {
            indexfeature2 = itf2 - feature_name.begin();
        }

        for (int j = 0; j < table_size;j++) {//לולאה שבודקות את הזמנים יענו TIMESTEP
            float Xcorlation = myTable[j].at(indexfeature1);// בזמן J בטור של האינדקסים הקורלטיבים
            float Ycorlation = myTable[j].at(indexfeature2);
            Point* A = new Point (Xcorlation,Ycorlation);
                float myDEV = dev(*A, corelatfeature.at(i).lin_reg);// כנראה צריך לקבל אשכרה נקודה
                if (myDEV > corelatfeature.at(i).threshold) {// אם ההחסרה בינהם הביאה לערך חריגה גדול יותר מהלמידה
                    string full = corelatfeature.at(i).feature1 + "-" + corelatfeature.at(i).feature2;
                    AnomalyReport *An = new AnomalyReport(full, (j + 1));
                    MyAnomlyReport.push_back(*An);
                }

        }
    }
    return MyAnomlyReport;



}


