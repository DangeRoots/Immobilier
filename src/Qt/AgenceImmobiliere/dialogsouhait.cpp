#include "dialogsouhait.h"
#include "ui_dialogsouhait.h"

DialogSouhait::DialogSouhait(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSouhait)
{
    ui->setupUi(this);
    this->setWindowTitle("Ajouter un nouveau souhait");
}

DialogSouhait::DialogSouhait(Souhait *souhait, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSouhait)
{
    ui->setupUi(this);
    m_souhait = souhait;
    changed = false;
    this->setWindowTitle("Liste des souhaits");

    // Création de la barre de menu
    m_menu.setupUi(ui->widget_barreMenu);
    m_menu.label_fenetre->setText("Souhait");
    m_menu.image_fenetre->setPixmap(QPixmap(":/app/bien96"));
    m_menu.pushButton_1->setToolTip("Valider");
    m_menu.pushButton_2->setToolTip("Annuler");
    m_menu.pushButton_3->setVisible(false);

    ui->label_NomClient->setText((m_souhait->getClient())->getNom());
    ui->lineEdit_BudgetMax->setText(QString::number(m_souhait->getBudget()));
    ui->lineEdit_SurfHabMin->setText(QString::number(m_souhait->getSurfaceHabitable()));
    ui->lineEdit_SurJardMin->setText(QString::number(m_souhait->getSurfaceJardin()));

    m_listeVilles = m_souhait->getVilles();
    for (int i=0; i<m_listeVilles.size(); i++)
    {
        ui->textEdit_Villes->append(m_listeVilles[i]->getNom()+" ("+m_listeVilles[i]->getCodePostal()+")");
    }

    // Signaux & slots
    QObject::connect(m_menu.pushButton_2,SIGNAL(clicked()),this,SLOT(fermer()));
    QObject::connect(m_menu.pushButton_1,SIGNAL(clicked()),this,SLOT(valider()));
    QObject::connect(ui->button_ChercherVilles,SIGNAL(clicked()),this,SLOT(chercherVilles()));

    QObject::connect(ui->lineEdit_BudgetMax,SIGNAL(textChanged(QString)), this, SLOT(setEtat(QString)));
    QObject::connect(ui->lineEdit_SurfHabMin,SIGNAL(textChanged(QString)), this, SLOT(setEtat(QString)));
    QObject::connect(ui->lineEdit_SurJardMin,SIGNAL(textChanged(QString)), this, SLOT(setEtat(QString)));
    QObject::connect(ui->comboBox_Ville,SIGNAL(activated(QString)), this, SLOT(copierVille(QString)));

}

void DialogSouhait::copierVille(QString ville)
{
    ui->textEdit_Villes->append(ville+" "+ui->lineEdit_CodePostal->text());
    ui->comboBox_Ville->clear();
}


DialogSouhait::~DialogSouhait()
{
    delete ui;
}


void DialogSouhait::setEtat(QString)
{
    if (!changed)
        changed=true;
}

void DialogSouhait::fermer()
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

