
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    vector<vector<float>>mytablevector=ts.getthetable();
    int sizeofcolom=mytablevector[1].size();//כמה עמודות יש
    for (int j = 0;j<sizeofcolom;j++){
        float theFirst [mytablevector.size()];// המערך שאליו בודקים הראשון
        float theOthers [mytablevector.size()];// המערך שבודקים אליו
        std::copy(mytablevector.at(j).begin(), mytablevector.at(j).end(), theFirst);//העתקה של הוקטור לתוך המערך
        for (int i=1;i< )


}





	// TODO Auto-generated destructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub

}

