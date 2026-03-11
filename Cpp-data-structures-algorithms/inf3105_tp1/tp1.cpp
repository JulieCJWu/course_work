/*  INF3105 | Structures de données et algorithmes
 *  UQAM | Département d'informatique
 *  Automne 2016 | TP1
 *  http://ericbeaudry.ca/INF3105/
 */

/*
 * @author Chao-Jung (Julie) Wu
 * @version 9.00.06
 * @since 2016-09-29
 */
#include <iostream>
#include <fstream>
#include <string>
#include "immeuble.h"
#include "station.h"
#include "tableau.h"



/*
 * PROTOTYPE
 */
int tp1(std::istream& entree);
void calculate_Station_Installation(const Tableau<Station> stations, const Tableau<Immeuble> immeubles, 
        Tableau<double> &frq_served, Tableau<Immeuble>& immeuble_choisi, int& total_clients);
void ExchangeSort(Tableau<Station>& stations);
void displayResults(const Tableau<Station> stations, const Tableau<Immeuble> immeuble_choisi, int& total_clients);
bool verify1stPenalty (const int s, const Tableau<Station> stations, const Tableau<Immeuble> immeuble_choisi, const Immeuble im_i);
void assignFrq(Tableau<double>& frq_served, const Tableau<Immeuble> immeubles, const Station s, const Immeuble im_s);

/*
 *  MAIN()
 */
int main(int argc, char** argv)
{
    if (argc > 1) {
        std::ifstream fichier_entree(argv[1]);

        if(fichier_entree.fail()){
            std::cerr << "Erreur de lecture du fichier '" << argv[1] << "'" << std::endl;
            return 1;
        }
        return tp1(fichier_entree);
    }

    else {
        return tp1(std::cin);
    }
}


/*
 *  FUNCTION TP1
 */

/*
 * reads file or std::cin and displays the results
 * stores stations data in a table template with Station class attributes
 * stores buildings data in a table template with Immeuble class attributes
 * 
 * @param entree    file name or std::cin to be read
 * @return 0        function ends normally
 */
int tp1(std::istream& entree){
    Tableau<Station> stations;
    Tableau<Immeuble> immeubles;
    
    { // Début de la lecture.

        int nbstations=0;
        entree >> nbstations;
        for(int i=0;i<nbstations;i++){
            Station s;
            entree >> s;
            stations.ajouter(s);
        }

        while(entree){
            Immeuble immeuble;
            entree >> immeuble;

            if(!entree)
                break;
            immeubles.ajouter(immeuble);

        }
    } // Fin de la lecture.

    Tableau<double> frq_served;
    for (int i = 0; i < immeubles.taille(); i++)
        frq_served.ajouter(0.0);
    
    Tableau<Immeuble> immeuble_choisi;
    Immeuble immeuble_empty;
    for (int i = 0; i < stations.taille(); i++)
        immeuble_choisi.ajouter(immeuble_empty);

    int total_clients = 0;

    ExchangeSort(stations);

    calculate_Station_Installation(stations, immeubles, frq_served, immeuble_choisi, total_clients);
    displayResults(stations, immeuble_choisi, total_clients);   
    return 0;
}


/* 
 *  OTHER FUNCTIONS
 */



/*
 * sorts stations by radius in descending order
 */
void ExchangeSort(Tableau<Station>& stations){       
     if (stations.taille() == 1) return;
     if (stations.taille() > 2) return;
     int i, j;
     Station temp;  
     int numLength = stations.taille(); 
     for (i=0; i< (numLength -1); i++)    
          for(j = (i+1); j < numLength; j++)   
                if (getRadius(stations[i]) < getRadius(stations[j]))   
                {
                        temp= stations[i];          
                        stations[i] = stations[j];
                        stations[j] = temp;
                }
}




