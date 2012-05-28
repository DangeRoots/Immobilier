#ifndef DIALOGLISTERECHERCHESOUHAITS_H
#define DIALOGLISTERECHERCHESOUHAITS_H

/*!
  * \file dialoglisterecherchesouhaits.h
  * \brief Liste des souhaits correspondant au bien d'un client. 
  * 
  * \author Gilles Coulais
  * \version 1.0
  */


#include <QDialog>
#include <widgetsouhait.h>
#include <Souhait.h>
#include <Bien.h>
#include <BDD.h>
#include <ui_barreMenuFiche.h>

/*!
 \namespace Ui
 \brief Espace de nom de l'interface graphique
 */
namespace Ui {
    class DialogListeRechercheSouhaits;
}

/*!
 * \class DialogListeRechercheSouhaits
 * \brief Liste des souhaits associés à un bien
 * 
 * Cette classe permet d'afficher la liste des souhaits associés à un bien.
 * Sur la base des données du bien, cet écran présente la liste des souhaits correspondant.
 * Certaines données du bien sont étendues afin de ne pas proposer une liste de souhaits
 * trop restrictives : les prix maximum et minimum sont analysés à +/- 5 %.
 */
class DialogListeRechercheSouhaits : public QDialog
{
    Q_OBJECT

public:

	/*!
      \brief    Constructeur
      \param [in,out]   bien Bien*, le bien pour lequel les souhaits sont recherchés
      \param [in,out]   parent QWidget*, la fenêtre parente
      */
    explicit DialogListeRechercheSouhaits(Bien* bien, QWidget *parent = 0);

    /*!
      \brief    Destructeur
      */
    ~DialogListeRechercheSouhaits();

private:
    Ui::DialogListeRechercheSouhaits *ui;
    Ui::barreMenuFiche m_menu;
    Bien* m_bien;
    BDD *m_db;
    QList<Souhait *> m_listeSouhaits;
    int m_nbLigne;

    void remplirListeSouhaits();
    void rechercherSouhaits();
    int souhaitExistant(Souhait* souhait);
    void creerWidget(Souhait* souhait);
    Souhait* creerSouhait();
    void ajouterSouhait(Souhait* s);
};

#endif // DIALOGLISTERECHERCHESOUHAITS_H
