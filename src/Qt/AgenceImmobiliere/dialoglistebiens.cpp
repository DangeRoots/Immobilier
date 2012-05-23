#include "dialoglistebiens.h"
#include "ui_dialoglistebiens.h"
#include <Bien.h>
#include <widgetbien.h>
#include <QMessageBox>

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
    this->setWindowTitle("Liste des biens");
    m_menu.setupUi(ui->widget_barreMenu);
    m_menu.label_fenetre->setText("Biens");
    m_menu.image_fenetre->setPixmap(QPixmap(":/app/bien96"));
    m_menu.pushButton_3->setVisible(false);
    // Bouton de fermeture
    m_menu.pushButton_1->setIcon(QIcon(":/app/annuler96"));
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
}

DialogListeBiens::~DialogListeBiens()
{
    delete ui;
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
                    WidgetBien *bienUi = new WidgetBien();
                    Ville *ville = new Ville();
                    //QDate date(requete.value(4).toString().left(4).toInt(),requete.value(4).toString().mid(5,2).toInt(),requete.value(4).toString().right(2).toInt());
                    QDate date(requete.value(4).toDate());
                    Bien *bien = new Bien(requete.value(3).toUInt(),date,requete.value(5).toUInt(),requete.value(6).toUInt(),ville,m_client);
                    this->m_listeBiens.append(bien);
                    ui->label_NomClient->setText(bien->getClient()->getNom());
                    bienUi->setPrixVente(bien->getPrix());
                    bienUi->setSurfaceHabitable(bien->getSurf(Bien::habitation));
                    bienUi->setSurfaceJardin(bien->getSurf(Bien::jardin));
                    bienUi->setDateMiseVente(date);
                    bienUi->getBoutonDate()->setDisabled(true);

                    ui->tableWidget_listeBiens->setColumnWidth(0,ui->tableWidget_listeBiens->width());
                    ui->tableWidget_listeBiens->setRowHeight(ligne,bienUi->height());
                    ui->tableWidget_listeBiens->setCellWidget(ligne,0,bienUi);
                    ligne++;
                }
            }
        }
    }
    m_db->close();
}
