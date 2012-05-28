#ifndef VILLE_H
#define VILLE_H

/*!
  \file Ville.h
  \brief Ville permet de décrire une ville.
  \author Gilles Coulais
  \version 1.0
  */

#include "BDD.h"
#include <QObject>

/*!
 * \class Ville
 * \brief Cette classe décrit la ville
 *
 * La ville est utilisée dans de nombreux objets de l'application,
 * tels que le client, le bien ou le souhait.
 * Cette classe représente la ville et propose des méthodes permettant
 * d'y accéder.
 * Cette classe ne propose aucune interface graphique, ni de méthodes permettant
 * de créer de nouvelles villes ou de modifier les villes existantes.
 */
class Ville : public QObject
{
    Q_OBJECT
private:
    unsigned int m_num;
    QString m_nom;
    QString m_codePostal;
    Ville retrieveFromDB(QString nom, QString codePostal);

public:
     /*!
      \brief    Constructeur par défaut
      */
    explicit Ville(QObject *parent = 0);

   /*!
      \brief    Constructeur
      \param [in]   num entier, le numéro de la ville
      \param [in]   nom QString, le nom de la ville
      \param [in]   codePostal QString, le code postal de la villle
      */
    Ville(int num, QString nom, QString codePostal);

   /*!
      \brief    Destructeur
      */
    ~Ville ();
    /*!
      \brief    Obtenir le nom

      Permet d'obtenir le nom de la ville
      \return   QString le nom de la ville
      */
    QString getNom();

    /*!
      \brief    Obtenir le code postal

      Permet d'obtenir le code postal de la ville
      \return   QString le code postal de la ville
      */
    QString getCodePostal();

    /*!
      \brief    Obtenir le numéro

      Permet d'obtenir le numéro de la ville
      \return   int le numéro de la ville, 0 pour une nouvelle villes
      */
    int getNum();

    /*!
      \brief    Ville existante

      Permet de savoir si une ville existe dans la base
      \return   bool vrai si la ville existe déjà, faux sinon
      */
    static bool isExisting(QString nom, QString codePostal);

    /*!
      \brief    Modifier la ville

      Permet de modifier la ville
      \return   void
      */
    void modifierVille(QString nom, QString codePostal);

    /*!
      \brief    Affecter ville

      Opérateur de copie par affectation
      \return   void
      */
    void operator=(const Ville &ville);

signals:

public slots:

};

#endif // VILLE_H
