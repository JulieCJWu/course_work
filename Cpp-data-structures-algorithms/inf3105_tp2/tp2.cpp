/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    http://ericbeaudry.ca/INF3105/tp2/
*/

/* tp2.cpp
 *
 * @author Chao-Jung (Julie) Wu; LUO, Xiaohui (LUOX31037903);
 * @version 2.00.03 // 
 * @since 2016-11-07
 */


#include <fstream>
#include <iostream>
#include <string>
#include "succ.h"
#include "point.h"

using namespace std;

/*
 * PROTOTYPE
 */
int tp2(istream& entree);
bool suggerer (Succursale &departure, Succursale &arrival , Date &debut, Date &fin, Point &origine, Point &destination, ArbreMap<string, Succursale> &branches);

/*
 *  MAIN()
 *  
 *  syntaxe d'appel : ./tp2 [nomfichier.txt]
 */
int main(int argc, const char** argv){
    // Gestion de l'entrée :
    //  - lecture depuis un fichier si un argument est spécifié;
    //  - sinon, lecture depuis std::cin.
    if(argc>1){
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail()){
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
         return tp2(entree_fichier);
    }else
         return tp2(std::cin);        

    return 0;
}


/*
 *  FUNCTION TP2
 */

/*
 * read data from file or std input
 *
 * creer:     register branches data
 * reserver:  accept or refuse reservatiob request, and update bookings if accept
 * suggerer:  suggest pick up and return branches for client's inqury
 *
 * @param entree    file name or std::cin to be read
 */
int tp2(istream& entree){
    ArbreMap<string, Succursale> branches; //nom -> branch data
    Date init = Date();
    
    int id=0;
    while(entree){
        std::string commande;
        entree >> commande >> ws;
        if(!entree) break;
        cout << ++id << " : ";
       
        if(commande=="creer"){
            string nom;
            Point p;            
            int nbVoitures=0, nbPlacesLibres=0;
            entree >> nom >> p >> nbVoitures >> nbPlacesLibres;
            
            Succursale s(nom, p, nbVoitures+nbPlacesLibres);
            s.ajouter(init, nbVoitures);
            branches[nom] = s;
            
            cout << "Creee"  << endl;
        }else if(commande=="reserver"){
            string origine, destination;
            Date debut, fin;
            entree >> origine >> debut >> destination >> fin;
            bool ok = false;

            if (branches.contient(origine) && branches.contient(destination))
                ok = branches[origine].verifyAvail (debut, fin, branches[destination]);
                        
            cout << (ok ? "Acceptee" : "NonDispo") << endl;
        }else if(commande=="suggerer"){
            Point origine, destination;
            Date debut, fin;
            entree >> origine >> debut >> destination >> fin;
            bool ok = false;
            Succursale departure;
            Succursale arrival;
            
            ok = suggerer (departure, arrival, debut, fin, origine, destination, branches);

            if (ok)
                cout << departure << " " << arrival << endl;

            else
                cout << "Impossible" << endl;
        }else{
            cout << "Commande '" << commande << "' invalide!" << endl;
            return 2;
        }
        char pointvigule=0;
        entree >> pointvigule >> ws;
        if(pointvigule!=';'){
            cout << "Fichier d'entrée invalide!" << endl;
            return 3;
        }
    }
    
    return 0;
}

/* 
 *  FUNCTION SUGGESTION
 */
bool suggerer(Succursale& departure, Succursale& arrival, Date &debut, Date &fin,
    Point &origine, Point &destination, ArbreMap<string, Succursale> &branches) {

    bool candidate;
    ArbreMap<string, Succursale>::Iterateur iter_branches(branches);
    if (!iter_branches)
        return false;
    ArbreMap<string, Succursale>::Iterateur iter_branches_copy = iter_branches;

    //destination and origine are different branches
    ArbreMap<double, Succursale> destination_candidates;
    while (iter_branches) {
        it_type iter_bookings = iter_branches.valeur().get_it(fin);
        candidate = true;
        while (iter_bookings) {
            if (! branches[iter_branches.cle()].hasParking(iter_bookings.cle())) {
                candidate = false;
                break;
            }
            ++iter_bookings;
        }
        if (candidate)
            destination_candidates[iter_branches.valeur().distance(destination)] = iter_branches.valeur();

        ++iter_branches;
    }
    ArbreMap<double, Succursale>::Iterateur iter_destination_candidates(destination_candidates);

    iter_branches = iter_branches_copy;
    ArbreMap<double, Succursale> origine_candidates;
    while (iter_branches) {

        it_type iter_bookings = iter_branches.valeur().get_it(debut);
        it_type iter_bookings_copy = iter_bookings;
        
        // departure and arrival at different branches
        if ( iter_branches.valeur() != iter_destination_candidates.valeur() ) {// departure and arrival at different branches
            candidate = true;
            while (iter_bookings) {
                if (iter_bookings.valeur() == 0) {
                    candidate = false;
                    break;
                }
                ++iter_bookings;
            }
            if (candidate) 
                origine_candidates[iter_branches.valeur().distance(origine)] = iter_branches.valeur(); 
        }
        
        //destination and origine are SAME branch
        iter_bookings = iter_bookings_copy;
        if ( iter_branches.valeur() == iter_destination_candidates.valeur() ) {
            candidate = true;
            it_type iter2 = iter_branches.valeur().get_it(fin);
            if ( (! iter_branches.valeur().trouve_it(fin)) && iter2.valeur() == 0)
                candidate = false;
            if (candidate) 
            {
            while (iter_bookings && iter_bookings.cle() < fin) {
                if (iter_bookings.valeur() == 0) {
                    candidate = false;
                    break;
                }
                ++iter_bookings;
            }
            }
            if (candidate) {
                origine_candidates[iter_branches.valeur().distance(origine)] = iter_branches.valeur(); // ajouter origine candidates
                destination_candidates[iter_branches.valeur().distance(destination)] = iter_branches.valeur(); //ajouter destination candidates
            }
        }
        ++iter_branches;
    }
    ArbreMap<double, Succursale>::Iterateur iter_origine_candidates(origine_candidates);
    departure = iter_origine_candidates.valeur(); // decision made
    arrival = iter_destination_candidates.valeur(); // decision made

    return true;
}
