/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    Auteur(s): 
*/
/* succ.cpp
 *
 * @author Chao-Jung (Julie) Wu
 * @version 1.00.07
 * @since 2016-11-07
 */


#include "succ.h"

Succursale::Succursale (std::string _nom, Point _point, int _nbparking)
  : nom(_nom), point(_point), nbparking(_nbparking) {
}

void Succursale::ajouter(Date d, int nbcar) {
    bookings[d] = nbcar;
}

double Succursale::distance(const Point& p)const{
    return point.distance( p );
}

bool Succursale::hasParking(const Date& d) const {
    return nbparking - bookings[d] > 0;
}

bool Succursale::operator ==(const Succursale& s) const {
    return nom == s.nom;
}

bool Succursale::operator !=(const Succursale& s) const {
    return nom != s.nom;
}

bool Succursale::verifyAvail (const Date& debut, const Date& fin, Succursale& other) {

    if (fin < debut) return false;
    
    it_type iter1 = get_it(debut);
    
    it_type iter1copy = iter1; 

    it_type iter2 = other.get_it(fin);
    it_type iter2copy = iter2;     

    if ( *this != other) {
        while(iter1) {
            if (iter1.valeur() == 0) return false;
            ++iter1;
        }

        while (iter2) {
            if ( ! other.hasParking( iter2.cle() )) 
                return false;
            ++iter2;
        }

    }else {
        if ( iter2.valeur() == 0 && iter2.cle() < fin)
            return false;
        while(iter1.cle() < iter2.cle()) {
            if (iter1.valeur() == 0)  return false;
            ++iter1;
        }   
    }
    updatebookings (debut, fin, other, iter1copy, iter2copy);
    return true;
}

void Succursale::updatebookings (const Date& debut, const Date& fin, Succursale& other, it_type& iter1, it_type& iter2) {

    // set fin Date in bookings
    if (iter2.cle() < fin) {
        other.bookings[fin] = iter2.valeur();
        //iter2 = other.bookings.rechercher(fin);
    }
    // set debut Date in bookings
    if (iter1.cle() < debut) {
        bookings[debut] = iter1.valeur();
    } 
    if (*this != other) {
        iter1 = bookings.rechercher(debut);
        iter2 = other.bookings.rechercher(fin);
        while (iter2) {iter2.valeur()++; ++iter2;}
        while (iter1) {iter1.valeur()--; ++iter1;}
    }
    else {
        iter1 = bookings.rechercher(debut);
        iter2 = bookings.rechercher(fin);
        while (iter1.cle() < iter2.cle()) 
            {iter1.valeur()--; ++iter1;}
        }
}

ostream& operator << (ostream& os, const Succursale& s){
    os << s.nom;
    return os;
}