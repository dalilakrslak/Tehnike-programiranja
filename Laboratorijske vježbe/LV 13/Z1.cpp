/* 
    TP 16/17 (LV 13, Zadatak 1)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <memory>
const double PI=4*std::atan(1);
class Lik{
public:
    virtual ~Lik(){}
    virtual void IspisiSpecificnosti() const=0;
    virtual double DajObim() const=0;
    virtual double DajPovrsinu() const=0;
    void Ispisi() const{
        IspisiSpecificnosti();
        std::cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<std::endl;
    }
};
class Krug: public Lik{
    double r;
public:
    Krug(double r){
        if(r<=0) throw std::domain_error("Neispravni parametri");
        Krug::r=r;
    }
    void IspisiSpecificnosti() const{
        std::cout<<"Krug poluprecnika "<<r<<std::endl;
    }
    double DajObim() const{
        return 2*PI*r;
    }
    double DajPovrsinu() const{
        return std::pow(r,2)*PI;
    }
};
class Pravougaonik: public Lik{
    double a,b;
public:
    Pravougaonik(double a, double b){
        if(a<=0 || b<=0) throw std::domain_error("Neispravni parametri");
        Pravougaonik::a=a; Pravougaonik::b=b;
    }
    void IspisiSpecificnosti() const{
        std::cout<<"Pravougaonik sa stranicama duzine "<<a<<" i "<<b<<std::endl;
    }
    double DajObim() const{
        return 2*a+2*b;
    }
    double DajPovrsinu() const{
        return a*b;
    }
};
class Trougao: public Lik{
    double a,b,c;
public:
    Trougao(double a, double b, double c){
        if(a<=0 || b<=0 || c<=0 || (a+b)<=c || (a+c)<=b || (b+c)<=a) throw std::domain_error("Neispravni parametri");
        Trougao::a=a; Trougao::b=b; Trougao::c=c;
    }
    void IspisiSpecificnosti() const{
        std::cout<<"Trougao sa stranicama duzine "<<a<<", "<<b<<" i "<<c<<std::endl;
    }
    double DajObim() const{
        return a+b+c;
    }
    double DajPovrsinu() const{
        double s=DajObim()/2;
        return std::sqrt(s*(s-a)*(s-b)*(s-c));
    }
};
int main ()
{
    std::cout<<"Koliko zelite likova: ";
    int broj_likova;
    std::cin>>broj_likova;
    std::vector<std::shared_ptr<Lik>> vektor(broj_likova);
    int i(0);
    while(i<broj_likova){
        try{
            char unos,pom;
            std::cin.ignore(1000, '\n');
            std::cout<<"Lik "<<i+1<<": ";
            unos=std::cin.get();
            double a,b,c,r;
            if(unos=='K'){
                std::cin>>r;
                if(!std::cin || std::cin.peek()!='\n'){
                    std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
                    continue;
                }
                vektor[i]=std::make_shared<Krug>(Krug(r));
                i++;
            }
            else if(unos=='P'){
                std::cin>>a>>pom>>b;
                if(!std::cin || std::cin.peek()!='\n'){
                    std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
                    continue;
                }
                vektor[i]=std::make_shared<Pravougaonik>(Pravougaonik(a,b));
                i++;
            }
            else if(unos=='T'){
                std::cin>>a>>pom>>b>>pom>>c;
                if(!std::cin || std::cin.peek()!='\n'){
                    std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
                    continue;
                }
                vektor[i]=std::make_shared<Trougao>(Trougao(a,b,c));
                i++;
            }
            else{
                std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
        
            }
        }
        catch(std::domain_error izuzetak){
            std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
        }
    }
    std::cout<<std::endl;
    for(auto pom: vektor) pom->Ispisi();
	return 0;
}