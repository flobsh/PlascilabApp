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
    void activationBoutonsEdition(QModelIndex const& indexModele);
    void desactivationBoutonsEdition();
    void changementSelectionVueTableSQL();
    void eteindreRaspberry();

private:

    //--------------------------//
    // Onglet Horaires RER      //
    //--------------------------//

    QWebView *pageWeb;

    //--------------------------//
    // Onglet Administration    //
    //--------------------------//

    // Layout principal

    QFrame *fAdministration;
        QHBoxLayout *layoutAdministration;

    // Table de vue SQL

    QVBoxLayout *layoutVuesTables;

        QTableView *vueTableAdherents;
            QSqlQueryModel *modeleAdherents;

        QTableView *vueTableBeneficiaires;
            QSqlQueryModel *modeleBeneficiaires;

    // Détails et bénéficiaires

    QHBoxLayout *layoutDetailsBeneficiaires;

        QGroupBox *gbDetails;
            QGridLayout *layoutDetails;
                QHBoxLayout *layoutIDs;
                    QLabel *labelNumAdherent;
                    QLabel *affAdherent;
                    QLabel *labelIDCarte;
                    QLabel *affIDCarte;

                QLabel *labelDetailsNom, *affDetailsNom;
                QLabel *labelDetailsPrenom, *affDetailsPrenom;
                QLabel *labelDetailsDesignation, *affDetailsDesignation;
                QLabel *labelDetailsAdresse, *affDetailsAdresse;
                QLabel *labelDetailsCP, *affDetailsCP;
                QLabel *labelDetailsVille, *affDetailsVille;
                QLabel *labelDetailsMail, *affDetailsMail;
                QLabel *labelDetailsTel, *affDetailsTel;
                QLabel *labelDetailsTypeAdhesion, *affDetailsTypeAdhesion;
                QLabel *labelDetailsAbonnement, *affDetailsAbonnement;
                QLabel *labelDetailsDateDebut, *affDetailsDateDebut;
                QLabel *labelDetailsDateDebut, *affDetailsMail;


    // Colonne de boutons

    QVBoxLayout *layoutBoutonsAdministration;

        QGroupBox *gbConnexion;
            QVBoxLayout *layoutGBConnexion;
                QPushButton *bConnexion;
                QPushButton *bParametres;

        QGroupBox *gbRecherche;
            QHBoxLayout *layoutGBRecherche;
                QPushButton *bRecherche;
                QLineEdit *lineRecherche;

        QGroupBox *gbAdministration;
            QVBoxLayout *layoutGBAdministration;
                QPushButton *bListeAdherents;
                QPushButton *bAdherentsNonAJour;
                QPushButton *bAjouterAdherent;
                QPushButton *bCrediterAdherent;
                QPushButton *bEditerAdherent;
                QPushButton *bSupprimerAdherent;

    // Affichage de l'état des serveurs

    QHBoxLayout *layoutServeurs;
        QGridLayout *layoutAffichageServeurs;
            QLabel *labelCommunicationServeur;
            QLabel *labelCommunicationSQL;
            QLabel *affCommunicationServeur;
            QLabel *affCommunicationSQL;

        QVBoxLayout *layoutBoutonsServeurs;
            QPushButton *bRafraichirServeur;
            QPushButton *bRafraichirSQL;

    //--------------------------//
    // Onglet Passages          //
    //--------------------------//

    QTableView *vueJournal;

    //--------------------------//
    // Structure principale     //
    //--------------------------//

    QGridLayout *layoutPrincipal;
        QTabWidget *barreOnglets;

        QFrame *fAfficheurBadge;
            QGridLayout *layoutAfficheurBadge;
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

    //--------------------------//
    // Données                  //
    //--------------------------//

    QString ipAccueil;
    QString ipBaseDonnees;
    QString ipRaspberry;
    QString nomBaseDonnees;
    QString nomUtilisateurLectureBDD;
    QString motPasseLectureBDD;
    int portServeur;

    //------------------------------//
    // Serveur et bases de données  //
    //------------------------------//

    Serveur *serveur;

    QSqlDatabase *baseDonnees;
    QSqlDatabase *baseAdmin;
};

#endif // FENPRINCIPALE_H
