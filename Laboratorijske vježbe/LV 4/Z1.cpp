//TP 2021/2022: LV 4, Zadatak 1
#include <iostream>
#include <cmath>
int Cifre(long long int n, int &c_min, int &c_max){
    int br_cifri=0;
    c_min=std::fabs(n%10);
    c_max=std::fabs(n%10);
    do{
        int cifra=std::fabs(n%10);
        if(cifra<c_min) c_min=cifra;
        if(cifra>c_max) c_max=cifra;
        n/=10;
        br_cifri++;
    } while(n!=0);
    return br_cifri;
}
int main ()
{
    long long int n;
    std::cout<<"Unesite broj: ";
    std::cin>>n;
    int min, max;
    int cifre=Cifre(n, min, max);
    std::cout<<"Broj "<<n<<" ima "<<cifre<<" cifara, najveca je "<<max<<" a najmanja "<<min<<".";
	return 0;
}