void DialogSouhait::valider()
{
    // To remove a database connection, first close the database using QSqlDatabase::close(),
    // then remove it using the static method QSqlDatabase::removeDatabase().
    // Savoir si la base supporte les transactions:
    // QSqlDriver::hasFeature(QSqlDriver::Transactions) will return true

    // Vérifier les données
    if (checkData())
    {
        QMessageBox::critical(this,"Données incorrectes","Tous les champs doivent être complétés");
    }
    else
    {   // Si Ok
        m_souhait->setBudget(ui->lineEdit_BudgetMax->text().toInt());
        m_souhait->setSurfaceHabitable(ui->lineEdit_SurfHabMin->text().toInt());
        m_souhait->setSurfaceJardin(ui->lineEdit_SurJardMin->text().toInt());
        // recuperer les villes
        foreach (Ville *v, m_listeVilles)
        {
            m_souhait->modifierVilles(v);
        }
    } // a la sortie de cette boucle, mon souhait est construit !

//    QSqlDatabase::database().transaction();
//    QSqlQuery query;
//    query.exec("SELECT id FROM employee WHERE name = 'Torild Halvorsen'");
//    if (query.next()) {
//        int employeeId = query.value(0).toInt();
//        query.exec("INSERT INTO project (id, name, ownerid) "
//                   "VALUES (201, 'Manhattan Project', "
//                   + QString::number(employeeId) + ')');
//    }
//    QSqlDatabase::database().commit();


    // sauvegarder le souhait

    // connaitre la liste des souhaits existants pour ce client
    m_db = new BDD();
    if (m_db->ouvrir())
    {
        // Requete qui recupere juste le num du souhait correspondant au client
        QSqlQuery requeteListeSouhait(m_db->getDb());
        requeteListeSouhait.prepare("Select souhaits.num_s, souhaits.num_c FROM souhaits Where souhaits.num_c=:numClient Order by souhaits.num_s");
        requeteListeSouhait.bindValue(":numClient", m_souhait->getClient()->getNum());
        if (requeteListeSouhait.exec())
        {
            if (requeteListeSouhait.size() < 1)
            {
                // Ce client n'a pas de souhait
            }
            else // la requete me ramene le(s) numéro(s) de souhait existant(s) dans la BDD
            {
                // Ranger ces numéros dans ma liste de numéros de souhait
                // pour pouvoir comparer
                for (int i = 0; i< requeteListeSouhait.size(); i++)
                {
                    while(requeteListeSouhait.next())
                    {
                        m_listeNumeroSouhaits[i] = requeteListeSouhait.value(0).toInt();
                    }

                }
            }

        }

        // Fermer la connexion
        m_db->close();
    } // Ici, si client avait des souhaits, listeNuméroSouhaits contient les numéros des souhaits récupérés

    // Ouvrir une transaction
            // Sauvegarder le souhait
            // Récupérer la nouvelle liste des souhaits pour ce client
            // Comparer les deux listes de souhaits pour identifier le numéro du nouveau souhait
            // insérer les villes dans villes_souhaitees avec le nouveau numéro
        // Fermer la transaction : Commit / Rollback

    if (m_souhait->sauvegarderSouhait())
    {
//-------------------------------------------------
        // vu que le souhait est sauvegardé
        // recupéré son numéro pour pouvoir l'associer à la ville dans la table villes_souhaitées
        int numSouhait;
        m_db = new BDD();

        if (m_db->ouvrir())
        {
            QSqlQuery requeteNumSouhait(m_db->getDb());
            requeteNumSouhait.prepare("SELECT num_s FROM souhaits WHERE num_c=:numClient");
            requeteNumSouhait.bindValue(":numClient", m_souhait->getClient()->getNum());
            if (requeteNumSouhait.exec())
            {
                qDebug() << "Requete numSouhait ok";
                while (requeteNumSouhait.next())
                    numSouhait = requeteNumSouhait.value(0).toInt();
                qDebug() << numSouhait;

            }
            //a la sortie de la boucle, numSouhait correspond au numero du souhait enregistré dans la base
//---------------------------------

            // sauvegarder les villes associées
            foreach (Ville *v, m_listeVilles)
            {
                qDebug() << numSouhait
                         << v->getNum();
                m_souhait->sauvegarderVillesSouhaitees(numSouhait,v->getNum());
            }

            QMessageBox::information(this,"Données sauvegardées","Bien sauvegardé");
            this->close();
        }
        else
        {
            QMessageBox::critical(this,"Sauvegarde impossible","Le souhait n'a pas été sauvegardé. Vérifiez vos données !");
        }
        m_db->close();
    }
}

bool DialogSouhait::checkData()
{

    if (ui->lineEdit_BudgetMax->text().isEmpty() || ui->lineEdit_SurfHabMin->text().isEmpty()|| ui->lineEdit_SurJardMin->text().isEmpty())
        return true;
    else return false;
}

void DialogSouhait::chercherVilles()
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
                        ui->comboBox_Ville->addItem(ville->getNom());
                    }
                }
            }
        }
        m_db->close();
    }
}
