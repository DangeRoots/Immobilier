#ifndef DIALOGACCUEIL_H
#define DIALOGACCUEIL_H

#include <QDialog>
#include <ui_barreMenuFiche.h>
#include <ui_accueilResultat.h>
#include <widgetclient.h>
#include "BDD.h"
#include "Parametre.h"
#include <dialogbien.h>
#include <dialogsouhait.h>
#include <dialogclient.h>
#include <Client.h>
#include <QList>
#include <dialoglistebiens.h>
#include <dialoglistesouhait.h>


namespace Ui {
    class DialogAccueil;
}

class DialogAccueil : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAccueil(QWidget *parent = 0);
    ~DialogAccueil();

private:
    Ui::DialogAccueil *ui;
    Ui::barreMenuFiche m_menu;

    BDD *m_db;
    DialogClient *m_dialogClient;

    DialogListeBiens *m_dialogListeBiens;
    DialogBien *m_dialogBien;
    DialogSouhait *m_dialogSouhait;
    DialogListeSouhait *m_dialogListeSouhaits;
    Client *m_clientCourant;
    QList<Client *> m_listeClients;

public slots:
    void reset();
    void chercherClients();
    void nouveauClient();
    void nouveauBien(int);
    void ouvrirClient(int);
    void ouvrirListeSouhaits(int);
    void ouvrirListeBiens(int);
    void nouveauSouhait(int);
};

#endif // DIALOGACCUEIL_H
