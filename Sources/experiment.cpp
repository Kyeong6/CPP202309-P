#include "experiment.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

// 바이오차 대체율에 따른 시멘트양 계산 함수
void ExperimentData::calculateCement()
{
    double bioAsh = bioRate * 48.5; // 바이오차 1%당 바이오차 양(g)

        // 바이오차에 따른 시멘트 양 계산
    if (bioRate == 0.01) {
        cement = 4.80 - bioAsh / 1000.0;
    }
    else if (bioRate == 0.02) {
        cement = 4.75 - bioAsh / 1000.0;
    }
    else if (bioRate == 0.03) {
        cement = 4.71 - bioAsh / 1000.0;
    }
    else if (bioRate == 0.04) {
        cement = 4.66 - bioAsh / 1000.0;
    }
    else if (bioRate == 0.05) {
        cement = 4.56 - bioAsh / 1000.0;
    }
    else if (bioRate == 0.06) {
        cement = 4.56 - bioAsh / 1000.0;
    }
}

// 클래스 생성자 생성
ExperimentData::ExperimentData(int bioRate, double water, double fineAggregate)
{
    this->bioRate = static_cast<double>(bioRate) / 100;
    this->water = water;
    this->fineAggregate = fineAggregate;
    calculateCement(); // 시멘트 양을 새롭게 계산
    setSpecimenName();
}

void ExperimentData::setCompressiveStrength(double value)
{
    compressiveStrength = value;
}

void ExperimentData::setTensileStrength(double value)
{
    tensileStrength = value;
}

void ExperimentData::setFlexuralStrength(double value)
{
    flexuralStrength = value;
}

void ExperimentData::setSuitability(string value)
{
    suitability = value;
}

// 바이오차 1%는 48.5g에 해당, 즉 비율이 올라가면 곱해준다
void ExperimentData::setCement()
{
    double bioAsh = bioRate * 48.5;
    cement = 4.8 - bioAsh / 1000.0;
}

// 포함 비율에 따른 실험체 명 설정
void ExperimentData::setSpecimenName()
{
    specimenName = "WB-C-" + to_string(static_cast<int>(bioRate * 100));
}

void ExperimentData::setBioRate(double rate)
{
    bioRate = rate;
}

void ExperimentData::setFlowTestSuitability(bool suitable)
{
    isFlowTestSuitable = suitable;
}

void ExperimentData::setCompressiveSuitability(bool suitable)
{
    isCompressiveSuitable = suitable;
}

void ExperimentData::setTensileSuitability(bool suitable)
{
    isTensileSuitable = suitable;
}

void ExperimentData::setFlexuralSuitability(bool suitable)
{
    isFlexuralSuitable = suitable;
}

double ExperimentData::getBioRate()
{
    return 100 * bioRate;
}

double ExperimentData::getBioAsh()
{
    return bioRate * 48.5;
}

double ExperimentData::getWater()
{
    return water;
}

double ExperimentData::getCement()
{
    return cement;
}

double ExperimentData::getFineAggregate()
{
    return fineAggregate;
}

bool ExperimentData::getFlowTestSuitability() const
{
    return isFlowTestSuitable;
}

// 표 출력 및  텍스트 파일 저장에 적합/부적합으로 출력
string ExperimentData::getFlowTestSuitabilityString() const
{
    if (isFlowTestSuitable) {
        return "부적합";
    }
    else {
        return "적합";
    }
}

double ExperimentData::getCompressiveStrength()
{
    return compressiveStrength;
}

double ExperimentData::getTensileStrength()
{
    return tensileStrength;
}

double ExperimentData::getFlexuralStrength()
{
    return flexuralStrength;
}

string ExperimentData::getSuitability()
{
    return suitability;
}

string ExperimentData::getSpecimenName()
{
    return specimenName;
}

bool ExperimentData::getCompressiveSuitability() const
{
    return isCompressiveSuitable;
}

bool ExperimentData::getTensileSuitability() const
{
    return isTensileSuitable;
}

bool ExperimentData::getFlexuralSuitability() const
{
    return isFlexuralSuitable;
}

// 사용자에게 바이오차 대체율을 입력받는 함수의 유효성 판별
// 바이오차는 0 ~ 6%까지 사용
int ExperimentData::getBioRate() const
{
    int bioRate;
    while (true) {
        cout << "바이오차 대체율을(%)을 입력하시오 : ";
        cin >> bioRate;
        if (bioRate < 0 or bioRate > 6) {
            cout << "잘못된 입력입니다. 바이오차 대체율을 0 ~ 6% 사이의 값으로 입력해주세요." << endl;
            continue;
        }
        break;
    }
    return bioRate;
}

void ExperimentData::printSpecimenName()
{
    cout << "실험체(공시체)명 : " << getSpecimenName() << endl;
}


// 바이오차 대체율에 따라 시멘트 양이 결정
// 물과 잔골재양은 고정값
void ExperimentData::printMaterials()
{
    double bioAsh = getBioAsh();
    double cement = getCement(); // 시멘트 양을 그대로 가져옴

    cout << "바이오차 양 : " << bioAsh << "g" << endl;
    cout << "시멘트 양 : " << fixed << setprecision(2) << cement << "kg" << endl; // 시멘트 양 반올림하여 출력
    cout << "물 양 : 2.29Kg" << endl; // 고정값
    cout << "잔골재 양 : 11.04kg" << endl; // 고정값
}

