#include "fenplascilabapp.h"
#include "ui_fenplascilabapp.h"
#include "fenconnexion.h"
#include "fenajouteradherent.h"
#include "fenediteradherent.h"
#include "fencrediteradherent.h"

#include <iostream>

#include <QFile>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QTcpSocket>
#include <QSignalSpy>

/**
 * @brief Crée une nouvelle instance de fenêtre principale
 * @param parent Wiget parent
 */

FenPlascilabApp::FenPlascilabApp(QWidget *parent) : QWidget(parent), ui(new Ui::FenPlascilabApp) {

    //-------------------------------------//
    // Initialisation interface graphique  //
    //-------------------------------------//

    QString version("2.0.0 Alpha");
    ui->setupUi(this);
    this->setWindowTitle("Plascilab App - v." + version);

    //------------------------------//
    // Initialisation des données   //
    //------------------------------//

    ipAccueil = "0.0.0.0";
    ipBaseDonnees = "0.0.0.0";
    ipRaspberry = "0.0.0.0";
    nomBaseDonnees = "";
    nomUtilisateurLectureBDD = "";
    motPasseLectureBDD = "";
    portServeur = 50855;

    lireFichierConfiguration("configuration.json");

    //--------------------------------------//
    // Modèles pour les bases de données    //
    //--------------------------------------//

    modeleAdherents = new QSqlQueryModel();
    modeleBeneficiaires = new QSqlQueryModel();

    //------------------------------//
    // Initialisation du serveur    //
    //------------------------------//

    serveur = new Serveur(portServeur);
    connect(serveur, SIGNAL(messageServeur(QString)), this, SLOT(affMessageServeur(QString)));
    connect(serveur, SIGNAL(receptionIDCarte(QString)), this, SLOT(receptionIDCarte(QString)));
    serveur->ouvrir();

    //------------------------------//
    // Initialisation BDD Lecture   //
    //------------------------------//

    baseDonnees = new QSqlDatabase();
    *baseDonnees = QSqlDatabase::addDatabase("QODBC");
    baseDonnees->setHostName(ipBaseDonnees);
    baseDonnees->setUserName(nomUtilisateurLectureBDD);
    baseDonnees->setPassword(motPasseLectureBDD);
    baseDonnees->setDatabaseName("Driver={MySQL ODBC 8.0 Unicode Driver};"
                                 "Server=" + ipBaseDonnees + ";" +
                                 "Database=" + nomBaseDonnees + ";" +
                                 "Uid=" + nomUtilisateurLectureBDD + ";" +
                                 "Pwd=" + motPasseLectureBDD + ";");
    if (baseDonnees->open()) {
        affMessageSQL("Connecté sur " + baseDonnees->hostName() + " en tant que " + baseDonnees->userName());
    }
    else {
        affMessageSQL("La connexion sur " + baseDonnees->hostName() + " en tant que " + baseDonnees->userName() + " a échoué : " + baseDonnees->lastError().text());
    }

    //-------------------------------------//
    // Initialisation BDD Administrateur   //
    //-------------------------------------//

    baseAdmin = new QSqlDatabase();
    *baseAdmin = QSqlDatabase::addDatabase("QODBC", "Admin");
    baseAdmin->setHostName(ipBaseDonnees);
    baseAdmin->setDatabaseName(nomBaseDonnees);

    //---------------//
    // Connections   //
    //---------------//

    // Boutons connexion et paramètres

    connect(ui->bConnexion, SIGNAL(released()), this, SLOT(connexionBaseAdmin()));

    // Boutons d'administration

    connect(ui->bRafraichir, SIGNAL(released()), this, SLOT(affVueAdherents()));
    connect(ui->bAbnNonAJour, SIGNAL(released()), this, SLOT(affVueAdherentsNonAJour()));
    connect(ui->bAjouterAdh, SIGNAL(released()), this, SLOT(ajouterAdherent()));
    connect(ui->bEditerAdh, SIGNAL(released()), this, SLOT(editerAdherent()));
    connect(ui->bCrediterAdh, SIGNAL(released()), this, SLOT(crediterAdherent()));
    connect(ui->bSupprimerAdh, SIGNAL(released()), this, SLOT(supprimerAdherent()));

    // Vue des tables

    connect(ui->vueTableAdherents, SIGNAL(clicked(QModelIndex)), this, SLOT(activationBoutonsEdition()));
}

