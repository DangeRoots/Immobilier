#include "BDD.h"

BDD::BDD(QString typeConnection ,QString host, QString database, QString user, QString password)
{
    m_db = QSqlDatabase::addDatabase(typeConnection);
    m_db.setHostName(host);
    m_db.setDatabaseName(database);
    m_db.setUserName(user);
    m_db.setPassword(password);
}

BDD::BDD()
{
    m_settings = new Parametre();
    m_db = QSqlDatabase::addDatabase(m_settings->getTypeConnection());
    m_db.setHostName(m_settings->getHost());
    m_db.setDatabaseName(m_settings->getDataBaseName());
    m_db.setUserName(m_settings->getUser());
    m_db.setPassword(m_settings->getPassword());
}

BDD::~BDD()
{
    delete m_settings;
    QSqlDatabase::removeDatabase("immo");
}

bool BDD::isValid()
{
    return (m_db.isValid());
}

void BDD::close()
{
    m_db.close();
    m_db.removeDatabase(m_settings->getDataBaseName());
}

bool BDD::ouvrir()
{
    return m_db.open();
}

QSqlDatabase BDD::getDb()
{
    return this->m_db;
}
