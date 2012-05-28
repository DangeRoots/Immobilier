#include "dialogaccueil.h"
#include "ui_dialogaccueil.h"
#include <QMessageBox>

/*
  Constructeur
  */

DialogAccueil::DialogAccueil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAccueil)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    this->setWindowTitle("Gestion de biens immobiliers");
    //this->m_listeClients = new QList<Client>();
    // Création de la barre de menu
    m_menu.setupUi(ui->widget_barreMenu);
    m_menu.label_fenetre->setText("Accueil");
    m_menu.image_fenetre->setPixmap(QPixmap(":/app/accueil"));
    // Masquage du 3e bouton de la barre de menu
    // Edit demasquage pour test Agent
    m_menu.pushButton_3->setVisible(false);
    // Bouton de reset
    m_menu.pushButton_1->setIcon(QIcon(":/app/rafraichir96"));
    m_menu.pushButton_1->setToolTip("Reset");
    // Bouton Quitter
    m_menu.pushButton_2->setIcon(QIcon(":/app/quitter96"));
    m_menu.pushButton_2->setToolTip("Quitter l'application");
    //Préparation de l'interface
    ui->button_Ajouter->setToolTip("Créer un nouveau client");
    ui->button_Ajouter->setEnabled(false);
    ui->button_Effacer->setToolTip("Effacer la zone de recherche");
    ui->button_Ok->setToolTip("Lancer la recherche");
    ui->tableWidget_resultats->setColumnCount(1);
    ui->tableWidget_resultats->verticalHeader()->hide();
    ui->tableWidget_resultats->horizontalHeader()->hide();
    // SIGNAUX et SLOTS
    QObject::connect(m_menu.pushButton_2, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(m_menu.pushButton_1, SIGNAL(clicked()), this, SLOT(reset()));
//    QObject::connect(m_menu.pushButton_3,SIGNAL(clicked()), this, SLOT(gestionAgents()));
    QObject::connect(ui->button_Effacer, SIGNAL(clicked()), ui->lineEdit_Recherche, SLOT(clear()));
    QObject::connect(ui->button_Ok, SIGNAL(clicked()), this, SLOT(chercherClients()));
    QObject::connect(ui->button_Ajouter, SIGNAL(clicked()),this,SLOT(nouveauClient()));
}

DialogAccueil::~DialogAccueil()
{
    delete m_db;
    // delete m_dialogListeBiens;
    // delete m_clientCourant;
    delete ui;
}

void DialogAccueil::reset()
{
    ui->lineEdit_Recherche->clear();
    ui->tableWidget_resultats->clearContents();
    ui->tableWidget_resultats->clear();
    ui->tableWidget_resultats->setRowCount(0);
    ui->button_Ajouter->setEnabled(false);
}

