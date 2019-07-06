#include "fenprincipale.h"
#include "fenparametres.h"
#include "fenconnexion.h"
#include "fenajouteradherent.h"
#include "fenediteradherent.h"
#include "fencrediteradherent.h"
#include <iostream>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QFile>
#include <QTcpSocket>
#include <QSignalSpy>

FenPrincipale::FenPrincipale() {
    layoutPrincipal = new QGridLayout(this);

    barreOnglets = new QTabWidget();

    //--------------------------//
    // Onglet Horaires RER      //
    //--------------------------//

    pageWeb = new QWebView();
    pageWeb->load(QUrl("http://monrer.fr/?s=RIS"));

    //--------------------------//
    // Onglet Administration    //
    //--------------------------//

    // Tables de vues SQL

    vueTableAdherents = new QTableView();
    vueTableBeneficiaires = new QTableView();

    modeleAdherents = new QSqlQueryModel();
    modeleBeneficiaires = new QSqlQueryModel();

    layoutVuesTables = new QVBoxLayout();
    layoutVuesTables->addWidget(vueTableAdherents);
    layoutVuesTables->addWidget(vueTableBeneficiaires);
    layoutVuesTables->setStretch(0,3);
    layoutVuesTables->setStretch(1,1);

    // Colonne de boutons

        // Boutons de connexion

        bConnexion = new QPushButton("Connexion");
        bParametres = new QPushButton("Paramètres");

        layoutGBConnexion = new QVBoxLayout();
        layoutGBConnexion->addWidget(bConnexion);
        layoutGBConnexion->addWidget(bParametres);

        gbConnexion = new QGroupBox("Connexion");
        gbConnexion->setLayout(layoutGBConnexion);

        // Boutons de recherche

        bRecherche = new QPushButton("Go");
        bRecherche->setEnabled(false);

        lineRecherche = new QLineEdit();
        lineRecherche->setEnabled(false);

        layoutGBRecherche = new QHBoxLayout();
        layoutGBRecherche->addWidget(lineRecherche);
        layoutGBRecherche->addWidget(bRecherche);

        gbRecherche = new QGroupBox("Recherche");
        gbRecherche->setLayout(layoutGBRecherche);

        // Boutons d'administration

        bListeAdherents = new QPushButton("Rafraîchir la liste");
        bAdherentsNonAJour = new QPushButton("Adhérents non à jours");
        bAjouterAdherent = new QPushButton("Ajouter adhérent");
        bCrediterAdherent = new QPushButton("Créditer adhérent");
        bEditerAdherent = new QPushButton("Editer adhérent");
        bSupprimerAdherent = new QPushButton("Supprimer adhérent");

        bListeAdherents->setEnabled(false);
        bAdherentsNonAJour->setEnabled(false);
        bAjouterAdherent->setEnabled(false);
        bCrediterAdherent->setEnabled(false);
        bEditerAdherent->setEnabled(false);
        bSupprimerAdherent->setEnabled(false);

        layoutGBAdministration = new QVBoxLayout();
        layoutGBAdministration->addWidget(bListeAdherents);
        layoutGBAdministration->addWidget(bAdherentsNonAJour);
        layoutGBAdministration->addWidget(bAjouterAdherent);
        layoutGBAdministration->addWidget(bCrediterAdherent);
        layoutGBAdministration->addWidget(bEditerAdherent);
        layoutGBAdministration->addWidget(bSupprimerAdherent);

        gbAdministration = new QGroupBox("Administration");
        gbAdministration->setLayout(layoutGBAdministration);

        // Layout principal des boutons d'administration

        layoutBoutonsAdministration = new QVBoxLayout();
        layoutBoutonsAdministration->addWidget(gbConnexion);
        layoutBoutonsAdministration->addWidget(gbRecherche);
        layoutBoutonsAdministration->addWidget(gbAdministration);
        layoutBoutonsAdministration->setStretch(2,1);

    // Affichage de l'état des serveurs

    labelCommunicationServeur = new QLabel("Communication RaspberryPI : ");
    labelCommunicationSQL = new QLabel("Communication base de données : ");

    affCommunicationServeur = new QLabel();
    affCommunicationSQL = new QLabel();

    affCommunicationServeur->setAlignment(Qt::AlignLeft);
    affCommunicationSQL->setAlignment(Qt::AlignLeft);

    layoutAffichageServeurs = new QGridLayout();
    layoutAffichageServeurs->addWidget(labelCommunicationServeur, 0, 0);
    layoutAffichageServeurs->addWidget(labelCommunicationSQL,1,0);
    layoutAffichageServeurs->addWidget(affCommunicationServeur, 0, 1);
    layoutAffichageServeurs->addWidget(affCommunicationSQL, 1, 1);
    layoutAffichageServeurs->setColumnStretch(2,1);

    bRafraichirServeur = new QPushButton("Eteindre");
    bRafraichirSQL = new QPushButton("Rafraichir");

    layoutBoutonsServeurs = new QVBoxLayout();
    layoutBoutonsServeurs->addWidget(bRafraichirServeur);
    layoutBoutonsServeurs->addWidget(bRafraichirSQL);

    layoutServeurs = new QHBoxLayout();
    layoutServeurs->addLayout(layoutAffichageServeurs);
    layoutServeurs->addLayout(layoutBoutonsServeurs);
    layoutServeurs->setStretch(0,1);

    // Layout principal de l'onglet d'administration

    layoutEditeur = new QHBoxLayout();
    layoutEditeur->addLayout(layoutVuesTables);
    layoutEditeur->addLayout(layoutBoutonsAdministration);
    layoutEditeur->setStretch(0,1);

    layoutAdministration = new QVBoxLayout();
    layoutAdministration->addLayout(layoutEditeur);
    layoutAdministration->addLayout(layoutServeurs);

    fAdministration = new QFrame();
    fAdministration->setLayout(layoutAdministration);

    // Page 3 : Historique des passages

    vueJournal = new QTableView();

    // Ajout des page aux onglets

    barreOnglets->addTab(pageWeb, "Horaires RER");
    barreOnglets->addTab(fAdministration, "Administration");
    barreOnglets->addTab(vueJournal, "Historique des passages");

    // Afficheur Badge

    fAfficheurBadge = new QFrame();
    layoutAfficheurBadge = new QGridLayout();

    photoAdherent = new QLabel();

    labelID = new QLabel("<strong>ID</strong>");
    labelNom = new QLabel("<strong>Nom</strong>");
    labelPrenom = new QLabel("<strong>Prenom</strong>");
    labelDebutAbn = new QLabel("<strong>Début abonnement</strong>");
    labelFinAbn = new QLabel("<strong>Fin abonnement</strong>");

    affBadgeID = new QLabel();
    affBadgeNom = new QLabel();
    affBadgePrenom = new QLabel();
    affBadgeDebutAbn = new QLabel();
    affBadgeFinAbn = new QLabel();

    layoutAfficheurBadge->addWidget(labelID, 0, 1);
    layoutAfficheurBadge->addWidget(labelNom, 1, 1);
    layoutAfficheurBadge->addWidget(labelPrenom, 2, 1);
    layoutAfficheurBadge->addWidget(labelDebutAbn, 1, 3);
    layoutAfficheurBadge->addWidget(labelFinAbn, 2, 3);

    layoutAfficheurBadge->addWidget(affBadgeID, 0, 2);
    layoutAfficheurBadge->addWidget(affBadgeNom, 1, 2);
    layoutAfficheurBadge->addWidget(affBadgePrenom, 2, 2);
    layoutAfficheurBadge->addWidget(affBadgeDebutAbn, 1, 4);
    layoutAfficheurBadge->addWidget(affBadgeFinAbn, 2, 4);

    fAfficheurBadge->setLayout(layoutAfficheurBadge);

    layoutPrincipal->addWidget(barreOnglets, 0, 0);
    layoutPrincipal->addWidget(fAfficheurBadge, 1, 0);
    this->setLayout(layoutPrincipal);

    connect(bConnexion, SIGNAL(released()), this, SLOT(connexionBaseAdmin()));
    connect(bRecherche, SIGNAL(released()), this, SLOT(rechercherAdherent()));
    connect(bListeAdherents, SIGNAL(released()), this, SLOT(listeAdherents()));
    connect(bAdherentsNonAJour, SIGNAL(released()), this, SLOT(adherentsNonAJour()));
    connect(bAjouterAdherent, SIGNAL(released()), this, SLOT(ajouterAdherent()));
    connect(bCrediterAdherent, SIGNAL(released()), this, SLOT(crediterAdherent()));
    connect(bEditerAdherent, SIGNAL(released()), this, SLOT(editerAdherent()));
    connect(bSupprimerAdherent, SIGNAL(released()), this, SLOT(supprimerAdherent()));
    connect(bParametres, SIGNAL(released()), this, SLOT(affFenParametres()));
    connect(vueTableAdherents, SIGNAL(clicked(QModelIndex)), this, SLOT(activationBoutonsEdition(QModelIndex)));
    connect(bRafraichirServeur, SIGNAL(released()), this, SLOT(eteindreRaspberry()));

    // Lecture du fichier de configuration

    ipAccueil = "0.0.0.0";
    ipBaseDonnees = "192.168.30.253";
    ipRaspberry = "0.0.0.0";
    nomBaseDonnees = "projectrf";
    nomUtilisateurLectureBDD = "projectrf";
    motPasseLectureBDD = "projectrf";
    portServeur = 50885;

    lireFichierConfiguration("/home/florianb/Documents/Stage Planète Sciences - Eté 2019/PlascilabApp/configuration.json");

    // Serveur

    serveur = new Serveur(portServeur);
    connect(serveur, SIGNAL(messageServeur(QString)), this, SLOT(affMessageServeur(QString)));
    connect(serveur, SIGNAL(receptionIDCarte(QString)), this, SLOT(affAdherent(QString)));
    serveur->ouvrir();

    // Base de données SQL

    baseDonnees = new QSqlDatabase();
    *baseDonnees = QSqlDatabase::addDatabase("QMYSQL");
    baseDonnees->setHostName(ipBaseDonnees);
    baseDonnees->setUserName(nomUtilisateurLectureBDD);
    baseDonnees->setPassword(motPasseLectureBDD);
    baseDonnees->setDatabaseName(nomBaseDonnees);
    if (baseDonnees->open()) {
        affMessageSQL("Connecté sur " + baseDonnees->hostName() + " en tant que " + baseDonnees->userName());
    }
    else {
        affMessageSQL("La connexion sur " + baseDonnees->hostName() + " en tant que " + baseDonnees->userName() + " a échoué.");
    }

    // Base de données administrateur

    baseAdmin = new QSqlDatabase();
    *baseAdmin = QSqlDatabase::addDatabase("QMYSQL", "Admin");
    baseAdmin->setHostName(ipBaseDonnees);
    baseAdmin->setDatabaseName(nomBaseDonnees);
}

