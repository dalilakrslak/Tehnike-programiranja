//TP 2021/2022: LV 4, Zadatak 5
#include <iostream>
#include <cmath>
#include <vector>
template <typename NekiTip>
 std::vector<NekiTip> Presjek(std::vector<NekiTip> v1, std::vector<NekiTip> v2){
     std::vector<NekiTip> v;
     for(int i=0; i<v1.size(); i++){
         bool jednaki=0;
         for(int j=0; j<v2.size(); j++){
             if(v1.at(i)==v2.at(j)) jednaki=1;
         }
         if(jednaki){
             bool ponavljanje=0;
             for(int j=0; j<v.size(); j++){
                 if(v1.at(i)==v.at(j)) ponavljanje=1;
             }
             if(!ponavljanje) v.push_back(v1.at(i));
         }
     }
     return v;
 }
int main ()
{
    std::cout<<"Test za realne brojeve..."<<std::endl;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    int n1;
    std::cin>>n1;
    std::vector<double> v1;
    std::cout<<"Unesite elemente prvog vektora: ";
    for(int i=0; i<n1; i++){
        double pom;
        std::cin>>pom;
        v1.push_back(pom);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    int n2;
    std::cin>>n2;
    std::vector<double> v2;
    std::cout<<"Unesite elemente drugog vektora: ";
    for(int i=0; i<n2; i++){
        double pom;
        std::cin>>pom;
        v2.push_back(pom);
    }
    std::vector<double> v=Presjek(v1, v2);
    std::cout<<"Zajednicki elementi su: ";
    for(double x: v) std::cout<<x<<" ";
    std::cout<<std::endl;
    std::cout<<std::endl<<"Test za stringove..."<<std::endl;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    int vel1;
    std::cin>>vel1;
    std::vector<std::string> s1;
    std::cout<<"Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";
    for(int i=0; i<=vel1; i++){
        std::string pom;
        getline(std::cin, pom);
        s1.push_back(pom);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    int vel2;
    std::cin>>vel2;
    std::vector<std::string> s2;
    std::cout<<"Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
    for(int i=0; i<=vel2; i++){
        std::string pom;
        getline(std::cin, pom);
        s2.push_back(pom);
    }
    std::vector<std::string> s=Presjek(s1, s2);
    std::cout<<"Zajednicki elementi su: ";
    for(std::string x: s) std::cout<<x<<std::endl;
	return 0;
}
