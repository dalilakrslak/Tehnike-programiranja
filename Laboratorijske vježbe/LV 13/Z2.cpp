/* 
    TP 16/17 (LV 13, Zadatak 2)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <string>
class ApstraktniStudent{
    std::string ime,prezime;
    int indeks, polozeni_ispiti;
    double prosjek;
public:
    ApstraktniStudent(std::string ime, std::string prezime, int indeks){
        ApstraktniStudent::ime=ime; ApstraktniStudent::prezime=prezime; ApstraktniStudent::indeks=indeks;
        polozeni_ispiti=0; prosjek=5;
    }
    virtual ~ApstraktniStudent(){}
    std::string DajIme() const{
        return ime;
    }
    std::string DajPrezime() const{
        return prezime;
    }
    int DajBrojIndeksa() const{
        return indeks;
    }
    int DajBrojPolozenih() const{
        return polozeni_ispiti;
    }
    double DajProsjek() const{
        return prosjek;
    }
    void RegistrirajIspit(int nova){
        if(nova<5 || nova>10) throw std::domain_error("Neispravna ocjena");
        if(nova!=5){
            double pom=prosjek*polozeni_ispiti;
            polozeni_ispiti++;
            prosjek=(pom + nova)/polozeni_ispiti;
        }
    }
    void PonistiOcjene(){
        polozeni_ispiti=0;
        prosjek=5;
    }
    virtual void IspisiPodatke() const=0;
    virtual ApstraktniStudent *DajKopiju() const=0;
};
class StudentBachelor: public ApstraktniStudent{
public:
    StudentBachelor(std::string ime, std::string prezime, int indeks): ApstraktniStudent(ime, prezime,indeks){}
    void IspisiPodatke() const{
        std::cout<<"Student bachelor studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<std::endl;
        std::cout<<"ima prosjek "<<DajProsjek()<<"."<<std::endl;
    }
    StudentBachelor *DajKopiju() const{
        return new StudentBachelor(*this);
    }
};
class StudentMaster: public ApstraktniStudent{
    int godina;
public:
    StudentMaster(std::string ime, std::string prezime, int indeks, int godina): ApstraktniStudent(ime, prezime,indeks), godina(godina){}
    void IspisiPodatke() const{
        std::cout<<"Student master studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<std::endl;
        std::cout<<"zavrsio bachelor studij godine "<<godina<<",ima prosjek "<<DajProsjek()<<"."<<std::endl;
    }
    StudentMaster *DajKopiju() const{
        return new StudentMaster(*this);
    }
};
int main ()
{
    ApstraktniStudent *student1= new StudentBachelor("Dalila", "Krslak", 18906);
    student1->RegistrirajIspit(10);
    std::cout<<student1->DajIme()<<" "<<student1->DajPrezime()<<" "<<student1->DajBrojIndeksa()<<" "<<student1->DajBrojPolozenih()<<" "<<student1->DajProsjek()<<std::endl;
    student1->IspisiPodatke();
    delete student1;
    student1=new StudentMaster("Niko", "Nikic", 12345, 2001);
    student1->RegistrirajIspit(7);
    std::cout<<student1->DajIme()<<" "<<student1->DajPrezime()<<" "<<student1->DajBrojIndeksa()<<" "<<student1->DajBrojPolozenih()<<" "<<student1->DajProsjek()<<std::endl;
    student1->IspisiPodatke();
    delete student1;
	return 0;
}