void FenPrincipale::affMessageServeur(const QString &message) {
    affCommunicationServeur->setText(message);
}

void FenPrincipale::affMessageSQL(const QString &message) {
    affCommunicationSQL->setText(message);
}

void FenPrincipale::affFenParametres() {
    FenParametres fenParametres(this);
    fenParametres.setIPAccueil(ipAccueil);
    fenParametres.setIPRPi(ipRaspberry);
    fenParametres.setPortTCP(portServeur);
    fenParametres.setIPBaseDonnes(ipBaseDonnees);
    fenParametres.setNomBaseDonnees(nomBaseDonnees);
    fenParametres.setUtilisateurBaseDonnees(nomUtilisateurLectureBDD);
    fenParametres.setMotPasseBaseDonnees(motPasseLectureBDD);
    fenParametres.exec();

    if(fenParametres.result() == QDialog::Rejected) {
        return;
    }
    else {
        ipAccueil = fenParametres.getIPAccueil();
        ipRaspberry = fenParametres.getIPRPi();
        portServeur = fenParametres.getPortTCP();
        ipBaseDonnees = fenParametres.getIPBaseDonnes();
        nomBaseDonnees = fenParametres.getNomBaseDonnees();
        nomUtilisateurLectureBDD = fenParametres.getUtilisateurBaseDonnees();
        motPasseLectureBDD = fenParametres.getMotPasseBaseDonnees();
        ecrireFichierConfiguration("/home/florianb/Documents/Stage Planète Sciences - Eté 2019/PlascilabApp/configuration.json");
        serveur->setPortTCP(portServeur);
        serveur->reouvrir();
    }
}

