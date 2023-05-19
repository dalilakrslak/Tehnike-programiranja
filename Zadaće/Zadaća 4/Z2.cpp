//TP 2021/2022: Zadaća 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <tuple>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
const double PI=4*std::atan(1);
const double EPSILON=std::pow(10,-10);
class NepreklapajucaKugla{
    double x,y,z,r;
    NepreklapajucaKugla *prethodnik;
    static NepreklapajucaKugla *zadnji;
public:
    explicit NepreklapajucaKugla(double r=0){
        if(zadnji!=nullptr){
            PostaviPoluprecnik(r);
            PostaviX(0); PostaviY(0); PostaviZ(0);
            prethodnik=zadnji;
            zadnji=this;
        }
        else{
            PostaviPoluprecnik(r);
            PostaviX(0); PostaviY(0); PostaviZ(0);
            prethodnik=nullptr;
            zadnji=this;
        }
    }
    NepreklapajucaKugla(double x, double y, double z, double r=0){
        if(zadnji!=nullptr){
            PostaviPoluprecnik(r);
            PostaviX(x); PostaviY(y); PostaviZ(z);
            prethodnik=zadnji;
            zadnji=this;
        }
        else{
            PostaviX(x); PostaviY(y); PostaviZ(z);
            PostaviPoluprecnik(r);
            prethodnik=nullptr;
            zadnji=this;
        }
    }
    explicit NepreklapajucaKugla(const std::tuple<double, double, double> &centar, double r=0){
        if(zadnji!=nullptr){
            x=std::get<0>(centar);
            y=std::get<1>(centar);
            z=std::get<2>(centar);
            NepreklapajucaKugla::r=r;
            prethodnik=zadnji;
            zadnji=this;
        }
        else{
            x=std::get<0>(centar);
            y=std::get<1>(centar);
            z=std::get<2>(centar);
            NepreklapajucaKugla::r=r;
            prethodnik=nullptr;
            zadnji=this;
        }
    }
    ~NepreklapajucaKugla(){
        if(zadnji==this) zadnji=prethodnik;
        if(this->prethodnik!=nullptr){
            auto pom=zadnji;
            while(pom!=nullptr){
                if(pom!=nullptr && pom->prethodnik==this) pom->prethodnik=this->prethodnik;
                pom=pom->prethodnik;
            }
        }
        else{ 
            auto pom=zadnji;
            while(pom!=nullptr){
                if(pom!=nullptr && pom->prethodnik==this) pom->prethodnik=nullptr;
                pom=pom->prethodnik;
            }
        }
    }
    double DajX() const{
        return x;
    }
    double DajY() const{
        return y;
    }
    double DajZ() const{
        return z;
    }
    std::tuple<double, double, double> DajCentar() const{
        std::tuple<double, double, double> centar;
        std::get<0>(centar)=x; std::get<1>(centar)=y; std::get<2>(centar)=z;
        return centar;
    }
    double DajPoluprecnik() const{
        return r;
    }
    double DajPovrsinu() const{
        return 4*r*r*PI;
    }
    double DajZapreminu() const{
        return (4/3.)*r*r*r*PI;
    }
    NepreklapajucaKugla &PostaviX(double x){
        NepreklapajucaKugla::x=x;
        return *this;
    }
    NepreklapajucaKugla &PostaviY(double y){
        NepreklapajucaKugla::y=y;
        return *this;
    }
    NepreklapajucaKugla &PostaviZ(double z){
        NepreklapajucaKugla::z=z;
        return *this;
    }
    NepreklapajucaKugla &PostaviCentar(double x, double y, double z){
        PostaviX(x);
        PostaviY(y);
        PostaviZ(z);
        return *this;
    }
    NepreklapajucaKugla &PostaviCentar(const std::tuple<double, double, double> &centar){
        PostaviX(std::get<0>(centar));
        PostaviY(std::get<1>(centar));
        PostaviZ(std::get<2>(centar));
        return *this;
    }
    NepreklapajucaKugla &PostaviPoluprecnik(double r){
        if(r<0) throw std::domain_error("Ilegalan poluprecnik");
        NepreklapajucaKugla::r=r;
        return *this;
    }
    void Ispisi() const{
        std::cout<<"{("<<x<<","<<y<<","<<z<<"),"<<r<<"}"<<std::endl;
    }
    void Transliraj(double delta_x, double delta_y, double delta_z){
        x+=delta_x;
        y+=delta_y;
        z+=delta_z;
    }
    bool DaLiSadrzi(const NepreklapajucaKugla &k) const{
        double razmak=std::sqrt(std::pow(x-k.x,2)+std::pow(y-k.y,2)+std::pow(z-k.z,2));
        return(r-k.r-razmak>EPSILON || std::fabs(r-k.r-razmak)<EPSILON);
    }
    friend double RastojanjeCentara(const NepreklapajucaKugla &k1, const NepreklapajucaKugla &k2);
};
NepreklapajucaKugla* NepreklapajucaKugla::zadnji=nullptr;
double RastojanjeCentara(const NepreklapajucaKugla &k1, const NepreklapajucaKugla &k2){
    return std::sqrt(std::pow(k1.x-k2.x,2)+std::pow(k1.y-k2.y,2)+std::pow(k1.z-k2.z,2));
}
int main ()
{
    /*int broj_kugli;
    std::cout<<"Unesite broj kugli: ";
    std::cin>>broj_kugli;
    while(broj_kugli<=0){
        std::cout<<"Neispravan broj kugli, unesite ponovo!"<<std::endl;
        std::cin>>broj_kugli;
    }
    std::vector<std::shared_ptr<NepreklapajucaKugla>> v(broj_kugli);
    for(int i=0; i<broj_kugli; i++){
        double x,y,z;
        std::cout<<"Unesite centar za "<<i+1<<". kuglu: ";
        std::cin>>x>>y>>z;
        while(!std::cin){
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            std::cout<<"Neispravan centar, unesite ponovo: ";
            std::cin>>x>>y>>z;
        }
        double r;
        std::cout<<"Unesite poluprecnik: ";
        std::cin>>r;
        while(r<0 || !std::cin){
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            std::cout<<"Neispravan poluprecnik, unesite ponovo: ";
            std::cin>>r;
        }
        try{
            v[i]=std::make_shared<NepreklapajucaKugla>(x,y,z,r);
        }
        catch(...){
            i--;
        }
    }
    */
	return 0;
}
