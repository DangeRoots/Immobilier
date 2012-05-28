#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <Ville.h>
#include <BDD.h>

/*!
  \file Client.h
  \brief Client permet de décrire un client de l'agence, qu'il soit acheteur ou vendeur.
  \author Gilles Coulais
  \version 1.0
  */

/*!
 * \class Client
 * \brief Cette classe décrit le client qu'il soit acheteur ou vendeur
 * 
 * Le client est l'objet central du logiciel. Sans client, il est impossible de faire 
 * quelque action que ce soit. La classe Client permet de le représenter et de l'instancier, 
 * mais aussi de le sauvegarder dans la base.
 */
class Client : public QObject
{

public:
    /*!
      \brief    Constructeur
      \param [in]   num entier, le numéro du client
      \param [in]   nom QString, le nom du client
      \param [in]   adresse QString, l'adresse du client
      \param [in]   tel QString, le téléphone du client
      \param [in,out]   ville  Ville *, la ville du client
      \param [in]   numA entier, le numéro d'agent affecté au client acheteur
      */
    Client (int num, QString nom,QString adresse,QString tel, Ville *ville, int numA);

    /*!
      \brief    Destructeur
      */
    ~Client ();

    /*!
      * \brief    Modifier l'adresse
      * 
      Permet de modifier l'adresse
      \param [in]   adr QString, la nouvelle adresse
      \return   void
      */
    void setAdresse (QString adr);

    /*!
      * \brief    Modifier le téléphone
      * 
      Permet de modifier le téléphone
      \param [in]   tel QString, le nouveau téléphone
      \return   void
      */
    void setTelephone (QString tel);

    /*!
      \brief    Modifier le nom
      
      Permet de modifier le nom
      \param [in]   nom QString, le nouveau nom
      \return   void
      */
    void setNom(QString nom);

    /*!
      \brief    Modifier la ville
      
      Permet de modifier la ville
      \param [in,out]   ville Ville *, la nouvelle ville
      \return   void
      */
    void setVille(Ville *ville);

    /*!
      \brief    Modifier le numéro d'agent
      
      Permet de modifier le numéro d'agent
      \param [in]   num int, le nouveau numéro
      \return   void
      */
    void setNumA(int num);

    /*!
      \brief    Obtenir le numéro client
      
      Permet d'obtenir le numéro du client
      \return   int le numéro du client
      */
    int getNum();

    /*!
      \brief    Obtenir le numéro d'agent
      
      Permet d'obtenir le numéro de l'agent affecté au client
      \return   int le numéro de l'agent
      */
    int getNumA();

    /*!
      \brief    Obtenir le nom
      
      Permet d'obtenir le nom du client
      \return   QString le nom du client
      */
    QString getNom();

    /*!
      \brief    Obtenir l'adresse
      
      Permet d'obtenir l'adresse du client
      \return   QString l'adresse du client
      */
    QString getAdresse();

    /*!
      \brief    Obtenir le téléphone
      
      Permet d'obtenir le téléphone du client
      \return   QString le téléphone du client
      */
    QString getTel();

    /*!
      \brief    Obtenir la ville
      
      Permet d'obtenir la ville du client
      \return   Ville*  la ville du client
      */
    Ville* getVille();

    /*!
      \brief    Sauvegarder le client
      
      Permet de sauvegarder le client dans la base de données. Si le client n'existe pas dans la base, il est alors créé.
      \return   bool    vrai si la sauvegarde s'est correctement déroulée
      */
    bool sauvegarder();

private:
    unsigned int m_num;
    unsigned int m_num_a;
    QString m_nom;
    QString m_adresse;
    QString m_tel;
    Ville *m_ville;
    BDD *m_db;
};

#endif // CLIENT_H
