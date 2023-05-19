//TP 2021/2022: LV 3, Zadatak 7
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
typedef std::vector<std::vector<int>> Matrica;
Matrica PascalovTrougao(int n){
    Matrica trougao;
    if(n==0) return trougao;
    if(n<0) throw std::domain_error("Broj redova ne smije biti negativan");
    trougao.resize(n);
    for(int i=0; i<n; i++) trougao.at(i).resize(i+1);
    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            if(i==0 || j==0 || j==i) trougao.at(i).at(j)=1;
            else trougao.at(i).at(j)=trougao.at(i-1).at(j)+trougao.at(i-1).at(j-1);
        }
    }
    return trougao;
}
int NajvecaSirina(Matrica mat){
    int pom, najveca=0;
    for(std::vector<int> i: mat){
        for(int j: i){
            pom=0;
            if(j<0) pom++;
            while(j!=0){
                j/=10;
                pom++;
            }
            if(pom>najveca) najveca=pom;
        }
    }
    return najveca;
}
int main ()
{
    try{
        int n;
        std::cout<<"Unesite broj redova: ";
        std::cin>>n;
        Matrica proizvod=PascalovTrougao(n);
        int sirina=NajvecaSirina(proizvod);
        for(std::vector<int>i: proizvod){
            for(int j: i) std::cout<<std::setw(sirina+1)<<std::right<<j;
            std::cout<<std::endl;
        }
    }
    catch(std::domain_error izuzetak){
        std::cout<<izuzetak.what();
    }
	return 0;
}
