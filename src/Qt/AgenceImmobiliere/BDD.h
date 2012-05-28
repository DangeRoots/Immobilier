#ifndef CONNEXIONSQL_H
#define CONNEXIONSQL_H

/*!
  \file BDD.h
  \brief BDD permet de décrire un base de données.
  \author Icham Sirat
  \version 1.0
  */

#include <QtSql>
#include "Parametre.h"

/*!
 * \class BDD
 * \brief Cette classe permet les échanges avec la base de données
 * 
 * La base de données est accessible depuis les objets métier, tels que le client, le souhait ou le bien.
 * Les instances de ces objets n'ont pas connaissance des paramètres de la base qui sont chargés par 
 * la classe BDD. Cette classe propose des méthodes permettant de créer une instance de base, de vérifier 
 * qu'une connexion est ouverte ou de fermer une connexion existante.
 */
class BDD
{
public:

    /*!
      \brief    Constructeur par defaut
      */
    BDD();

    /*!
      \brief    Constructeur
      \param [in]   typeConnection QString, le type de connexion de la base de données
      \param [in]   host QString, l'adresse de la machine d'hébergement
      \param [in]   database QString, le nom de la base de données
      \param [in]   user QString, le nom du propiétaire de la base de données
      \param [in]   password QSting, le mot de passe de la base de données
      */
    BDD(QString typeConnection ,QString host, QString database, QString user, QString password);

    /*!
      \brief    Destructeur par defaut
      */
    ~BDD();

    /*!
      * \brief    Tester la validité de la connexion à la base de données
      * 
      * Permet de tester la validité de la base de données. Utilise la méthode QSqlDatabase::isValid().
      * \return   bool    vrai si la base de données est valide
      */
    bool isValid();

    /*!
      * \brief    Fermer la connexion à la base de données
      * 
      * Permet de fermer la base de données. Utilise la méthode QSqlDatabase::close().
      */
    void close();

    /*!
      * \brief    Ouvrir la connexion à la base de données
      * 
      * Permet d'ouvrir la base de données. Utilise la méthode QSqlDatabase::open().
      * \return   bool    vrai si l'ouverture de la base de données s'est correctement déroulée
      */
    bool ouvrir();

    /*!
      * \brief    Obtenir la base de données
      * 
      * Permet d'obtenir la base de données.
      * \return   QSqlDatabase    la base de données
      */

    QSqlDatabase getDb();

private:
    QSqlDatabase m_db;
    Parametre *m_settings;
};

#endif // CONNEXIONSQL_H
