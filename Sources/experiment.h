#pragma once
#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <string>

using namespace std;

class ExperimentData {
private:
    double bioRate; // 바이오차 대체율
    double water; // 물
    double cement; // 시멘트
    double fineAggregate; // 잔골재
    string specimenName; // 바이오차는 시멘트를 대체, 바이오차 대체율에 따라
    bool isFlowTestSuitable; // Flow-Test 적합 여부
    double compressiveStrength; // 압축강도
    string suitability; // 적합성 판별
    double tensileStrength; // 쪼갬인장강도
    double flexuralStrength; // 휨강도
    bool isCompressiveSuitable; // 압축강도 적합성
    bool isTensileSuitable; //쪼갬인장강도 적합성
    bool isFlexuralSuitable; // 휨강도 적합성
public:
    void calculateCement(); // 바이오차 대체율에 따른 시멘트양 계산
    ExperimentData(int bioRate, double water, double fineAggregate); // bioRate�� 0~6% 범위의 값이므로 정수로 설정
    // setter : 멤버 변수 값 설정
    void setCompressiveStrength(double value); 
    void setTensileStrength(double value); 
    void setFlexuralStrength(double value); 
    void setSuitability(string value); 
    void setCement(); 
    void setSpecimenName(); 
    void setBioRate(double rate);
    void setFlowTestSuitability(bool suitable);
    void setCompressiveSuitability(bool suitable);
    void setTensileSuitability(bool suitable); 
    void setFlexuralSuitability(bool suitable); 
    // getter : 멤버 변수 값 반환
    double getBioRate();
    double getBioAsh(); 
    double getWater(); 
    double getCement(); 
    double getFineAggregate();
    bool getFlowTestSuitability() const;
    string getFlowTestSuitabilityString() const;
    double getCompressiveStrength();
    double getTensileStrength(); 
    double getFlexuralStrength();
    string getSuitability();
    string getSpecimenName();
    bool getCompressiveSuitability() const;
    bool getTensileSuitability() const;
    bool getFlexuralSuitability() const;

    int getBioRate() const; 
    void printSpecimenName();
    void printMaterials();
    void saveFlowTest();
    void saveStrength(const string& strengthType);
    void checkStrengthSuitability();
    void printExperimentData();
    void saveExperimentDataToFile();
};


#endif // EXPERIMENTDATA_H
