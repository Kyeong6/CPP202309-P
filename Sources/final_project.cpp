#include <iostream>
#include <string>
using namespace std;

// 실험데이터 클래스 설정
class ExperimentData {
private:
    double bioRate; // 바이오차 대체율
    double water; // 물
    double cement; // 시멘트
    double fineAggregate; // 잔골재
    string experimentName; // 실험체명
    double flowTestValue; // 플로우 테스트 값
    double compressiveStrength; // 압축강도
    string suitability; // 적합성 판별

public:
    // 클래스 생성자 설정
    ExperimentData(double bioRate, double water, double cement, double fineAggregate, string experimentName) 
    // 멤버 초기화 리스트
    : bioRate(bioRate), water(water), cement(cement), fineAggregate(fineAggregate), experimentName(experimentName) {}
    
    // setter : 멤버 변수 값 설정
    void setFlowTestValue(double value) { flowTestValue = value; }
    void setCompressiveStrength(double value) { compressiveStrength = value; }
    void setSuitability(string value) { suitability = value; }
    
    // getter : 멤버 변수 값 반환
    double getBioRate() { return bioRate; }
    double getWater() { return water; }
    double getCement() { return cement; }
    double getFineAggregate() { return fineAggregate; }
    string getExperimentName() { return experimentName; }
    double getFlowTestValue() { return flowTestValue; }
    double getCompressiveStrength() { return compressiveStrength; }
    string getSuitability() { return suitability; }
};


int main() {

}