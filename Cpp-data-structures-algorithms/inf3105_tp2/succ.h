/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    Auteur(s): 
*/

/* succ.h
 *
 * @author Chao-Jung (Julie) Wu; LUO, Xiaohui (LUOX31037903);
 * @version 1.00.07
 * @since 2016-11-07
 */

#if !defined(__SUCC_H__)
#define __SUCC_H__
#include <string>
#include "arbreavl.h"
#include "arbremap.h"
#include "date.h"
#include "point.h"

using namespace std;
typedef ArbreMap<Date, int>::Iterateur it_type;

class Succursale
{
  public:
    Succursale(){};
    Succursale(std::string nom, Point point, int nbparking);
    ~Succursale(){};

    ArbreMap<Date, int>::Iterateur trouve_it(const Date& d)
        {return bookings.rechercher(d);};          
    ArbreMap<Date, int>::Iterateur get_it(const Date& d)
        {return bookings.rechercherEgalOuPrecedent(d);};      
    ArbreMap<Date, int>::Iterateur get_last()
        {return bookings.fin();};        

    void ajouter(Date d, int nbcar);
    double distance(const Point& p) const;
    bool hasParking(const Date& d) const ;
    bool verifyAvail (const Date& debut, const Date& fin, Succursale& other);
    void updatebookings (const Date& debut, const Date& fin, Succursale& other, it_type &iter1, it_type &iter2);
    
    bool operator ==(const Succursale& s) const;  
    bool operator !=(const Succursale& s) const;
 
  private:
    string nom;
    Point point;
    int nbparking;
    ArbreMap<Date, int> bookings; // date -> nbcar
  
  friend ostream& operator << (ostream&, const Succursale& s);
};

#endif