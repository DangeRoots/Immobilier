#ifndef WIDGETCLIENT_H
#define WIDGETCLIENT_H

/*!
  * \file widgetclient.h
  * \brief Composant graphique du client
  * 
  * \author Gilles Coulais
  * \version 1.0
  */

#include <QWidget>
#include <QPushButton>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
    class WidgetClient;
}

/*!
 * \class WidgetClient
 * \brief Composant graphique du client
 * 
 * Cette classe décrit le composant graphique du client.
 * Ce composant est utilisé dans les écrans de recherche. Il permet
 * l'affichage des données du client et propose un certain nombre de boutons
 * disponibles pour exécuter des actions sur le client, tels qu'accéder
 * au détail du client ou rechercher les biens ou souhaits correspondant.
 * Ces actions peuvent être reprogrammées et associées dynamiquement à des actions
 * lors de la construction du composant.
 */
class WidgetClient : public QWidget
{
    Q_OBJECT

public:
    /*!
      \brief    Constructeur par défaut
      */
    explicit WidgetClient(QWidget *parent = 0);

    /*!
      \brief    Destructeur
      */    
    ~WidgetClient();

    /*!
     * \brief    Modifier le nom affiché
     * 
     * Permet de modifier le nom de client affiché
     * \param [in]   nom string, le nouveau nom
     * \return 	void
     */    
    void setNom(QString nom);

    /*!
     * \brief    Modifier l'adresse affichée
     * 
     * Permet de modifier l'adresse de client affichée
     * \param [in]   adresse string, la nouvelle adresse
     * \return 	void
     */    
    void setAdresse(QString adresse);

    /*!
     * \brief    Modifier le téléphone affiché
     * 
     * Permet de modifier le numéro de téléphone affiché
     * \param [in]   tel string, le nouveau téléphone
     * \return 	void
     */    
    void setTelephone(QString tel);

    /*!
     * \brief    Modifier la ville affichée
     * 
     * Permet de modifier le nom de ville affiché
     * \param [in]   ville string, le nouveau nom de ville
     * \return 	void
     */    
    void setVille(QString ville);

    /*!
     * \brief    Modifier le code postal affiché
     * 
     * Permet de modifier le code postal affiché
     * \param [in]   cp string, le nouveau code postal
     * \return 	void
     */    
    void setCodePostal(QString cp);

    /*!
     * \brief    Modifier l'image du bien
     * 
     * Permet de modifier l'image affichée à l'écran pour matérialiser un bien
     * \param [in]   image QPixmap, la nouvelle image
     * \return 	void
     */    
    void setImageBien(QPixmap image);

    /*!
     * \brief    Modifier l'image du souhait
     * 
     * Permet de modifier l'image affichée à l'écran pour matérialiser un souhait
     * \param [in]   image QPixmap, la nouvelle image
     * \return 	void
     */    
    void setImageSouhait(QPixmap image);

    /*!
     * \brief    Obtenir le bouton d'accès aux biens
     * 
     * Permet d'obtenir le bouton d'accès aux biens du client ou 
     * à l'écran de création d'un bien 
     * Les actions déclenchées par ce bouton sont programmables
     * au moyen de signaux et de slots.
     * \return	QPushButton
     */
    QPushButton *getBoutonBien();

    /*!
     * \brief    Obtenir le bouton d'accès aux souhaits
     * 
     * Permet d'obtenir le bouton d'accès aux souhaits du client ou 
     * à l'écran de création d'un souhait
     * Les actions déclenchées par ce bouton sont programmables
     * au moyen de signaux et de slots.
     * \return	QPushButton
     */
    QPushButton *getBoutonSouhait();

    /*!
     * \brief    Obtenir le bouton d'accès au détail du client
     * 
     * Permet d'obtenir le bouton d'accès au détail du client et donc
     * d'ouvrir l'écran de modification du client.
     * Les actions déclenchées par ce bouton sont programmables
     * au moyen de signaux et de slots.
     * \return	QPushButton
     */
    QPushButton *getBoutonClient();

private:
    Ui::WidgetClient *ui;

};

#endif // WIDGETCLIENT_H
