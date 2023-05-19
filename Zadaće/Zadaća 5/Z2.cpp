//TP 2021/2022: Zadaća 5, Zadatak 2
#include <functional>
#include <iostream>
#include <cmath>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>
class Berza{
    std::vector<int> cijene;
    int minimalna, maksimalna;
public:
    Berza(int min, int max){
        if(min<0 || max<0) throw std::range_error("Ilegalne granicne cijene.");
        minimalna=min; maksimalna=max;
    }
    Berza(int max){
        if(max<0) throw std::range_error("Ilegalne granicne cijene");
        minimalna=0;
        maksimalna=max;
    }
    void RegistrirajCijenu(int cijena){
        if(cijena<minimalna || cijena>maksimalna) throw std::range_error("Ilegalna cijena");
        cijene.push_back(cijena);
    }
    int DajBrojRegistriranihCijena() const{
        return cijene.size();
    }
    void BrisiSve(){
        cijene.resize(0);
    }
    friend bool operator !(const Berza &b1);
    int DajMinimalnuCijenu() const{
        if(cijene.size()==0) throw std::range_error("Nema registriranih cijena");
        auto min=std::min_element(cijene.begin(),cijene.end());
        return *min;
    }
    int DajMaksimalnuCijenu() const{
        if(cijene.size()==0) throw std::range_error("Nema registriranih cijena");
        auto max=std::max_element(cijene.begin(), cijene.end());
        return *max;
    }
    int DajBrojCijenaVecihOd(int poredba) const{
        if(cijene.size()==0) throw std::range_error("Nema registriranih cijena");
        return std::count_if(cijene.begin(), cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, poredba));
    }
    void Ispisi() const;
    int operator [](int index){
        if(index<=0 || index>cijene.size()) throw std::range_error("Neispravan indeks");
        return cijene[index-1];
    }
    friend Berza &operator ++(Berza &b);
    friend Berza operator ++(Berza &b, int);
    friend Berza &operator --(Berza &b);
    friend Berza operator --(Berza &b, int);
    friend bool operator ==(const Berza &b1, const Berza &b2);
    friend bool operator !=(const Berza &b1, const Berza &b2);
    friend Berza operator -(const Berza &b);
    friend Berza operator +(const Berza &x, int y);
    friend Berza operator -(const Berza &x, int y);
    friend Berza operator +(int y, const Berza &x);
    friend Berza operator -(int y, const Berza &x);
    friend Berza operator -(const Berza &x, const Berza &y);
    friend Berza &operator +=(Berza &x, int y);
    friend Berza &operator -=(Berza &x, int y);
};
void Berza::Ispisi() const{
   std::vector<double> temp(cijene.size());
   std::copy(cijene.begin(), cijene.end(), temp.begin());
   std::transform(temp.begin(), temp.end(), temp.begin(),std::bind(std::divides<double>(), std::placeholders::_1, 100.));
   std::sort(temp.begin(), temp.end(), std::greater<double>());
   std::copy(temp.begin(), temp.end(), std::ostream_iterator<double>(std::cout<<std::setprecision(2)<<std::fixed,"\n")); 
}
bool operator !(const Berza &b){
    if(b.cijene.size()==0) return true;
    return false;
}
Berza &operator ++(Berza &b){
    std::transform(b.cijene.begin(), b.cijene.end(), b.cijene.begin(), std::bind(std::plus<int>(), std::placeholders::_1, 100));
    return b;
}
Berza operator ++(Berza &b, int){
    Berza pom=b;
    ++b;
    return pom;
}
Berza &operator --(Berza &b){
    std::transform(b.cijene.begin(), b.cijene.end(), b.cijene.begin(), std::bind(std::minus<int>(), std::placeholders::_1,100));
    return b;
}
Berza operator --(Berza &b, int){
    Berza pom=b;
    --b;
    return pom;
}
bool operator ==(const Berza &b1, const Berza &b2){
    if(b1.cijene.size()!=b2.cijene.size()) return false;
    return std::equal(b1.cijene.begin(), b1.cijene.end(), b2.cijene.begin(), std::bind(std::equal_to<int>(), std::placeholders::_1, std::placeholders::_2));
}
bool operator !=(const Berza &b1, const Berza &b2){
    return !(b1==b2);
}
Berza operator -(const Berza &b){
    Berza minus=b.maksimalna;
    minus.cijene.resize(b.cijene.size());
    std::transform(b.cijene.begin(), b.cijene.end(), minus.cijene.begin(), std::bind(std::minus<int>(), b.maksimalna, std::placeholders::_1));
    return minus;
}
Berza operator +(const Berza &x, int y){
    Berza povecan=x.maksimalna+y;
    povecan.cijene.resize(x.cijene.size());
    std::transform(x.cijene.begin(), x.cijene.end(), povecan.cijene.begin(), std::bind(std::plus<int>(), std::placeholders::_1, y));
    return povecan;
}
Berza operator -(const Berza &x, int y){
    Berza smanjen=x.maksimalna-y;
    smanjen.cijene.resize(x.cijene.size());
    std::transform(x.cijene.begin(), x.cijene.end(), smanjen.cijene.begin(), std::bind(std::minus<int>(), std::placeholders::_1, y));
    return smanjen;
}
Berza operator +(int y, const Berza &x){
    Berza povecan=x+y;
    return povecan;
}
Berza operator -(int y, const Berza &x){
    Berza smanjen=y;
    smanjen.cijene.resize(x.cijene.size());
    std::transform(x.cijene.begin(), x.cijene.end(), smanjen.cijene.begin(), std::bind(std::minus<int>(), y, std::placeholders::_1));
    return smanjen;
}
Berza operator -(const Berza &x, const Berza &y){
    if(x.cijene.size()!=y.cijene.size() || x.maksimalna!=y.maksimalna || x.minimalna!=y.minimalna) throw std::domain_error("Nesaglasni operandi");
    Berza oduzeti=x.maksimalna;
    oduzeti.cijene.resize(x.cijene.size());
    std::transform(x.cijene.begin(), x.cijene.end(), y.cijene.begin(), oduzeti.cijene.begin(), std::bind(std::minus<int>(), std::placeholders::_1, std::placeholders::_2));
    return oduzeti;
}
Berza &operator +=(Berza &x, int y){
    return x=x+y;
}
Berza &operator -=(Berza &x, int y){
    return x=x-y;
}
int main ()
{
	return 0;
}
