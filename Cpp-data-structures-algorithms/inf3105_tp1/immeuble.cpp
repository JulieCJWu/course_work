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
#include "immeuble.h"

Immeuble::Immeuble (std::string _nom, Point _p, double _ht, int _nbclient)
  : nom(_nom), p(_p), ht(_ht), nbclient(_nbclient)
{
}


double Immeuble::distance(const Immeuble& im)const{
    return p.distance(im.p);
}

bool Immeuble::operator < (const Immeuble im) const{
 return ht < im.ht;
}

int Immeuble::addClients(int nbcleints_sum) const{
    return nbclient + nbcleints_sum;
}


std::istream& operator >> (std::istream& is, Immeuble& im){
    if(is){   // Détection de la fin du fichier
        is >> im.nom
           >> im.p
           >> im.ht
           >> im.nbclient;
    }
    return is;
}

std::ostream& operator << (std::ostream& os, const Immeuble& im) {
  os << im.nom;
  return os;
}

std::string getNom(const Immeuble& im){
    return im.nom;
}






