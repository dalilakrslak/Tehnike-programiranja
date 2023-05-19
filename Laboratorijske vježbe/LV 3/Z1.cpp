//TP 2021/2022: LV 3, Zadatak 1
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
            for(int i: b) std::cout<<i<<" ";
        }
        if(c.size()==0) std::cout<<std::endl;
        else{
            for(int i: c) std::cout<<i<<" ";
        }
    }
	return 0;
}
