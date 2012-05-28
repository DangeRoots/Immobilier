#ifndef DIALOGACCUEIL_H
#define DIALOGACCUEIL_H

/*!
  \file dialogaccueil.h
  \brief Cette classe permet de créer la fenêtre principale de l'application.
  \author Gilles Coulais
  \version 1.0
  */

#include <QDialog>
#include <ui_barreMenuFiche.h>
#include <ui_accueilResultat.h>
#include <widgetclient.h>
#include "BDD.h"
#include "Parametre.h"
#include <dialogbien.h>
#include <dialogsouhait.h>
#include <dialogclient.h>
#include <Client.h>
#include <QList>
#include <dialoglistebiens.h>
#include <dialoglistesouhait.h>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
    class DialogAccueil;
}

/*!
 * \class DialogAccueil
 * \brief Fenêtre d'accueil du logiciel
 * 
 * L'application est organisée autour d'un certain nombre de fenêtre dépendantes les unes des autres.
 * La classe dialogaccueil contient la fenêtre principale. 
 * Toutes les autres fenêtres et tous les autres objets dépendent d'elle. 
 * Sa destruction entraîne la destruction de tous les autres objets et la fermeture de l'application. 
 */

class DialogAccueil : public QDialog
{
    Q_OBJECT

public:
    /*!
      \brief    Constructeur
      \param [in]   *parent	le parent. Ici la fenêtre n'a aucun parent.
      */
    explicit DialogAccueil(QWidget *parent = 0);
    
	/*!
      \brief    Destructeur
      */
    ~DialogAccueil();

private:
    Ui::DialogAccueil *ui;
    Ui::barreMenuFiche m_menu;
    BDD *m_db;
    DialogClient *m_dialogClient;
    DialogListeBiens *m_dialogListeBiens;
    DialogBien *m_dialogBien;
    DialogSouhait *m_dialogSouhait;
    DialogListeSouhait *m_dialogListeSouhaits;
    Client *m_clientCourant;
    QList<Client *> m_listeClients;
//    QList<Agent *> m_listeAgents;

public slots:
    /*!
      * \brief	remise à zéro
      * 
      * Remet à zéro l'intégralité de l'écran
      * Les listes sont vidées, les composants graphiques remis à zéro et reconstruit.
      * Ce slot permet d'obtenir un écran d'accueil à l'image de l'écran de démarrage.
      * \attention SLOT QT
      * \return   void
      */
    void reset();

    /*!
      * \brief	Chercher les clients
      * 
      * Déclenche la recherche des clients correspondant au nom saisi
      * dans la zone de recherche.
      * \attention SLOT QT
      * \return   void
      */    
    void chercherClients();
    
    /*!
      * \brief	Créer nouveau client
      * 
      * Permet de lancer la création d'un nouveau client. 
      * L'écran de détail du client sera affiché, composé de zones intégralement vides en
      * dehors du nom préalablement saisi dans la zone de recherche.
      * \attention SLOT QT
      * \return   void
      */   
    void nouveauClient();
    
    /*!
      * \brief	Créer nouveau bien
      * 
      * Permet de lancer la création d'un nouveau bien. 
      * L'écran de détail du bien sera affiché, composé de zones intégralement vides en
      * dehors du nom du client.
      * \attention SLOT QT
      * \return   void
      */      
    void nouveauBien(int);
    
    /*!
      * \brief	Ouvrir détail client
      * 
      * Permet d'ouvrir l'écran de détail du client
      * L'écran de détail du client sera affiché.
      * \attention SLOT QT
      * \return   void
      */      
    void ouvrirClient(int);
    
    /*!
      * \brief	Ouvrir liste souhaits
      * 
      * Permet d'ouvrir l'écran de liste des souhaits
      * \attention SLOT QT
      * \return   void
      */      
    void ouvrirListeSouhaits(int);

    /*!
      * \brief	Ouvrir liste biens
      * 
      * Permet d'ouvrir l'écran de liste des biens
      * \attention SLOT QT
      * \return   void
      */      
    void ouvrirListeBiens(int);

    /*!
      * \brief	Créer nouveau souhait
      * 
      * Permet de lancer la création d'un nouveau souhait. 
      * L'écran de détail du souhait sera affiché, composé de zones intégralement vides en
      * dehors du nom du client.
      * \attention SLOT QT
      * \return   void
      */      
    void nouveauSouhait(int);

//    void gestionAgents();
};

#endif // DIALOGACCUEIL_H
