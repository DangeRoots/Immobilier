#ifndef WIDGETSOUHAIT_H
#define WIDGETSOUHAIT_H

/*!
  * \file widgetsouhait.h
  * \brief Composant graphique du souhait
  * 
  * \author Icham Sirat
  * \version 1.0
  */

#include <QWidget>
#include <QPushButton>
#include <Souhait.h>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
    class WidgetSouhait;
}

/*!
 * \class WidgetSouhait
 * \brief Composant graphique du so)uhait
 * 
 * Cette classe décrit le composant graphique du souhait.
 * Ce composant est utilisé dans les écrans de recherche. Il permet
 * l'affichage des données du souhait et propose un certain nombre de boutons
 * disponibles pour exécuter des actions sur le souhait, tels qu'accéder
 * au détail du souhait.
 * Ces actions peuvent être reprogrammées et associées dynamiquement à des actions
 * lors de la construction du composant.
 */
class WidgetSouhait : public QWidget
{
    Q_OBJECT
    
public:
    /*!
      \brief    Constructeur par défaut
      */
    explicit WidgetSouhait(QWidget *parent = 0);

    /*!
      \brief    Constructeur
      \param [in,out]	souhait	Souhait*, le souhait
      \param [in,out]	parent	QWidget*, le parent
      */     
    WidgetSouhait(Souhait *souhait, QWidget *parent = 0);

    /*!
      \brief    Destructeur
      */     
    ~WidgetSouhait();

    /*!
     * \brief    Modifier le budget maximum
     * 
     * Permet de modifier le budget maximum du souhait
     * \param [in]   budget entier non signé, le nouveau budget max
     * \return 	void
     */
    void setBudgetMax(unsigned int budget);

    /*!
     * \brief    Modifier la surface habitable souhaitée
     * 
     * Permet de modifier la surface habitable souhaitée
     * \param [in]   surf entier non signé, la nouvelle surface
     * \return 	void
     */
    void setSurfaceHabitableSouhaitee(unsigned int surf);

    /*!
     * \brief    Modifier la surface de jardin souhaitée
     * 
     * Permet de modifier la surface de jardin souhaitée
     * \param [in]   surf entier non signé, la nouvelle surface
     * \return 	void
     */
    void setSurfaceJardinSouhaitee(unsigned int surf);

    /*!
     * \brief    Obtenir le budget maximum
     * 
     * Permet d'obtenir le budget maximum souhaité
     * \return 	entier	le budget
     */
    int getBudgetMax();

    /*!
     * \brief    Obtenir la surface habitable souhaitée
     * 
     * Permet d'obtenir la surface habitable souhaitée
     * \return 	entier	la surface
     */
    int getSurfaceHabitableSouhaitee();

    /*!
     * \brief    Obtenir la surface de jardin souhaitée
     * 
     * Permet d'obtenir la surface de jardin souhaitée
     * \return 	entier	la surface
     */
    int getSurfaceJardinSouhaitee();

    /*!
     * \brief    Obtenir le bouton de détail du souhait
     * 
     * Permet d'obtenir le bouton d'accès au détail du souhait.
     * Les actions déclenchées par ce bouton sont programmables
     * au moyen de signaux et de slots.
     * \return	QPushButton*
     */
    QPushButton* getBoutonDialogSouhait();

    /*!
     * \brief    Obtenir le bouton de suppression du souhait
     * 
     * Permet d'obtenir le bouton de suppression du souhait.
     * Les actions déclenchées par ce bouton sont programmables
     * au moyen de signaux et de slots.
     * \return	QPushButton*
     */
    QPushButton* getBoutonSupprimer();
    
private:
    Ui::WidgetSouhait *ui;
    Souhait *m_souhait;

    QList<Ville *> m_listeVilles;
};

#endif // WIDGETSOUHAIT_H
