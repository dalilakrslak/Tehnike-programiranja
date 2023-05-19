//TP 2021/2022: LV 3, Zadatak 4
#include <iostream>
#include <cmath>
#include <deque>
int SumaCifara(int x){
    int suma=0;
    while(x!=0){
        int cifra=x%10;
        x/=10;
        suma+=cifra;
    }
    return suma;
}
std::deque<int> IzdvojiElemente(std::deque<int> d, bool paran){
    std::deque<int> dek;
    if(paran){
        for(int i: d){
            if(SumaCifara(i)%2==0) dek.push_front(i);
        }
    }
    else{
        for(int i: d){
            if(SumaCifara(i)%2!=0) dek.push_front(i);
        }
    }
    return dek;
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
        std::deque<int> a;
        for(int i=0; i<n; i++){
            std::cin>>x;
            a.push_back(x);
        }
        std::deque<int> b=IzdvojiElemente(a, 1);
        std::deque<int> c=IzdvojiElemente(a, 0);
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

