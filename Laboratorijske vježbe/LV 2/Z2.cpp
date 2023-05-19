//TP 2020/2021: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>
bool TestPerioda(std::vector<double> v, int p){
    if(v.size()<=p || p==0) return false;
    for(int i=0;i<v.size()-p;i++){
        if(v.at(i)!=v.at(i+p)) return false;
    }
    return true;
}
int OdrediOsnovniPeriod(std::vector<double> v){
    for(int p=0;p<v.size();p++){
        if(TestPerioda(v, p)) return p;
    }
    return 0;
}
int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    double x;
    std::cin>>x;
    std::vector<double> v;
    while(x!=0){
        v.push_back(x);
        std::cin>>x;
    }
    int p=OdrediOsnovniPeriod(v);
    if(p==0) std::cout<<"Slijed nije periodican!"<<std::endl;
    else std::cout<<"Slijed je periodican sa osnovnim periodom "<<p<<"."<<std::endl;
    return 0;
}
