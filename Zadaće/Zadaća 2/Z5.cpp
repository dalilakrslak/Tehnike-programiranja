//TP 2021/2022: Zadaća 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <deque>
#include <list>
#include <string>
template <typename TipElemenata>
void UnistiMatricu(TipElemenata **mat, int br_redova){
    if(!mat) return;
    for(int i=0; i<br_redova; i++) delete [] mat[i];
    delete [] mat;
}
template <typename TipElemenata>
TipElemenata **StvoriMatricu(int br_redova, int br_kolona){
    TipElemenata **mat=new TipElemenata*[br_redova]{};
    try{
        for(int i=0; i<br_redova; i++) mat[i]=new TipElemenata[br_kolona];
    }
    catch(...){
        UnistiMatricu(mat, br_redova);
        throw;
    }
    return mat;
}
template <typename Tip1, typename Tip2, typename TipFje>
auto GeneraliziraniSpoljasnjiProizvod(Tip1 a1, Tip1 a2, Tip2 b1, Tip2 b2, TipFje f){
    decltype(f(*a1,*b1)) **mat=nullptr;
    Tip1 p1=a1, k1=a2;
    Tip2 p2=b1, k2=b2;
    int vel1(0), vel2(0);
    while(p1!=k1){
        vel1++;
        p1++;
    }
    p1=a1;
    while(p2!=k2){
        vel2++;
        p2++;
    }
    p2=b1;
    try{
        mat=StvoriMatricu<decltype(f(*a1,*b1))>(vel1, vel2);
        int i=0;
        while(p1!=k1){
            int j=0;
            while(p2!=k2){
                mat[i][j]=f(*p1,*p2);
                j++;
                p2++;
            }
            i++;
            p1++;
            p2=b1;
        }
    }
    catch(...){
        throw std::range_error("Nema dovoljno memorije!");
    }
    return mat;
}
int main ()
{
    std::cout<<"Duzina prve sekvence: ";
    int vel1;
    std::cin>>vel1;
    std::cout<<"Elementi prve sekvence: ";
    std::vector<double> v(vel1);
    for(double &pom: v) std::cin>>pom;
    std::cout<<"Duzina druge sekvence: ";
    int vel2;
    std::cin>>vel2;
    std::cout<<"Elementi druge sekvence: ";
    std::deque<double> d(vel2);
    for(double &pom: d) std::cin>>pom;
    std::cout<<"Generalizirani spoljasnji proizvod uz f(x,y)=x+2y: ";
    try{
        auto mat=GeneraliziraniSpoljasnjiProizvod(v.begin(), v.end(), d.begin(), d.end(), [](double x, double y){return x+2*y;});
        for(int i{}; i<v.size(); i++){
            for(int j{}; j<d.size(); j++){
                std::cout<<mat[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        UnistiMatricu(mat, vel1);
    }
    catch(std::range_error greska){
        std::cout<<greska.what();
    }
	return 0;
}
