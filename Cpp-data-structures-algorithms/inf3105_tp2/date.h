/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    http://ericbeaudry.ca/INF3105/tp2/
*/

/* date.h
 *
 * @author Chao-Jung (Julie) Wu; LUO, Xiaohui (LUOX31037903);
 * @version 1.00.01
 * @since 2016-11-07
 */

#if !defined(__DATE__H__)
#define __DATE__H__
#include <iostream>

class Date
{
  public:
    //Date(){};
    Date(int day=0, int hours=0, int mins=0);
        
    bool operator <(const Date& date) const;
    bool operator <=(const Date& date) const;
    bool operator ==(const Date& date) const;
  
  private:
    int day, hours, mins;

  friend std::ostream& operator << (std::ostream&, const Date& date);
  friend std::istream& operator >> (std::istream&, Date& date);
};

#endif



