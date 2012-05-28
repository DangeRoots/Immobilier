#include "dialoglistebiens.h"
#include "ui_dialoglistebiens.h"
#include <Bien.h>
#include <widgetbien.h>
#include <QMessageBox>
#include <QDebug>

DialogListeBiens::DialogListeBiens(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogListeBiens)
{
    ui->setupUi(this);
}

DialogListeBiens::DialogListeBiens(Client *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogListeBiens)
{
    ui->setupUi(this);
    m_client = client;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    this->setWindowTitle("Gestion de biens immobiliers");
    m_menu.setupUi(ui->widget_barreMenu);
    m_menu.label_fenetre->setText("Biens");
    m_menu.image_fenetre->setPixmap(QPixmap(":/app/bien96"));
    m_menu.pushButton_3->setVisible(false);
    // Bouton de fermeture
    m_menu.pushButton_1->setIcon(QIcon(":/app/back96"));
    m_menu.pushButton_1->setToolTip("Fermer la fenêtre");
    // Bouton Quitter
    m_menu.pushButton_2->setIcon(QIcon(":/app/quitter96"));
    m_menu.pushButton_2->setToolTip("Quitter l'application");
    ui->pushButton_ajouterBien->setToolTip("Créer un nouveau bien");
    ui->tableWidget_listeBiens->setColumnCount(1);
    ui->tableWidget_listeBiens->verticalHeader()->hide();
    ui->tableWidget_listeBiens->horizontalHeader()->hide();
    //Informations client
    ui->label_NomClient->setText(client->getNom());
    chercherBiens();
    // SIGNAUX et SLOTS
    QObject::connect(m_menu.pushButton_1,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(m_menu.pushButton_2,SIGNAL(clicked()),qApp,SLOT(quit()));
    QObject::connect(ui->pushButton_ajouterBien, SIGNAL(clicked()),this,SLOT(nouveauBien()));
}

DialogListeBiens::~DialogListeBiens()
{
    delete m_db;
    delete ui;
}

void DialogListeBiens::reset()
{
    ui->tableWidget_listeBiens->clearContents();
    ui->tableWidget_listeBiens->clear();
    ui->tableWidget_listeBiens->setRowCount(0);
}

void DialogListeBiens::chercherBiens()
{
    m_db = new BDD();
    if (m_db->ouvrir())
    {
        QSqlQuery requete(m_db->getDb());
        requete.prepare("select * from biens where num_c=:numClient");
        requete.bindValue(":numClient",QString::number(m_client->getNum()));
        if (requete.exec())
        {
            if (requete.size() < 1)
                QMessageBox::information(this,"Recherche client", "Aucun bien trouvé");
            else
            {
                // Initialisations
                ui->tableWidget_listeBiens->setRowCount(requete.size());
                int ligne = 0;
                while (requete.next())
                {
                    qDebug() << "numB : " << requete.value(0).toUInt() << endl
                           << "numV : " << requete.value(1).toUInt() << endl
                           << "Surface Habitable : " << requete.value(5).toUInt() << endl
                           << "Surface jardin : " << requete.value(6).toUInt() << endl;
                    WidgetBien *bienUi = new WidgetBien();
                    Ville *ville;
                    QSqlQuery req_ville(m_db->getDb());
                    req_ville.prepare("select * from Villes where num_v=:numVille");
                    req_ville.bindValue(":numVille",requete.value(1).toUInt());
                    if (req_ville.exec())
                    {
                        if (req_ville.size()>1)
                            QMessageBox::information(this,"Recherche des villes", "Plus d'une ville trouvé");
                        else while (req_ville.next())
                        {
                            qDebug() << "numVille : " << req_ville.value(0).toUInt() << endl
                                   << "nomVille : " << req_ville.value(1).toString() << endl
                                   << "CP : " << req_ville.value(2).toString() << endl;
                            ville = new Ville(req_ville.value(0).toInt(), req_ville.value(1).toString(),req_ville.value(2).toString());
                        }
                    }
                    QDate date(requete.value(4).toDate());
                    Bien *bien = new Bien(requete.value(0).toUInt(),requete.value(3).toUInt(),date,requete.value(5).toUInt(),requete.value(6).toUInt(),ville,m_client);
                    this->m_listeBiens.append(bien);
                    ui->label_NomClient->setText(bien->getClient()->getNom());
                    bienUi->setPrixVente(bien->getPrix());
                    bienUi->setSurfaceHabitable(bien->getSurfHabitable());
                    bienUi->setSurfaceJardin(bien->getSurfJardin());
                    bienUi->setDateMiseVente(date);
                    bienUi->setVille(ville->getNom());
                    bienUi->getBoutonDate()->setDisabled(true);

                    ui->tableWidget_listeBiens->setRowHeight(ligne,bienUi->height());
                    ui->tableWidget_listeBiens->setColumnWidth(0,bienUi->width());
                    ui->tableWidget_listeBiens->setCellWidget(ligne,0,bienUi);

                    QSignalMapper *mapperBien = new QSignalMapper(this);
                    QObject::connect(bienUi->getBoutonDialogBien(),SIGNAL(clicked()),mapperBien,SLOT(map()));
                    mapperBien->setMapping(bienUi->getBoutonDialogBien(),this->m_listeBiens.indexOf(bien));
                    connect(mapperBien,SIGNAL(mapped(int)),this,SLOT(ouvrirBien(int)));

                    QSignalMapper *mapperSouhaits = new QSignalMapper(this);
                    QObject::connect(bienUi->getBoutonListeSouhaits(),SIGNAL(clicked()),mapperSouhaits,SLOT(map()));
                    mapperSouhaits->setMapping(bienUi->getBoutonListeSouhaits(),this->m_listeBiens.indexOf(bien));
                    connect(mapperSouhaits,SIGNAL(mapped(int)),this,SLOT(ouvrirListeSouhaits(int)));
                    ligne++;
                }
            }
        }
    }
    m_db->close();
}

void DialogListeBiens::nouveauBien()
{
    QDate date = QDate::currentDate();
    Bien *bien = new Bien(0,0,date,0,0,new Ville(),m_client);
    m_dialogBien = new DialogBien(bien,this);
    m_dialogBien->exec();
    reset();
    chercherBiens();
}

void DialogListeBiens::ouvrirBien(int indexBien)
{
    m_bienCourant = this->m_listeBiens[indexBien];
    this->m_dialogBien = new DialogBien(m_bienCourant,this);
    m_dialogBien->exec();
    reset();
    chercherBiens();
}

void DialogListeBiens::ouvrirListeSouhaits(int indexBien)
{
    m_bienCourant = this->m_listeBiens[indexBien];
    this->m_listeSouhaits = new DialogListeRechercheSouhaits(m_bienCourant,this);
    m_listeSouhaits->exec();
    reset();
    chercherBiens();
}
