//TP 2020/2021: Tutorijal 2, Zadatak 5
#include <iostream>
#include <complex>
#include <cmath>
int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>n;
    std::complex<double>Zk,suma;
    double Zpom,fi,faza;
    std::cout<<std::endl;
    const double PI=4*std::atan(1);
    for(int i=0;i<n;i++){
        std::cout<<"Z"<<i+1<<" = ";
        std::cin>>Zpom;
        std::cout<<"fi"<<i+1<<" = ";
        std::cin>>fi;
        faza=(fi*PI)/180;
        std::cout<<std::endl;
        Zk=std::polar(Zpom,faza);
        suma+=double(1)/Zk;
    }
    std::complex<double>Z=double(1)/suma;
    std::cout<<"Paralelna veza ovih elemenata ima Z = "<<std::abs(Z)<<" i fi = "<<std::arg(Z)*180/PI<<"."<<std::endl;
    return 0;
}
