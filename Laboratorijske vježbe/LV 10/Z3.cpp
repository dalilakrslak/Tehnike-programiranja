/* 
    TP 16/17 (LV 10, Zadatak 3)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
class Vektor3d{
    double koordinate[3];
    mutable int brojacispisa=0;
public:
    Vektor3d(){
        koordinate[0]=0; koordinate[1]=0; koordinate[2]=0;
    }
    Vektor3d(double x, double y, double z){
        Postavi(x, y, z);
    }
    Vektor3d(const Vektor3d &v) {
        koordinate[0]=v.koordinate[0];
        koordinate[1]=v.koordinate[1];
        koordinate[2]=v.koordinate[2];
    }
    void Postavi(double x, double y, double z){
        koordinate[0] = x; koordinate[1] = y; koordinate[2] = z;
    }
    void PostaviX(double x) { Vektor3d::koordinate[0] = x; }
    void PostaviY(double y) { Vektor3d::koordinate[1] = y; }
    void PostaviZ(double z) {Vektor3d::koordinate[2] = z; }
    void Ocitaj(double &x, double &y, double &z) const{
        x = Vektor3d::koordinate[0]; y = Vektor3d::koordinate[1]; z = Vektor3d::koordinate[2];
    }
    void Ispisi() const{
        std::cout<<"{"<<koordinate[0]<<","<<koordinate[1]<<","<<koordinate[2]<<"}";
        brojacispisa++;
    }
    double DajX() const{ return koordinate[0]; }
    double DajY() const{ return koordinate[1]; }
    double DajZ() const{ return koordinate[2]; }
    double DajDuzinu() const {return std::sqrt(koordinate[0]*koordinate[0]+koordinate[1]*koordinate[1]+koordinate[2]*koordinate[2]);}
    int DajBrojIspisa() const{ return brojacispisa; }
    Vektor3d &PomnoziSaSkalarom(double s){
        koordinate[0]*=s; koordinate[1]*=s; koordinate[2]*=s;
        return *this;
    }
    Vektor3d &SaberiSa(const Vektor3d &v){
        koordinate[0]+=v.koordinate[0]; koordinate[1]+=v.koordinate[1]; koordinate[2]+=v.koordinate[2];
        return *this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};
Vektor3d ZbirVektora (const Vektor3d &v1, const Vektor3d &v2){
    Vektor3d v3;
    v3.koordinate[0]=v1.koordinate[0]+v2.koordinate[0]; v3.koordinate[1]=v1.koordinate[1]+v2.koordinate[1]; v3.koordinate[2]=v1.koordinate[2]+v2.koordinate[2];
    return v3;
}
int main ()
{
    Vektor3d v1;
    v1.Ispisi();
    std::cout<<std::endl;
    v1.PostaviX(4);
    v1.PostaviY(11);
    v1.PostaviZ(22);
    std::cout<<"X: "<<v1.DajX()<<", Y: "<<v1.DajY()<<", Z: "<<v1.DajZ()<<", duzina: "<<v1.DajDuzinu()<<std::endl;
    Vektor3d v2(1,2,3);
    v2.Ispisi();
    std::cout<<std::endl;
    v2.Postavi(4,11, 19);
    double x,y,z;
    v2.Ocitaj(x, y, z);
    std::cout<<"x: "<<x<<", y: "<<y<<", z: "<<z<<std::endl;
    v1.PomnoziSaSkalarom(1);
    v1.Ispisi();
    Vektor3d v=ZbirVektora(v1, v2);
    v.Ispisi();
    std::cout<<std::endl<<"Vektor 1 smo ispisali "<<v1.DajBrojIspisa()<<" puta, vektor 2 "<<v2.DajBrojIspisa()<<" puta, a njihov zbir "<<v.DajBrojIspisa()<<" puta.";
	return 0;
}