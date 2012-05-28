#ifndef DIALOGSOUHAIT_H
#define DIALOGSOUHAIT_H

/*!
  * \file dialogsouhait.h
  * \brief Fenêtre de détail du souhait
  * 
  * \author Icham Sirat
  * \version 1.0
  */

#include <QDialog>
#include <ui_barreMenuFiche.h>
#include <Souhait.h>
#include <Ville.h>
#include <QMessageBox>
#include <BDD.h>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
    class DialogSouhait;
}

/*!
 * \class DialogSouhait
 * \brief Écran de détail d'un souhait
 * 
 * Cette classe permet d'afficher un souhait
 * et les données associées à ce souhait. Il est alors possible
 * de modifier ces données et de sauvegarder le souhait. 
 * Cet écran est également utilisé lors de la création d'un souhait.
 */
class DialogSouhait : public QDialog
{
    Q_OBJECT

public:
    /*!
      \brief    Constructeur par défaut
      */
    explicit DialogSouhait(QWidget *parent = 0);
    
	/*!
      \brief    Constructeur
      \param [in,out]   souhait Souhait*, le souhait à afficher
      \param [in,out]   parent QWidget*, la fenêtre parente
      */    
    DialogSouhait(Souhait *souhait, QWidget *parent = 0);
    
    /*!
      \brief    Destructeur
      */
    ~DialogSouhait();

private:
    Ui::DialogSouhait *ui;
    Ui::barreMenuFiche m_menu;
    Souhait *m_souhait;
    QList<Ville *> m_listeVilles;
    QList<qint16> m_listeNumeroSouhaits;
    BDD *m_db;

    bool checkData();
    bool changed;

public slots:
    /*!
      * \brief    Changer d'état
      * 
      * Permet de changer l'objet d'état
      * L'état est modifié dès qu'une donnée a été modifiée
      * Dans ce cas, à la fermeture de la fenêtre, une sauvegarde
      * sera proposée.
	  * \attention SLOT QT
      * \return   void
      */
    void setEtat(QString);

    /*!
      * \brief    Fermer la fenêtre
      * 
      * Permet de fermer la fenêtre de dialogue
      * Ce slot vérifie que des données n'ont pas été modifiées,
      *  le cas échéant, propose la sauvegarde des données
      *  puis ferme la fenêtre de dialogue
	  * \attention SLOT QT
      * \return   void
      */
    void fermer();

    /*!
      * \brief	Sauvegarder le souhait
      * 
      * Permet de sauvegarder les données du souhait dans la base. 
      * Ce slot vérifie que les données nécessaires ont été saisies
      * puis demande à la base de données de sauvegarder le souhait
      * Si le souhait n'existe pas, il est créé par la base.
      * \attention SLOT QT
      * \return   void
      */
    void valider();
    
    /*!
      * \brief    Recherche de villes
      * 
      * Permet de rechercher les villes correspondant à un code postal
      * Lorsqu'une ville est trouvé, son nom est affiché dans une comboBox.
	  * \attention SLOT QT
      * \return   void
      */    
    void chercherVilles();

     /*!
      * \brief    Ajouter une ville
      * 
      * Permet d'ajouter une ville au souhait. Un souhait est valable pour une
      * ou plusieurs villes. Ce SLOT permet d'ajouter une nouvelle ville à la 
      * liste des villes associées à un souhiat.
      * 
	  * \attention SLOT QT
      * \return   void
      */    
    void copierVille(QString);
};

#endif // DIALOGSOUHAIT_H