void FenPrincipale::affAdherent(const QString &idCarteStr) {
    QString idCarteHex = idToHex((idCarteStr)).toUpper();

    if(baseDonnees->isOpen()) {
        QSqlQuery requete(*baseDonnees);
        requete.prepare("SELECT id, nom, prenom, typeAbn, dateDebutAbn, dateFinAbn FROM Abonnes WHERE id = :_id");
        requete.bindValue(":_id", idCarteHex);
        requete.exec();
        requete.last();
        if(requete.isValid()) {
            affBadgeNom->setText(requete.value(1).toString());
            affBadgePrenom->setText(requete.value(2).toString());
            if(requete.value(3).toString() != "Aucun") {
                affBadgeDebutAbn->setText(requete.value(4).toDate().toString("dd/MM/yyyy"));
                affBadgeFinAbn->setText(requete.value(5).toDate().toString("dd/MM/yyyy"));
            }
            else {
                affBadgeDebutAbn->setText("<Aucun abonnement>");
                affBadgeFinAbn->setText("<Aucun Abonnement>");
            }

        }
        else {
            affBadgeNom->setText("<Badge non attribué>");
            affBadgePrenom->setText("<Badge non attribué>");
            affBadgeDebutAbn->setText("<Badge non attribué>");
            affBadgeFinAbn->setText("<Badge non attribué>");
        }

    }

    affBadgeID->setText(idCarteHex);
}

