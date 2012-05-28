#ifndef DIALOGRECHERCHEBIENS_H
#define DIALOGRECHERCHEBIENS_H

/*!
  * \file dialogrecherchebiens.h
  * \brief Écran de recherche multicritères des biens
  * 
  * \author Gilles Coulais
  * \version 0.1
  */
#include <QDialog>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
    class DialogRechercheBiens;
}

/*!
 * \class DialogRechercheBiens
 * \brief Recherche multicritères de biens
 * 
 * Cette classe permet de rechercher des biens en fonction
 * de critères variables, tels que les surfaces de jardin ou surface habitable,
 * ou le prix de vente.
 * 
 * \attention Cet écran n'est pas implémenté. Il n'est donc pas accessible dans l'application.
 */
class DialogRechercheBiens : public QDialog
{
    Q_OBJECT

public:
    /*!
      \brief    Constructeur par défaut
      */
    explicit DialogRechercheBiens(QWidget *parent = 0);

    /*!
      \brief    Destructeur
      */
    ~DialogRechercheBiens();

private:
    Ui::DialogRechercheBiens *ui;
};

#endif // DIALOGRECHERCHEBIENS_H
