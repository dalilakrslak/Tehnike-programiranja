//TP 2021/2022: Zadaća 2, Zadatak 4
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
template <typename Tip>
bool Kriterij(std::vector<Tip> v1, std::vector<Tip> v2){
    auto suma1=Tip(), suma2=Tip();
    for(auto &pom: v1) suma1+=pom;
    for(auto &pom: v2) suma2+=pom;
    if (suma1==suma2) return v1>v2;
    return suma1>suma2;
}
template <typename Tip>
void SortirajPoSumiRedova (std::vector<std::vector<Tip>> &m){
    sort(m.begin(),m.end(),Kriterij<Tip>);
}
int main ()
{
    std::cout<<"Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa):";
    std::vector<std::vector<int>> m;
    for(int i=0; ; i++){
        bool kraj=false;
        for(int j=0; ; j++){
            int x;
            std::cin>>x;
            if(!std::cin){
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                if(j==0) kraj=true;
                break;
            }
            m.resize(i+1);
            m.at(i).push_back(x);
        }
        if(kraj) break;
    }
    std::cout<<std::endl<<"Matrica nakon sortiranja: "<<std::endl;
    SortirajPoSumiRedova(m);
    for(int i=0; i<m.size(); i++){
        for(int j=0; j<m.at(i).size(); j++){
            std::cout<<m.at(i).at(j)<<" ";
        }
        std::cout<<std::endl;
    }
	return 0;
}
