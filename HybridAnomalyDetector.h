

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
    vector<correlatedFeatures> veccorSAD;
    string Corthresh;
public:
    const string &getCorthresh1() const;

    void setCorthresh1(const string &corthresh);

public:
    SimpleAnomalyDetector SAD;
	HybridAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
	virtual ~HybridAnomalyDetector();
    vector<correlatedFeatures> getNormalModel(){
        return veccorSAD;
    }

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */