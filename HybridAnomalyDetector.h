

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_


#include "SimpleAnomalyDetector.h"
#include "minCircle.h"


class HybridAnomalyDetector:public SimpleAnomalyDetector {
    vector<correlatedFeatures> veccorSAD;

public:
    SimpleAnomalyDetector SAD;
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
