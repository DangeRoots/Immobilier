#ifndef VILLE_H
#define VILLE_H

#include "BDD.h"
#include <QObject>

/*!
  \file Ville.h
  \brief Ville permet de décrire une ville
  \author Icham Sirat, Gilles Coulais
  \version 1.0
  */

class Ville : public QObject
{
    Q_OBJECT
private:
    unsigned int m_num;
    QString m_nom;
    QString m_codePostal;

    /*!
      \brief    Obtenir le nom et le code postal de la ville enregistrés dans la base de données
      Permet d'obtenir le nom et le code postal de la ville enregistrés dans la base de données
      \param [in]   nom QString, le nom de la ville
      \param [in]   codePostal QString, le code postal de la ville
      \return   Ville la ville correspondante dans la base de données
      */
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
      \param [in]   codePostal QString, le code postal de la ville
      */
    Ville(int num, QString nom, QString codePostal);

    /*!
      \brief    Destructeur
      */
    ~Ville ();

    /*!
      \brief    Obtenir le nom de la ville
      Permet d'obtenir le nom de la ville
      \return   QString le nom de la ville
      */
    QString getNom();

    /*!
      \brief    Obtenir le code postal de la ville
      Permet d'obtenir le code postal de la ville
      \return   QString le code postal de la ville
      */
    QString getCodePostal();

    /*!
      \brief    Obtenir le numéro de la ville
      Permet d'obtenir le numéro de la ville
      \return   int le numéro de la ville
      */
    int getNum();

    /*!
      \brief    Savoir si une ville est présente dans la base de données
      Permet de savoir si une ville est présente dans la base de données
      \param [in]   nom QString, le nom de la ville
      \param [in]   codePostal QString, le code postal de la ville
      \return   bool vrai si la ville est présente dans la base de données
      */
    static bool isExisting(QString nom, QString codePostal);

    /*!
      \brief    Modifier le nom et le code postal de la ville
      Permet de modifier le nom et le code postal de la ville
      \param [in]   nom QString, le nom de la ville
      \param [in]   codePostal QString, le code postal de la ville
      \return   void
      */
    void modifierVille(QString nom, QString codePostal);

    /*!
       \brief    Copier deux objets villes
       Permet de copier deux objets villes
       \param [in]   &ville, une ville
       \return   void
       */

    void operator=(const Ville &ville);

signals:

public slots:

};

#endif // VILLE_H
