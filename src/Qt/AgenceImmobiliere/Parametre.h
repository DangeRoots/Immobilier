#ifndef PARAMETRE_H
#define PARAMETRE_H

#include <qfile.h>
#include <QtXml/qdom.h>
#include <QtXml/QDomDocument>

/*!
  \file Parametre.h
  \brief Parametre permet de récupérer les paramètres de connexion de la base de données.
  \author Icham Sirat
  \version 1.0
  */

class Parametre
{
public:
    // Chargement des paramètres de l'application dans un fichier XML
    /*!
      \brief    Constructeur par défaut
      Permet d'obtenir les paramètres de la connexion en lisant un fichier XML
      */
    Parametre();

    /*!
      \brief    Obtenir le type de la connexion
      Permet d'obtenir le type de la connexion
      \return   QString le type de la connexion
      */
    QString getTypeConnection();

    /*!
      \brief    Obtenir l'adresse de la machine d'hébergement
      Permet d'obtenir l'adresse de la machine d'hébergement
      \return   QString l'adresse de la machine d'hébergement
      */
    QString getHost();

    /*!
      \brief    Obtenir le nom de la base de données
      Permet d'obtenir le nom de la base de données
      \return   QString le nom de la base de données
      */
    QString getDataBaseName();

    /*!
      \brief    Obtenir le nom du propriétaire de la base de données
      Permet d'obtenir le nom du propriétaire de la base de données
      \return   QString le nom du propriétaire de la base de données
      */
    QString getUser();

    /*!
      \brief    Obtenir le mot de passe de la base de données
      Permet d'obtenir le mot de passe de la base de données
      \return   QString le mot de passe de la base de données
      */
    QString getPassword();


private:
    QDomDocument *doc;
    QString typeConnection, host, dataBaseName, user, password;

};

#endif // PARAMETRE_H
