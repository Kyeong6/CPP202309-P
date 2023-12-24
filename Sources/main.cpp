#include <iostream>
#include "experiment.h"
using namespace std;

// 사용자에게 바이오차 대체율을 입력받는 함수
int getBioRateFromUser() {
    int bioRate;
    while (true) {
        cout << "바이오차 대체율(%)을 입력하시오 : ";
        cin >> bioRate;
        if (bioRate < 0 or bioRate > 6) {
            cout << "잘못된 입력입니다. 바이오차 대체율을 0 ~ 6% 사이의 값으로 입력해주세요." << endl;
            continue;
        }
        break;
    }
    return bioRate;
}


int main() {

    // 바이오차 대체율 입력 
    int bioRate = getBioRateFromUser(); 

    // ExperimentData 객체 생성
    ExperimentData data(bioRate, 2.29, 11.04); 

    // 실험체명 출력
    data.printSpecimenName(); 

    // 재료량 출력
    data.printMaterials(); 

    // Flow-Test 출력
    data.saveFlowTest(); 

    // 강도 입력(압축, 쪼갬인장, 휨)
    data.saveStrength("압축강도"); 
    data.saveStrength("쪼갬인장강도");
    data.saveStrength("휨강도");

    // 강도 적합성 확인
    data.checkStrengthSuitability(); 

    // 실험 데이터 출력
    data.printExperimentData(); 

    // 파일에 데이터 저장
    data.saveExperimentDataToFile(); 

    return 0;
}