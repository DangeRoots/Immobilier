#ifndef BIEN_H
#define BIEN_H

/*!
  \file Bien.h
  \brief Bien permet de décrire un bien immobilier.
  \author Gilles Coulais
  \version 1.0
  */

#include <QObject>
#include <QDate>
#include "Ville.h"
#include "Client.h"
#include <BDD.h>

/*!
 * \class Bien
 * \brief Cette classe décrit le bien mis en vente
 * 
 * Le bien est associé à un client vendeur.
 * La classe Bien permet de le représenter et de l'instancier, 
 * mais aussi de le sauvegarder dans la base.
 */
class Bien : public QObject
{
 //   Q_OBJECT

private:
    unsigned int m_num;
    unsigned int m_prixVente;
    QDate m_dateMiseVente;
    unsigned int m_surfaceHabitable;
    unsigned int m_surfaceJardin;
    Ville *m_ville;
    Client *m_client;
    BDD *m_db;

public:
    /*!
      \brief    Constructeur
      \param [in]   prix entier positif, le prix de vente
      \param [in,out]   &date QDate, la date de mise en vente
      \param [in]   surfHab entier positif, la surface habitable
      \param [in]   surfJar entier positif, la surface de jardin
      \param [in,out]   ville  Ville *, la ville où se situe le bien
      \param [in,out]   client Client *, le client qui vend le bien
      */
    Bien(unsigned int prix, QDate &date, unsigned int surfHab, unsigned int surfJar, Ville *ville, Client *client);

    /*!
      \brief    Constructeur
      \param [in]   numB entier positif, le numéro du bien tel que fourni par la base de données. 0 pour les nouveaux biens
      \param [in]   prix entier positif, le prix de vente
      \param [in,out]   &date QDate, la date de mise en vente
      \param [in]   surfHab entier positif, la surface habitable
      \param [in]   surfJar entier positif, la surface de jardin
      \param [in,out]   ville  Ville *, la ville où se situe le bien
      \param [in,out]   client Client *, le client qui vend le bien
      */
    Bien(unsigned int numB, unsigned int prix, QDate &date, unsigned int surfHab, unsigned int surfJar, Ville *ville, Client *client);

    /*!
      * \brief    Modifier le prix
      * 
      * Permet de modifier le prix de vente du bien
      * \param [in]   prix int, le nouveau prix
      * \return   void
      */
    void setPrix(unsigned int prix);

    /*!
      * \brief    Modifier la date
      * 
      * Permet de modifier la date de mise en vente du bien
      * \param [in]   date QDate, la nouvelle date
      * \return   void
      */
    void setDate(QDate date);

    /*!
      * \brief    Modifier la ville
      * 
      * Permet de modifier la ville dans laquelle se trouve le bien
      * \param [in]   ville Ville*, la nouvelle ville
      * \return   void
      */
    void setVille(Ville* ville);

    /*!
      * \brief    Obtenir le prix de vente
      * 
      * Permet d'obtenir le prix de vente du bien
      * \return   int le prix de vente
      */
    int getPrix();

    /*!
      * \brief    Obtenir la surface habitable
      * 
      * Permet d'obtenir la surface habitable du bien
      * \return   int la surface
      */
    int getSurfHabitable();

    /*!
      * \brief    Obtenir la surface de jardin
      * 
      * Permet d'obtenir la surface de jardin du bien
      * \return   int la surface
      */
    int getSurfJardin();

    /*!
      * \brief    Modifier la surface habitable
      * 
      * Permet de modifier la surface habitable du bien
      * \param [in]   surf int, la nouvelle surface
      * \return   void
      */
    void setSurfHabitable(int surf);

    /*!
      * \brief    Modifier la surface de jardin
      * 
      * Permet de modifier la surface de jardin du bien
      * \param [in]   surf int, la nouvelle surface
      * \return   void
      */
    void setSurfJardin(int surf);

    /*!
      * \brief    Sauvegarder le bien
      * 
      * Permet de sauvegarder le bien dans la base de données. Si le bien n'existe pas dans la base, il est alors créé.
      * \return   bool    vrai si la sauvegarde s'est correctement déroulée
      */
    bool sauvegarder();

    /*!
      * \brief    Obtenir le client
      * 
      * Permet d'obtenir le client vendeur
      * \return   Client* un pointeur vers le client
      */
    Client* getClient();

    /*!
      * \brief    Obtenir la date de mise en vente
      * 
      * Permet d'obtenir la date de mise en vente du bien
      * \return   QDate date de mise en vente
      */
    QDate getDate();

    /*!
      * \brief    Obtenir la ville
      * 
      * Permet d'obtenir la ville dans laquelle se situe le bien
      * \return   Ville* un pointeur vers la ville
      */
    Ville* getVille();

signals:

public slots:

};

#endif // BIEN_H
