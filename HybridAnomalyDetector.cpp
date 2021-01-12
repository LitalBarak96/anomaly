
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts){
    SAD.setCorthresh(this->getCorthresh());
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

//        Point **arrayofPointmostCor = new Point *[sizeoftable-1];
//        for (int j = 0; j < sizeoftable; j++) {
//            arrayofPointmostCor[j] = new Point(mytablevector[j][firstCorlatindex], mytablevector[j][SecCorlateIndex]);
//        }

//        veccorSAD.at(i).circle = findMinCircle(arrayofPointmostCor, sizeoftable-1);


    }


    }

}
vector<struct AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries &ts) {
    int flag = 0;
    vector<vector<float>>myTable=ts.getthetable();
    int table_size=int(myTable.size());
    vector<string>feature_name=ts.getfeaturs();
    int size_of_colom=myTable[1].size();
    vector<correlatedFeatures>corelatfeature=veccorSAD;
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
//            corrlation <stof(Corthresh) && corelatfeature.at(i).corrlation > 0.5
            if (corelatfeature.at(i).typeofdata =="circle") {
                    if (!(inornot(corelatfeature.at(i).circle,*A))) {// אם ההחסרה בינהם הביאה לערך חריגה גדול יותר מהלמידה
                        string full = corelatfeature.at(i).feature1 + "-" + corelatfeature.at(i).feature2;
                        AnomalyReport *An = new AnomalyReport(full, (j + 1));
                        MyAnomlyReport.push_back(*An);

                }
            }
            if (corelatfeature.at(i).typeofdata=="linear" && flag == 0 ){
                flag =1;
                for (int i = 0 ;i <SAD.detect(ts).size();i++){
                    MyAnomlyReport.push_back(SAD.detect(ts).at(i));
                }
            }
        }



    }
    return MyAnomlyReport;
}

const string &HybridAnomalyDetector::getCorthresh1() const {
    return Corthresh;
}

void HybridAnomalyDetector::setCorthresh1(const string &corthresh) {
    Corthresh = corthresh;
}