void FenPrincipale::adherentsNonAJour() {
    QSqlQuery requete(*baseAdmin);
    requete.prepare("SELECT * from Abonnes WHERE dateDebutAbn > (:_dateCourante) OR dateFinAbn < (:_dateCourante)");
    requete.bindValue(":_dateCourante", QDate::currentDate().toString("yyyy-MM-dd"));
    requete.exec();
    requete.last();

    modeleAdherents->setQuery(requete);

    if(modeleAdherents->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", modeleAdherents->lastError().text());
        return;
    }
    modeleAdherents->setHeaderData(0, Qt::Horizontal, "ID");
    modeleAdherents->setHeaderData(1, Qt::Horizontal, "Nom");
    modeleAdherents->setHeaderData(2, Qt::Horizontal, "Prenom");
    modeleAdherents->setHeaderData(3, Qt::Horizontal, "Mail");
    modeleAdherents->setHeaderData(4, Qt::Horizontal, "N° Téléphone");
    modeleAdherents->setHeaderData(5, Qt::Horizontal, "Type abn");
    modeleAdherents->setHeaderData(6, Qt::Horizontal, "Nombre abn");
    modeleAdherents->setHeaderData(7, Qt::Horizontal, "Début abn");
    modeleAdherents->setHeaderData(8, Qt::Horizontal, "Fin abn");

    vueTableAdherents->setModel(modeleAdherents);
    vueTableAdherents->show();
}

void FenPrincipale::rechercherAdherent() {
    QSqlQuery requete(*baseAdmin);
    requete.prepare("SELECT * from Abonnes WHERE id LIKE :_recherche OR nom LIKE :_recherche OR prenom LIKE :_recherche");
    requete.bindValue(":_recherche", "%" + lineRecherche->text() + "%");
    requete.exec();
    requete.last();

    modeleAdherents->setQuery(requete);

    if(modeleAdherents->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", modeleAdherents->lastError().text());
        return;
    }
    modeleAdherents->setHeaderData(0, Qt::Horizontal, "ID");
    modeleAdherents->setHeaderData(1, Qt::Horizontal, "Nom");
    modeleAdherents->setHeaderData(2, Qt::Horizontal, "Prenom");
    modeleAdherents->setHeaderData(3, Qt::Horizontal, "Mail");
    modeleAdherents->setHeaderData(4, Qt::Horizontal, "N° Téléphone");
    modeleAdherents->setHeaderData(5, Qt::Horizontal, "Type abn");
    modeleAdherents->setHeaderData(6, Qt::Horizontal, "Nombre abn");
    modeleAdherents->setHeaderData(7, Qt::Horizontal, "Début abn");
    modeleAdherents->setHeaderData(8, Qt::Horizontal, "Fin abn");

    vueTableAdherents->setModel(modeleAdherents);
    vueTableAdherents->show();
}

void FenPrincipale::listeAdherents() {
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

    vueTableAdherents->setModel(modeleAdherents);
    vueTableAdherents->show();
}

