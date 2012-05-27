#include "dialoglistesouhait.h"
#include "ui_dialoglistesouhait.h"

//DialogListeSouhait::DialogListeSouhait(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::DialogListeSouhait)
//{
//    ui->setupUi(this);
//}

DialogListeSouhait::DialogListeSouhait(Client *client, QWidget *parent):
    QDialog(parent),
    ui(new Ui::DialogListeSouhait)
{
    ui->setupUi(this);
    m_client = client;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    this->setWindowTitle("Liste des souhaits");
    m_menu.setupUi(ui->widget_barreMenu);
    m_menu.label_fenetre->setText("Souhaits");
    m_menu.image_fenetre->setPixmap(QPixmap(":/app/souhait96"));
    m_menu.pushButton_3->setVisible(false);
    // Bouton de fermeture
    m_menu.pushButton_1->setIcon(QIcon(":/app/back96"));
    m_menu.pushButton_1->setToolTip("Fermer la fenêtre");
    // Bouton Quitter
    m_menu.pushButton_2->setIcon(QIcon(":/app/quitter96"));
    m_menu.pushButton_2->setToolTip("Quitter l'application");
    //Informations client
    ui->label_NomClient->setText(client->getNom());

    ui->tableWidget_listeSouhaits->setColumnCount(1);
    ui->tableWidget_listeSouhaits->verticalHeader()->hide();
    ui->tableWidget_listeSouhaits->horizontalHeader()->hide();

    chercherSouhait();
    // SIGNAUX et SLOTS
    QObject::connect(m_menu.pushButton_1,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(m_menu.pushButton_2,SIGNAL(clicked()),qApp,SLOT(quit()));
    QObject::connect(ui->pushButton_ajouterSouhait, SIGNAL(clicked()),this,SLOT(nouveauSouhait()));
}

DialogListeSouhait::~DialogListeSouhait()
{
    delete ui;
}

void DialogListeSouhait::chercherSouhait()
{
    m_db = new BDD();
    if (m_db->ouvrir())
    {
        QSqlQuery requete(m_db->getDb());
        requete.prepare("SELECT souhaits.num_s, souhaits.num_c, souhaits.budget_max_s, souhaits.surface_hab_min_s, souhaits.surface_jardin_min_s, villes.nom_v, villes.num_v, villes.code_postal_v, clients.nom_c FROM souhaits INNER JOIN clients ON souhaits.num_c = clients.num_c INNER JOIN villes_souhaitees ON souhaits.num_s = villes_souhaitees.num_s INNER JOIN villes ON villes_souhaitees.num_v = villes.num_v Where clients.num_c =:numClient Order by souhaits.num_s");

        requete.bindValue(":numClient", QString::number(m_client->getNum()));
        if (requete.exec())
        {
            if (requete.size() < 1)
                QMessageBox::information(this,"Recherche client", "Aucun souhait trouvé");
            else
            {

                while (requete.next())
                {
                    if (m_listeSouhaits.size() > 0)
                    {
                        for (int i =0; i< m_listeSouhaits.size(); i++)
                        {
                            // Si je suis sur le même souhait
                            if(m_listeSouhaits[i]->getNum() == requete.value(0).toInt())
                            {
                                foreach (Ville *v, m_listeSouhaits[i]->getVilles())
                                {
                                    if (v->getNum() != requete.value(6).toInt())
                                    {
                                        Ville *ville = new Ville(requete.value(6).toInt(),requete.value(5).toString(),requete.value(7).toString());
                                        m_listeSouhaits[i]->modifierVilles(ville);
                                    }

                                }

                            }
                            else
                            {
                                QList<Ville *> m_listeVilles;
                                Ville *ville = new Ville(requete.value(6).toInt(),requete.value(5).toString(),requete.value(7).toString());
                                m_listeVilles.append(ville);
                                Souhait *souhait = new Souhait(requete.value(0).toInt(), requete.value(2).toInt(), requete.value(3).toInt(), requete.value(4).toInt()
                                                               ,m_listeVilles, m_client);
                                this->m_listeSouhaits.append(souhait);

                            }
                        }
                    }
                    else
                    {
                        QList<Ville *> m_listeVilles;
                        Ville *ville = new Ville(requete.value(6).toInt(),requete.value(5).toString(),requete.value(7).toString());
                        m_listeVilles.append(ville);
                        Souhait *souhait = new Souhait(requete.value(0).toInt(), requete.value(2).toInt(), requete.value(3).toInt(), requete.value(4).toInt()
                                                       ,m_listeVilles, m_client);
                        this->m_listeSouhaits.append(souhait);

                    }
                }
            }
        }
        m_db->close();
    }

    // création des widgets
    int ligne = 0;
    ui->tableWidget_listeSouhaits->setRowCount(m_listeSouhaits.size());
    for (int i=0; i < m_listeSouhaits.size(); i++)
    {
        WidgetSouhait *souhaitUi = new WidgetSouhait(m_listeSouhaits[i]);
        souhaitUi->setBudgetMax(m_listeSouhaits[i]->getBudget());
        souhaitUi->setSurfaceHabitableSouhaitee(m_listeSouhaits[i]->getSurfaceHabitable());
        souhaitUi->setSurfaceJardinSouhaitee(m_listeSouhaits[i]->getSurfaceJardin());

        ui->tableWidget_listeSouhaits->setColumnWidth(0,souhaitUi->width());
        ui->tableWidget_listeSouhaits->setRowHeight(ligne,souhaitUi->height());
        ui->tableWidget_listeSouhaits->setCellWidget(ligne,0,souhaitUi);

        QSignalMapper *mapper = new QSignalMapper(this);
        QObject::connect(souhaitUi->getBoutonDialogSouhait(),SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(souhaitUi->getBoutonDialogSouhait(),this->m_listeSouhaits.indexOf(m_listeSouhaits[i]));
        connect(mapper,SIGNAL(mapped(int)),this,SLOT(ouvrirSouhait(int)));

        ligne++;


    }
}

void DialogListeSouhait::nouveauSouhait()
{
    QList<Ville *> listeVilles;
    Souhait *newSouhait = new Souhait(0,0,0,0, listeVilles,m_client);
    m_dialogSouhait = new DialogSouhait(newSouhait, this);
    m_dialogSouhait->exec();
}

void DialogListeSouhait::ouvrirSouhait(int indexSouhait)
{
    m_souhaitCourant = this->m_listeSouhaits[indexSouhait];
    this->m_dialogSouhait = new DialogSouhait(m_souhaitCourant);
    m_dialogSouhait->exec();

}
