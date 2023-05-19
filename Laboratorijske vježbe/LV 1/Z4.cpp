//TP 2016/2017: LV 1, Zadatak 4
#include <iostream>
#include <cmath>
int main ()
{
    double n;
    std::cout<<"Unesite prirodan broj ili 0 za kraj: ";
    std::cin>>n;
    double ostatak=n-int(n);
    while(n!=0 || !std::cin){
        if(!std::cin || n<0 || ostatak!=0){
            std::cout<<"Niste unijeli prirodan broj!"<<std::endl;
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        }
        else{
            int suma=0;
            for(int i=1;i<n;i++){
                if(int(n)%i==0) suma+=i;
            }
            if(suma<n) std::cout<<"Broj "<<n<<" je manjkav!"<<std::endl;
            else if(suma==n) std::cout<<"Broj "<<n<<" je savrsen!"<<std::endl;
            else if(suma>n) std::cout<<"Broj "<<n<<" je obilan!"<<std::endl;
        }
        std::cout<<"Unesite prirodan broj ili 0 za kraj: ";
        std::cin>>n;
        ostatak=n-int(n);
    }
    if(n==0) std::cout<<"Dovidjenja!";
	return 0;
}