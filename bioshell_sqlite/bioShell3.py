#!/usr/bin/python
#==== les imports ============
import os.path
from Bio import Entrez, SeqIO, GenBank
import sqlite3
import re

#==== introduction du programme ============
programme = "bioShell3"
authors = "Chao-Jung Wu"
version = "3.03.03"
date = "Automne 2015"
"""
Ce programme sauvegarde le SeqRecord depuis NCBI dans un fichier locale, et charge les données pertinentes à la BD locale.
Ce programme est (sera) optimisé ver traiter les séquences de HIV.

Avant d’afficher le prompt, le programme connect à la BD « sequences.db », et genere un repertoire « sequences » pour sauvgarder les fichiers des sequences depuis NCBI.

== Liste des commandes du shell ==
exit / quit : quitter le programme.
help        : afficher la liste des commandes.
list        : affichage de la liste des séquences dans la BD.
load        : charge le SeqRecord d'accession depuis NCBI dans un fichier sous « sequences », et charge les données pertinentes à la BD
remove      : suppression d’une séquence en spécifiant en option son id. Format : remove ID
infos       : affichage les donnéees et statistiques de la séquence dont l’id est passée en paramètre. Format : infos ID
find        : recherche d’un motif dans toutes les séquences. Format : find motif
loadmany    : charge un fichier des accessions, et LOAD chaque accession . Fomat: loadmany fichier
view        : affiche le contenu d'un fichier de SeqRecord locale. Format: view ID
"""
introduction = programme+" version "+version+", par "+authors+" ("+date+")"
print ( "\n"+"="* (len(introduction)+5) )
print ( "==", introduction, "  " )
print ( "="* (len(introduction)+5) +"\n")

#==== les variables des fonctions ========================
cmd_valide_single = "exit", "quit", "help", "list",
cmd_valide_composite = "add", "remove", "infos", "find", "load", "loadmany", "view"
SiteParType = ["a c t g".split(),
               "a c u g".split(),
               "a c d e f g h i k l m n p q r s t v w y".split()]
dataTypeNames = ["adn", "arn", "aa"]
size_limit = int(10000) # taille maximun de SeqRecord (length de sequence)
motif_size = int(5)     # taille minimun de motif

BD_Data = {}            # BD_Data = {champ, valeur} dans la BD locale
BD_ChampParType = "accession, seq_length, molecular_type, definition, date, sequence_content, isolate, country, subtype, organism, gene".split(", ")
accession, seq_length, molecular_type, definition, date, gene, product, sequence_content, isolate, country, subtype, organism, id_groupGene = "", "", "", "", "", "", "", "", "", "", "", "", "", 

#==== les fonctions ========================
def test_existence_repertoire():
    """ Genere un repertoire pour garder les fichiers SeqRecord d'accesion"""
    if not os.path.exists("sequences"):
        os.mkdir("sequences")
		
def fin_du_programme( liste_cmd ):
    """ Retourne True si la commande saisie est quit ou exit, sinon False """
    if commande_est("exit", liste_cmd) or commande_est("quit", liste_cmd):
        conn.close()
        print("\nFin normal du shell, à bientôt...\n")
        return True
    return False

def lire_commande():
    """ Retourne une liste de la commande + les options lus au clavier """
    liste_cmd = []
    while liste_cmd == []:
        liste_cmd = input("bioShell3> ").lower().split()    
    return liste_cmd

def commande_est( cmd_a_tester, liste_cmd):
    """ Retourne True si la commande est tester est celle qui est saisie """
    if len(liste_cmd) == 1 and cmd_a_tester == liste_cmd[0] and liste_cmd[0] in cmd_valide_single:
        return True	
    elif len(liste_cmd) == 2 and cmd_a_tester == liste_cmd[0] and liste_cmd[0] in cmd_valide_composite:
        return True

def afficher_help():
    """ Affiche l'aide """
    print("\n== Liste des commandes du shell ==")
    print("exit / quit : quitter le programme.")
    print("help        : afficher la liste des commandes.")
    print("list        : affichage de la liste des séquences dans la BD.")
    print("remove      : suppression d’une séquence en spécifiant en option son id. Format : remove ID")
    print("infos       : affichage les donnéees et statistiques de la séquence dont l’id est passée en paramètre. Format : infos ID")
    print("find        : recherche d’un motif dans toutes les séquences. Format : find motif")
    print("loadmany    : charge un fichier des accessions, et LOAD chaque accession . Fomat: loadmany fichier")
    print("view        : affiche le contenu d'un fichier de SeqRecord locale. Format: view ID\n")
        
