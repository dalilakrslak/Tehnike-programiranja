//TP 2021/2022: Zadaća 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
int CiklickaPermutacija(std::vector<int> v1, std::vector<int> v2){
    if(v1.size()!=v2.size()) return -1;
    if(v1==v2) return 0;
    int vel=v1.size();
    bool uslov=0;
    int pomak=0;
    for(int i=vel-1; i>=0; i--){
        if(v2.at(0)==v1.at(i)){
            int pom=0;
            int pom1=i;
            int pom2=0;
            while(v1.at(pom1)==v2.at(pom2)){
                if(pom1==vel-1 || pom2==vel-1){
                    pom++;
                    pom2++;
                    int j=0;
                    while(v1.at(j)==v2.at(pom2)){
                        if(j==vel-1 || pom2==vel-1){
                            uslov=1;
                            pomak=vel-pom;
                            break;
                        }
                        pom2++;
                        j++;
                    }
                    break;
                }
                pom1++;
                pom2++;
                pom++;
            }
        }
    }
    if(uslov) return pomak;
    return -1;
}
int main ()
{
    std::cout<<"Prva sekvenca: ";
    int x;
    std::vector<int> v1;
    while(std::cin>>x && x!='.'){
        v1.push_back(x);
    }
    std::cin.clear();
    std::cin.ignore(1000,'\n');
    std::cout<<"Druga sekvenca: ";
    std::vector<int> v2;
    while(std::cin>>x && x!='.'){
        v2.push_back(x);
    }
    std::cin.clear();
    std::cin.ignore(1000,'\n');
    int pomak=CiklickaPermutacija(v1,v2);
    if(pomak!=-1) std::cout<<"Druga sekvenca je ciklicka permutacija prve s pomakom "<<pomak<<".";
    else std::cout<<"Druga sekvenca nije ciklicka permutacija prve.";
	return 0;
}
