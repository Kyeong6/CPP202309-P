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
    string specimenName; // 바이오차는 시멘트를 대체, 바이오차 대체율에 따라 
    double flowTestValue; // 플로우 테스트 값
    double compressiveStrength; // 압축강도
    string suitability; // 적합성 판별

public:
    // 클래스 생성자 설정
    // bioRate는 0~6% 범위의 값이므로 정수로 설정
    ExperimentData(int bioRate, double water, double fineAggregate) 
    // 멤버 초기화 리스트
    : bioRate(bioRate), water(water), fineAggregate(fineAggregate) 
    {
        setBioRate(bioRate);
        setCement();
        setSpecimenName();
    }

    // setter : 멤버 변수 값 설정
    void setFlowTestValue(double value) { flowTestValue = value; }
    void setCompressiveStrength(double value) { compressiveStrength = value; }
    void setSuitability(string value) { suitability = value; }
    void setCement() {
        // Cement는 bioRate 비율에 따라 값이 줄어듬
        cement = 1.0 - bioRate;
    }
    // 실험체(공시체)명 설정
    void setSpecimenName() {
        specimenName = "WB-C-" + to_string(static_cast<int>(bioRate * 100));
    }
    void setBioRate(int rate) {
        bioRate = static_cast<double>(rate) / 100;
    }

    // getter : 멤버 변수 값 반환
    double getBioRate() { return bioRate; }
    double getWater() { return water; }
    double getCement() { return cement; }
    double getFineAggregate() { return fineAggregate; }
    double getFlowTestValue() { return flowTestValue; }
    double getCompressiveStrength() { return compressiveStrength; }
    string getSuitability() { return suitability; }
    string getSpecimenName() { return specimenName; }
};


int main() {

    int bioRate;

    // 1. 바이오차 대체율 입력, 값의 범위는 0~6%
    while (true) {

        cout << "바이오차 대체율(%)을 입력하시오 : ";
        cin >> bioRate;

        // 잘못된 입력일 경우 문장 출력 후 재질문
        if (bioRate < 0 or bioRate > 6) {
            cout << "잘못된 입력입니다. 바이오차 대체율을 0 ~ 6% 사이의 값으로 입력해주세요." << endl;
            continue;
        }
        break;
    }

    // 2. 바이오차 대체율에 따른 실험체명 설정
    ExperimentData data(bioRate, 1.0, 3.0);
    cout << "실험체(공시체)명 : " << data.getSpecimenName() << endl;
    

    // 다음 단계
    // 3. 바이오차 비율에 따른 시멘트 및 바이오차 값 설정, 다른 재료인 물과 잔골재는 항상 고정값
    // 4. 시간대 별(10,20,30,40min) Flowtest 입력 요청 문장 출력, 입력받은 값의 평균값 저장
    // 5. 실험체의 압축강도 입력(실험체명 당 4개 존재) 후 평균값 저장
    // 6. 표를 통해 데이터들을 한 눈에 출력 및 플로우 테스트와 압축강도의 평균값을 통해 적합성 여부 판별

    return 0;

}