def afficher_message_erreur():
    """ Affiche un message d'erreur pour une commande inconnue """
    print("\nCette commande n'est pas valide.")

def createTable(c):
    """Genere 2 tables pour les données récupérée depuis SeqRecord"""
    c.executescript('''
        CREATE TABLE IF NOT EXISTS groupGene (
            gene             TEXT      NOT NULL,
            accession        TEXT      NOT NULL,
            id_groupGene     INTEGER   NOT NULL,

            PRIMARY KEY (id_groupGene)
            FOREIGN KEY (accession) REFERENCES genbank (accession) ON DELETE CASCADE
            );
            
        CREATE TABLE IF NOT EXISTS genbank (
            accession        TEXT      NOT NULL,
            seq_length       INTEGER   NOT NULL,
            molecular_type   TEXT,
            definition       TEXT,
            date             TEXT,
            sequence_content TEXT      NOT NULL,
            isolate          TEXT,
            country          TEXT,
            subtype          TEXT,
            organism         TEXT,
                  
            PRIMARY KEY (accession)
            );

        CREATE TABLE IF NOT EXISTS groupProtein (
            HIVgene          TEXT      NOT NULL,
            product          TEXT      NOT NULL,

            PRIMARY KEY (HIVgene)
            );      
        ''')
    icount = 0
    for row in c.execute('''SELECT * FROM groupProtein'''):
        icount += 1    
    if icount <= 0:
        c.executescript('''       
            INSERT INTO groupProtein VALUES ("gag", "Gag polyprotein (MA, CA, SP1, NC, SP2, P6)");
            INSERT INTO groupProtein VALUES ("pol", "Pol polyprotein (RT, RNase H, IN, PR)");
            INSERT INTO groupProtein VALUES ("env", "gp160 (gp120, gp41)");
            INSERT INTO groupProtein VALUES ("tat", "Tat");
            INSERT INTO groupProtein VALUES ("rev", "Rev");
            INSERT INTO groupProtein VALUES ("nef", "Nef");
            INSERT INTO groupProtein VALUES ("vpr", "Vpr");
            INSERT INTO groupProtein VALUES ("vif", "Vif");
            INSERT INTO groupProtein VALUES ("vpu", "Vpu");
       ''')

def ID_format_estValide( ID ):
    """ Retourne True si l'id est de la forme XX999999 (2 lettres + 6 chiffres) """
    return re.search('^[A-Za-z]{2}\d{6}$', ID)

def ID_existe_deja(c, ID):
    """ Retourne True si le nouvel id existe dans sequences.db, sinon False """
    ID = ID.upper()
    query = '''SELECT accession FROM genbank'''
    list_seq = []
    for row in c.execute(query):
        list_seq += row
    return ID in list_seq

def insertData_in_genbank(c, liste_cmd):
    """appelle LoadSeqRecord(ID) et store_data(c, record)"""
    ID = liste_cmd[1].upper()
    if ID_format_estValide(ID):
        LoadSeqRecord(ID)
        if not ID_existe_deja(c, ID):
            allrecord = fetch_data(ID)
            if allrecord:
                store_data(c, allrecord)            
        else:
            print("\nL\'accession", ID, "existe dans sequences.db deja.\n")
    else:
        print("\nLe format d'accession", ID, "n'est pas valide: XX999999\n")

def LoadSeqRecord(accession):
    try:
        if not os.path.isfile("sequences/"+accession+".gb"):
            Entrez.email = "Your.Name.Here@example.org"
            handle = Entrez.efetch(db="nucleotide", id=accession, rettype="gb", retmode="text")
            SeqRecord = SeqIO.read(handle, "gb")
            if len(SeqRecord) < size_limit:
                SeqIO.write(SeqRecord, "sequences/"+accession+".gb", "gb")
                handle.close()
                print("\nLe SeqRecord de", accession, "est téléchargé.")
            else:
                print("\nTaille de SeqRecord:", len(SeqRecord), "bp ( size limit:", size_limit, "bp )\nLe SeqRecord de", accession, "est trop grand, aucun fichier est téléchargé.")
        else:
            print("\nLe SeqRecord de", accession, "existe deja.")
    except:
        print("\nERROR: possible que l'accession n'existe pas dans NCBI.")

