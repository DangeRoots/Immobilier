#ifndef DIALOGBIEN_H
#define DIALOGBIEN_H

/*!
  \file dialogbien.h
  \brief Fenêtre de détail du bien. Affiche et permet la modification des données d'un bien
  \author Gilles Coulais
  \version 1.0
  */

#include <QDialog>
#include <ui_barreMenuFiche.h>
#include <Bien.h>
#include <Client.h>
#include <BDD.h>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
    class DialogBien;
}

/*!
 * \class DialogBien
 * \brief Fenêtre de détail du bien
 * 
 * Cette classe contient les méthodes et attributs nécessaires à la présentation
 * graphique d'un bien. Elle permet la modification des données du bien et sa sauvegarde.
 */
class DialogBien : public QDialog
{
    Q_OBJECT

public:

    /*!
      \brief    Constructeur par défaut
      */
    explicit DialogBien(QWidget *parent = 0);
    
	/*!
      \brief    Constructeur
      \param [in,out]   bien Bien*, le bien à afficher
      \param [in,out]   parent QWidget*, la fenêtre parente
      */
    DialogBien(Bien *bien, QWidget *parent=0);

	/*!
      \brief    Constructeur
      \param [in,out]   client Client*, le client associé au bien
      \param [in,out]   parent QWidget*, la fenêtre parente
      */
    DialogBien(Client *client, QWidget *parent=0);
    
    /*!
      \brief    Destructeur
      */
    ~DialogBien();

private:
    Ui::DialogBien *ui;
    Ui::barreMenuFiche m_menu;
    Bien *m_bien;
    BDD *m_db;
    QList <Ville *> m_listeVilles;
    bool changed;
    bool checkData();
    Ville* chercherVille();

public slots:
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
      * \brief    Active le bouton de recherche de villes
      * 
      * Par défaut, le bouton de recherche de villes est désactivé. Il est 
      * nécessaire de saisir un code postal pour activer le bouton.
      * Ce slot permet l'activation du bouton.
	  * \attention SLOT QT
      * \return   void
      */      
    void enableRechercherVilles(QString);

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
      * \brief    Changer d'état
      * 
      * Permet de changer l'objet d'état
      * L'état est modifié dès qu'une donnée a été modifiée
      * Dans ce cas, à la fermeture de la fenêtre, une sauvegarde
      * sera proposée.
	  * \attention SLOT QT
      * \return   void
      */
    void setEtat(QDate);

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
};

#endif // DIALOGBIEN_H
