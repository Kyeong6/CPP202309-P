#include <iostream>
#include <string>
#include <iomanip> 
#include <sstream>
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
    double tensileStrength; // 쪼갬강도 강도
    double flexuralStrength; // 휨 강도

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
    void setTensileStrength(double value) { tensileStrength = value; }
    void setFlexuralStrength(double value) { flexuralStrength = value; }
    void setSuitability(string value) { suitability = value; }
    void setCement() {
        // Cement는 bioRate 비율에 따라 값이 줄어듬
        // 현재는 프로젝트를 진행 중이므로 시멘트의 기본값 1000(g)으로 설정
        cement = 1000 * (1.0 - bioRate);
    }
    // 실험체(공시체)명 설정
    void setSpecimenName() {
        specimenName = "WB-C-" + to_string(static_cast<int>(bioRate * 100));
    }
    void setBioRate(int rate) {
        bioRate = static_cast<double>(rate) / 100;
    }

    // getter : 멤버 변수 값 반환
    double getBioRate() { return 100 * bioRate; }
    double getBioAsh() { return 1000 * bioRate; }
    double getWater() { return water; }
    double getCement() { return cement; }
    double getFineAggregate() { return fineAggregate; }
    double getFlowTestValue() { return flowTestValue; }
    double getCompressiveStrength() { return compressiveStrength; }
    double getTensileStrength() { return tensileStrength; }
    double getFlexuralStrength() { return flexuralStrength; }
    string getSuitability() { return suitability; }
    string getSpecimenName() { return specimenName; }
};

// 바이오차 대체율 유효성 판별 함수
int getBioRate() {
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

// 대체율에 따른 실험체명 설정 함수
void printSpecimenName(ExperimentData& data) {
    cout << "실험체(공시체)명 : " << data.getSpecimenName() << endl;
}

// 바이오차 비율에 따른 시멘트량 및 재료량 출력
void printMaterials(ExperimentData& data) {
    cout << "바이오차 양 : " << data.getBioAsh() << "g" << endl;
    cout << "시멘트 양 : " << data.getCement() << "g" << endl;
    cout << "물 양 : " << data.getWater() << "g" << endl;
    cout << "잔골재 양 : " << data.getFineAggregate() << "g" << endl;
}

// 시간대 별 Flow-Test값 입력, 입력받은 값의 평균값 저장
void saveFlowTest(ExperimentData& data) {
    string input;
    double flowTestValues[4];
    // Flow-Test 시간은 고정값
    int times[4] = {10, 20, 30, 40};

    // for (int i = 0; i < 4; i++) {
    //     cout << times[i] << "분의 Flow-Test 값을 입력하세요 : ";
    //     cin >> flowTestValues[i];
    // }
    cout << "각 시간 별 Flow-Test 값을 공백으로 구분하여 cm 단위로 입력하세요 : ";
    // 해당 코드 작성하지 않을 경우 위 출력 문장 후 프로그램 종료
    cin.ignore();
    // 입력 한 줄로 받기
    getline(cin, input);

    // 입력 stringstream에 저장
    stringstream ss(input);

    // stringstream에서 Flow-Test 값 추출
    for (int i = 0; i < 4; i++) {
        ss >> flowTestValues[i];
    }

    double sum = 0;
    for (int i = 0; i < 4; i++) {
        sum += flowTestValues[i];
    }

    double average = sum / 4;
    // setFlowTestValue() 함수 호출하여 평균값 설정
    data.setFlowTestValue(average);
}


// 실험체의 압축강도 입력, 입력받은 값의 평균값 저장
void saveCompressiveStrength(ExperimentData& data) {
    string input;
    double compressiveStrengthValues[3];

    // 유효성 검사를 위한 while문 설정
    while (true) {
        cout << "실험체의 압축강도를 공백으로 구분하여 KN 단위(실수)로 입력하세요 : ";
        cin.ignore();
        // 입력 한 줄로 받기
        getline(cin, input);

        // 입력 stringstream에 저장
        stringstream ss(input);

        // validInput 변수를 통한 유효성 검사 실행
        bool validInput = true;
        for (int i = 0; i < 3; i++) {
            if (!(ss >> compressiveStrengthValues[i])) {
                validInput = false;
                cout << "유효하지 않은 입력입니다. 숫자(실수)를 공백으로 구분하여 입력하세요." << endl;
                break;
            }
        }

        if (validInput) {
            break;
        }
    }

    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += compressiveStrengthValues[i];
    }

    double average = sum / 3;
    // setCompressiveStrength() 함수 호출하여 평균값 설정
    data.setCompressiveStrength(average);
}