// 실험 결과의 적합성을 알기 위해 플로우 테스트 값을 확인
// 0 ~ 40분 까지의 5개의 값 입력 및 유효성 검사 실시
// 플로우 테스트 값 중 하나라도 150mm 이하의 값을 가지면 적합하지 않는 코드 작성
void ExperimentData::saveFlowTest()
{
    string input;
    double flowTestValues[5];
    // Flow-Test 시간은 고정값, 0은 직후 Flow-Test 값
    int times[5] = { 0, 10, 20, 30, 40 };

    // 유효성 검사를 위한 while문
    while (true) {
        cout << "10분 간격의 시간대 별 (0분 ~ 40분) Flow-Test 값을 공백으로 구분하여 mm단위로 입력하세요 :";
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
    setFlowTestSuitability(isFlowTestSuitable);
}

// 실험 결과의 적합성을 알기 위해 3개의 강도 값을 확인
// 압축, 쪼갬인장, 휨강도 각각의 3개의 값을 입력 및 유효성 검사 실시
void ExperimentData::saveStrength(const string& strengthType)
{
    string input;
    // 강도 입력 리스트
    double strengthValues[3];

    // 유효성 검사를 위한 while문
    while (true) {
        cout << "실험체의 " << strengthType << "를 공백으로 구분하여 KN 단위(실수)로 3개의 값을 입력하세요 : ";
        cin.ignore();
        getline(cin, input);

        stringstream ss(input);

        // 유효성 검사를 위한 vaildInput 설정
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

    // 강도에 따라서 setter 함수에 평균값 저장
    if (strengthType == "압축강도") {
        setCompressiveStrength(transformedValue);
    }
    else if (strengthType == "쪼갬인장강도") {
        setTensileStrength(transformedValue);
    }
    else if (strengthType == "휨강도") {
        setFlexuralStrength(transformedValue);
    }
}


// 입력받은 강도 값이 적합한지 파악하는 함수
// 설계 기준 강도 이상의 값을 가진다면 적합
void ExperimentData::checkStrengthSuitability()
{
    // 설계 기준 강도 설정(Mpa)
    double standardCompressiveStrength = 17.89; // 기준 압축강도
    double standardTensileStrength = 2.5;     // 기준 쪼갬인장강도
    double standardFlexuralStrength = 4.5;     // 기준 휨강도

    // 실험 결과
    double compressiveStrength = getCompressiveStrength();
    double tensileStrength = getTensileStrength();
    double flexuralStrength = getFlexuralStrength();

    // 각각의 적합 여부 저장
    // 강도가 설계 기준 강도값 이상이면 적합
    bool isCompressiveSuitable = (compressiveStrength >= standardCompressiveStrength);
    bool isTensileSuitable = (tensileStrength >= standardTensileStrength);
    bool isFlexuralSuitable = (flexuralStrength >= standardFlexuralStrength);

    // 적합 여부를 ExperimentData 클래스에 저장
    setCompressiveSuitability(isCompressiveSuitable);
    setTensileSuitability(isTensileSuitable);
    setFlexuralSuitability(isFlexuralSuitable);
}

// 최종적으로 표 형태로 데이터들을 출력
void ExperimentData::printExperimentData()
{
    // 컬렴명(keyword) 출력
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
    cout << left << setw(21) << getSpecimenName()
        << left << setw(22) << static_cast<int>(getBioRate())
        << left << setw(18) << getCement()
        << left << setw(16) << getWater()
        << left << setw(21) << getFineAggregate()
        << left << setw(16) << getFlowTestSuitabilityString()
        << left << setw(18) << (getCompressiveSuitability() ? "적합" : "부적합")
        << left << setw(17) << (getTensileSuitability() ? "적합" : "부적합")
        << left << setw(16) << (getFlexuralSuitability() ? "적합" : "부적합") << endl;
}

// 표로 출력한 내용을 텍스트 파일에 저장
void ExperimentData::saveExperimentDataToFile()
{
    // 파일에 추가 모드로 열기
    ofstream outputFile("experiment_data.txt", ios_base::app);

    if (outputFile.is_open()) {
        // 이전에 표 헤더가 파일에 쓰여졌는지 확인 후 추가하지 않는다
        if (outputFile.tellp() == 0) {
            outputFile << left << setw(18) << "실험체명"
                << left << setw(33) << "바이오차 대체율(%)"
                << left << setw(23) << "시멘트 양(kg)"
                << left << setw(18) << "물 양(kg)"
                << left << setw(23) << "잔골재 양(kg)"
                << left << setw(23) << "플로우 테스트"
                << left << setw(17) << "압축강도"
                << left << setw(23) << "쪼갬인장강도"
                << left << setw(18) << "휨강도" << endl;

            for (int i = 0; i < 130; i++) outputFile << '-';
            outputFile << '\n';
        }

        outputFile << left << setw(17) << getSpecimenName()
            << left << setw(20) << static_cast<int>(getBioRate())
            << fixed << setprecision(2) << left << setw(15) << getCement()
            << left << setw(16) << getWater()
            << left << setw(17) << getFineAggregate()
            << left << setw(15) << getFlowTestSuitabilityString()
            << left << setw(17) << (getCompressiveSuitability() ? "적합" : "부적합")
            << left << setw(16) << (getTensileSuitability() ? "적합" : "부적합")
            << left << setw(16) << (getFlexuralSuitability() ? "적합" : "부적합") << endl;

        outputFile.close();
        cout << "데이터가 파일에 추가되었습니다." << endl;
    }
    else {
        cout << "파일을 열 수 없습니다." << endl;
    }
}


