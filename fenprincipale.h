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
#include <QGroupBox>

#include "serveur.h"

class FenPrincipale : public QWidget {
    Q_OBJECT

public:
    FenPrincipale();
    ~FenPrincipale();

private:
    QString idToHex(QString const& idCarte);
    void lireFichierConfiguration(QString nomFichier);
    void ecrireFichierConfiguration(QString nomFichier);

public slots:
    void affMessageServeur(QString const& message);
    void affMessageSQL(QString const& message);
    void affFenParametres();
    bool connexionBaseAdmin();
    void affAdherent(QString const& idCarte);
    void ajouterAdherent();
    void listeAdherents();
    void adherentsNonAJour();
    void editerAdherent();
    void crediterAdherent();
    void supprimerAdherent();
    void rechercherAdherent();
    void activationBoutonsEdition();
    void desactivationBoutonsEdition();
    void changementSelectionVueTableSQL();
    void eteindreRaspberry();

private:
    QString ipAccueil;
    QString ipBaseDonnees;
    QString ipRaspberry;
    QString nomBaseDonnees;
    QString nomUtilisateurLectureBDD;
    QString motPasseLectureBDD;
    int portServeur;
    QGridLayout *layoutPrincipal;
    QVBoxLayout *layoutAdministration;
    QGridLayout *layoutAfficheurBadge;
    QVBoxLayout *layoutGBConnexion;
    QVBoxLayout *layoutGBAdministration;
    QHBoxLayout *layoutGBRecherche;
    QGroupBox *gbConnexion;
    QGroupBox *gbRecherche;
    QGroupBox *gbAdministration;
    QTabWidget *barreOnglets;
    QWebView *pageWeb;
    QTableView *vueTableSQL;
    QTableView *vueJournal;
    QPushButton *bConnexion;
    QPushButton *bListeAdherents;
    QPushButton *bAdherentsNonAJour;
    QPushButton *bAjouterAdherent;
    QPushButton *bCrediterAdherent;
    QPushButton *bEditerAdherent;
    QPushButton *bSupprimerAdherent;
    QPushButton *bParametres;
    QPushButton *bRecherche;
    QLineEdit *lineRecherche;
    QFrame *fAdministration;
    QVBoxLayout *layoutBoutonsAdministration;
    QVBoxLayout *layoutBoutonsServeurs;
    QHBoxLayout *layoutServeurs;
    QHBoxLayout *layoutEditeur;
    QGridLayout *layoutAffichageServeurs;
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
