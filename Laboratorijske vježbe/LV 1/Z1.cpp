//TP 2016/2017: LV 1, Zadatak 1
#include <iostream>
#include <cmath>
int main ()
{
    int a,b,c;
    std::cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    std::cin>>a>>b>>c;
    int d;
    std::cout<<"Unesite sirinu plocice u centimetrima: ";
    std::cin>>d;
    int pov_bazena=(a*b+2*a*c+2*b*c)*10000;
    int pov_plocice=std::pow(d,2);
    if(pov_bazena%pov_plocice==0 && (a*100)%d==0 && (b*100)%d==0 && (c*100)%d==0){
        int broj_plocica=pov_bazena/pov_plocice;
        std::cout<<std::endl<<"Za poplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<std::endl<<"potrebno je "<<broj_plocica<<" plocica.";
    }
    else std::cout<<std::endl<<"Poplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<std::endl<<"nije izvodljivo bez lomljenja plocica!";
	return 0;
}