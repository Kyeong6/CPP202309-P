#include <iostream>
#include <string>
#include <iomanip> 
#include <sstream>
using namespace std;

// 실험데이터 클래스 설정
class ExperimentData {
private:
    double bioRate; // 바이오차 대체율
    double water; // 고정값으로 설정된 물
    double cement; // 시멘트
    double fineAggregate; // 잔골재
    string specimenName; // 바이오차는 시멘트를 대체, 바이오차 대체율에 따라 
    bool isFlowTestSuitable; // Flow-Test 적합 여부
    double compressiveStrength; // 압축강도
    string suitability; // 적합성 판별
    double tensileStrength; // 쪼갬인장강도
    double flexuralStrength; // 휨강도
    bool isCompressiveSuitable; // 압축강도 적합성
    bool isTensileSuitable; // 쪼갬인장강도 적합성
    bool isFlexuralSuitable; // 휨강도 적합성

public:

    void calculateCement() {
        double bioAsh = bioRate * 48.5; // 바이오차 1%당 바이오차 양(g)
        
        // 바이오차에 따른 시멘트 양 계산
        if (bioRate == 0.01) {
            cement = 4.80 - bioAsh / 1000.0;
        } else if (bioRate == 0.02) {
            cement = 4.75 - bioAsh / 1000.0;
        } else if (bioRate == 0.03) {
            cement = 4.71 - bioAsh / 1000.0;
        } else if (bioRate == 0.04) {
            cement = 4.66 - bioAsh / 1000.0;
        } else if (bioRate == 0.05) {
            cement = 4.56 - bioAsh / 1000.0;
        } else if (bioRate == 0.06) {
            cement = 4.56 - bioAsh / 1000.0;
        }
    }
    // 클래스 생성자 설정
    // bioRate는 0~6% 범위의 값이므로 정수로 설정
    ExperimentData(int bioRate, double water, double fineAggregate) 
    // 멤버 초기화 리스트
    : bioRate(bioRate), water(water), fineAggregate(fineAggregate) 
    {
        setBioRate(static_cast<double>(bioRate) / 100);
        calculateCement(); // 시멘트 양을 새롭게 계산
        setSpecimenName();
    }

    // setter : 멤버 변수 값 설정
    void setCompressiveStrength(double value) { compressiveStrength = value; }
    void setTensileStrength(double value) { tensileStrength = value; }
    void setFlexuralStrength(double value) { flexuralStrength = value; }
    void setSuitability(string value) { suitability = value; }
    void setCement() {
        double bioAsh = bioRate * 48.5;
        cement = 4.8 - bioAsh / 1000.0;
    }
    // 실험체(공시체)명 설정
    void setSpecimenName() {
        specimenName = "WB-C-" + to_string(static_cast<int>(bioRate * 100));
    }
    void setBioRate(double rate) {
        bioRate = rate;
    }
     void setFlowTestSuitability(bool suitable) {
        isFlowTestSuitable = suitable;
    }
    void setCompressiveSuitability(bool suitable) {
        isCompressiveSuitable = suitable;
    }

    void setTensileSuitability(bool suitable) {
        isTensileSuitable = suitable;
    }

    void setFlexuralSuitability(bool suitable) {
        isFlexuralSuitable = suitable;
    }

    // getter : 멤버 변수 값 반환
    double getBioRate() { return 100 * bioRate; }
    double getBioAsh() { return bioRate * 48.5; }
    double getWater() { return water; }
    double getCement() { return cement; }
    double getFineAggregate() { return fineAggregate; }
    bool getFlowTestSuitability() const { return isFlowTestSuitable; }
    string getFlowTestSuitabilityString() const {
        if (isFlowTestSuitable) {
            return "부적합";
        } else {
            return "적합";
        }
    }
    double getCompressiveStrength() { return compressiveStrength; }
    double getTensileStrength() { return tensileStrength; }
    double getFlexuralStrength() { return flexuralStrength; }
    string getSuitability() { return suitability; }
    string getSpecimenName() { return specimenName; }
    bool getCompressiveSuitability() const { return isCompressiveSuitable; }
    bool getTensileSuitability() const { return isTensileSuitable; }
    bool getFlexuralSuitability() const { return isFlexuralSuitable; }
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
    double bioAsh = data.getBioAsh();
    double cement = data.getCement(); // 시멘트 양을 그대로 가져옴

    cout << "바이오차 양 : " << bioAsh << "g" << endl;
    cout << "시멘트 양 : " << fixed << setprecision(2) << cement << "kg" << endl; // 시멘트 양 반올림하여 출력
    cout << "물 양 : 2.29Kg" << endl; // 고정값
    cout << "잔골재 양 : 11.04kg" << endl; // 고정값
}


// 시간대 별 Flow-Test값 입력, 입력받은 값의 부적합 여부 저장
void saveFlowTest(ExperimentData& data) {
    string input;
    double flowTestValues[5];
    // Flow-Test 시간은 고정값, 0은 직후 Flow-Test 값
    int times[5] = {0, 10, 20, 30, 40};

    // 유효성 검사를 위한 while문
    while (true) {
        cout << "각 시간 별(초기값은 직후) Flow-Test 값을 공백으로 구분하여 mm 단위로 입력하세요 : ";
        cin.ignore();
        // 입력 한 줄로 받기
        getline(cin, input);

        // 입력 stringstream에 저장
        stringstream ss(input);

        // validInput 변수를 통한 유효성 검사
        // 시간 대 별 5개의 입력을 작성하지 않았을 경우
        bool validInput = true;
        for (int i = 0; i < 5; i++) {
            if (!(ss >> flowTestValues[i])) {
                validInput = false;
                cout << "유효하지 않은 입력입니다. 숫자를 공백으로 구분하여 5개 입력하세요." << endl;
                break;
            }
        }

        if (validInput) {
            break;
        }
    }

    bool isFlowTestSuitable = true; // 기본적으로 적합으로 설정

    // 150mm 이상이면 적합으로 설정
    for (int i = 0; i < 5; i++) {
        if (flowTestValues[i] >= 150) {
            isFlowTestSuitable = false;
            break;
        }
    }

    // 적합 여부를 ExperimentData 클래스에 저장
    data.setFlowTestSuitability(isFlowTestSuitable);
}

