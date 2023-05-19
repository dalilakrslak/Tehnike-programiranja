//TP 2021/2022: Zadaća 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <array>
#include <string>
typedef std::vector<std::vector<double>> Matrica;
typedef std::array<Matrica, 2> ModerniNiz;
Matrica KreirajMatricu(int br_redova, int br_kolona){
    return Matrica(br_redova, std::vector<double>(br_kolona));
}
int BrojRedova(Matrica m){
    return m.size();
}
int BrojKolona (Matrica m){
    if(m.size()!=0) return m.at(0).size();
    return 0;
}
bool MoguSeMnoziti (Matrica m1, Matrica m2){
    return BrojKolona(m1)==BrojRedova(m2);
}
bool IstiBrojElemenata(Matrica m){
    if(m.size()==0) return true;
    int red1=m.at(0).size();
    for(int i=0; i<BrojRedova(m); i++){
        if(red1!=m.at(i).size()) return false;
    }
    return true;
}
Matrica MnozenjeMatrica(Matrica m1, Matrica m2){
    if(!IstiBrojElemenata(m1) || !IstiBrojElemenata(m2)) throw std::domain_error("Neispravna matrica!");
    if(!MoguSeMnoziti(m1, m2)) throw std::domain_error("Matrice nisu saglasne za mnozenje!");
    auto m3=KreirajMatricu(BrojRedova(m1), BrojKolona(m2));
    for(int i=0; i<BrojRedova(m1); i++){
        for(int j=0; j<BrojKolona(m2); j++){
            double suma=0;
            for(int k=0; k<BrojRedova(m2); k++) suma+=m1.at(i).at(k)*m2.at(k).at(j);
            m3.at(i).at(j)=suma;
        }
    }
    return m3;
}
ModerniNiz DoolittleLU (Matrica H){
    if(BrojKolona(H)!=BrojRedova(H)) throw std::domain_error("Matrica mora biti kvadratna!");
    if(!IstiBrojElemenata(H)) throw std::domain_error("Neispravna matrica!");
    int n=BrojRedova(H);
    Matrica L=KreirajMatricu(n, n);
    Matrica U=KreirajMatricu(n, n);
    const long double epsilon=0.0000000001;
    for(int i=0; i<n; i++){
        for(int j=0; j<i;j++){
            double suma=0;
            for(int k=0; k<j; k++) suma+=L.at(i).at(k)*U.at(k).at(j);
            L.at(i).at(j)=(H.at(i).at(j)-suma)/U.at(j).at(j);
        }
        for(int j=i; j<n; j++){
            if(j==i) L.at(i).at(j)=1;
            double suma=0;
            for(int m=0; m<i; m++) suma+=L.at(i).at(m)*U.at(m).at(j);
            U.at(i).at(j)=H.at(i).at(j)-suma;
            if(std::fabs(U.at(i).at(i))<epsilon) throw std::domain_error("Matrica je singularna!");
        }
    }
    ModerniNiz LU;
    LU.at(0)=L;
    LU.at(1)=U;
    return LU;
}
bool ProvjeriFaktorizaciju (Matrica H, ModerniNiz LU){
    const long double epsilon=0.0000000001;
    if(BrojRedova(H)!=BrojKolona(H) || !IstiBrojElemenata(H)) return false;
    int n=BrojRedova(H);
    if(BrojRedova(LU.at(0))!=n || BrojKolona(LU.at(0))!=n || BrojRedova(LU.at(1))!=n || BrojKolona(LU.at(1))!=n) return false;
    auto pom=MnozenjeMatrica(LU.at(0), LU.at(1));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!(std::fabs(H.at(i).at(j)-pom.at(i).at(j))<epsilon)) return false;
        }
    }
    return true;
}
int main ()
{
    try{
        int n=0;
        std::cout<<"Broj redova/kolona matrice: ";
        std::cin>>n;
        auto H=KreirajMatricu(n, n);
        std::cout<<"Elementi matrice: ";
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                std::cin>>H.at(i).at(j);
            }
        }
        ModerniNiz LU=DoolittleLU(H);
        std::cout<<std::endl<<std::endl<<"Matrica L:"<<std::endl;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                std::cout<<LU.at(0).at(i).at(j)<<" ";
            }
            std::cout<<std::endl;
        }  
        std::cout<<std::endl<<"Matrica U:"<<std::endl;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                std::cout<<LU.at(1).at(i).at(j)<<" ";
            }
            std::cout<<std::endl;
        }
    }
    catch(std::domain_error greska){
        std::string ispis=greska.what();
        if(ispis=="Matrica je singularna!") std::cout<<std::endl<<"LU faktorizacija ne postoji, jer je matrica singularna!";
        else std::cout<<ispis;
    }
	return 0;
}