/*
 * calculates the best buidling to install the station
 * displays the names of the stations and the buildings to install
 *
 * @param stations          the table contains the list of stations
 * @param immeubles         the table contains the buildings for which the station wishes to provide service
 * @param immeuble_choisi   the table of chozen buildings to install the corresponding stations
 * @param frq_served        the table of the frequencies of the buildings served by the stations
 * @param total_clients     the total clients served by all the stations
 */
void calculate_Station_Installation(const Tableau<Station> stations, const Tableau<Immeuble> immeubles, 
        Tableau<double> &frq_served, Tableau<Immeuble>& immeuble_choisi, int& total_clients){
    int nbclientmax = -1;
    for (int s = 0; s < stations.taille(); s++) {
        bool penalty = false;
        for (int i = 0; i < immeubles.taille(); i++ ){   // i for cancidate
            if ( stations[s].satisfiesHT( immeubles[i] )) {
                penalty = verify1stPenalty (s, stations, immeuble_choisi, immeubles[i]);
                if (! penalty) {
                    int nbclients = 0;
                    for (int j = 0; j < immeubles.taille(); j++) {
                        if( stations[s].covers(immeubles[i], immeubles[j]) ){ // j for customer
                            if ( frq_served[j] == 0 )
                                nbclients = immeubles[j].addClients( nbclients );
                            if ( frq_served[j] == getFreq(stations[s]))
                                penalty = true;
                        }
                    }
                    if (nbclients >= nbclientmax && !penalty ) {
                        nbclientmax = nbclients;
                        immeuble_choisi[s] = immeubles[i];
                    }
                }
             }
        }
        if (nbclientmax > 0)
            total_clients += nbclientmax;
        nbclientmax = -1;
        assignFrq(frq_served, immeubles, stations[s], immeuble_choisi[s]);
    }
}



/*
 * displays results
 *
 * @param stations          the table contains the list of stations
 * @param immeuble_choisi   the table of chozen buildings to install the corresponding stations
 * @param total_clients     the total clients served by all the stations 
 */
void displayResults(const Tableau<Station> stations, const Tableau<Immeuble> immeuble_choisi, int& total_clients){
    for (int s=0; s < stations.taille(); s++)
        if (getNom( immeuble_choisi[s] ) != "")
            std::cout << stations[s] << " " << immeuble_choisi[s] << std::endl;
        else
            std::cout << stations[s] << " " << "--" << std::endl;
    std::cout << total_clients << std::endl;     
}



/*
 * verifies if there is penalty
 * the penlaty is given when previously installed stations of the same frequency with the current station overlap the service range with the current choice of building
 *
 * @param s                 the index of current station to be installed in the table of stations
 * @param stations          the table contains the list of stations
 * @param immeuble_choisi   the table of chozen buildings to install the corresponding stations
 * @param im_i              the building of the current choice to install the station
 */
bool verify1stPenalty (const int s, Tableau<Station> stations, const Tableau<Immeuble> immeuble_choisi, const Immeuble im_i){   
    bool penalty = false;
    int p = 0;
    while (++p < s)  
        if (
            getFreq(stations[s]) == getFreq(stations[p])
                &&  
            (stations[s].addRadius(stations[p]) <= im_i.distance(immeuble_choisi[p]))
           )
           penalty = true;

    return penalty;
}




/*
 * assigns frequency of the immeuble served by the station to the corresponding frq_served table
 *
 * @param frq_served    the table of the frequencies of the buildings served by the stations
 * @param immeubles     the table contains the buildings for which the station wishes to provide service
 * @param s             the current station
 * @param im_s          the chozen building to install the current station
 *
 */
void assignFrq(Tableau<double>& frq_served, const Tableau<Immeuble> immeubles, const Station s, const Immeuble im_s){
    if (getNom( im_s ) != "")
        for (int k = 0; k < immeubles.taille(); k++)
            if (s.covers(im_s, immeubles[k]))
                if (frq_served[k] == 0)
                    frq_served[k] = getFreq(s);
}
