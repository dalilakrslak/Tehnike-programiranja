//TP 2020/2021: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>

int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>n;
    std::complex<double>Zk,suma;
    std::cout<<std::endl;
    for(int i=0;i<n;i++){
        std::cout<<"Z_"<<i+1<<" = ";
        std::cin>>Zk;
        suma+=double(1)/Zk;
    }
    std::complex<double>Z=double(1)/suma;
    std::cout<<std::endl<<"Paralelna veza ovih elemenata ima impedansu Z_ = "<<Z<<"."<<std::endl;
    return 0;
}
