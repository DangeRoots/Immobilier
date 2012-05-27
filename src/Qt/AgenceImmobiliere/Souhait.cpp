#include "Souhait.h"

Souhait::Souhait(unsigned int numSouhait, unsigned int budgetMax, unsigned int surfHabMin, unsigned int surfJardMin, QList<Ville *> ville, Client *client)
{
    this->m_numSouhait = numSouhait;
    this->m_budgetMax = budgetMax;
    this->m_surfaceHabitableMinimum = surfHabMin;
    this->m_surfaceJardinMinimum = surfJardMin;
    this->m_listeVilles = ville;
    this->m_client = client;
}

Souhait::~Souhait()
{
}

int Souhait::getNum()
{
    return this->m_numSouhait;
}

int Souhait::getBudget()
{
    return this->m_budgetMax;
}

int Souhait::getSurfaceHabitable()
{
    return this->m_surfaceHabitableMinimum;
}

int Souhait::getSurfaceJardin()
{
    return this->m_surfaceJardinMinimum;
}

Client* Souhait::getClient()
{
    return this->m_client;
}

QList<Ville *> Souhait::getVilles()
{
    return this->m_listeVilles;
}

void Souhait::setNum(unsigned int numSouhait)
{
    this->m_numSouhait = numSouhait;
}

void Souhait::setBudget(unsigned int budget)
{
    this->m_budgetMax = budget;
}

void Souhait::setSurfaceHabitable(unsigned int surf)
{
    this->m_surfaceHabitableMinimum = surf;
}

void Souhait::setSurfaceJardin(unsigned int surf)
{
    this->m_surfaceJardinMinimum = surf;
}

void Souhait::modifierVilles(Ville *ville)
{
    this->m_listeVilles.append(ville);
}

bool Souhait::sauvegarderSouhait()
{
    m_db = new BDD();
    bool res;
    if (m_db->ouvrir())
    {
        QSqlQuery requeteSouhait(m_db->getDb());


        switch(this->getNum())
        {
        case (0):
            //INSERT INTO souhaits(
            //num_s, num_c, budget_max_s, surface_hab_min_s, surface_jardin_min_s)
            //VALUES (?, ?, ?, ?, ?);
            requeteSouhait.prepare("INSERT INTO souhaits VALUES(default,:numClient,:budgetMax,:surfH,:surfJ)");
            requeteSouhait.bindValue(":numClient", this->getClient()->getNum());
            requeteSouhait.bindValue(":budgetMax", this->getBudget());
            requeteSouhait.bindValue(":surfH", this->getSurfaceHabitable());
            requeteSouhait.bindValue(":surfJ", this->getSurfaceJardin());
            break;
        default:
            //UPDATE souhaits
            //   SET num_s=?, num_c=?, budget_max_s=?, surface_hab_min_s=?, surface_jardin_min_s=?
            // WHERE <condition>;
            requeteSouhait.prepare("UPDATE souhaits SET num_c=:numClient,budget_max_s=:budgetMax,surface_hab_min_s=:surfH,surface_jardin_min_s=:surfJ WHERE num_s=:numSouhait");
            requeteSouhait.bindValue(":numSouhait", this->getNum());
            requeteSouhait.bindValue(":numClient", this->getClient()->getNum());
            requeteSouhait.bindValue(":budgetMax", this->getBudget());
            requeteSouhait.bindValue(":surfH", this->getSurfaceHabitable());
            requeteSouhait.bindValue(":surfJ", this->getSurfaceJardin());
        }
        if (requeteSouhait.exec())
            res = true;
        else
            res = false;
    }
    return res;
    m_db->close();
}

bool Souhait::sauvegarderVillesSouhaitees(int numS, int numV)
{
    m_db = new BDD();
    bool res;

        if (m_db->ouvrir())
        {
            QSqlQuery requeteVillesSouhaitees(m_db->getDb());

            requeteVillesSouhaitees.prepare("INSERT INTO villes_souhaitees VALUES(:num_v,:num_s)");
            requeteVillesSouhaitees.bindValue(":num_s",numS);
            requeteVillesSouhaitees.bindValue(":num_v", numV);

            if (requeteVillesSouhaitees.exec())
                res = true;
            else
                res = false;
        }
    m_db->close();
    return res;
}
