//TP 2020/2021: Tutorijal 2, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>
bool DaLiJeProst(int n){
    if(n<2) return false;
    for(int i=2;i<=std::sqrt(n);i++){
        if(n%i==0) return false;
    }
    return true;
}
std::vector<int> ProstiBrojeviUOpsegu(int a, int b){
    std::vector<int> prosti;
    for(int i=a;i<b;i++){
        if(DaLiJeProst(i)) prosti.push_back(i);
    }
    if(DaLiJeProst(b)) prosti.push_back(b);
    return prosti;
}
int main ()
{
    int a,b;
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>a>>b;
    std::vector<int> prosti;
    prosti=ProstiBrojeviUOpsegu(a, b);
    if(prosti.size()==0) std::cout<<"Nema prostih brojeva u rasponu od "<<a<<" do "<<b<<"!";
    else{
        std::cout<<"Prosti brojevi u rasponu od "<<a<<" do "<<b<<" su: ";
        for(int i=0; i<prosti.size(); i++){
            if(i==prosti.size()-1) std::cout<<prosti.at(i)<<std::endl;
            else std::cout<<prosti.at(i)<<", ";
        }
    }
    return 0;
}