/**
 * @brief FenPlascilabApp::idToHex Convertit le code de la carte en chaîne de caractère hexadécimale
 * @param idCarteStr Le code de la carte, sous la forme "000.000.000.000.000"
 * @return Le code de la carte sous format hexadécimal
 */

QString FenPlascilabApp::idToHex(const QString &idCarteStr) {
    QStringList idCarte = idCarteStr.split(".");
    return  (QString::number(idCarte.at(0).toInt(), 16) +
            QString::number(idCarte.at(1).toInt(), 16) +
            QString::number(idCarte.at(2).toInt(), 16) +
            QString::number(idCarte.at(3).toInt(), 16) +
            QString::number(idCarte.at(4).toInt(), 16)).toUpper();
}

/**
 * @brief FenPlascilabApp::lireFichierConfiguration Lit le fichier de configuration
 * @param nomFichier Emplacement du fichier de configuration
 */

void FenPlascilabApp::lireFichierConfiguration(QString nomFichier) {
    QFile fichierConfiguration(nomFichier);

    if(!fichierConfiguration.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier de configuration");
        return;
    }

    QByteArray donneesConfiguration = fichierConfiguration.readAll();

    QJsonDocument fichierConfigurationJSON(QJsonDocument::fromJson(donneesConfiguration));

    QJsonObject donneesConfigurationJSON = fichierConfigurationJSON.object();

    if(donneesConfigurationJSON.contains("ipAccueil") && donneesConfigurationJSON["ipAccueil"].isString()) {
        ipAccueil = donneesConfigurationJSON["ipAccueil"].toString();
    }

    if(donneesConfigurationJSON.contains("ipBaseDonnees") && donneesConfigurationJSON["ipBaseDonnees"].isString()) {
        ipBaseDonnees = donneesConfigurationJSON["ipBaseDonnees"].toString();
    }

    if(donneesConfigurationJSON.contains("ipRaspberry") && donneesConfigurationJSON["ipRaspberry"].isString()) {
        ipRaspberry = donneesConfigurationJSON["ipRaspberry"].toString();
    }

    if(donneesConfigurationJSON.contains("nomBaseDonnees") && donneesConfigurationJSON["nomBaseDonnees"].isString()) {
        nomBaseDonnees = donneesConfigurationJSON["nomBaseDonnees"].toString();
    }

    if(donneesConfigurationJSON.contains("nomUtilisateurLectureBDD") && donneesConfigurationJSON["nomUtilisateurLectureBDD"].isString()) {
        nomUtilisateurLectureBDD = donneesConfigurationJSON["nomUtilisateurLectureBDD"].toString();
    }

    if(donneesConfigurationJSON.contains("motPasseLectureBDD") && donneesConfigurationJSON["motPasseLectureBDD"].isString()) {
        motPasseLectureBDD = donneesConfigurationJSON["motPasseLectureBDD"].toString();
    }

    if(donneesConfigurationJSON.contains("portServeur") && donneesConfigurationJSON["portServeur"].isDouble()) {
        portServeur = donneesConfigurationJSON["portServeur"].toInt();
    }

    fichierConfiguration.close();
}

/**
 * @brief FenPlascilabApp::ecrireFichierConfiguration Ecrit le fichier de configuration
 * @param nomFichier Emplacement du fichier de configuration
 */

