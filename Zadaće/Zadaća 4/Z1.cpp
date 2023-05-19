//TP 2021/2022: Zadaća 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <tuple>
#include <vector>
#include <memory>
#include <algorithm>
const double PI=4*std::atan(1);
const double EPSILON=std::pow(10,-10);
class Kugla{
    double x,y,z,r;
public:
    explicit Kugla(double r=0){
        PostaviPoluprecnik(r);
        PostaviX(0); PostaviY(0); PostaviZ(0);
    }
    Kugla(double x, double y, double z, double r=0){
        PostaviX(x);
        PostaviY(y);
        PostaviZ(z);
        PostaviPoluprecnik(r);
    }
    explicit Kugla(const std::tuple<double, double, double> &centar, double r=0){
        x=std::get<0>(centar);
        y=std::get<1>(centar);
        z=std::get<2>(centar);
        Kugla::r=r;
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
    Kugla &PostaviX(double x){
        Kugla::x=x;
        return *this;
    }
    Kugla &PostaviY(double y){
        Kugla::y=y;
        return *this;
    }
    Kugla &PostaviZ(double z){
        Kugla::z=z;
        return *this;
    }
    Kugla &PostaviCentar(double x, double y, double z){
        PostaviX(x);
        PostaviY(y);
        PostaviZ(z);
        return *this;
    }
    Kugla &PostaviCentar(const std::tuple<double, double, double> &centar){
        PostaviX(std::get<0>(centar));
        PostaviY(std::get<1>(centar));
        PostaviZ(std::get<2>(centar));
        return *this;
    }
    Kugla &PostaviPoluprecnik(double r){
        if(r<0) throw std::domain_error("Ilegalan poluprecnik");
        Kugla::r=r;
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
    friend bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2);
    bool DaLiSadrzi(const Kugla &k) const{
        double razmak=std::sqrt(std::pow(x-k.x,2)+std::pow(y-k.y,2)+std::pow(z-k.z,2));
        return(r-k.r-razmak>EPSILON || std::fabs(r-k.r-razmak)<EPSILON);
    }
    friend double RastojanjeCentara(const Kugla &k1, const Kugla &k2);
};
bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2){
    if(std::fabs(k1.x-k2.x)>EPSILON*(std::fabs(k1.x)+std::fabs(k2.x)) || std::fabs(k1.y-k2.y)>EPSILON*(std::fabs(k1.y)+std::fabs(k2.y)) || std::fabs(k1.z-k2.z)>EPSILON*(std::fabs(k1.z)+std::fabs(k2.z)) || std::fabs(k1.r-k2.r)>EPSILON*(std::fabs(k1.r)+std::fabs(k2.r))) return false;
    return true;
}
bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2){
    if(std::fabs(k1.r-k2.r)<EPSILON*(std::fabs(k1.r)+std::fabs(k2.r))) return true;
    return false;
}
bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2){
    if(std::fabs(k1.x-k2.x)>EPSILON*(std::fabs(k1.x)+std::fabs(k2.x)) || 
       std::fabs(k1.y-k2.y)>EPSILON*(std::fabs(k1.y)+std::fabs(k2.y)) ||
       std::fabs(k1.z-k2.z)>EPSILON*(std::fabs(k1.z)+std::fabs(k2.z))) return false;
    return true;
}
bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2){
    double zbir=k1.r+k2.r;
    double razmak=std::sqrt(std::pow(k1.x-k2.x,2)+std::pow(k1.y-k2.y,2)+std::pow(k1.z-k2.z,2));
    if(std::fabs(razmak-zbir)<EPSILON*(std::fabs(razmak)+std::fabs(zbir))) return true;
    return false;
}
bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2){
    double zbir=k1.r+k2.r;
    double razlika=std::fabs(k1.r-k2.r);
    double razmak=std::sqrt(std::pow(k1.x-k2.x,2)+std::pow(k1.y-k2.y,2)+std::pow(k1.z-k2.z,2));
    if(razmak>zbir || razmak<razlika) return false;
    return true;
}
bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2){
    if(DaLiSeSijeku(k1,k2) || k1.DaLiSadrzi(k2) || k2.DaLiSadrzi(k1) || DaLiSeDodirujuIznutra(k1,k2) || DaLiSuIdenticne(k1,k2)) return true;
    return false;
}
bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2){
    double zbir=k1.r+k2.r;
    double razlika=std::fabs(k1.r-k2.r);
    double razmak=std::sqrt(std::pow(k1.x-k2.x,2)+std::pow(k1.y-k2.y,2)+std::pow(k1.z-k2.z,2));
    if(razmak<zbir && razmak>razlika) return true;
    return false;
}
double RastojanjeCentara(const Kugla &k1, const Kugla &k2){
    return std::sqrt(std::pow(k1.x-k2.x,2)+std::pow(k1.y-k2.y,2)+std::pow(k1.z-k2.z,2));
}
int main ()
{
    int broj_kugla;
    std::cout<<"Unesite broj kugla: ";
    std::cin>>broj_kugla;
    std::vector<std::shared_ptr<Kugla>> v(broj_kugla);
    for(int i=0; i<broj_kugla; i++){
        double r,x,y,z;
        std::cout<<"Unesite centar "<<i+1<<". kugle: ";
        std::cin>>x>>y>>z;
        std::cout<<"Unesite poluprecnik "<<i+1<<". kugle: ";
        std::cin>>r;
        try{
            v[i]=std::make_shared<Kugla>(x,y,z,r);
        }
        catch(std::domain_error greska){
            std::cout<<greska.what()<<std::endl;
            i--;
        }
    }
    std::cout<<"Unesite parametre translacije (delta_x,delta_y,delta_z): ";
    double delta_x,delta_y,delta_z;
    std::cin>>delta_x>>delta_y>>delta_z;
    std::transform(v.begin(), v.end(), v.begin(), [delta_x,delta_y,delta_z](std::shared_ptr<Kugla> pok){pok->Transliraj(delta_x, delta_y, delta_z); return pok;});
    std::sort(v.begin(), v.end(), [](std::shared_ptr<Kugla> pok1, std::shared_ptr<Kugla> pok2){return pok1->DajZapreminu()<pok2->DajZapreminu();});
    std::cout<<"Kugle nakon obavljenje transformacije imaju sljedece vrijednosti: "<<std::endl;
    std::for_each(v.begin(), v.end(), [](std::shared_ptr<Kugla> pok1){pok1->Ispisi();});
    auto povrsina=std::max_element(v.begin(),v.end(),[](std::shared_ptr<Kugla> pok1, std::shared_ptr<Kugla> pok2){return pok1->DajPovrsinu()<pok2->DajPovrsinu();});
    std::cout<<"Kugla sa najvecom povrsinom je: ";
    (*povrsina)->Ispisi();
    static bool ima=false;
    static std::vector<std::pair<std::shared_ptr<Kugla>,std::shared_ptr<Kugla>>> parovi;
    std::for_each(v.begin(), v.end(), [v](std::shared_ptr<Kugla> pok){
        std::for_each(v.begin(), v.end(), [pok,v](std::shared_ptr<Kugla> pokk){
            if(DaLiSeSijeku(*pok, *pokk)){
                auto pom1=std::make_pair(pokk,pok);
                auto pom2=std::make_pair(pok,pokk);
                auto it=std::find(parovi.begin(), parovi.end(), pom1);
                if(it==parovi.end()){
                    parovi.push_back((pom2));
                    std::cout<<"Presjecaju se kugle: ";
                    ima=true;
                    pok->Ispisi();
                    pokk->Ispisi();
                }
            }
        });
    });
    if(!ima) std::cout<<"Ne postoje kugle koje se presjecaju!";
	return 0;
}
