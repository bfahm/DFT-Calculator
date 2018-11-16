#include <iostream>
#include <cmath>
#include "Complex.h"

#define PI 3.14159265
using namespace std;


Complex omegaNValue (int k, int n, int N){
    /*
     * Function Return 1 if k*n equals 0(without doing further calculations)
     * If not: */
    if (k*n != 0){
        int angle = (2*180/(N))* k * n;                     // Get the angle using the right formula
        double validRadian = angle*PI/180;                  // Convert it to Radian

        double cosResult = cos(validRadian);                // We use cos(theta) + j sin(theta) instead of the
        if (abs(cosResult) < 0.0000001) cosResult = 0;      // exponential form.
        double sinResult = sin(validRadian);
        if (abs(sinResult) < 0.0000001) sinResult = 0;      // If number is too small, just reset it to zero
        Complex result (cosResult,-sinResult);              // Create a Complex object of the number we just calculated

        return result;
    }
    return 1;
}

Complex* omegaNInflator (Complex omegaNMatrix[], int N) {
    /*
     * This function uses the @omegaNValue function to fill the omegaN matrix
     * NOTE: Instead of using n and k, we just use N
     * NOTE: Instead of having to deal with multidimensional array (not junior-developer-friendly) we just convert
     *        the it two 1D array
     * Parameters:  - empty matrix that will be filled,
     *              - number of N-points, useful to replace n and k with. */
    int counter = 0;                                      // Used for iterating through the empty matrix and filling it

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            omegaNMatrix[counter] = omegaNValue(i, j, N); // Nested for loop is used to come up with different
            counter += 1;                                 // combinations of numbers (0,0) - (0,1) - (1,2) - (3,1)
        }
    }
    return omegaNMatrix;                                  // Return the filled Matrix.
}

Complex* calculateDFT (Complex omegaNMatrix[],int xnMatrix[], Complex multiplicationOutput[], int N) {
    /*
     * The Main Operating Function,
     * Used to multiply Wn*x(N)
     * Parameters:  -Wn Matrix
     *              -x(n) Matrix
     *              -empty Matrix to be filled with result
     *              -N-points*/

    int offset = 0;                         // offset to enter new row after each iteration
    Complex singleRowResult = 0;            // results of a single row,
    for (int i = 0; i < N; i++) {           // 'i' for loop used to iterate over each row
        for (int j = 0; j < N; j++) {       // 'j' for loop used to iterate over each element from both matrices
            singleRowResult = singleRowResult.add(omegaNMatrix[j + offset].multiply(xnMatrix[j]));
        }                                   // ex: (x1*y1), (x2*y2) where 1, 2 represent 'j'
        multiplicationOutput[i] = singleRowResult;
        singleRowResult = 0;                // reset and reuse next row
        offset += N;                        // access next row
    }
    return multiplicationOutput;
}

double calculateMag(Complex number){
    /*
     * Calculate Magnitude of given complex number after splitting to real and imaginary components
     * */
    double real = number.returnReal();
    double img = number.returnImg();
    return sqrt(pow(real, 2)+pow(img,2));
}

double calculatePhase(Complex number){
    /*
     * Calculate Phase of given complex number after splitting to real and imaginary components
     * */
    double real = number.returnReal();
    double img = number.returnImg();
    double theta = img/real;
    double result = atan (theta) * 180 / PI;    // atan = inverse tan
    /*if(result<0){
        result+=180;
    }else*/ if(result == -0){                   // disabled adding 0.5PI to display accurate raw results
        result = 0;                             // change at will...
    }
    return result;
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
    cout << "-----------------------------------------------------------------------------------------" << endl<< endl ;
    cout <<"Printing Results:" << endl<<endl;

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

    int xnMatrix[N];
    cout << endl <<  "Enter X(N) values:" << endl;
    cout << N << " values needed" << endl;
    cout << "Continue with ZEROS '0' if you want to enter number of Xs less than N-point Number" << endl;
    for (int i = 0; i < N; i++) {
        cin >> xnMatrix[i];
    }
    cout << "Successfully Entered x(N) values." << endl;

    /*
     * Initialize empty arrays to be passed and used in functions.
     * */
    Complex omegaNHolder[N*N];
    Complex outputHolder[N];

    Complex* omegaNMatrix = omegaNInflator(omegaNHolder, N);
    printOmegaN(omegaNMatrix, N);
    Complex* results = calculateDFT(omegaNMatrix, xnMatrix, outputHolder, N);
    printResults(results, N);
}

