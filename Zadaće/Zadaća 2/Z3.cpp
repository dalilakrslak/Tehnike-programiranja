//TP 2021/2022: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <type_traits>
#include <vector>
#include <utility>
template <typename Tip1, typename Tip2>
auto ZbirKontejnera(Tip1 kontejner1, Tip2 kontejner2){
    auto p1=kontejner1.begin(), k1=kontejner1.end();
    auto p2=kontejner2.begin(), k2=kontejner2.end();
    std::vector<decltype(*p1+*p2)> vrati;
    int vel1(0), vel2(0), vel(0);
    while(p1!=k1){
        vel1++;
        p1++;
    }
    p1=kontejner1.begin();
    while(p2!=k2){
        vel2++;
        p2++;
    }
    p2=kontejner2.begin();
    int i=0;
    if(vel1==vel2){
        vrati.resize(vel1);
        while(p1!=k1 && p2!=k2){
            vrati.at(i)=*p1+*p2;
            p1++;
            p2++;
            i++;
        }
    }
    else if(vel1>vel2){
        vrati.resize(vel1);
        while(p1!=k1){
            vrati.at(i)=*p1+*p2;
            p1++;
            p2++;
            i++;
            if(p2==k2 && p1!=k1){
                typename std::remove_reference_t<decltype(*p2)> dodani{};
                while(p1!=k1){
                    vrati.at(i)=*p1+dodani;
                    p1++;
                    i++;
                }
                break;
            }
        }
    }
    else{
        vrati.resize(vel2);
        while(p2!=k2){
            vrati.at(i)=*p1+*p2;
            p1++;
            p2++;
            i++;
            if(p1==k1 && p2!=k2){
                typename std::remove_reference_t<decltype(*p1)> dodani{};
                while(p2!=k2){
                    vrati.at(i)=*p2+dodani;
                    p2++;
                    i++;
                }
                break;
            }
        }
    }
    return vrati;
}
int main ()
{
    std::cout<<"Duzina prvog kontejnera: ";
    int vel1;
    std::cin>>vel1;
    std::cout<<"Elementi prvog kontejnera: ";
    std::vector<double> v1(vel1);
    for(double &pom: v1) std::cin>>pom;
    std::cout<<"Duzina drugog kontejnera: ";
    int vel2;
    std::cin>>vel2;
    std::cout<<"Elementi drugog kontejnera: ";
    std::vector<double> v2(vel2);
    for(double &pom: v2) std::cin>>pom;
    auto zbir=ZbirKontejnera(v1, v2);
    std::cout<<"Zbir kontejnera: ";
    for(auto pom: zbir) std::cout<<pom<<" ";
	return 0;
}
