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

#if !defined(_STATION__H_)
#define _STATION__H_
#include <iostream>
#include <string>
#include "immeuble.h"

class Station
{
  public:
    Station(){};
    Station(std::string nom, double radius, double ht_min, double freq);
    
    bool satisfiesHT(const Immeuble& im) const;
    bool hasSameFrq(const Station& s) const;
    bool covers(const Immeuble& im1, const Immeuble& im2)const;
    double addRadius(const Station& s)const;
  

  private:
    std::string nom;
    double radius, ht_min, freq;

  friend std::istream& operator >> (std::istream&, Station&);
  friend std::ostream& operator << (std::ostream&, const Station&);
  friend std::string getNom (const Station&);
  friend double getRadius (const Station&);
  friend double getFreq (const Station&);
};
#endif

