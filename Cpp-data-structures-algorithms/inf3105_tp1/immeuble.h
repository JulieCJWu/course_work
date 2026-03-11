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

#if !defined(_IMMEUBLE__H_)
#define _IMMEUBLE__H_
#include <iostream>
#include <string>
#include "point.h"


class Immeuble
{
  public:
    Immeuble(){};
    Immeuble(std::string nom, Point p, double ht, int nbclient);
    
    double distance(const Immeuble& im) const;
    bool operator < (const Immeuble im) const;
    int addClients(int nbcleints_sum) const;

  private:
    std::string nom;
    Point p;
    double ht;
    int nbclient;

  friend class Station;
  friend std::istream& operator >> (std::istream&, Immeuble&);
  friend std::ostream& operator << (std::ostream&, const Immeuble&);
  friend std::string getNom(const Immeuble&);

};
#endif




