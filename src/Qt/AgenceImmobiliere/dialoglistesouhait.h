#ifndef DIALOGLISTESOUHAIT_H
#define DIALOGLISTESOUHAIT_H

/*!
  * \file dialoglistesouhait.h
  * \brief Liste des souhaits d'un client
  * 
  * \author Gilles Coulais
  * \author Icham Sirat
  * \version 1.0
  */

#include <QDialog>
#include <ui_barreMenuFiche.h>
#include <Client.h>
#include <BDD.h>
#include <QMessageBox>
#include <Souhait.h>
#include <widgetsouhait.h>
#include <Ville.h>
#include <dialogsouhait.h>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
class DialogListeSouhait;
}

/*!
 * \class DialogListeSouhait
 * \brief Liste des souhaits d'un client
 * 
 * Cette classe permet d'afficher la liste des souhaits d'un client 
 * et les données associées à ces souhaits.
 * En outre, chaque souhait listé est associé à des actions possibles, telles 
 * que l'accès à la fenêtre de détail du souhait.
 */
class DialogListeSouhait : public QDialog
{
    Q_OBJECT
    
public:
	/*!
      \brief    Constructeur
      \param [in,out]   client Client*, le client dont les souhaits doivent être affichés.
      \param [in,out]   parent QWidget*, la fenêtre parente
      */
    DialogListeSouhait(Client *client, QWidget *parent = 0);

    /*!
      \brief    Destructeur
      */
    ~DialogListeSouhait();
    
private:
    Ui::DialogListeSouhait *ui;
    Ui::barreMenuFiche m_menu;

    Client *m_client;
    DialogSouhait *m_dialogSouhait;
    BDD *m_db;
    Souhait *m_souhaitCourant;
    QList<Souhait *> m_listeSouhaits;
    QList<Ville *> m_listeVilles;

    void chercherSouhait();

public slots:
    /*!
      * \brief	Créer un nouveau souhait
      * 
      * Ouvre une fenêtre de détail d'un souhait pour un nouveau souhait.
      * 
      * \attention SLOT QT
      * \return   void
      */
    void nouveauSouhait();

    /*!
      * \brief	Ouvre une fenêtre de détail d'un souhait existant
      * 
      * Ouvre la fenêtre de détail d'un souhait existant. 
      * Cette fenêtre en permettra la modification.
      * 
      * \attention SLOT QT
      * \return   void
      */    
    void ouvrirSouhait(int);
};

#endif // DIALOGLISTESOUHAIT_H