void FenPrincipale::ajouterAdherent() {

    FenAjouterAdherent fenAjouterAdherent;
    fenAjouterAdherent.exec();

    if(fenAjouterAdherent.result() == QDialog::Rejected) {
        return;
    }

    if(!baseAdmin->isOpen()) {
        QMessageBox::critical(this, "Erreur", "Erreur : l'accès à la base a été coupé.");
        return;
    }

    QSqlQuery requete(*baseAdmin);
    requete.prepare("INSERT INTO Abonnes (id, nom, prenom, mail, tel, typeAbn, nbAbn, dateDebutAbn, dateFinAbn) "
                    "VALUES (:id, :nom, :prenom, :mail, :tel, :typeAbn, :nbAbn, :dateDebutAbn, :dateFinAbn)");
    requete.bindValue(":id", fenAjouterAdherent.getID());
    requete.bindValue(":nom", fenAjouterAdherent.getNom());
    requete.bindValue(":prenom", fenAjouterAdherent.getPrenom());
    requete.bindValue(":mail", fenAjouterAdherent.getMail());
    requete.bindValue(":tel", fenAjouterAdherent.getTel());
    requete.bindValue(":typeAbn", fenAjouterAdherent.getTypeAbn());
    if(fenAjouterAdherent.getTypeAbn() != "Aucun") {
        requete.bindValue(":dateDebutAbn", fenAjouterAdherent.getDateDebutAbn().toString("yyyy-MM-dd"));
        requete.bindValue(":dateFinAbn", fenAjouterAdherent.getDateFinAbn().toString("yyyy-MM-dd"));
        if(fenAjouterAdherent.getTypeAbn() != "Autre") {
            requete.bindValue(":nbAbn", fenAjouterAdherent.getNbAbn());
        }
        else {
            requete.bindValue(":nbAbn", 1);
        }
    }
    else {
        requete.bindValue(":nbAbn", 0);
        requete.bindValue(":dateDebutAbn", QVariant::Date);
        requete.bindValue(":dateFinAbn", QVariant::Date);
    }



    if(!requete.exec()) {
        QMessageBox::critical(this, "Erreur", "L'édition de la base de données a échoué." + requete.lastError().text());
        return;
    }

    listeAdherents();
}