void FenPlascilabApp::ecrireFichierConfiguration(QString nomFichier) {
    QFile fichierConfiguration(nomFichier);

    if(!fichierConfiguration.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier de configuration");
        return;
    }

    QJsonObject donneesConfigurationJSON;
    donneesConfigurationJSON["ipAccueil"] = ipAccueil;
    donneesConfigurationJSON["ipBaseDonnees"] = ipBaseDonnees;
    donneesConfigurationJSON["ipRaspberry"] = ipRaspberry;
    donneesConfigurationJSON["nomBaseDonnees"] = nomBaseDonnees;
    donneesConfigurationJSON["nomUtilisateurLectureBDD"] = nomUtilisateurLectureBDD;
    donneesConfigurationJSON["motPasseLectureBDD"] = motPasseLectureBDD;
    donneesConfigurationJSON["portServeur"] = portServeur;

    QJsonDocument fichierConfigurationJSON(donneesConfigurationJSON);
    fichierConfiguration.write(fichierConfigurationJSON.toJson());
    fichierConfiguration.close();
}

/**
 * @brief FenPlascilabApp::affMessageServeur (slot) Affiche un message sur le label associé à l'affichage des messages serveurs
 * @param message Message à afficher
 */

void FenPlascilabApp::affMessageServeur(const QString &message) {
    ui->affServeurRPi->setText(message);
}

/**
 * @brief FenPlascilabApp::affMessageSQL (slot) Affiche un message sur le label associé à l'affichage des messages de la base de données
 * @param message Message à afficher
 */

void FenPlascilabApp::affMessageSQL(const QString &message) {
    ui->affServeurSQL->setText(message);
}

void FenPlascilabApp::receptionIDCarte(const QString &donnees) {
    QString idCarteHex(idToHex(donnees));

    QSqlQuery requeteAdherent(*baseDonnees);
    requeteAdherent.prepare("SELECT nom, prenom, dateDebutAbn, dateFinAbn FROM Adherents WHERE idCarte = :_idCarte");
    requeteAdherent.bindValue(":_idCarte", idCarteHex);
    requeteAdherent.exec();
    requeteAdherent.last();

    ui->affBadgeID->setText(idCarteHex.toUpper());
    ui->affBadgeNom->setText(requeteAdherent.value(0).toString());
    ui->affBadgePrenom->setText(requeteAdherent.value(1).toString());
    ui->affBadgeDebutAbn->setText(requeteAdherent.value(2).toDate().toString("dd/MM/yyyy"));
    ui->affBadgeFinAbn->setText(requeteAdherent.value(3).toDate().toString("dd/MM/yyyy"));
}

/**
 * @brief FenPlascilabApp::connexionBaseAdmin Affiche une fenêtre de connexion à la base de données administrateur
 * @return true si la connexion à la base a réussi, false sinon
 */

bool FenPlascilabApp::connexionBaseAdmin() {
    if(ui->bConnexion->text() == "Déconnexion") {
        deconnexionBaseAdmin();
        return false;
    }

    FenConnexion *fenConnexion = new FenConnexion(this);
    fenConnexion->exec();

    if(fenConnexion->result() == QDialog::Rejected) {
        delete fenConnexion;
        return false;
    }

    baseAdmin->setUserName(fenConnexion->getUtilisateur());
    baseAdmin->setPassword(fenConnexion->getMotPasse());
    baseAdmin->setDatabaseName("Driver={MySQL ODBC 8.0 Unicode Driver};"
                               "Database=" + nomBaseDonnees + ";"
                               "Server=" + ipBaseDonnees + ";"
                               "Uid=" + fenConnexion->getUtilisateur() + ";"
                               "Pwd=" + fenConnexion->getMotPasse() + ";");

    delete fenConnexion;

    if(!baseAdmin->open()) {
        QMessageBox::critical(this, "Erreur", "Erreur d'authentification. Vérifiez que la base de donnée est accessible et que vos identfiants sont corrects.");
        baseAdmin->close();
        return false;
    }

    ui->lineRecherche->setEnabled(true);
    ui->bRecherche->setEnabled(true);
    ui->bRafraichir->setEnabled(true);
    ui->bAjouterAdh->setEnabled(true);
    ui->bAbnNonAJour->setEnabled(true);
    ui->bConnexion->setText("Déconnexion");

    affVueAdherents();

    return true;
}

