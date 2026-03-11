/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    http://ericbeaudry.ca/INF3105/tp2/
*/
#if !defined(__POINT__H__)
#define __POINT__H__
#include <iostream>

// Représente un point sur la surface de la Terre approximée par une sphère parfaite.
class Point {
  public:
    double distance(const Point&) const;
  private:
    double latitude;
    double longitude;

  friend std::ostream& operator << (std::ostream&, const Point&);
  friend std::istream& operator >> (std::istream&, Point&);
};

#endif