void FenPrincipale::editerAdherent() {
    FenEditerAdherent fenEditerAdherent(this);

    QSqlQuery requete(*baseAdmin);
    requete.prepare("SELECT id, nom, prenom, mail, tel FROM Abonnes WHERE id = :_id");
    requete.bindValue(":_id", vueTableAdherents->model()->index(vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data().toString());
    requete.exec();
    requete.last();

    fenEditerAdherent.setID(requete.value(0).toString());
    fenEditerAdherent.setNom(requete.value(1).toString());
    fenEditerAdherent.setPrenom(requete.value(2).toString());
    fenEditerAdherent.setMail(requete.value(3).toString());
    fenEditerAdherent.setTel(requete.value(4).toString());

    fenEditerAdherent.exec();

    if(fenEditerAdherent.result() == QDialog::Rejected) {
        return;
    }

    if(!baseAdmin->isOpen()) {
        QMessageBox::critical(this, "Erreur", "Erreur : l'accès à la base a été coupé.");
        return;
    }

    requete.prepare("UPDATE Abonnes SET nom = :_nom, prenom = :_prenom, mail = :_mail, tel = :_tel WHERE id = :_id");
    requete.bindValue(":_nom", fenEditerAdherent.getNom());
    requete.bindValue(":_prenom", fenEditerAdherent.getPrenom());
    requete.bindValue(":_mail", fenEditerAdherent.getMail());
    requete.bindValue(":_tel", fenEditerAdherent.getTel());
    requete.bindValue(":_id", vueTableAdherents->model()->index(vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data().toString());
    requete.exec();

    listeAdherents();
}

void FenPrincipale::crediterAdherent() {
    FenCrediterAdherent fenCrediterAdherent(this);
    fenCrediterAdherent.exec();

    if(fenCrediterAdherent.result() == QDialog::Rejected) {
        return;
    }

    if(!baseAdmin->isOpen()) {
        QMessageBox::critical(this, "Erreur", "Erreur : l'accès à la base a été coupé.");
        return;
    }

    QSqlQuery requete(*baseAdmin);
    requete.prepare("UPDATE Abonnes SET typeAbn = :_typeAbn, nbAbn = :_nbAbn, dateDebutAbn = :_dateDebutAbn, dateFinAbn = :_dateFinAbn WHERE id = :_id");
    requete.bindValue(":_typeAbn", fenCrediterAdherent.getTypeAbn());
    requete.bindValue(":_nbAbn", fenCrediterAdherent.getNbAbn());
    requete.bindValue(":_dateDebutAbn", fenCrediterAdherent.getDateDebutAbn().toString("yyyy-MM-dd"));
    requete.bindValue(":_dateFinAbn", fenCrediterAdherent.getDateFinAbn().toString("yyyy-MM-dd"));
    requete.bindValue(":_id", vueTableAdherents->model()->index(vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data().toString());

    if(!requete.exec()) {
        QMessageBox::critical(this, "Erreur", "L'édition de la base de données a échoué.");
        return;
    }

    listeAdherents();
}

void FenPrincipale::supprimerAdherent() {
    QSqlQuery requete(*baseAdmin);
    requete.prepare("SELECT id, nom, prenom FROM Abonnes WHERE id = (:_id)");
    requete.bindValue(":_id", vueTableAdherents->model()->index(vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data().toString());
    requete.exec();
    requete.last();

    int reponse = QMessageBox::question(this, "Supprimer un adhérent", "Etes-vous sûr de vouloir supprimer " +
                                        requete.value(2).toString() + " " +
                                        requete.value(1).toString() + " (ID : " +
                                        requete.value(0).toString() + ") de la base de données ?",
                                        QMessageBox::Yes | QMessageBox::No);

    if(reponse == QMessageBox::No) {
        return;
    }
    else {
        requete.prepare("DELETE FROM Abonnes WHERE id = :_id");
        requete.bindValue(":_id", vueTableAdherents->model()->index(vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data().toString());
        requete.exec();
        return;
    }

    listeAdherents();

}

bool FenPrincipale::connexionBaseAdmin() {
    if(bConnexion->text() == "Déconnexion") {
        bConnexion->setText("Connexion");
        vueTableAdherents->setModel(nullptr);
        baseAdmin->close();
        lineRecherche->setEnabled(false);
        bRecherche->setEnabled(false);
        bListeAdherents->setEnabled(false);
        bAdherentsNonAJour->setEnabled(false);
        bAjouterAdherent->setEnabled(false);
        bCrediterAdherent->setEnabled(false);
        bEditerAdherent->setEnabled(false);
        bSupprimerAdherent->setEnabled(false);
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

    delete fenConnexion;

    if(!baseAdmin->open()) {
        QMessageBox::critical(this, "Erreur", "Erreur d'authentification. Vérifiez que la base de donnée est accessible et que vos identfiants sont corrects.");
        baseAdmin->close();
        return false;
    }

    lineRecherche->setEnabled(true);
    bRecherche->setEnabled(true);
    bListeAdherents->setEnabled(true);
    bAjouterAdherent->setEnabled(true);
    bAdherentsNonAJour->setEnabled(true);
    bConnexion->setText("Déconnexion");

    listeAdherents();

    return true;
}

void FenPrincipale::eteindreRaspberry() {
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

QString FenPrincipale::idToHex(const QString &idCarteStr) {
    QStringList idCarte = idCarteStr.split(".");
    return  QString::number(idCarte.at(0).toInt(), 16) +
            QString::number(idCarte.at(1).toInt(), 16) +
            QString::number(idCarte.at(2).toInt(), 16) +
            QString::number(idCarte.at(3).toInt(), 16) +
            QString::number(idCarte.at(4).toInt(), 16);
}

void FenPrincipale::lireFichierConfiguration(QString nomFichier) {
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

void FenPrincipale::ecrireFichierConfiguration(QString nomFichier) {
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

void FenPrincipale::activationBoutonsEdition(QModelIndex const& indexModele) {

    QSqlQuery requete(*baseAdmin);
    requete.prepare("SELECT * from Beneficiaires WHERE id = :_id");
    requete.bindValue(":_id", vueTableAdherents->model()->index(vueTableAdherents->selectionModel()->selectedIndexes().at(0).row(), 0).data());
    requete.exec();
    requete.last();

    modeleBeneficiaires->setQuery(requete);

    if(modeleBeneficiaires->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", modeleBeneficiaires->lastError().text());
        return;
    }

    bEditerAdherent->setEnabled(true);
    bCrediterAdherent->setEnabled(true);
    bSupprimerAdherent->setEnabled(true);

    vueTableBeneficiaires->setModel(modeleBeneficiaires);
}

void FenPrincipale::desactivationBoutonsEdition() {
    bEditerAdherent->setEnabled(false);
    bCrediterAdherent->setEnabled(false);
    bSupprimerAdherent->setEnabled(false);
}

void FenPrincipale::changementSelectionVueTableSQL() {
    if(!vueTableAdherents->selectionModel()->selectedIndexes().isEmpty() && vueTableAdherents->selectionModel()->selectedIndexes().at(0).isValid()) {
        bCrediterAdherent->setEnabled(true);
        bEditerAdherent->setEnabled(true);
        bSupprimerAdherent->setEnabled(true);
    }
    else {
        bCrediterAdherent->setEnabled(false);
        bEditerAdherent->setEnabled(false);
        bSupprimerAdherent->setEnabled(false);
    }
}

FenPrincipale::~FenPrincipale() {
    baseDonnees->close();
    delete serveur;
    serveur = nullptr;
}

