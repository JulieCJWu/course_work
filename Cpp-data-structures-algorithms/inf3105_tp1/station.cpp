/*  INF3105 | Structures de données et algorithmes
 *  UQAM | Département d'informatique
 *  Automne 2016 | TP1
 *  http://ericbeaudry.ca/INF3105/
 */

/*
 * @author Chao-Jung (Julie) Wu
 * @version 6.00.04
 * @since 2016-09-29
 */

#include "station.h"

Station::Station(std::string _nom, double _radius, double _ht_min, double _freq) 
  : nom(_nom), radius(_radius), ht_min(_ht_min), freq(_freq)
{
}


bool Station::satisfiesHT(const Immeuble& im) const{
    return im.ht >= ht_min;
}

bool Station::hasSameFrq(const Station& s) const{
    return freq == s.freq;
}


bool Station::covers(const Immeuble& im1, const Immeuble& im2)const{
    return im1.distance(im2) <= radius;
}


double Station::addRadius(const Station& s)const{
    return radius + s.radius;
}


std::istream& operator >> (std::istream& is, Station& s){
    if(is){
        is >> s.nom
           >> s.radius
           >> s.ht_min
           >> s.freq;
    }
    return is;
}

std::ostream& operator << (std::ostream& os, const Station& s) {
  os << s.nom;
  return os;
}

std::string getNom (const Station& station){
    return station.nom;
}

double getRadius (const Station& station){
    return station.radius;
}


double getFreq (const Station& station){
    return station.freq;
}
