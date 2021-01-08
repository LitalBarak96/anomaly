
#include "HybridAnomalyDetector.h"
#include "timeseries.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}


HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts){
    SAD.learnNormal(ts);
    vector<vector<float>>mytablevector=ts.getthetable();
    int firstCorlatindex= 0;
    int SecCorlateIndex = 0 ;
    this->veccorSAD = SAD.getNormalModel();
    int sizeoftable = ts.getthetable().size();
    for (int i =0 ;i <this->veccorSAD.size();i++){
    if (veccorSAD.at(i).typeofdata=="circle") {
        for (int k = 0; k < ts.getfeaturs().size(); k++) {
            if (veccorSAD.at(i).feature1 == ts.getfeaturs().at(k)) {
                firstCorlatindex = k;
            }
            if (veccorSAD.at(i).feature2 == ts.getfeaturs().at(k)) {
                SecCorlateIndex = k;
            }
        }

        Point **arrayofPointmostCor = new Point *[sizeoftable];
        for (int j = 0; j < sizeoftable; j++) {
            arrayofPointmostCor[j] = new Point(mytablevector[j][firstCorlatindex], mytablevector[j][SecCorlateIndex]);
        }
        veccorSAD.at(i).circle.radius = findMinCircle(arrayofPointmostCor, sizeoftable).radius;
        veccorSAD.at(i).circle.center = findMinCircle(arrayofPointmostCor, sizeoftable).center;


    }


    }

}
vector<struct AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries &ts) {

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

        for (int j = 0; j < table_size; j++) {//לולאה שבודקות את הזמנים יענו TIMESTEP
            float Xcorlation = myTable[j].at(indexfeature1);// בזמן J בטור של האינדקסים הקורלטיבים
            float Ycorlation = myTable[j].at(indexfeature2);
            Point *A = new Point(Xcorlation, Ycorlation);
            if (corelatfeature.at(i).corrlation < 0.9 && corelatfeature.at(i).corrlation > 0.5) {
                if (inornot(corelatfeature.at(i).circle, *A)) {// אם ההחסרה בינהם הביאה לערך חריגה גדול יותר מהלמידה
                    string full = corelatfeature.at(i).feature1 + "-" + corelatfeature.at(i).feature2;
                    AnomalyReport *An = new AnomalyReport(full, (j + 1));
                    MyAnomlyReport.push_back(*An);

                }
            }
        }



    }
    return MyAnomlyReport;
}