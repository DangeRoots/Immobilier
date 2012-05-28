#ifndef DIALOGLISTEBIENS_H
#define DIALOGLISTEBIENS_H

/*!
  * \file dialoglistebiens.h
  * \brief Liste des biens d'un client. 
  * 
  * \author Gilles Coulais
  * \version 1.0
  */

#include <ui_barreMenuFiche.h>
#include <QDialog>
#include <QList>
#include <Client.h>
#include <Bien.h>
#include <dialogbien.h>
#include <BDD.h>
#include <dialoglisterecherchesouhaits.h>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
    class DialogListeBiens;
}

/*!
 * \class DialogListeBiens
 * \brief Liste des biens d'un client
 * 
 * Cette classe permet d'afficher la liste des biens d'un client 
 * et les données associées à ces biens.
 * En outre, chaque bien listé est associé à des actions possibles, telles 
 * que l'accès à la fenêtre de détail du bien ou la recherche de souhaits
 * correspondant au bien.
 */
class DialogListeBiens : public QDialog
{
    Q_OBJECT

public:
    /*!
      \brief    Constructeur par défaut
      */
    explicit DialogListeBiens(QWidget *parent = 0);

	/*!
      \brief    Constructeur
      \param [in,out]   client Client*, le client dont les biens doivent être affichés.
      \param [in,out]   parent QWidget*, la fenêtre parente
      */
    DialogListeBiens(Client *client, QWidget *parent = 0);

    /*!
      \brief    Destructeur
      */
    ~DialogListeBiens();

private:
    Ui::DialogListeBiens *ui;
    Ui::barreMenuFiche m_menu;
    Client *m_client;
    QList<Bien *> m_listeBiens;
    DialogBien *m_dialogBien;
    DialogListeRechercheSouhaits *m_listeSouhaits;
    BDD *m_db;
    Bien *m_bienCourant;

    void chercherBiens();
    void reset();

public slots:

    /*!
      * \brief	Ouvrir une fenêtre de dialogue pour un nouveau bien
      * 
      * Un bouton permet d'ouvrir un écran de création d'un bien.
      * Ce SLOT est appelé lors de l'appui sur ce bouton, accompagné des
      * informations relatives au client.
      * \attention SLOT QT
      * \return   void
      */
    void nouveauBien();

    /*!
      * \brief	Ouvrir une fenêtre de dialogue pour un bien existant
      * 
      * Pour chaque bien affiché, un bouton permet d'ouvrir l'écran de détail du bien.
      * Ce SLOT est appelé lors de l'appui sur ce bouton, accompagné des
      * informations relatives au client.
      * \attention SLOT QT
      * \return   void
      */
    void ouvrirBien(int);
    
    /*!
      * \brief	Ouvrir la liste des souhaits correspondant au bien
      * 
      * Pour chaque bien affiché, un bouton permet de rechercher et d'afficher
      * la liste des souhaits correspondants.
      * Ce SLOT est appelé lors de l'appui sur ce bouton, accompagné des
      * informations relatives au bien.
      * \attention SLOT QT
      * \return   void
      */    
    void ouvrirListeSouhaits(int);
};

#endif // DIALOGLISTEBIENS_H
