#ifndef DIALOGSOUHAIT_H
#define DIALOGSOUHAIT_H

#include <QDialog>
#include <ui_barreMenuFiche.h>
#include <Souhait.h>
#include <Ville.h>
#include <QMessageBox>
#include <BDD.h>

namespace Ui {
    class DialogSouhait;
}

class DialogSouhait : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSouhait(QWidget *parent = 0);
    DialogSouhait(Souhait *souhait, QWidget *parent = 0);
    ~DialogSouhait();

private:
    Ui::DialogSouhait *ui;
    Ui::barreMenuFiche m_menu;
    Souhait *m_souhait;
    QList<Ville *> m_listeVilles;
    BDD *m_db;

    bool checkData();
    bool changed;

public slots:
    void setEtat(QString);
    void fermer();
    void valider();
    void chercherVilles();
    void copierVille(QString);
};

#endif // DIALOGSOUHAIT_H