void DialogAccueil::chercherClients()
{
    ui->button_Ajouter->setEnabled(true);
    QString client = ui->lineEdit_Recherche->text().toUpper();
    if (client.isEmpty())
        QMessageBox::information(this,"Recherche client", "Merci de saisir au moins une lettre dans la zone de recherche");
    else
    {
        QString requete = "select CLIENTS.NUM_C, CLIENTS.nom_c, CLIENTS.adresse_c, CLIENTS.tel_c, ";
        requete += "VILLES.nom_v, VILLES.code_postal_v, VILLES.num_v,CLIENTS.NUM_A,";
        requete += "(select count(BIENS.num_b) from Biens where biens.num_c=clients.num_c) as NbBiens, ";
        requete += "(select count(SOUHAITS.num_s) from Souhaits where souhaits.num_c=clients.num_c) as NbSouhaits ";
        requete += "from CLIENTS INNER JOIN VILLES on VILLES.NUM_V=CLIENTS.NUM_V ";
        requete += "left outer JOIN BIENS on BIENS.num_c=CLIENTS.num_c ";
        requete += "left outer JOIN SOUHAITS on SOUHAITS.num_c=CLIENTS.num_c ";
        requete += "where CLIENTS.nom_c like'" + client + "%'";
        requete += "group by clients.num_c, clients.nom_c, clients.adresse_c,clients.tel_c, villes.nom_v,villes.code_postal_v,villes.num_v,CLIENTS.NUM_A ";
        requete += "order by clients.num_c";

        m_db = new BDD();
        if (m_db->ouvrir())
        {
            QSqlQuery resultat;
            if (resultat.exec(requete))
            {
                if (resultat.size() < 1)
                    QMessageBox::information(this,"Recherche client", "Aucun client trouvé");
                else
                {
                    // Initialisations
                    ui->tableWidget_resultats->setRowCount(resultat.size());
                    int ligne = 0;
                    while (resultat.next())
                    {
                        WidgetClient *clientUi = new WidgetClient();
                        Ville *ville = new Ville(resultat.value(6).toInt(),resultat.value(4).toString(),resultat.value(5).toString());
                        // Debug Infos
                        qDebug()    << "NumV : " << ville->getNum() << endl
                                    << "NomV : " << ville->getNom() << endl
                                    << "CP : " << ville->getCodePostal();
                        // Fin
                        Client *client = new Client(resultat.value(0).toInt(),resultat.value(1).toString(),resultat.value(2).toString(),resultat.value(3).toString(),ville,resultat.value(7).toInt());
                        this->m_listeClients.append(client);

                        int nbBiens = resultat.value(8).toInt();
                        int nbSouhaits = resultat.value(9).toInt();
                        clientUi->setNom(client->getNom());
                        clientUi->setVille(ville->getNom());
                        clientUi->setAdresse(client->getAdresse());
                        clientUi->setTelephone(client->getTel());
                        clientUi->setCodePostal(ville->getCodePostal());

                        //NbSouhait = 0
                        if (nbSouhaits < 1)
                        {
                            clientUi->setImageSouhait(QPixmap(":/app/add_souhait96"));
                            clientUi->getBoutonSouhait()->setToolTip("Créer un nouveau souhait pour ce client");
                            QSignalMapper *mapperSouhait = new QSignalMapper(this);
                            QObject::connect(clientUi->getBoutonSouhait(),SIGNAL(clicked()),mapperSouhait,SLOT(map()));
                            mapperSouhait->setMapping(clientUi->getBoutonSouhait(),this->m_listeClients.indexOf(client));
                            connect(mapperSouhait,SIGNAL(mapped(int)),this,SLOT(nouveauSouhait(int)));

                        } else {
                            clientUi->getBoutonSouhait()->setToolTip("Accéder à la liste des souhaits de ce client");
                            QSignalMapper *mapperSouhait = new QSignalMapper(this);
                            QObject::connect(clientUi->getBoutonSouhait(),SIGNAL(clicked()),mapperSouhait,SLOT(map()));
                            mapperSouhait->setMapping(clientUi->getBoutonSouhait(),this->m_listeClients.indexOf(client));
                            connect(mapperSouhait,SIGNAL(mapped(int)),this,SLOT(ouvrirListeSouhaits(int)));
                        }

                        //NbBien = 0
                        if (nbBiens < 1)
                        {
                            clientUi->setImageBien(QPixmap(":/app/add_bien96"));
                            clientUi->getBoutonBien()->setToolTip("Créer un nouveau bien pour ce client");
                            // m_dialogBien = new DialogBien();
                            QSignalMapper *mapperBien = new QSignalMapper(this);
                            QObject::connect(clientUi->getBoutonBien(),SIGNAL(clicked()),mapperBien,SLOT(map()));
                            mapperBien->setMapping(clientUi->getBoutonBien(),this->m_listeClients.indexOf(client));
                            connect(mapperBien,SIGNAL(mapped(int)),this,SLOT(nouveauBien(int)));
                            // QObject::connect(clientUi->getBoutonBien(),SIGNAL(clicked()), m_dialogBien,SLOT(exec()));
                        } else {
                            clientUi->getBoutonBien()->setToolTip("Accéder à la liste des biens de ce client");
                            QSignalMapper *mapperBien = new QSignalMapper(this);
                            QObject::connect(clientUi->getBoutonBien(),SIGNAL(clicked()),mapperBien,SLOT(map()));
                            mapperBien->setMapping(clientUi->getBoutonBien(),this->m_listeClients.indexOf(client));
                            connect(mapperBien,SIGNAL(mapped(int)),this,SLOT(ouvrirListeBiens(int)));

                        }

                        QSignalMapper *mapper = new QSignalMapper(this);
                        clientUi->getBoutonClient()->setToolTip("Ouvrir la fiche client");
                        QObject::connect(clientUi->getBoutonClient(),SIGNAL(clicked()),mapper,SLOT(map()));
                        mapper->setMapping(clientUi->getBoutonClient(),this->m_listeClients.indexOf(client));
                        connect(mapper,SIGNAL(mapped(int)),this,SLOT(ouvrirClient(int)));

                        ui->tableWidget_resultats->setColumnWidth(0,ui->tableWidget_resultats->width()-15);
                        ui->tableWidget_resultats->setRowHeight(ligne,clientUi->height());
                        ui->tableWidget_resultats->setCellWidget(ligne,0,clientUi);
                        ligne++;
                    }
                }
            }
        }
        m_db->close();
    }
}