// 실험체의 쪼갬강도 입력, 입력받은 값의 평균값 저장
void saveTensileStrength(ExperimentData& data) {
    string input;
    double tensileStrengthValues[3];

    // 유효성 검사를 위한 while문 설정
    while (true) {
        cout << "실험체의 쪼갬강도를 공백으로 구분하여 KN 단위(실수)로 입력하세요 : ";
        cin.ignore();
        // 입력 한 줄로 받기
        getline(cin, input);

        // 입력 stringstream에 저장
        stringstream ss(input);

        // validInput 변수를 통한 유효성 검사 실행
        bool validInput = true;
        for (int i = 0; i < 3; i++) {
            if (!(ss >> tensileStrengthValues[i])) {
                validInput = false;
                cout << "유효하지 않은 입력입니다. 숫자(실수)를 공백으로 구분하여 입력하세요." << endl;
                break;
            }
        }

        if (validInput) {
            break;
        }
    }

    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += tensileStrengthValues[i];
    }

    double average = sum / 3;
    // setTensileStrength() 함수 호출하여 평균값 설정
    data.setTensileStrength(average);
}

// 실험체의 휨강도 입력, 입력받은 값의 평균값 저장
void saveFlexuralStrength(ExperimentData& data) {
    string input;
    double flexuralStrengthValues[3];

    // 유효성 검사를 위한 while문 설정
    while (true) {
        cout << "실험체의 휨강도를 공백으로 구분하여 KN 단위(실수)로 입력하세요 : ";
        cin.ignore();
        // 입력 한 줄로 받기
        getline(cin, input);

        // 입력 stringstream에 저장
        stringstream ss(input);

        // validInput 변수를 통한 유효성 검사 실행
        bool validInput = true;
        for (int i = 0; i < 3; i++) {
            if (!(ss >> flexuralStrengthValues[i])) {
                validInput = false;
                cout << "유효하지 않은 입력입니다. 숫자(실수)를 공백으로 구분하여 입력하세요." << endl;
                break;
            }
        }

        if (validInput) {
            break;
        }
    }

    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += flexuralStrengthValues[i];
    }

    double average = sum / 3;
    // setFlexuralStrength() 함수 호출하여 평균값 설정
    data.setFlexuralStrength(average);
}

void printExperimentData(ExperimentData& data) {
    // 컬럼명 출력
    cout << "실험체명           바이오차 대체율  시멘트 양     물 양      잔골재 양     플로우 테스트 평균값  압축강도 평균값\n";

    // 구분선 출력
    for (int i = 0; i < 112; i++) cout << '-';
    cout << '\n';

    // 실험 데이터 출력
    cout << data.getSpecimenName() << string(25 - data.getSpecimenName().length(), ' ') // 실험체명
         << data.getBioRate() << string(20 - to_string(data.getBioRate()).length(), ' ') // 바이오차 대체율
         << data.getCement() << string(21 - to_string(data.getCement()).length(), ' ') // 시멘트 양
         << data.getWater() << string(20 - to_string(data.getWater()).length(), ' ') // 물 양
         << data.getFineAggregate() << string(26 - to_string(data.getFineAggregate()).length(), ' ') // 잔골재 양
         << data.getFlowTestValue() << string(25 - to_string(data.getFlowTestValue()).length(), ' ') // 플로우 테스트 평균값
         << data.getCompressiveStrength() << string(20 - to_string(data.getCompressiveStrength()).length(), ' ') << '\n'; // 압축강도 평균값
        //  << data.getSuitability() << '\n'; // 적합성 판별
}




int main() 
{
    // 1. 바이오차 대체율 입력, 값의 범위는 0~6%
    int bioRate = getBioRate();
    
    // 2. 바이오차 대체율에 따른 실험체명 설정, 물과 잔골재 양 설정(고정값)
    ExperimentData data(bioRate, 1.0, 3.0);
    printSpecimenName(data);
    
    // 3. 바이오차 비율에 따른 재료량 출력
    printMaterials(data);
    
    // 4. 시간대 별(10,20,30,40min) Flowtest 입력 요청 문장 출력, 입력받은 값의 평균값 저장
    saveFlowTest(data);

    // 5. 실험체의 압축강도, 쪼갬강도 입력(실험체명 당 3개 존재) 후 평균값 저장
    saveCompressiveStrength(data);
    saveTensileStrength(data);
    saveFlexuralStrength(data);

    // 6. 플로우 테스트와 압축강도의 평균값을 통한 적합성 판별
    

    // 7. 표를 통해 데이터들을 한 눈에 출력 
    printExperimentData(data);

    return 0;

}