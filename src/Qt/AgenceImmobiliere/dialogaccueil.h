#ifndef DIALOGACCUEIL_H
#define DIALOGACCUEIL_H

/*!
  \file dialogaccueil.h
  \brief Cette classe permet de créer la fenêtre principale de l'application.
  \class L'application est organisée autour d'un certain nombre de fenêtre dépendantes les unes des autres. La classe dialogaccueil contient la fenêtre principale. Toutes les autres fenêtres et tous les autres objets dépendent d'elle. Sa destruction entraîne la destruction de tous les autres objets et la fermeture de l'application. 
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

namespace Ui {
    class DialogAccueil;
}

class DialogAccueil : public QDialog
{
    Q_OBJECT

public:
    /*!
      \brief    Constructeur
      \param [in]   *parent	le parent
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
    void reset();
    void chercherClients();
    void nouveauClient();
    void nouveauBien(int);
    void ouvrirClient(int);
    void ouvrirListeSouhaits(int);
    void ouvrirListeBiens(int);
    void nouveauSouhait(int);

//    void gestionAgents();
};

#endif // DIALOGACCUEIL_H