def fetch_data(ID):
    """retourne un tuple des données depuis le fichier locale de SeqRecord d'accession"""
    try:
        fh = open("sequences/"+ID+".gb", "r")
        accession, seq_length, molecular_type, definition, date, gene, product, protein_id, sequence_content, isolate, country, subtype, organism, id_groupGene = "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        accession = ID
        i = 0
        multigene = {}
        multigene_list = []
        for ligne in fh:
            ligne = ligne.rstrip("\n")
            mots = re.split("\s+", ligne)

            m1 = re.match("^LOCUS", ligne)
            if m1:
                seq_length = mots[2]
                molecular_type = mots[4]
                date = mots[6]
            
            m2 = re.match("^DEFINITION +(.+)", ligne)
            if m2:
                definition = m2.group(1)
    
            m3 = re.search("^\s+/gene=\"([^\s]+)\"", ligne)
            if m3:
                multigene[m3.group(1)] = i
            i += 1
 
            m6 = re.search("^\s+\d+((\s[atcgu]{1,10})+)", ligne)
            if m6:
                m7 = re.sub("\s", "", m6.group(1))
                sequence_content += m7
                
            m8 = re.search("^\s+/(isolate|strain)=\"(.+)\"", ligne)
            if m8:
                isolate = m8.group(2)
  
            m9 = re.search("^\s+/country=\"(.+)\"", ligne)
            if m9:
                country = m9.group(1)
      
            m10 = re.search("^\s+/note=\"subtype:\s*(.+)\"", ligne)
            if m10:
                subtype = m10.group(1)

            m11 = re.search("^\s+/organism=\"(.+)\"", ligne)
            if m11:
                organism = m11.group(1)
                if organism == "Human immunodeficiency virus 1":
                    organism = "HIV-1"

        for key in multigene:
            gene += key+","
        multigene_list = gene.split(",")
        del multigene_list[len(multigene_list)-1]

        record = (gene, accession, seq_length, molecular_type, definition, date, sequence_content, isolate, country, subtype, organism)
        return record, multigene_list
    except:
        print("ERROR: Aucunne donnée est récupérée.\n")

def store_data(c, allrecord):
    """charge les données dans la BD"""
    try:
        c.execute('INSERT INTO genbank (accession, seq_length, molecular_type, definition, date, sequence_content, isolate, country, subtype, organism) VALUES (?,?,?,?,?,?,?,?,?,?)', allrecord[0][1:])
        multigene_list = allrecord[1]
        for i in range(len(multigene_list)):
            c.execute('INSERT INTO groupGene (gene, accession) VALUES (?,?)', (multigene_list[i], allrecord[0][1]))
            conn.commit()
        print("Les données de SeqRecord de", allrecord[0][1], "sont stockés dans sequences.db locale.\n")
    except ValueError:
        print("Des valeurs sont invalides.")
    except sqlite3.Error as e:
        print(e)
    except:
        print("ERROR: Aucunne donnée est stockée à la BD sequences.db.\n")

def lister(c):
    """ Affiche la liste des Sequences """
    query = '''SELECT accession FROM genbank'''
    list_seq = []
    for row in c.execute(query):        
        list_seq += row
    print()
    for i in list_seq:
        print(i)
    print()

def supprimer_sequence(c, liste_cmd):
    """ Supprime une accession de séquence dans sequences.db """
    ID = liste_cmd[1].upper()
    if ID_existe_deja(c, ID):
        c.execute("DELETE FROM groupGene WHERE accession=?", (ID,))        
        c.execute("DELETE FROM genbank WHERE accession=?", (ID,))
        conn.commit()
        print("\nLes données de", ID, "sont supprimees depuis sequences.db\n" )
    else:
        print("\nCet ID d'accession n'existe pas dans sequences.db\n")

def afficher_infos(c, liste_cmd):
    """ Affiche les infos de la séquence sélectionnée (les champs et valeurs, ainsi que les statistiques)"""
    ID = liste_cmd[1].upper()
    if ID_existe_deja(c, ID):
        print()
        query = '''SELECT * FROM genbank WHERE accession=?'''
        data = []
        for row in c.execute(query, (ID,)):
            data += row
        for i in range(len(BD_ChampParType)-1):
            BD_Data[BD_ChampParType[i]] = data[i]
        for champ, valeur in BD_Data.items():
            print("{0:<18s}: {1:}".format(champ, valeur))
        print()

        query = '''SELECT HIVgene, product
                   FROM groupProtein AS gp JOIN groupGene AS gg ON gp.HIVgene = gg.gene
                                        join genbank AS gb ON gb.accession = gg.accession
                   WHERE gb.accession=?'''
        for row in c.execute(query, (ID,)):
            print("{0:<18s}: {1:}".format("gene", row[0]))
            print("{0:<18s}: {1:}".format("product", row[1]), "\n")

        seq_of_interest = BD_Data.get("sequence_content")
        type_de_sequence, count, appearances = statistiques (seq_of_interest)
        print("Statistiques      : ")   # afficher le numbre de chaque residue, sauf numbre est 0
        for residue, appearance in appearances.items():
            if appearance != 0:
                print("{0:<5s}:{1:6}".format(residue, appearance))
        print()
    else:
        print("\nCet ID n'existe pas dans la BD, réessayez ...\n")

