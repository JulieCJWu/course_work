/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    http://ericbeaudry.ca/INF3105/tp2/
*/

/* date.cpp
 *
 * @author Chao-Jung (Julie) Wu; LUO, Xiaohui (LUOX31037903);
 * @version 1.00.01
 * @since 2016-11-07
 */


#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

Date::Date(int _day, int _hours, int _mins)
  : day(_day), hours(_hours), mins(_mins) {
}

bool Date::operator <(const Date& d) const{
    /* 
    if (day > d.day) return false;
    if (day < d.day) return true;
    if (hours > d.hours) return false;
    if (hours < d.hours) return true;
    return mins < d.mins ? true : false;
    */

    // i tested the two versions, execution time about the same for testF+02.txt (real	2m51.721s)
     
    return (day * 1440 + hours * 60 + mins) < (d.day * 1440 + d.hours * 60 + d.mins);
}

bool Date::operator <=(const Date& d) const{
    return d < *this ? false : true;
}

bool Date::operator ==(const Date& d) const{
    return (day == d.day && hours == d.hours && mins == d.mins);
}

std::ostream& operator << (std::ostream& os, const Date& d){
    int day, hours, mins;
    day = d.day;
    hours = d.hours;
    mins = d.mins;

    char chaine[40];
    sprintf(chaine, "%dj_%02dh%02dm", day, hours, mins);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    int day, hours, mins;
    char j, m, h, underscore;
    is >> day >> j >> underscore >> hours >> h >> mins >> m;
    assert(j=='j');
    assert(underscore=='_');
    assert(h=='h' && m=='m');

    d.day = day;
    d.hours = hours;
    d.mins = mins;
    return is;
}



