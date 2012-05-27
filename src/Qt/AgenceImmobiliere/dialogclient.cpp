#include "dialogclient.h"
#include "ui_dialogclient.h"
#include <QMessageBox>
#include <Ville.h>

DialogClient::DialogClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogClient)
{
    ui->setupUi(this);
}

DialogClient::DialogClient(Client *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogClient)
{
    ui->setupUi(this);
    changed = false;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    this->setWindowTitle("Fiche client - " + client->getNom());
    m_client = client;

    // debug infos
    qDebug()    << "NumA : " << m_client->getNumA() << endl
                << "Nom : " << m_client->getNom() << endl
                << "NumC : " << m_client->getNum() << endl
                << "Adr : "<< m_client->getAdresse() << endl
                << "tel : " << m_client->getTel() << endl
                << "NumVille : " << m_client->getVille()->getNum();
    // debug infos

    m_menu.setupUi(ui->widget_barreMenu);
    if (m_client->getNom().isEmpty())
        m_menu.label_fenetre->setText("Nouveau client");
    else
        m_menu.label_fenetre->setText(m_client->getNom());
    m_menu.image_fenetre->setPixmap(QPixmap(":/app/client96"));
    m_menu.pushButton_3->setVisible(false);

    ui->lineEdit_Nom->setText(m_client->getNom());
    ui->lineEdit_Adresse->setText(m_client->getAdresse());
    ui->lineEdit_CodePostal->setText(m_client->getVille()->getCodePostal());
    ui->lineEdit_Telephone->setText(m_client->getTel());
    ui->comboBox_Villes->addItem(m_client->getVille()->getNom());

    // ui->button_Biens->setEnabled(false);
    ui->button_Biens->setVisible(false);
    //ui->button_Souhaits->setEnabled(false);
    ui->button_Souhaits->setVisible(false);

    // Signaux et Slots
    // Boutons de menu
    QObject::connect(m_menu.pushButton_1,SIGNAL(clicked()),this,SLOT(valider()));
    QObject::connect(m_menu.pushButton_2,SIGNAL(clicked()),this,SLOT(fermer()));
    // changement de valeurs des champs
    QObject::connect(ui->lineEdit_Adresse,SIGNAL(textChanged(QString)),this,SLOT(setEtat(QString)));
    QObject::connect(ui->lineEdit_CodePostal,SIGNAL(textChanged(QString)),this,SLOT(setEtat(QString)));
    QObject::connect(ui->lineEdit_Nom,SIGNAL(textChanged(QString)),this,SLOT(setEtat(QString)));
    QObject::connect(ui->lineEdit_Nom,SIGNAL(textChanged(QString)),this,SLOT(changerLabel(QString)));
    QObject::connect(ui->lineEdit_Telephone,SIGNAL(textChanged(QString)),this,SLOT(setEtat(QString)));
    QObject::connect(ui->comboBox_Villes,SIGNAL(currentIndexChanged(QString)),this,SLOT(setEtat(QString)));
    QObject::connect(ui->button_ChercherVilles,SIGNAL(clicked()),this,SLOT(chercherVilles()));
}

DialogClient::~DialogClient()
{
    delete ui;
}

void DialogClient::valider()
{
    // Vérifier les données
    if (!checkData())
    {
        QMessageBox::critical(this,"Données incorrectes","Tous les champs doivent être complétés");
    }
    else
    {   // Si Ok
        m_client->setAdresse(ui->lineEdit_Adresse->text().toUpper());
        m_client->setNom(ui->lineEdit_Nom->text().toUpper());
        Ville *ville = chercherVille();
        m_client->setVille(ville);
        m_client->setTelephone(ui->lineEdit_Telephone->text());
        // Sauvegarder le client
        if (m_client->sauvegarder())
        {
            QMessageBox::information(this,"Données sauvegardées","Client sauvegardé");
            this->close();
        }
        else
        {
            QMessageBox::critical(this,"Sauvegarde impossible","Le client n'a pas été sauvegardé. Vérifiez vos données !");
        }
    }
}

bool DialogClient::checkData()
{
    if (ui->lineEdit_Adresse->text().isEmpty()
            || ui->label_CodePostal->text().isEmpty()
            || ui->lineEdit_Nom->text().isEmpty()
            || ui->label_Telephone->text().isEmpty()
            || ui->comboBox_Villes->currentText().isEmpty())
        return false;
    else return true;
}

void DialogClient::fermer()
{
    if (changed)
    {
        int reponse = QMessageBox::warning(this,"Données modifiées","Des données ont été modifiées sans être sauvegardées. Voulez vous les sauvegarder maintenant ?",QMessageBox::Yes | QMessageBox::No);
        if (reponse == QMessageBox::No)
            this->close();
        else
            this->valider();
    }
    else
    {
        this->close();
    }
}

void DialogClient::setEtat(QString value)
{
    if (!changed)
        changed=true;
}

void DialogClient::changerLabel(QString value)
{
    m_menu.label_fenetre->setText(value);
}

void DialogClient::chercherVilles()
{
    if (ui->lineEdit_CodePostal->text().isEmpty())
        QMessageBox::information(this,"Données incorrectes","Merci de renseigner le code postal");
    else
    {
        QString requete = "select * from VILLES where CODE_POSTAL_V='" + ui->lineEdit_CodePostal->text();
        requete += "' order by nom_v";
        qDebug() << requete;
        // pour chaque res, création d'une ville
        m_db = new BDD();
        if (m_db->ouvrir())
        {
            QSqlQuery resultat;
            if (resultat.exec(requete))
            {
                if (resultat.size() < 1)
                    QMessageBox::information(this,"Recherche client", "Aucune ville ne correspond à ce code postal");
                else
                {
                    while (resultat.next())
                    {
                        Ville *ville = new Ville(resultat.value(0).toInt(), resultat.value(1).toString(), resultat.value(2).toString());
                        m_listeVilles.append(ville);
                        qDebug() << ville->getNom();
                        ui->comboBox_Villes->addItem(ville->getNom());
                    }
                }
            }
        }
        m_db->close();
    }
}

Ville* DialogClient::chercherVille()
{
    Ville *ville;
    QString requete = "select * from villes where nom_v='";
    requete += ui->comboBox_Villes->currentText();
    requete += "' and CODE_POSTAL_V='";
    requete += ui->lineEdit_CodePostal->text();
    requete += "'";

    //Debug Infos
    qDebug() << requete;
    //FIN

    m_db = new BDD();
    if (m_db->ouvrir())
    {
        QSqlQuery resultat;
        if (resultat.exec(requete))
        {
            if (resultat.size() < 1)
                QMessageBox::information(this,"Recherche ville", "Aucune ville ne correspond à ce code postal");
            else if (resultat.size() > 1)
                QMessageBox::information(this,"Recherche ville", "Trop de résultats");
            else while (resultat.next())
            {
                //Debug Infos
                qDebug()    << resultat.value(0).toInt()
                            << resultat.value(1).toString()
                            << resultat.value(2).toString()
                            << endl;
                // FIN
                ville = new Ville(resultat.value(0).toInt(), resultat.value(1).toString(), resultat.value(2).toString());
                //Debug Infos
                qDebug()    << ville->getNom()
                            << ville->getNum()
                            << ville->getCodePostal();
                // FIN
            }
        }
    }
    m_db->close();
    return ville;
}

Client * DialogClient::getClient()
{
    return this->m_client;
}