void DialogAccueil::nouveauClient()
{
    Ville *ville = new Ville();
    m_clientCourant = new Client(0,ui->lineEdit_Recherche->text(),QString(""),QString(""),ville,0);    
    this->m_dialogClient = new DialogClient(m_clientCourant,this);
    m_dialogClient->exec();
    reset();
    ui->lineEdit_Recherche->setText(m_dialogClient->getClient()->getNom());
    chercherClients();
}

void DialogAccueil::ouvrirClient(int indexClient)
{
    // Debug Infos
    qDebug()    << "NumA : " << m_listeClients[indexClient]->getNumA() << endl
                << "Nom : " << m_listeClients[indexClient]->getNom() << endl
                << "NumC : " << m_listeClients[indexClient]->getNum() << endl
                << "Adr : "<< m_listeClients[indexClient]->getAdresse() << endl
                << "tel : " << m_listeClients[indexClient]->getTel() << endl
                << "NumVille : " << m_listeClients[indexClient]->getVille()->getNum();
    //Fin
    m_clientCourant = this->m_listeClients[indexClient];
    this->m_dialogClient = new DialogClient(m_clientCourant, this);
    m_dialogClient->exec();
    reset();
    ui->lineEdit_Recherche->setText(m_clientCourant->getNom());
    chercherClients();
}

void DialogAccueil::ouvrirListeSouhaits(int indexClient)
{
    m_clientCourant = this->m_listeClients[indexClient];
    this->m_dialogListeSouhaits= new DialogListeSouhait(m_clientCourant,this);
    m_dialogListeSouhaits->exec();
    reset();
    ui->lineEdit_Recherche->setText(m_clientCourant->getNom());
    chercherClients();
}

void DialogAccueil::ouvrirListeBiens(int indexClient)
{
    qDebug() << m_listeClients[indexClient]->getNom() << " " << m_listeClients[indexClient]->getNum();
    m_clientCourant = this->m_listeClients[indexClient];
    this->m_dialogListeBiens = new DialogListeBiens(m_clientCourant,this);
    m_dialogListeBiens->exec();
    reset();
    ui->lineEdit_Recherche->setText(m_clientCourant->getNom());
    chercherClients();
}

void DialogAccueil::nouveauBien(int indexClient)
{
    qDebug() << m_listeClients[indexClient]->getNom() << " " << m_listeClients[indexClient]->getNum();
    m_clientCourant = this->m_listeClients[indexClient];
    QDate date = QDate::currentDate();
    Bien *bien = new Bien(0,0,date,0,0,new Ville(),m_clientCourant);
    this->m_dialogBien = new DialogBien(bien,this);
    m_dialogBien->exec();
    reset();
    ui->lineEdit_Recherche->setText(m_clientCourant->getNom());
    chercherClients();
}

void DialogAccueil::nouveauSouhait(int indexClient)
{
    m_clientCourant = this->m_listeClients[indexClient];
    QList<Ville *> listeVilles;
    Souhait *newSouhait = new Souhait(0,0,0,0, listeVilles,m_clientCourant);
    m_dialogSouhait = new DialogSouhait(newSouhait, this);
    m_dialogSouhait->exec();
    reset();
    ui->lineEdit_Recherche->setText(m_clientCourant->getNom());
    chercherClients();
}

//void DialogAccueil::gestionAgents()
//{
//    QString requete = "SELECT * FROM agents INNER JOIN clients On agents.num_a = clients.num_a ORDER BY agents.num_a";
//    m_db = new BDD();
//    if (m_db->ouvrir())
//    {
//        QSqlQuery resultat;
//        if (resultat.exec(requete))
//        {
//            if (resultat.size() < 1)
//                QMessageBox::information(this, "Recherche Agent", "Aucun agent trouvé");
//            else
//            {
//                ui->tableWidget_resultats->setRowCount(resultat.size());
//                int ligne = 0;
//                while (resultat.next())
//                {
//                    if (m_listeAgents.size() > 0)
//                    {
//                        for (int i =0; i< m_listeAgents.size(); i++)
//                        {
//                            // Si je suis sur le même agent
//                            if(m_listeAgents[i]->getNum() == resultat.value(0).toInt())
//                            {
//                              // faire qq chose
//                            }
//                        }
//                    }
//                    else
//                    {
//                        // Je créer le nouvel agent
//                        WidgetAgent *agentUi = new WidgetAgent();
//                        Agent *agent = new Agent(resultat.value(0).toInt(), resultat.value(1).toString());
//                        this->m_listeAgents.append(agent);
//                        agentUi->setNom(agent->getNom());


//                        ui->tableWidget_resultats->setColumnWidth(0,ui->tableWidget_resultats->width()-15);
//                        ui->tableWidget_resultats->setRowHeight(ligne,agentUi->height());
//                        ui->tableWidget_resultats->setCellWidget(ligne,0,agentUi);
//                        ligne++;


//                    }



//                }
//            }
//        }
//    }
//}
