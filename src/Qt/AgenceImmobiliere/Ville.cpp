#include <Ville.h>

Ville::Ville(QObject *parent) :
    QObject(parent)
{
}

Ville::Ville(int num, QString nom, QString codePostal) :
    QObject()
{
    this->m_nom = nom;
    this->m_codePostal = codePostal;
    this->m_num = num;
}

Ville::~Ville()
{
}

QString Ville::getNom()
{
    return this->m_nom;
}

QString Ville::getCodePostal()
{
    return this->m_codePostal;
}

bool Ville::isExisting(QString nom, QString codePostal)
{
    QSqlQuery q;
    q.prepare("SELECT * from VILLES where NOM_V = :q_nom AND CODE_POSTAL_V = :q_codePostal");
    q.bindValue(":q_nom", nom.toUpper());
    q.bindValue(":q_codePostal", codePostal.toUpper());

    if (q.exec())
    {
        if (q.size() > 0)
            return true;
    }
    return false;
}

void Ville::modifierVille(QString nom, QString codePostal)
{
    this->m_nom = nom;
    this->m_codePostal= codePostal;
}

void Ville::operator=(const Ville &ville)
{
    this->m_codePostal = ville.m_codePostal;
    this->m_nom = ville.m_nom;
    this->m_num = ville.m_num;
}

int Ville::getNum()
{
    return this->m_num;
}
