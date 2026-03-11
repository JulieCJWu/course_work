/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    http://ericbeaudry.ca/INF3105/tp2/
*/

/* arbremap.h
 *
 * @author Chao-Jung (Julie) Wu; LUO, Xiaohui (LUOX31037903)
 * @version 1.00.05 // 161112 luo
 * @since 2016-11-06
 */


#if !defined(__ARBREMAP__H__)
#define __ARBREMAP__H__

#include "arbreavl.h"

template <class K, class V>
class ArbreMap
{

 class Entree{
    public:
        Entree(const K& cle)
            :cle(cle),valeur(){}
        K cle;
        V valeur;

        bool operator < (const Entree& e) const 
            { return cle < e.cle; }
 };

 ArbreAVL<Entree> entrees;

  public:
    bool contient(const K&) const;
    void enlever(const K&);
    void vider();
    bool vide() const;
    const V& operator[] (const K&) const;
    V& operator[] (const K&);

    class Iterateur {
      public:
        Iterateur(ArbreMap& a) 
            : iter(a.entrees.debut()) {}

        Iterateur(typename ArbreAVL<Entree>::Iterateur i) 
            : iter(i) {}

        operator bool() const 
            {return iter.operator bool();};


        Iterateur& operator++() 
            {++iter; return *this;}
        Iterateur& operator--() 
            {--iter; return *this;}     
        const Iterateur& operator* () const {return *this;}//overloading *Iterator

        const K& cle() const 
            {return (*iter).cle;}

        V& valeur() 
            {return (V&) (*iter).valeur;}

      private:
        typename ArbreAVL<Entree>::Iterateur iter;
        };

    Iterateur debut() 
        { return Iterateur(*this); }

    Iterateur fin() 
        { return Iterateur(entrees.fin());}

    //Iterateur rechercher(const K& cle)
    Iterateur rechercher(const K& cle) const // I added const, not sure if good
        { return Iterateur(entrees.rechercher(cle));}

    Iterateur rechercherEgalOuSuivant(const K& cle) 
        {return Iterateur(entrees.rechercherEgalOuSuivant(cle));}

    //Iterateur rechercherEgalOuPrecedent(const K& cle)
    Iterateur rechercherEgalOuPrecedent(const K& cle) const // I added const, not sure if good
        {return Iterateur(entrees.rechercherEgalOuPrecedent(cle));}

  private:
    // À compléter
};


template <class K, class V>
void ArbreMap<K,V>::vider(){
    typename ArbreAVL<Entree>::Iterateur iter = entrees.debut();
    while(iter){ 
        Entree  *e = &entrees[iter];
        iter++;       
        delete e;
    }
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const{
       typename ArbreAVL<Entree>::Iterateur iter = entrees.debut();
       return !entrees[iter].cle;
}

template <class K, class V>
void ArbreMap<K,V>::enlever(const K& cle)
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(Entree(cle));
    if(iter != NULL){
        entrees[iter].valeur = NULL;
        entrees[iter].cle = NULL;
        delete entrees;   
    }
}

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& cle) const
{
    Entree entree(cle);
    return entrees.contient(entree);
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& cle)  const
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(Entree(cle));
    return entrees[iter].valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& cle)
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(Entree(cle));
    if(!iter){
        entrees.inserer(Entree(cle));
        iter = entrees.rechercher(cle);
    }
    return entrees[iter].valeur;
}

#endif
