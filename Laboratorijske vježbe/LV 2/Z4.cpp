//TP 2020/2021: Tutorijal 2, Zadatak 4
#include <iostream>
#include <complex>

int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>n;
    std::complex<double>Zk,suma;
    double R,X;
    std::cout<<std::endl;
    for(int i=0;i<n;i++){
        std::cout<<"R"<<i+1<<" = ";
        std::cin>>R;
        std::cout<<"X"<<i+1<<" = ";
        std::cin>>X;
        std::cout<<std::endl;
        Zk=std::complex<double>(R,X);
        suma+=double(1)/Zk;
    }
    std::complex<double>Z=double(1)/suma;
    std::cout<<"Paralelna veza ovih elemenata ima R = "<<Z.real()<<" i X = "<<Z.imag()<<"."<<std::endl;
    return 0;
}