def statistiques (seq_of_interest):
    """retourne les analyses de la sequence"""
    for i in range(3):
        count = 0
        appearances = {}
        type_de_sequence = ""
        for j in SiteParType[i]:
            appearances[j] = seq_of_interest.count(j)
            count += appearances[j]
        if count == len(seq_of_interest):
            type_de_sequence = dataTypeNames[i]
            break
    return type_de_sequence, count, appearances

def trouver_motif(c, liste_cmd):
    """ Affiche la position du motif dans chaque séquence """
    motif = liste_cmd[1]
    if len(motif) >= motif_size:
        motif_pas_trouve = True
        print()
        for row in c.execute("SELECT accession, sequence_content from genbank"):
            ID = row[0]
            sequence = row[1]        
            if motif in sequence:
                motif_pas_trouve = False
                position = sequence.find(motif, 0)
                while position != -1:  # -1 => pas trouver, erreur
                    print("id="+ID, "=>","position :", position)
                    position = sequence.find(motif, position+1)
        if motif_pas_trouve:
            print("Le motif n'est pas reconnu dans les séquences.")
        print()
    else:
        print("\nLa taille minimun de motif est", motif_size, "bp dans ce program.\n")

def loadMany_depuisFichier(c, liste_cmd):
    """ lire un fichier qui contient plusieurs numeros d'accession, et LOAD les accessions dans les fichiers et la BD """
    if os.path.isfile(liste_cmd[1]):
        try:
            fh = open(liste_cmd[1], "r")
            deja_charge = False
            for ligne in fh:
                ID = ligne.upper().rstrip("\n")
                liste_accession = []
                query = '''SELECT accession FROM genbank'''
                for row in c.execute(query):
                    liste_accession += row
                if ID not in liste_accession:
                    liste_cmd = ["", ID]
                    insertData_in_genbank(c, liste_cmd)
                else:
                    deja_charge = True
            if deja_charge:
                print("\nQuelque(s) accession(s) existe un fichier locale deja.\n")
        except:
            print("\nERROR: problem à lire le fichier: ", liste_cmd[1], "\n")
    else:
        print("\nERROR: Le fichier ", liste_cmd[1], "n'existe pas.\n")
        
def View_fichierLocale(c, liste_cmd):
    """affiche le contenu d'un SeqRecord locale"""
    accession = liste_cmd[1].upper()
    if os.path.isfile( "sequences/"+accession+".gb"):
        fh = open("sequences/"+accession+".gb", "r")
        print()
        for ligne in fh:
            print(ligne.rstrip())
        print()
    else:
        print("Cet fichier n'existe pas. Passez en parametre l'option LIST et réessayez ...\n")

'''
========================================================
==== programme principale ==============================
========================================================'''
#==== connection a la base de donnees ==================
conn = sqlite3.connect('sequences.db')
c = conn.cursor()

#==== creation de la table genebank ====================
createTable(c)
test_existence_repertoire()

#==== option ===========================================
liste_cmd = []
liste_cmd = lire_commande()

while not fin_du_programme(liste_cmd):

    if commande_est("help", liste_cmd):
        afficher_help()

    elif commande_est("list", liste_cmd):
        lister(c)
         
    elif commande_est("load", liste_cmd):
        insertData_in_genbank(c, liste_cmd)

    elif commande_est("remove", liste_cmd):
        supprimer_sequence(c, liste_cmd)

    elif commande_est("infos", liste_cmd):
        afficher_infos(c, liste_cmd)
    
    elif commande_est("find", liste_cmd):
        trouver_motif(c, liste_cmd)

    elif commande_est("loadmany", liste_cmd):
        loadMany_depuisFichier(c, liste_cmd)

    elif commande_est("view", liste_cmd):
         View_fichierLocale(c, liste_cmd)
         
    else:
        afficher_message_erreur()
        afficher_help()
    
    liste_cmd = lire_commande()
