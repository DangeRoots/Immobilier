#ifndef SOUHAIT_H
#define SOUHAIT_H

#include <QObject>
#include "Ville.h"
#include "Client.h"
#include <BDD.h>

/*!
  \file Souhait.h
  \brief Souhait permet de décrire un souhait d'un client acheteur de l'agence.
  \author Gilles Coulais
  \author Icham Sirat
  \version 1.0
  */

/*!
 * \class Souhait
 * \brief Cette classe décrit le souhait
 * 
 * Le souhait représente une recherche faite par un client acheteur.
 * Cette classe représente le souhait et propose des méthodes permettant
 * de le créer, de le modifier ou encore de le sauvegarder dans la base.
 * Cette classe ne propose aucune interface graphique.
 */
class Souhait : public QObject
{
    //    Q_OBJECT

private:
    unsigned int m_numSouhait;
    unsigned int m_budgetMax;
    unsigned int m_surfaceHabitableMinimum;
    unsigned int m_surfaceJardinMinimum;
    QList<Ville *> m_listeVilles;
    Client *m_client;
    BDD *m_db;

public:
    /*!
      \brief    Constructeur
      \param [in]   numSouhait entier non signé, le numéro du souhait
      \param [in]   budgetMax entier non signé, le budget maximum du souhait
      \param [in]   surfHabMin entier non signé, la surface habitable minimum du souhait
      \param [in]   surfJardMin entier non signé, la surface du jardin minimum du souhait
      \param [in,out]   ville  liste de Ville *, la liste des villes du souhait
      \param [in, out]   client Client *, le client correspondant au souhait
      */
    Souhait(unsigned int numSouhait,unsigned int budgetMax, unsigned int surfHabMin, unsigned int surfJardMin, QList<Ville *> ville, Client *client);

    /*!
      \brief    Destructeur par défaut
      */
    ~Souhait();

    /*!
      \brief    Obtenir le numéro du souhait
      
      Permet d'obtenir le numéro du souhait
      \return   int le numéro du souhait
      */
    int getNum();

    /*!
      \brief    Obtenir le budget maximum du souhait
      
      Permet d'obtenir le budget maximum du souhait
      \return   int le budget du souhait
      */
    int getBudget();

    /*!
      \brief    Obtenir la surface habitable minimum du souhait
      
      Permet d'obtenir la surface habitable minimum du souhait
      \return   int la surface habitable minimum du souhait
      */
    int getSurfaceHabitable();

    /*!
      \brief    Obtenir la surface du jardin minimum du souhait
      
      Permet d'obtenir la surface du jardin minimum du souhait
      \return   int la surface du jardin minimum du souhait
      */
    int getSurfaceJardin();

    /*!
      \brief    Obtenir le client
      
      Permet d'obtenir le client du souhait
      \return   Client*  le client du souhait
      */
    Client *getClient();

    /*!
      \brief    Obtenir la liste des villes
      
      Permet d'obtenir la liste des villes du souhait
      \return   QList< Ville*>  la liste des villes du client
      */
    QList<Ville *> getVilles();

    /*!
      \brief    Modifier le numéro
      
      Permet de modifier le numéro
      \param [in]   numSouhait unsigned int, le nouveau numéro
      \return   void
      */
    void setNum(unsigned int numSouhait);

    /*!
      \brief    Modifier le budget maximum
      
      Permet de modifier le budget maximum
      \param [in]   budget unsigned int, la nouveau budget
      \return   void
      */
    void setBudget(unsigned int budget);

    /*!
      \brief    Modifier la surface habitable minimum
      
      Permet de modifier la surface habitable minimum
      \param [in]   surf unsigned int, la nouvelle surface habitable
      \return   void
      */
    void setSurfaceHabitable(unsigned int surf);

    /*!
      \brief    Modifier la surface du jardin minimum
      
      Permet de modifier la surface du jardin minimum
      \param [in]   surf unsigned int, la nouvelle surface du jardin
      \return   void
      */
    void setSurfaceJardin(unsigned int surf);

    /*!
      \brief    Modifier la ville
      
      Permet de modifier la ville
      \param [in]   ville Ville *, la nouvelle ville
      \return   void
      */
    void modifierVilles(Ville *ville);

    /*!
      \brief    Sauvegarder le souhait
      
      * Permet de sauvegarder le souhait dans la base de données. 
      * Si le souhait n'existe pas dans la base, il est alors créé.
      \return   bool    vrai si la sauvegarde s'est correctement déroulée
      */
    bool sauvegarderSouhait();

    /*!
      \brief    Sauvegarder les villes correspondantes au souhait
      
      Permet de sauvegarder les villes correspondantes au souhait dans la base de données.
      \return   bool    vrai si la sauvegarde s'est correctement déroulée
      */
    bool sauvegarderVillesSouhaitees(int, int);
};

#endif // SOUHAIT_H
