#ifndef DIALOGCLIENT_H
#define DIALOGCLIENT_H

/*!
  \file dialogclient.h
  \brief Fenêtre de détail du client. Affiche et permet la modification des données d'un client
  \author Gilles Coulais
  \version 1.0
  */

#include <QDialog>
#include <ui_barreMenuFiche.h>
#include <QList>
#include <Client.h>
#include <BDD.h>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
    class DialogClient;
}

/*!
 * \class DialogClient
 * \brief Fenêtre de détail du client
 * 
 * Cette classe permet d'afficher une fenêtre de détail du client.
 * Il est utile à la création, mais aussi à la modification des données
 * du client telles que son nom ou son adresse.
 * La fenêtre client permet également de sauvegarder des modifications
 * faites sur le client affiché.
 */
class DialogClient : public QDialog
{
    Q_OBJECT

public:
    /*!
      \brief    Constructeur par défaut
      */
    explicit DialogClient(QWidget *parent = 0);

	/*!
      \brief    Constructeur
      \param [in,out]   client Client*, le client à afficher
      \param [in,out]   parent QWidget*, la fenêtre parente
      */
    DialogClient(Client *client, QWidget *parent=0);

    /*!
      * \brief    Destructeur
      */
    ~DialogClient();

    /*!
      * \brief    Obtenir le client
      * 
      * Permet d'obtenir le client
      * \return   Client* le client
      */
    Client* getClient();

private:
    Ui::DialogClient *ui;
    Ui::barreMenuFiche m_menu;
    Client *m_client;
    QList <Ville *> m_listeVilles;
    BDD *m_db;
    bool changed;
    bool checkData();
    Ville* chercherVille();

public slots:
    /*!
      * \brief	Sauvegarder le client
      * 
      * Permet de sauvegarder les données du client dans la base. 
      * Ce slot vérifie que les données nécessaires ont été saisies
      * puis demande à la base de données de sauvegarder le client
      * Si le client n'existe pas, il est créé par la base.
      * \attention SLOT QT
      * \return   void
      */
    void valider();

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
      * \brief    Changer label
      * 
      * Permet de modifier un label dynamiquement
      * Utilisé lors de la saisie d'un nouveau client
      * pour modifier dynamiquement l'intitulé de la fenêtre.
	  * \attention SLOT QT
      * \return   void
      */
    void changerLabel(QString);

    /*!
      * \brief    Recherche de villes
      * 
      * Permet de rechercher les villes correspondant à un code postal
      * Lorsqu'une ville est trouvé, son nom est affiché dans une comboBox.
	  * \attention SLOT QT
      * \return   void
      */
    void chercherVilles();
};

#endif // DIALOGCLIENT_H
