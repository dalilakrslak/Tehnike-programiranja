//TP 2021/2022: LV 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
int SumaCifara(int x){
    int suma=0;
    while(x!=0){
        int cifra=x%10;
        x/=10;
        suma+=cifra;
    }
    return suma;
}
std::vector<int> IzdvojiElemente(std::vector<int> v, bool paran){
    std::vector<int> vektor;
    if(paran){
        for(int i: v){
            if(SumaCifara(i)%2==0) vektor.push_back(i);
        }
    }
    else{
        for(int i: v){
            if(SumaCifara(i)%2!=0) vektor.push_back(i);
        }
    }
    return vektor;
}
int main ()
{
    int n;
    std::cout<<"Koliko zelite unijeti elemenata: ";
    std::cin>>n;
    if(n<=0) std::cout<<"Broj elemenata mora biti veci od 0!"<<std::endl;
    else{
        std::cout<<"Unesite elemente: ";
        int x;
        std::vector<int> a;
        for(int i=0; i<n; i++){
            std::cin>>x;
            a.push_back(x);
        }
        std::vector<int> b=IzdvojiElemente(a, 1);
        std::vector<int> c=IzdvojiElemente(a, 0);
        if(b.size()==0) std::cout<<std::endl;
        else{
            for(int i=0; i<b.size(); i++){
                if(i==b.size()-1) std::cout<<b.at(i)<<std::endl;
                else std::cout<<b.at(i)<<",";
            }
        }
        if(c.size()==0) std::cout<<std::endl;
        else{
            for(int i=0; i<c.size(); i++){
                if(i==c.size()-1) std::cout<<c.at(i)<<std::endl;
                else std::cout<<c.at(i)<<",";
            }
        }
    }
	return 0;
}
