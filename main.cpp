#include <iostream>
#include <cmath>
#define PI 3.14159265
using namespace std;

class Complex
{
private:
    double real;
    double img;

public:
    Complex(double r = 0, double i = 0): real(r), img(i) {};

    double returnReal(){
        return this->real;
    }
    double returnImg(){
        return this->img;
    }
    Complex add(const Complex& c)
    {
        Complex comp;
        comp.real = this->real + c.real;
        comp.img = this->img + c.img;
        return comp;
    }
    Complex subtract(const Complex& c)
    {
        Complex comp;
        comp.real = this->real - c.real;
        comp.img = this->img - c.img;
        return comp;
    }
    Complex multiply(const Complex& c){
        Complex tempReal((c.real*this->real) + ((c.img*this->img)*(-1)), 0);
        Complex midOne(0, (this->img*c.real));
        Complex midTwo(0, (this->real*c.img));

        Complex midWayPassAdd(tempReal.add(midOne));
        Complex result(midWayPassAdd.add(midTwo));

        return result;

    }
    void printComplex(){
        if(this->img==0){
            cout<<this->real;
        }else if(this->real==0) {
            if(this->img<0) {
                cout<<"-j";
            }else if(this->img==0) {
                cout<<"0";
            }else {
                cout<<"j";
            }
        }else if(this->img>0){
            cout<<this->real<<"+"<<this->img<<"j";
        }else{
            cout<<this->real<<this->img<<"j";
        }
    }
};

double calculateMag(Complex number){
    double real = number.returnReal();
    double img = number.returnImg();
    return sqrt(pow(real, 2)+pow(img,2));
}

double calculatePhase(Complex number){
    double real = number.returnReal();
    double img = number.returnImg();
    double param = img/real;
    double result = atan (param) * 180 / PI;
    if(result<0){
        result+=180;
    }else if(result == -0){
        result = 0;
    }
    return result;
}

Complex omegaNValue (int k, int n, int N){
    if (k*n != 0){
        int angle = (2*180/(N))* k * n;
        double validRadian = angle*PI/180;

        double cosResult = cos(validRadian);
        if (abs(cosResult) < 0.0000001) cosResult = 0;
        double sinResult = sin(validRadian);
        if (abs(sinResult) < 0.0000001) sinResult = 0;
        Complex result (cosResult,-sinResult);

        return result;
    }
    return 1;
}

Complex* omegaNInflator (Complex omegaNMatrix[], int N) {
    int n = N, k = N;
    int counter = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            omegaNMatrix[counter] = omegaNValue(i, j, N);
            counter += 1;
        }
    }
    return omegaNMatrix;
}

Complex* calculateDFT (Complex omegaNMatrix[],Complex multiplicationOutput[], int N) {
    int userInput[N];
    cout << endl << "Enter X(N) values:" << endl;
    cout << N << " values needed" << endl;
    cout << "Continue with ZEROS '0' if you want to enter number of Xs less than N-point Number" << endl;
    for (int i = 0; i < N; i++) {
        cin >> userInput[i];
    }
    cout << "Successfully Entered x(N) values." << endl;
    //-------------------------------------
    int multiplier = 0;
    Complex singleRowResult = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            singleRowResult = singleRowResult.add(omegaNMatrix[j + multiplier].multiply(userInput[j]));
        }
        multiplicationOutput[i] = singleRowResult;
        singleRowResult = 0;
        multiplier += N;
    }
    return multiplicationOutput;
}

void printOmegaN(Complex matrix[], int N) {
    cout << endl << "Printing Wn:" << endl;
    int offset = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[j+offset].printComplex();
            cout << "\t\t\t";
        }
        offset+=N;
        cout << endl;
    }
}

void printResults(Complex matrix[], int N) {
    cout << "---------------------------------------------------" << endl;
    cout << "Printing Results:" << endl << endl;

    cout << "X(N) = [";
    for (int i = 0; i < N; i++) {
        matrix[i].printComplex();
        if(i!=(N-1)) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    cout<<"Magnitudes = [";
    for(int i = 0; i<N; i++){
        cout <<calculateMag(matrix[i]);
        if(i!=(N-1)) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    cout<<"Phases = [";
    for(int i = 0; i<N; i++){
        cout <<calculatePhase(matrix[i]);
        if(i!=(N-1)) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int main()
{
    cout<<"DFT Calculator"<<endl<<endl;

    cout << "Enter the number of N-Points:"<<endl;
    int N;
    cin >>  N;

    Complex omegaNHolder[N*N];
    Complex outputHolder[N];

    Complex* omegaNMatrix = omegaNInflator(omegaNHolder, N);
    printOmegaN(omegaNMatrix, N);
    Complex* results = calculateDFT(omegaNMatrix, outputHolder, N);
    printResults(results, N);
}

