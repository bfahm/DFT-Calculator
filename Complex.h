//
// Created by Bola on 11/16/2018.
//

#pragma once
#include <iostream>

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

    Complex add(const Complex& c){
        Complex comp;
        comp.real = this->real + c.real;
        comp.img = this->img + c.img;
        return comp;
    }

    Complex subtract(const Complex& c){
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
