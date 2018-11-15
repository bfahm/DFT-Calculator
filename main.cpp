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

    double returnReal(void)
    {
        return this->real;
    }
    double returnImg(void)
    {
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
    void printComplex(void)
    {
        if (this->img>0) {
            if(this->img==1){
                cout << this->real << " + j";
            }else {
                cout << this->real << " + j" << this->img;
            }
        }else if(this->img<0){
            if(this->img==-1){
                cout << this->real << " - j";
            }else {
                cout << this->real << " - j" << this->img;
            }
        }else{
            cout << this->real;
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
    }
    return result;
}

Complex omegaNValue (int k, int n, int N){
    if (k*n != 0){
        double angle = (2*180/(N))* k * n;
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

Complex omegaNMatrix (int N, int toPrint, int toMultiply){
    int n = N, k = N;
    Complex matrix[k][n];
    for(int i = 0; i<n; i++){
        for(int j = 0; j<k; j++){
            matrix[i][j] = omegaNValue(i, j, N);
        }
    }
    //-----------------------------------------
    if(toPrint==1){
        cout<<"Printing Wn Matrix form:"<<endl;
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++){
                matrix[i][j].printComplex();
                cout << "\t\t\t";
            }
            cout << endl;
        }
    }else if(toPrint==2){
        cout<<"Printing Wn Vector form:"<<endl;
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++) {
                matrix[i][j].printComplex();
                cout << endl;
            }
        }
    }
    //-----------------------------------------
    if(toMultiply==1){
        int numOfInput = N;
        int userInput[numOfInput];
        cout<<"Enter X(N) values:"<<endl;
        cout<<numOfInput<<" values needed"<<endl;
        cout<<"Continue with ZEROS '0' if you want to enter number of Xs less than N-point Number"<<endl;
        for (int i = 0; i<numOfInput; i++){
            cin >> userInput[i];
        }
        //-------------------------------------
        Complex multiplicationOutput[numOfInput];
        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                multiplicationOutput[i] = multiplicationOutput[i].add(matrix[i][j].multiply(userInput[j]));
            }
        }
        cout<<"Results:"<<endl;
        cout<<"---------------------------------------------------"<<endl;
        for(int i = 0; i<numOfInput; i++){
            multiplicationOutput[i].printComplex();
            cout << endl;
        }
        //-------------------------------------
        cout<<"---------------------------------------------------"<<endl;
        cout<<"Printing Magnitudes"<<endl;
        cout<<"[";
        for(int i = 0; i<numOfInput; i++){
            cout <<calculateMag(multiplicationOutput[i]);
            cout << "\t\t";
        }
        cout << "]" << endl;
        cout<<"Printing Phases"<<endl;
        cout<<"[";
        for(int i = 0; i<numOfInput; i++){
            cout <<calculatePhase(multiplicationOutput[i]);
            cout << "\t";
        }
        cout << "]" << endl;
    }
    return matrix[k][n];
}




int main()
{
    cout << "Enter the number of N-Points:"<<endl;
    int N;
    cin >>  N;
    cout << "Do you want to show the Omega 'Wn' matrix while calculations occur?"<<endl;
    cout << "Type: \n0 for no, \n1 for yes - matrix form,\n2 for yes - vector form"<<endl;
    int toPrint;
    cin >> toPrint;
    if(toPrint!=0 && toPrint!=1 && toPrint!=2){
        cout << "Error: Wrong input type."<<endl;
        exit(0);
    }
    cout << "Do you want to show the final result (disable for testing purposes)?"<<endl;
    cout << "Type 0 for no, 1 for yes"<<endl;
    int toResult;
    cin >> toResult;
    if(toResult!=0 && toResult!=1){
        cout << "Error: Wrong input type."<<endl;
        exit(0);
    }
    cout << "-----------------------------------------------------------------" << endl;
    omegaNMatrix(N, toPrint, toResult);


}