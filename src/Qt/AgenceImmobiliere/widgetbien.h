#ifndef WIDGETBIEN_H
#define WIDGETBIEN_H

/*!
  * \file widgetbien.h
  * \brief Composant graphique du bien
  * 
  * \author Gilles Coulais
  * \version 1.0
  */

#include <QWidget>
#include <QPushButton>
#include <QDateEdit>
#include <Ville.h>
#include <QDate>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
    class WidgetBien;
}

/*!
 * \class WidgetBien
 * \brief Composant graphique du bien
 * 
 * Cette classe décrit le composant graphique du bien.
 * Ce composant est utilisé dans les écrans de recherche. Il permet
 * l'affichage des données du bien et propose un certain nombre de boutons
 * disponibles pour exécuter des actions sur le bien, tels qu'accéder
 * au détail du bien ou rechercher les souhaits correspondant.
 * Ces actions peuvent être reprogrammées et associées dynamiquement à des actions
 * lors de la construction du composant.
 */
class WidgetBien : public QWidget
{
    Q_OBJECT

public:
    /*!
      \brief    Constructeur par défaut
      */
    explicit WidgetBien(QWidget *parent = 0);
    
    /*!
      \brief    Destructeur
      */    
    ~WidgetBien();

    /*!
     * \brief    Obtenir le bouton de détail du bien
     * 
     * Permet d'obtenir le bouton d'accès au détail du bien.
     * Les actions déclenchées par ce bouton sont programmables
     * au moyen de signaux et de slots.
     * \return	QPushButton
     */
    QPushButton* getBoutonDialogBien();

    /*!
     * \brief    Obtenir le bouton de liste des souhaits
     * 
     * Permet d'obtenir le bouton d'accès à la liste des souhaits.
     * Les actions déclenchées par ce bouton sont programmables
     * au moyen de signaux et de slots.
     * \return	QPushButton
     */
    QPushButton* getBoutonListeSouhaits();

    /*!
     * \brief    Obtenir le prix de vente
     * 
     * Permet d'obtenir le prix de vente du bien.
     * \return 	int	le prix de vente
     */
    int getPrixVente();

    /*!
     * \brief    Obtenir la surface habitable
     * 
     * Permet d'obtenir la surface habitable du bien.
     * \return 	int	la surface habitable
     */
    int getSurfaceHabitable();

    /*!
     * \brief    Obtenir la surface de jardin
     * 
     * Permet d'obtenir la surface de jardin du bien.
     * \return 	int	la surface de jardin
     */
    int getSurfaceJardin();

    /*!
     * \brief    Obtenir le bouton d'édition de la date
     * 
     * Permet d'obtenir le bouton d'édition de la date de mise en vente
     * Les actions déclenchées par ce bouton sont programmables
     * au moyen de signaux et de slots.
     * \return	QDateEdit
     */
    QDateEdit* getBoutonDate();

    /*!
     * \brief    Obtenir la ville 
     * 
     * Permet d'obtenir la ville associée au bien
     * \return 	Ville	la ville
     */
    Ville* getVille();

    /*!
     * \brief    Modifier le prix de vente
     * 
     * Permet de modifier le prix de vente du bien.
     * \param [in]   prix entier, le nouveau prix
     * \return 	void
     */
    void setPrixVente(int prix);

    /*!
     * \brief    Modifier la surface habitable
     * 
     * Permet de modifier la surface habitable du bien.
     * \param [in]   surf entier, la nouvelle surface
     * \return 	void
     */
    void setSurfaceHabitable(int surf);

    /*!
     * \brief    Modifier la surface de jardin
     * 
     * Permet de modifier la surface de jardin du bien.
     * \param [in]   surf entier, la nouvelle surface
     * \return 	void
     */
    void setSurfaceJardin(int surf);

    /*!
     * \brief    Modifier la ville
     * 
     * Permet de modifier le nom de ville affiché
     * \param [in]   ville string, le nouveau nom
     * \return 	void
     */
    void setVille(QString ville);

    /*!
     * \brief    Modifier le code postal
     * 
     * Permet de modifier le code postal affiché
     * \param [in]   cp string, le nouveau code postal
     * \return 	void
     */
    void setCodePostal(QString cp);

    /*!
     * \brief    Modifier la date
     * 
     * Permet de modifier la date de mise en vente affichée
     * \param [in]   date Date, la nouvelle date
     * \return 	void
     */
    void setDateMiseVente(QDate date);

private:
    Ui::WidgetBien *ui;
};

#endif // WIDGETBIEN_H