void FenPlascilabApp::deconnexionBaseAdmin() {
    ui->bConnexion->setText("Connexion");
    ui->vueTableAdherents->setModel(nullptr);
    ui->vueTableBeneficiaire->setModel(nullptr);
    cacherDetails();
    baseAdmin->close();
    ui->lineRecherche->setEnabled(false);
    ui->bRecherche->setEnabled(false);
    ui->bRafraichir->setEnabled(false);
    ui->bAbnNonAJour->setEnabled(false);
    ui->bAjouterAdh->setEnabled(false);
    ui->bCrediterAdh->setEnabled(false);
    ui->bEditerAdh->setEnabled(false);
    ui->bEditerAdh->setEnabled(false);
}

bool FenPlascilabApp::baseAdminAccessible() {
    if(!baseAdmin->open()) {
        QMessageBox::critical(this, "Erreur", "La base de données n'est plus accessible. Vérifiez les connexions et tentez de vous reconnecter.");
        deconnexionBaseAdmin();
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief FenPlascilabApp::affVueAdherents Affiche la liste des adhérents dans la vue prévue à cet effet
 */

void FenPlascilabApp::affVueAdherents() {
    modeleAdherents->setQuery("SELECT id, idCarte, typeAdhesion, nom, prenom, designation, adresse, cp, ville, tel, mail, dureeAbn, dateDebutAbn, dateFinAbn from Adherents", *baseAdmin);
    if(modeleAdherents->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", modeleAdherents->lastError().text());
        return;
    }
    modeleAdherents->setHeaderData(0, Qt::Horizontal, "N° Adhérent");
    modeleAdherents->setHeaderData(1, Qt::Horizontal, "ID Carte");
    modeleAdherents->setHeaderData(2, Qt::Horizontal, "Type d'adhésion");
    modeleAdherents->setHeaderData(3, Qt::Horizontal, "Nom");
    modeleAdherents->setHeaderData(4, Qt::Horizontal, "Prénom");
    modeleAdherents->setHeaderData(5, Qt::Horizontal, "Désignation");
    modeleAdherents->setHeaderData(6, Qt::Horizontal, "Adresse");
    modeleAdherents->setHeaderData(7, Qt::Horizontal, "CP");
    modeleAdherents->setHeaderData(8, Qt::Horizontal, "Ville");
    modeleAdherents->setHeaderData(9, Qt::Horizontal, "Tel");
    modeleAdherents->setHeaderData(10, Qt::Horizontal, "Mail");
    modeleAdherents->setHeaderData(11, Qt::Horizontal, "Abonnement");
    modeleAdherents->setHeaderData(12, Qt::Horizontal, "Début");
    modeleAdherents->setHeaderData(13, Qt::Horizontal, "Fin");

    ui->vueTableAdherents->setModel(modeleAdherents);
    ui->vueTableAdherents->show();
}

void FenPlascilabApp::affVueAdherentsNonAJour() {

    QSqlQuery requeteAdhNonAJour(*baseAdmin);
    requeteAdhNonAJour.prepare("SELECT id, idCarte, typeAdhesion, nom, prenom, designation, adresse, cp, ville, tel, mail, dureeAbn, dateDebutAbn, dateFinAbn from Adherents WHERE dateDebutAbn > :_dateCourante OR dateFinAbn < :_dateCourante");
    requeteAdhNonAJour.bindValue(":_dateCourante", QDate::currentDate().toString("yyyy-MM-dd"));
    requeteAdhNonAJour.exec();
    requeteAdhNonAJour.last();

    modeleAdherents->setQuery(requeteAdhNonAJour);
    if(modeleAdherents->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", modeleAdherents->lastError().text());
        return;
    }
    modeleAdherents->setHeaderData(0, Qt::Horizontal, "N° Adhérent");
    modeleAdherents->setHeaderData(1, Qt::Horizontal, "ID Carte");
    modeleAdherents->setHeaderData(2, Qt::Horizontal, "Type d'adhésion");
    modeleAdherents->setHeaderData(3, Qt::Horizontal, "Nom");
    modeleAdherents->setHeaderData(4, Qt::Horizontal, "Prénom");
    modeleAdherents->setHeaderData(5, Qt::Horizontal, "Désignation");
    modeleAdherents->setHeaderData(6, Qt::Horizontal, "Adresse");
    modeleAdherents->setHeaderData(7, Qt::Horizontal, "CP");
    modeleAdherents->setHeaderData(8, Qt::Horizontal, "Ville");
    modeleAdherents->setHeaderData(9, Qt::Horizontal, "Tel");
    modeleAdherents->setHeaderData(10, Qt::Horizontal, "Mail");
    modeleAdherents->setHeaderData(11, Qt::Horizontal, "Abonnement");
    modeleAdherents->setHeaderData(12, Qt::Horizontal, "Début");
    modeleAdherents->setHeaderData(13, Qt::Horizontal, "Fin");

    ui->vueTableAdherents->setModel(modeleAdherents);
    ui->vueTableAdherents->show();
}

/**
 * @brief FenPlascilabApp::affVueBeneficiaires Affiche la liste des bénéficiaires pour un adhérent donné
 */

void FenPlascilabApp::affVueBeneficiaires() {

    QSqlQuery requeteBeneficiaires(*baseAdmin);
    requeteBeneficiaires.prepare("SELECT nom, prenom from Beneficiaires WHERE id = :_id");
    if(ui->vueTableAdherents->selectionModel()->selectedIndexes().isEmpty()) {
        return;
    }
    else {
        requeteBeneficiaires.bindValue(":_id", ui->vueTableAdherents->model()->index(ui->vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data());
        requeteBeneficiaires.exec();
        requeteBeneficiaires.last();
    }

    modeleBeneficiaires->setQuery(requeteBeneficiaires);

    if(modeleBeneficiaires->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", modeleBeneficiaires->lastError().text());
        return;
    }

    modeleBeneficiaires->setHeaderData(0, Qt::Horizontal, "Nom");
    modeleBeneficiaires->setHeaderData(1, Qt::Horizontal, "Prénom");
    ui->vueTableBeneficiaire->setModel(modeleBeneficiaires);
}

/**
 * @brief FenPlascilabApp::affDetails Affiche les détails de l'adhérent
 */

void FenPlascilabApp::affDetails() {
    int ligneSelectionnee = ui->vueTableAdherents->selectionModel()->selectedIndexes().at(0).row();

    ui->affID->setText(modeleAdherents->index(ligneSelectionnee, 0).data().toString());
    ui->affIDCarte->setText(modeleAdherents->index(ligneSelectionnee, 1).data().toString());
    ui->affNom->setText(modeleAdherents->index(ligneSelectionnee, 3).data().toString());
    ui->affPrenom->setText(modeleAdherents->index(ligneSelectionnee, 4).data().toString());
    ui->affDesignation->setText(modeleAdherents->index(ligneSelectionnee, 5).data().toString());
    ui->affAdresse->setText(modeleAdherents->index(ligneSelectionnee, 6).data().toString());
    ui->affCP->setText(modeleAdherents->index(ligneSelectionnee, 7).data().toString());
    ui->affVille->setText(modeleAdherents->index(ligneSelectionnee, 8).data().toString());
    ui->affMail->setText(modeleAdherents->index(ligneSelectionnee, 10).data().toString());
    ui->affTel->setText(modeleAdherents->index(ligneSelectionnee, 9).data().toString());
    ui->affAbonnement->setText(modeleAdherents->index(ligneSelectionnee, 11).data().toString());
    ui->affTypeAbn->setText(modeleAdherents->index(ligneSelectionnee, 2).data().toString());
    ui->affDebutAbn->setText(modeleAdherents->index(ligneSelectionnee, 12).data().toDate().toString("dd/MM/yyyy"));
    ui->affFinAbn->setText(modeleAdherents->index(ligneSelectionnee, 13).data().toDate().toString("dd/MM/yyyy"));

}

/**
 * @brief FenPlascilabApp::ajouterAdherent Affiche une fenêtre permettant d'ajouter un adhérent et ajoute cet adhérent à la base de données
 */

void FenPlascilabApp::ajouterAdherent() {

    FenAjouterAdherent fenAjouterAdherent(this, serveur);
    fenAjouterAdherent.exec();

    if(fenAjouterAdherent.result() == QDialog::Rejected) {
        return;
    }

    QSqlQuery requeteAjout(*baseAdmin);
    requeteAjout.prepare("INSERT INTO Adherents VALUES (NULL, :_idCarte, :_typeAdhesion, :_nom, :_prenom, :_designation, :_adresse, :_cp, :_ville, :_tel, :_mail, :_dureeAbn, :_nbAbn, :_dateDebutAbn, :_dateFinAbn);"
                         "INSERT INTO Beneficiaires VALUES ((SELECT MAX(id) FROM Adherents), :_nom, :_prenom);");
    requeteAjout.bindValue(":_idCarte", fenAjouterAdherent.getID());
    requeteAjout.bindValue(":_typeAdhesion", fenAjouterAdherent.getTypeAdhesion());
    requeteAjout.bindValue(":_nom", fenAjouterAdherent.getNom());
    requeteAjout.bindValue(":_prenom", fenAjouterAdherent.getPrenom());
    requeteAjout.bindValue(":_designation", fenAjouterAdherent.getDesignation());
    requeteAjout.bindValue(":_adresse", fenAjouterAdherent.getAdresse());
    requeteAjout.bindValue(":_cp", fenAjouterAdherent.getCP());
    requeteAjout.bindValue(":_ville", fenAjouterAdherent.getVille());
    requeteAjout.bindValue(":_tel", fenAjouterAdherent.getTel());
    requeteAjout.bindValue(":_mail", fenAjouterAdherent.getMail());
    requeteAjout.bindValue(":_dureeAbn", fenAjouterAdherent.getAbonnement());
    requeteAjout.bindValue(":_nbAbn", fenAjouterAdherent.getNbAbn());
    requeteAjout.bindValue(":_dateDebutAbn", fenAjouterAdherent.getDateDebutAbn());
    requeteAjout.bindValue(":_dateFinAbn", fenAjouterAdherent.getDateFinAbn());

    requeteAjout.exec();
    requeteAjout.last();

    if(requeteAjout.lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", requeteAjout.lastError().text());
        return;
    }

    affVueAdherents();
}

void FenPlascilabApp::editerAdherent() {

    if(!idAdherentSelectionneIsValid()) {
        return;
    }

    int idAdherent(getIDAdherentSelectionne());


    QSqlQuery requeteEdition(*baseAdmin);
    requeteEdition.prepare("SELECT id, idCarte, typeAdhesion, nom, prenom, designation, adresse, cp, ville, tel, mail FROM Adherents WHERE id = :_id;");
    requeteEdition.bindValue(":_id", ui->vueTableAdherents->model()->index(ui->vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data().toInt());
    requeteEdition.exec();
    requeteEdition.last();

    if(requeteEdition.lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", requeteEdition.lastError().text());
        return;
    }

    idAdherent = requeteEdition.value(0).toInt();

    FenEditerAdherent fenEditerAdherent(this);
    fenEditerAdherent.setID(requeteEdition.value(1).toString());
    fenEditerAdherent.setTypeAdhesion(requeteEdition.value(2).toString());
    fenEditerAdherent.setNom(requeteEdition.value(3).toString());
    fenEditerAdherent.setPrenom(requeteEdition.value(4).toString());
    fenEditerAdherent.setDesignation(requeteEdition.value(5).toString());
    fenEditerAdherent.setAdresse(requeteEdition.value(6).toString());
    fenEditerAdherent.setCP(requeteEdition.value(7).toString());
    fenEditerAdherent.setVille(requeteEdition.value(8).toString());
    fenEditerAdherent.setMail(requeteEdition.value(10).toString());
    fenEditerAdherent.setTel(requeteEdition.value(9).toString());

    fenEditerAdherent.exec();

    if(fenEditerAdherent.result() == QDialog::Rejected) {
        return;
    }

    requeteEdition.prepare("UPDATE Adherents SET idCarte = :_idCarte, typeAdhesion = :_typeAdhesion, nom = :_nom, prenom = :_prenom, designation = :_designation, adresse = :_adresse, cp = :_cp, ville = :_ville, tel = :_ville, mail = :_mail WHERE id = :_id");
    requeteEdition.bindValue(":_idCarte", fenEditerAdherent.getID());
    requeteEdition.bindValue(":_typeAdhesion", fenEditerAdherent.getTypeAdhesion());
    requeteEdition.bindValue(":_nom", fenEditerAdherent.getNom());
    requeteEdition.bindValue(":_prenom", fenEditerAdherent.getPrenom());
    requeteEdition.bindValue(":_designation", fenEditerAdherent.getDesignation());
    requeteEdition.bindValue(":_adresse", fenEditerAdherent.getAdresse());
    requeteEdition.bindValue(":_cp", fenEditerAdherent.getCP());
    requeteEdition.bindValue(":_ville", fenEditerAdherent.getVille());
    requeteEdition.bindValue(":_tel", fenEditerAdherent.getTel());
    requeteEdition.bindValue(":_mail", fenEditerAdherent.getMail());
    requeteEdition.bindValue(":_id", idAdherent);

    requeteEdition.exec();
    requeteEdition.last();

    if(requeteEdition.lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", requeteEdition.lastError().text());
        return;
    }

    affVueAdherents();
}

void FenPlascilabApp::crediterAdherent() {

    int idAdherent(0);

    QSqlQuery requeteCredit(*baseAdmin);
    requeteCredit.prepare("SELECT id, dureeAbn, nbAbn, dateDebutAbn, dateFinAbn FROM Adherents WHERE id = :_id;");
    requeteCredit.bindValue(":_id", ui->vueTableAdherents->model()->index(ui->vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data().toInt());
    requeteCredit.exec();
    requeteCredit.last();

    if(requeteCredit.lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", requeteCredit.lastError().text());
        return;
    }

    idAdherent = requeteCredit.value(0).toInt();

    FenCrediterAdherent fenCrediterAdherent(this);
    fenCrediterAdherent.setAbonnement(requeteCredit.value(1).toString());
    fenCrediterAdherent.setNbAbn(requeteCredit.value(2).toInt());
    fenCrediterAdherent.setDateDebutAbn(requeteCredit.value(3).toDate());
    fenCrediterAdherent.setDateFinAbn(requeteCredit.value(4).toDate());

    fenCrediterAdherent.exec();

    if(fenCrediterAdherent.result() == QDialog::Rejected) {
        return;
    }

    requeteCredit.prepare("UPDATE Adherents SET dureeAbn = :_dureeAbn, nbAbn = :_nbAbn, dateDebutAbn = :_dateDebutAbn, dateFinAbn = :_dateFinAbn WHERE id = :_id");
    requeteCredit.bindValue(":_dureeAbn", fenCrediterAdherent.getAbonnement());
    requeteCredit.bindValue(":_nbAbn", fenCrediterAdherent.getNbAbn());
    requeteCredit.bindValue(":_dateDebutAbn", fenCrediterAdherent.getDateDebutAbn());
    requeteCredit.bindValue(":_dateFinAbn", fenCrediterAdherent.getDateFinAbn());
    requeteCredit.bindValue(":_id", idAdherent);

    requeteCredit.exec();
    requeteCredit.last();

    if(requeteCredit.lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", requeteCredit.lastError().text());
        return;
    }

    affVueAdherents();
}

void FenPlascilabApp::supprimerAdherent() {

    QSqlQuery requeteSuppresion(*baseAdmin);
    requeteSuppresion.prepare("SELECT id, nom, prenom FROM Adherents WHERE id = (:_id)");
    requeteSuppresion.bindValue(":_id", ui->vueTableAdherents->model()->index(ui->vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data().toInt());
    requeteSuppresion.exec();
    requeteSuppresion.last();

    int reponse = QMessageBox::question(this, "Supprimer un adhérent", "Etes-vous sûr de vouloir supprimer " +
                                        requeteSuppresion.value(2).toString() + " " +
                                        requeteSuppresion.value(1).toString() + " (ID : " +
                                        requeteSuppresion.value(0).toString() + ") de la base de données ?",
                                        QMessageBox::Yes | QMessageBox::No);

    if(reponse == QMessageBox::No) {
        return;
    }
    else {
        requeteSuppresion.prepare("DELETE FROM Adherents WHERE id = :_id");
        requeteSuppresion.bindValue(":_id", ui->vueTableAdherents->model()->index(ui->vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data().toInt());
        requeteSuppresion.exec();
    }

    affVueAdherents();
    return;
}

/**
 * @brief FenPlascilabApp::cacherDetails Cache les détails d'un adhérent
 */

void FenPlascilabApp::cacherDetails() {

    ui->affID->clear();
    ui->affIDCarte->clear();
    ui->affNom->clear();
    ui->affPrenom->clear();
    ui->affDesignation->clear();
    ui->affAdresse->clear();
    ui->affCP->clear();
    ui->affVille->clear();
    ui->affMail->clear();
    ui->affTel->clear();
    ui->affAbonnement->clear();
    ui->affTypeAbn->clear();
    ui->affDebutAbn->clear();
    ui->affFinAbn->clear();

}

/**
 * @brief FenPlascilabApp::activationBoutonsEdition Active les boutons d'édition
 */

void FenPlascilabApp::activationBoutonsEdition() {

    if(!idAdherentSelectionneIsValid()) {
        desactivationBoutonsEdition();
        return;
    }

    affVueBeneficiaires();
    affDetails();

    ui->bEditerAdh->setEnabled(true);
    ui->bCrediterAdh->setEnabled(true);
    ui->bSupprimerAdh->setEnabled(true);
}

void FenPlascilabApp::desactivationBoutonsEdition() {

    ui->vueTableBeneficiaire->setModel(nullptr);
    cacherDetails();

    ui->bEditerAdh->setEnabled(false);
    ui->bCrediterAdh->setEnabled(false);
    ui->bSupprimerAdh->setEnabled(false);
}

bool FenPlascilabApp::idAdherentSelectionneIsValid() const {
    return !ui->vueTableAdherents->selectionModel()->selectedIndexes().isEmpty() && ui->vueTableAdherents->selectionModel()->selectedIndexes().at(0).isValid();
}

int FenPlascilabApp::getIDAdherentSelectionne() const {
    return ui->vueTableAdherents->model()->index(ui->vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data().toInt();
}

void FenPlascilabApp::eteindreRaspberry() {

    QTcpSocket client(this);
    QSignalSpy signalConnexion(&client, SIGNAL(connected()));

    std::cout<< "Envoi.." + ipRaspberry.toStdString() << std::endl;
    client.abort();
    client.connectToHost("10.10.0.196", 50854);
    signalConnexion.wait(5000);
    std::cout << client.state() << std::endl;
    std::cout << client.write(QByteArray("TERM")) << std::endl;
    client.waitForBytesWritten(5000);
    client.close();
    std::cout<< "Envoi terminé" << std::endl;
}

FenPlascilabApp::~FenPlascilabApp()
{
    delete serveur;
    delete baseAdmin;
    delete baseDonnees;
    delete ui;
}