// 사용자에게 입력받은 강도(압축, 쪼갬, 휨) 저장 함수
void saveStrength(ExperimentData& data, const string& strengthType) {
    string input;
    // 강도 입력 리스트
    double strengthValues[3];

    // 유효성 검사를 위한 while문
    while (true) {
        cout << "실험체의 " << strengthType << "를 공백으로 구분하여 KN 단위(실수)로 입력하세요 : ";
        cin.ignore();
        getline(cin, input);

        stringstream ss(input);

        // 유효성 검사를 위한 validInput 설정
        bool validInput = true;
        for (int i = 0; i < 3; i++) {
            if (!(ss >> strengthValues[i])) {
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
        sum += strengthValues[i];
    }

    double average = sum / 3;

    // 적합성 파악을 위한 평균값 변환 
    double transformedValue = (average * 1000) / (50 * 50);

    // 강도에 따른 set 함수에 평균값 저장
    if (strengthType == "압축강도") {
        data.setCompressiveStrength(transformedValue);
    } else if (strengthType == "쪼갬인장강도") {
        data.setTensileStrength(transformedValue);
    } else if (strengthType == "휨강도") {
        data.setFlexuralStrength(transformedValue);
    }
}

// 강도를 통한 적합성 파악 함수
void checkStrengthSuitability(ExperimentData& data) {
    
    // 설계 기준 강도 설정 (Mpa)
    double standardCompressiveStrength = 17.89; // 기준 압축강도
    double standardTensileStrength = 2.5;     // 기즌 쪼갬인장강도
    double standardFlexuralStrength = 4.5;     // 기준 휨강도

    // 실험 결과
    double compressiveStrength = data.getCompressiveStrength();
    double tensileStrength = data.getTensileStrength();
    double flexuralStrength = data.getFlexuralStrength();

    // 각각의 적합 여부 저장
    // 강도가 설계 기준 강도값 이상이면 적합
    bool isCompressiveSuitable = (compressiveStrength >= standardCompressiveStrength);
    bool isTensileSuitable = (tensileStrength >= standardTensileStrength);
    bool isFlexuralSuitable = (flexuralStrength >= standardFlexuralStrength);

    // 적합 여부를 ExperimentData 클래스에 저장
    data.setCompressiveSuitability(isCompressiveSuitable);
    data.setTensileSuitability(isTensileSuitable);
    data.setFlexuralSuitability(isFlexuralSuitable);
}

// 최종 표 출력
void printExperimentData(ExperimentData& data) {

    // 컬럼명 출력
    cout << left << setw(18) << "실험체명"
     << left << setw(33) << "바이오차 대체율(%)"
     << left << setw(23) << "시멘트 양(kg)"
     << left << setw(18) << "물 양(kg)"
     << left << setw(23) << "잔골재 양(kg)"
     << left << setw(23) << "플로우 테스트"
     << left << setw(17) << "압축강도"
     << left << setw(23) << "쪼갬인장강도"
     << left << setw(18) << "휨강도" << endl;
    
    // 구분선 출력
    for (int i = 0; i < 150; i++) cout << '-';
    cout << '\n';

    // 값 출력
    cout << left << setw(21) << data.getSpecimenName()
         << left << setw(22) << static_cast<int>(data.getBioRate())
         << left << setw(18) << data.getCement()
         << left << setw(16) << data.getWater()
         << left << setw(21) << data.getFineAggregate()
         << left << setw(14) << data.getFlowTestSuitabilityString()
         << left << setw(18) << (data.getCompressiveSuitability() ? "적합" : "부적합")
         << left << setw(17) << (data.getTensileSuitability() ? "적합" : "부적합")
         << left << setw(16) << (data.getFlexuralSuitability() ? "적합" : "부적합") << endl;
}


int main() 
{
    // 1. 바이오차 대체율 입력, 값의 범위는 0~6%
    int bioRate = getBioRate();
    
    // 2. 바이오차 대체율에 따른 실험체명 설정, 물과 잔골재 양 설정(고정값)
    ExperimentData data(bioRate, 2.29, 11.04);
    
    printSpecimenName(data);
    
    // 3. 바이오차 비율에 따른 재료량 출력
    printMaterials(data);
    
    // 4. 시간대 별(10,20,30,40min) Flowtest 입력 요청 문장 출력, 입력받은 값의 평균값 저장
    saveFlowTest(data);

    // 5. 실험체의 압축강도, 쪼갬강도 입력(실험체명 당 3개 존재) 후 평균값 저장
    saveStrength(data, "압축강도");
    saveStrength(data, "쪼갬강도");
    saveStrength(data, "휨강도");

    // 6. 플로우 테스트와 압축강도의 평균값을 통한 적합성 판별
    checkStrengthSuitability(data);    

    // 7. 표를 통해 데이터들을 한 눈에 출력 
    printExperimentData(data);

    return 0;
}