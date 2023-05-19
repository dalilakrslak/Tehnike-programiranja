//TP 2021/2022: LV 3, Zadatak 6
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
typedef std::vector<std::vector<int>> Matrica;
Matrica KreirajMatricu(int broj_redova, int broj_kolona){
    return Matrica(broj_redova, std::vector<int>(broj_kolona));
}
Matrica KroneckerovProizvod(std::vector<int> v1, std::vector<int> v2){
    Matrica proizvod=KreirajMatricu(v1.size(), v2.size());
    for(int i=0; i<v1.size(); i++){
        for(int j=0; j<v2.size(); j++){
            proizvod.at(i).at(j)=v1.at(i)*v2.at(j);
        }
    }
    return proizvod;
} 
int NajvecaSirina(Matrica mat){
    int pom, najveca=0;
    for(std::vector<int>i: mat){
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
    int m;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    std::cin>>m;
    std::vector<int> v1;
    std::cout<<"Unesite elemente prvog vektora: ";
    for(int i=0;i<m;i++){
        int x;
        std::cin>>x;
        v1.push_back(x);
    }
    int n;
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>n;
    std::vector<int> v2;
    std::cout<<"Unesite elemente drugog vektora: ";
    for(int i=0;i<n;i++){
        int x;
        std::cin>>x;
        v2.push_back(x);
    }
    Matrica proizvod=KroneckerovProizvod(v1, v2);
    int sirina=NajvecaSirina(proizvod);
    for(std::vector<int> i: proizvod){
        for(int j: i) std::cout<<std::setw(sirina+1)<<j;
        std::cout<<std::endl;
    }
	return 0;
}
