//TP 2021/2022: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
class Spremnik{
protected:
    double tezina;
    std::string sadrzaj;
public:
    Spremnik(double tezinaa, std::string naziv){
        tezina=tezinaa;
        sadrzaj=naziv;
    }
    virtual ~Spremnik(){}
    virtual double DajTezinu() const{
        return tezina;
    }
    virtual double DajUkupnuTezinu() const=0;
    virtual void Ispisi() const=0;
    virtual Spremnik *DajKopiju() const=0;
};
class Sanduk: public Spremnik{
    std::vector<double> predmeti;
public:
    Sanduk(double tezinaa, std::string naziv, std::vector<double> tezine): Spremnik(tezinaa, naziv){
        predmeti=tezine;
    }
    double DajUkupnuTezinu() const override{
        double ukupna(0);
        for(auto pom: predmeti) ukupna+=pom;
        ukupna+=DajTezinu();
        return ukupna;
    }
    void Ispisi() const override{
        std::cout<<"Vrsta spremnika: Sanduk"<<std::endl;
        std::cout<<"Sadrzaj: "<<sadrzaj<<std::endl;
        std::cout<<"Tezine predmeta: ";
        for(auto pom: predmeti) std::cout<<pom<<" ";
        std::cout<<"(kg)"<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
    }    
    Spremnik *DajKopiju() const override{
        return new Sanduk(*this);
    }
};
class Vreca: public Spremnik{
    double praskasta_materija;
public:
    Vreca(double tezinaa, std::string naziv, double prah): Spremnik(tezinaa, naziv){
        praskasta_materija=prah;
    }
    double DajUkupnuTezinu() const override{
        double ukupna=DajTezinu()+praskasta_materija;
        return ukupna;
    }
    void Ispisi() const override{
        std::cout<<"Vrsta spremnika: Vreca"<<std::endl;
        std::cout<<"Sadrzaj: "<<sadrzaj<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl;
        std::cout<<"Tezina pohranjene materije: "<<praskasta_materija<<" (kg)"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
    }
    Spremnik *DajKopiju() const override{
        return new Vreca(*this);
    }
};
class Bure: public Spremnik{
    double gustina, zapremina;
public:
    Bure(double tezinaa, std::string naziv, double spec, double zap): Spremnik(tezinaa, naziv){
        gustina=spec;
        zapremina=zap;
    }
    double DajUkupnuTezinu() const override{
        double ukupna=(gustina*zapremina)/1000;
        ukupna+=DajTezinu();
        return ukupna;
    }
    void Ispisi() const override{
        std::cout<<"Vrsta spremnika: Bure"<<std::endl;
        std::cout<<"Sadrzaj: "<<sadrzaj<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl;
        std::cout<<"Specificna tezina tecnosti: "<<gustina<<" (kg/m^3)"<<std::endl;
        std::cout<<"Zapremina tecnosti: "<<zapremina<<" (l)"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
    }
    Spremnik *DajKopiju() const override{
        return new Bure(*this);
    }
};
class Skladiste{
    std::vector<std::shared_ptr<Spremnik>> v;
public:
    Skladiste(){}
    Skladiste(const Skladiste &s): v(s.v.size()){
        for(int i=0; i<s.v.size(); i++) v.at(i)=std::shared_ptr<Spremnik>(s.v.at(i)->DajKopiju());
    }
    Skladiste &operator =(const Skladiste &s){
        v.resize(s.v.size());
        for(int i=0; i<s.v.size(); i++) v.at(i)=std::shared_ptr<Spremnik>(s.v.at(i)->DajKopiju());
        return *this;
    }
    Skladiste(Skladiste &&s){
        v=s.v;
        s.v.resize(0);
    }
    Skladiste &operator =(Skladiste &&s){
        v=s.v;
        s.v.resize(0);
        return *this;
    }
    Spremnik *DodajSanduk(double tezinaa, std::string naziv, std::vector<double> tezine){
        Spremnik *sandukk=new Sanduk(tezinaa, naziv, tezine);
        v.push_back(std::shared_ptr<Spremnik>(sandukk));
        return sandukk;
    }
    Spremnik *DodajVrecu(double tezinaa, std::string naziv, double prah){
        Spremnik *vrecaa=new Vreca(tezinaa, naziv, prah);
        v.push_back(std::shared_ptr<Spremnik>(vrecaa));
        return vrecaa;
    }
    Spremnik *DodajBure(double tezinaa, std::string naziv, double spec, double zap){
        Spremnik *buree=new Bure(tezinaa, naziv, spec, zap);
        v.push_back(std::shared_ptr<Spremnik>(buree));
        return buree;
    }
    Spremnik *DodajSpremnik(Spremnik *spremnikk, bool vlasnistvo){
        if(vlasnistvo){
            v.push_back(std::shared_ptr<Spremnik>(spremnikk));
            return spremnikk;
        }
        auto temp=spremnikk->DajKopiju();
        v.push_back(std::shared_ptr<Spremnik>(temp));
        return temp;
    }
    void BrisiSpremnik(Spremnik *spremnikk){
        int i(0);
        auto pocetak=v.begin();
        for(auto pom: v){
            if(pom.get()==spremnikk) v.erase(pocetak+i);
            i++;
        }
    }
    Spremnik &DajNajlaksi() const{
        if(v.size()==0) throw std::range_error("Skladiste je prazno");
        int i(0);
        double najlaksi=v.at(0)->DajTezinu();
        std::shared_ptr<Spremnik> vrati=v.at(0);
        for(auto pom: v){
            if(najlaksi>pom->DajTezinu()){
                najlaksi=pom->DajTezinu();
                vrati=pom;
            }
            i++;
        }
        return *vrati;
    }
    Spremnik &DajNajtezi() const{
        if(v.size()==0) throw std::range_error("Skladiste je prazno");
        int i(0);
        double najtezi=v.at(0)->DajTezinu();
        std::shared_ptr<Spremnik> vrati=v.at(0);
        for(auto pom: v){
            if(najtezi<pom->DajTezinu()){
                najtezi=pom->DajTezinu();
                vrati=pom;
            }
            i++;
        }
        return *vrati;
    }
    int BrojPreteskih(int poredba) const{
        int preteski(0);
        for(auto pom: v){
            if(poredba<=pom->DajUkupnuTezinu()) preteski++;
        }
        return preteski;
    }
    void IzlistajSkladiste() const{
        std::vector<std::shared_ptr<Spremnik>> temp=v;
        std::sort(temp.begin(), temp.end(), [](std::shared_ptr<Spremnik> s1, std::shared_ptr<Spremnik> s2){return s1->DajUkupnuTezinu()>s2->DajUkupnuTezinu();});
        for(auto pom: temp) pom->Ispisi();
    }
    void UcitajIzDatoteke(std::string dat);
};
void Skladiste::UcitajIzDatoteke(std::string dat){
    std::ifstream ulazni_tok(dat);
    if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
    
}
int main ()
{
    try{
        Skladiste s;
        s.UcitajIzDatoteke("ROBA.TXT");
        s.IzlistajSkladiste();
    }
    catch(std::logic_error izuzetak){
        std::cout<<izuzetak.what();
    }
    catch(std::range_error izuzetak){
        std::cout<<izuzetak.what();
    }
	return 0;
}
