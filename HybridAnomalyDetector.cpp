
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

}