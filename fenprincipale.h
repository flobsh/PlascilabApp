#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QTabWidget>
#include <QtWebKitWidgets>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQueryModel>

#include "serveur.h"

class FenPrincipale : public QWidget {
    Q_OBJECT

    public:
        FenPrincipale();
        ~FenPrincipale();

    private:
        QString idToHex(QString const& idCarte);

    public slots:
        void affMessageServeur(QString const& message);
        void affMessageSQL(QString const& message);
        void affFenParametres();
        bool connexionBaseAdmin();
        void affAdherent(QString const& idCarte);
        void ajouterAdherent();
        void listeAdherents();
        void editerAdherent();
        void crediterAdherent();
        void supprimerAdherent();
        void activationBoutonsEdition();
        void desactivationBoutonsEdition();

    private:
        QGridLayout *layoutPrincipal;
        QVBoxLayout *layoutAdministration;
        QGridLayout *layoutAfficheurBadge;
        QTabWidget *barreOnglets;
        QWebView *pageWeb;
        QTableView *vueTableSQL;
        QTableView *vueJournal;
        QPushButton *bListeAdherents;
        QPushButton *bAjouterAdherent;
        QPushButton *bCrediterAdherent;
        QPushButton *bEditerAdherent;
        QPushButton *bSupprimerAdherent;
        QPushButton *bParametres;
        QFrame *fAdministration;
        QVBoxLayout *layoutBoutonsAdministration;
        QHBoxLayout *layoutEditeur;
        QGridLayout *layoutServeurs;
        QLabel *labelCommunicationServeur;
        QLabel *labelCommunicationSQL;
        QLabel *affCommunicationServeur;
        QLabel *affCommunicationSQL;
        QFrame *fAfficheurBadge;
        QLabel *photoAdherent;
        QLabel *labelID;
        QLabel *labelNom;
        QLabel *labelPrenom;
        QLabel *labelDebutAbn;
        QLabel *labelFinAbn;
        QLabel *affBadgeID;
        QLabel *affBadgeNom;
        QLabel *affBadgePrenom;
        QLabel *affBadgeDebutAbn;
        QLabel *affBadgeFinAbn;
        QPushButton *bRafraichirServeur;
        QPushButton *bRafraichirSQL;

        Serveur *serveur;

        QSqlDatabase *baseDonnees;
        QSqlDatabase *baseAdmin;
        QSqlQueryModel *modeleSQL;
};

#endif // FENPRINCIPALE_H
