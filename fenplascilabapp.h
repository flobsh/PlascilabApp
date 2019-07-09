#ifndef FENPLASCILABAPP_H
#define FENPLASCILABAPP_H

#include <QWidget>
#include "serveur.h"
#include <QSqlDatabase>
#include <QSqlQueryModel>

namespace Ui {
class FenPlascilabApp;
}

class FenPlascilabApp : public QWidget
{
    Q_OBJECT

public:
    explicit FenPlascilabApp(QWidget *parent = nullptr);
    static QString idToHex(QString const& idCarte);
    ~FenPlascilabApp();

public slots:
    void affMessageServeur(QString const& message);
    void affMessageSQL(QString const& message);
    bool connexionBaseAdmin();
    void deconnexionBaseAdmin();
    bool baseAdminAccessible();
    void affVueAdherents();
    void affVueAdherentsNonAJour();
    void affVueBeneficiaires();
    void activationBoutonsEdition();
    void desactivationBoutonsEdition();
    void receptionIDCarte(QString const& donnees);
    void affDetails();
    void cacherDetails();
    void rechercherAdherent();
    void ajouterAdherent();
    void editerAdherent();
    void crediterAdherent();
    void supprimerAdherent();
    void ajouterBeneficiaire();
    void supprimerBeneficiaire();
    void eteindreRaspberry();
    int getIDAdherentSelectionne() const;
    bool idAdherentSelectionneIsValid() const;

private slots:
    void lireFichierConfiguration(QString nomFichier);
    void ecrireFichierConfiguration(QString nomFichier);

private:

    //--------------------------//
    // Interface utilisateur    //
    //--------------------------//

    Ui::FenPlascilabApp *ui;

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

    //-----------------------------------//
    // Modèles pour les base de données  //
    //-----------------------------------//

    QSqlQueryModel *modeleAdherents;
    QSqlQueryModel *modeleBeneficiaires;

    //------------------------------//
    // Serveur et bases de données  //
    //------------------------------//

    Serveur *serveur;

    QSqlDatabase *baseDonnees;
    QSqlDatabase *baseAdmin;
};

#endif // FENPLASCILABAPP_H
