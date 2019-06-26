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

FenPrincipale::FenPrincipale() {
    layoutPrincipal = new QGridLayout(this);

    barreOnglets = new QTabWidget();

    // Page 1 : Horaires RER

    pageWeb = new QWebView();
    pageWeb->load(QUrl("http://monrer.fr/?s=RIS"));

    // Page 2 : Outils Administratifs

    fAdministration = new QFrame();
    layoutAdministration = new QVBoxLayout();

        // Administration de la BDD

    layoutEditeur = new QHBoxLayout();
    layoutBoutonsAdministration = new QVBoxLayout();

    vueTableSQL = new QTableView();

    bListeAdherents = new QPushButton("Liste adhérents");
    bAjouterAdherent = new QPushButton("Ajouter adhérent");
    bCrediterAdherent = new QPushButton("Créditer adhérent");
    bEditerAdherent = new QPushButton("Editer adhérent");
    bSupprimerAdherent = new QPushButton("Supprimer adhérent");
    bParametres = new QPushButton("Paramètres");

    bCrediterAdherent->setEnabled(false);
    bEditerAdherent->setEnabled(false);
    bSupprimerAdherent->setEnabled(false);

    layoutBoutonsAdministration->addWidget(bListeAdherents);
    layoutBoutonsAdministration->addWidget(bAjouterAdherent);
    layoutBoutonsAdministration->addWidget(bCrediterAdherent);
    layoutBoutonsAdministration->addWidget(bEditerAdherent);
    layoutBoutonsAdministration->addWidget(bSupprimerAdherent);
    layoutBoutonsAdministration->addWidget(bParametres);

    layoutEditeur->addWidget(vueTableSQL);
    layoutEditeur->addLayout(layoutBoutonsAdministration);

        // Affichage de l'état des serveurs

    layoutServeurs = new QGridLayout();

    labelCommunicationServeur = new QLabel("Communication RaspberryPI : ");
    labelCommunicationSQL = new QLabel("Communication base de données : ");

    affCommunicationServeur = new QLabel();
    affCommunicationSQL = new QLabel();

    bRafraichirServeur = new QPushButton("Rafraichir");
    bRafraichirSQL = new QPushButton("Rafraichir");

    affCommunicationServeur->setAlignment(Qt::AlignLeft);
    affCommunicationSQL->setAlignment(Qt::AlignLeft);

    layoutServeurs->addWidget(labelCommunicationServeur, 0, 0);
    layoutServeurs->addWidget(labelCommunicationSQL,1,0);
    layoutServeurs->addWidget(affCommunicationServeur, 0, 1);
    layoutServeurs->addWidget(affCommunicationSQL, 1, 1);
    layoutServeurs->addWidget(bRafraichirServeur, 0, 3);
    layoutServeurs->addWidget(bRafraichirSQL, 1, 3);
    layoutServeurs->setColumnStretch(2,1);

    layoutAdministration->addLayout(layoutEditeur);
    layoutAdministration->addLayout(layoutServeurs);

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

    connect(bListeAdherents, SIGNAL(released()), this, SLOT(listeAdherents()));
    connect(bAjouterAdherent, SIGNAL(released()), this, SLOT(ajouterAdherent()));
    connect(bCrediterAdherent, SIGNAL(released()), this, SLOT(affFenConnexion()));
    connect(bSupprimerAdherent, SIGNAL(released()), this, SLOT(affFenConnexion()));
    connect(bParametres, SIGNAL(released()), this, SLOT(affFenParametres()));

    connect(vueTableSQL, SIGNAL(activated(QModelIndex)), this, SLOT(activationBoutonsEdition()));

    // Serveur

    serveur = new Serveur();
    connect(serveur, SIGNAL(messageServeur(QString)), this, SLOT(affMessageServeur(QString)));
    connect(serveur, SIGNAL(receptionIDCarte(QString)), this, SLOT(affAdherent(QString)));
    serveur->ouvrir();

    // Base de données SQL

    baseDonnees = new QSqlDatabase();
    *baseDonnees = QSqlDatabase::addDatabase("QMYSQL");
    baseDonnees->setHostName("192.168.30.253");
    baseDonnees->setUserName("projectrf");
    baseDonnees->setPassword("projectrf");
    baseDonnees->setDatabaseName("projectrf");
    if (baseDonnees->open()) {
        affMessageSQL("Connecté sur " + baseDonnees->hostName() + " en tant que " + baseDonnees->userName());
    }
    else {
        affMessageSQL("La connexion sur " + baseDonnees->hostName() + " en tant que " + baseDonnees->userName() + " a échoué.");
    }

    // Base de données administrateur

    baseAdmin = new QSqlDatabase();
    *baseAdmin = QSqlDatabase::addDatabase("QMYSQL", "Admin");
    baseAdmin->setHostName("192.168.30.253");
    baseAdmin->setDatabaseName("projectrf");

    // Modele SQL

    modeleSQL = new QSqlQueryModel;
}


void FenPrincipale::affMessageServeur(const QString &message) {
    affCommunicationServeur->setText(message);
}

void FenPrincipale::affMessageSQL(const QString &message) {
    affCommunicationSQL->setText(message);
}

void FenPrincipale::affFenParametres() {
    FenParametres fenParametres(this);
    fenParametres.exec();
}

void FenPrincipale::affAdherent(const QString &idCarteStr) {
    affBadgeID->setText(idToHex((idCarteStr)).toUpper());
}

void FenPrincipale::listeAdherents() {
    if(bListeAdherents->text() == "Cacher la liste") {
        bListeAdherents->setText("Liste adhérents");
        return;
    }

    if(!connexionBaseAdmin()) {
        return;
    }

    modeleSQL->setQuery("SELECT * from Abonnes", *baseAdmin);
    if(modeleSQL->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", modeleSQL->lastError().text());
        return;
    }
    modeleSQL->setHeaderData(0, Qt::Horizontal, "ID");
    modeleSQL->setHeaderData(1, Qt::Horizontal, "Nom");
    modeleSQL->setHeaderData(2, Qt::Horizontal, "Prenom");
    modeleSQL->setHeaderData(3, Qt::Horizontal, "Mail");
    modeleSQL->setHeaderData(4, Qt::Horizontal, "N° Téléphone");
    modeleSQL->setHeaderData(5, Qt::Horizontal, "Début abn");
    modeleSQL->setHeaderData(6, Qt::Horizontal, "Fin abn");

    vueTableSQL->setModel(modeleSQL);
    vueTableSQL->show();

    baseAdmin->close();
    bListeAdherents->setText("Cacher la liste");
}

void FenPrincipale::ajouterAdherent() {
    if(!connexionBaseAdmin()) {
        return;
    }

    FenAjouterAdherent fenAjouterAdherent;
    fenAjouterAdherent.exec();

    if(fenAjouterAdherent.result() == QDialog::Rejected) {
        baseAdmin->close();
        return;
    }

    if(!baseAdmin->isOpen()) {
        QMessageBox::critical(this, "Erreur", "Erreur : l'accès à la base a été coupé.");
        baseAdmin->close();
        return;
    }

    QSqlQuery requete(*baseAdmin);
    requete.prepare("INSERT INTO Abonnes (id, nom, prenom, mail, tel, typeAbn, nbAbn, dateDebutAbn, dateFinAbn"
                    "VALUES (:id, :nom, :prenom, :mail, :tel, :typeAbn, :nbAbn, :dateDebutAbn, :dateFinAbn");
    requete.bindValue(":id", fenAjouterAdherent.getID());
    requete.bindValue(":nom", fenAjouterAdherent.getNom());
    requete.bindValue(":prenom", fenAjouterAdherent.getPrenom());
    requete.bindValue(":mail", fenAjouterAdherent.getMail());
    requete.bindValue(":tel", fenAjouterAdherent.getTel());
    requete.bindValue(":typeAbn", fenAjouterAdherent.getTypeAbn());
    requete.bindValue(":nbAbn", fenAjouterAdherent.getNbAbn());
    requete.bindValue(":dateDebutAbn", fenAjouterAdherent.getDateDebutAbn().toString("yyyyy-MM-dd"));
    requete.bindValue(":dateFinAbn", fenAjouterAdherent.getDateFinAbn().toString("yyyyy-MM-dd"));

    if(!requete.exec()) {
        QMessageBox::critical(this, "Erreur", "L'édition de la base de données a échoué.");
        baseAdmin->close();
        return;
    }

    baseAdmin->close();
    listeAdherents();
}

void FenPrincipale::editerAdherent() {
    if(!connexionBaseAdmin()) {
        return;
    }

    FenEditerAdherent fenEditerAdherent(this);

    QSqlQuery requete(*baseAdmin);
    requete.prepare("SELECT nom, prenom, mail, tel FROM Abonnes WHERE id = (_id)"
                    "VALUES (:_id)");
    requete.exec();

    QSqlRecord resultat = requete.record();
    fenEditerAdherent.setID(resultat.field("id").value().toString());
    fenEditerAdherent.setNom(resultat.field("nom").value().toString());
    fenEditerAdherent.setPrenom(resultat.field("prenom").value().toString());
    fenEditerAdherent.setMail(resultat.field("mail").value().toString());
    fenEditerAdherent.setTel(resultat.field("tel").value().toString());

    fenEditerAdherent.exec();

    if(fenEditerAdherent.result() == QDialog::Rejected) {
        baseAdmin->close();
        return;
    }

    if(!baseAdmin->isOpen()) {
        QMessageBox::critical(this, "Erreur", "Erreur : l'accès à la base a été coupé.");
        baseAdmin->close();
        return;
    }

    requete.prepare("UPDATE Abonnes SET nom = (_nom), prenom = (_prenom), mail = (_mail), tel = (_tel)"
                    "VALUES (:_nom, :_prenom, :_mail, :_tel");
    requete.bindValue(":_nom", fenEditerAdherent.getNom());
    requete.bindValue(":_prenom", fenEditerAdherent.getPrenom());
    requete.bindValue(":_mail", fenEditerAdherent.getMail());
    requete.bindValue(":_tel", fenEditerAdherent.getTel());
    requete.exec();

    listeAdherents();
}

void FenPrincipale::crediterAdherent() {
    if(!connexionBaseAdmin()) {
        return;
    }

    FenCrediterAdherent fenCrediterAdherent(this);
    fenCrediterAdherent.exec();

    if(fenCrediterAdherent.result() == QDialog::Rejected) {
        baseAdmin->close();
        return;
    }

    if(!baseAdmin->isOpen()) {
        QMessageBox::critical(this, "Erreur", "Erreur : l'accès à la base a été coupé.");
        baseAdmin->close();
        return;
    }

    QSqlQuery requete(*baseAdmin);
    requete.prepare("UPDATE Abonnes SET typeAbn = (_typeAbn), nbAbn = (_nbAbn), dateDebutAbn = (_dateDebutAbn), dateFinAbn = (_dateFinAbn)"
                    "VALUES (:typeAbn, :_nbAbn, :_dateDebutAbn, :_dateFinAbn");
    requete.bindValue(":typeAbn", fenCrediterAdherent.getTypeAbn());
    requete.bindValue(":nbAbn", fenCrediterAdherent.getNbAbn());
    requete.bindValue(":dateDebutAbn", fenCrediterAdherent.getDateDebutAbn().toString("yyyyy-MM-dd"));
    requete.bindValue(":dateFinAbn", fenCrediterAdherent.getDateFinAbn().toString("yyyyy-MM-dd"));

    if(!requete.exec()) {
        QMessageBox::critical(this, "Erreur", "L'édition de la base de données a échoué.");
        baseAdmin->close();
        return;
    }

    baseAdmin->close();
    listeAdherents();
}

void FenPrincipale::supprimerAdherent() {
    if(!connexionBaseAdmin()) {
        return;
    }

    QSqlQuery requete(*baseAdmin);
    requete.prepare("SELECT nom, prenom FROM Abonnes WHERE id = (_id)"
                    "VALUES (:_id)");
    //TODO : bind
    requete.exec();

    QSqlRecord resultat = requete.record();

    int reponse = QMessageBox::question(this, "Supprimer un adhérent", "Etes-vous sûr de vouloir supprimer " +
                                        resultat.field("prenom").value().toString() + " " +
                                        resultat.field("nom").value().toString() + " (ID : " +
                                        resultat.field("id").value().toString() + ") de la base de données ?",
                                        QMessageBox::Yes | QMessageBox::No);

    if(reponse == QMessageBox::No) {
        baseAdmin->close();
        return;
    }
    else {
        requete.prepare("DELETE FROM Abonnes WHERE id =(_id)"
                        "VALUES (:_id)");
        //TODO bind
        requete.exec();
        baseAdmin->close();
        return;
    }

}

bool FenPrincipale::connexionBaseAdmin() {
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

    return true;

}

QString FenPrincipale::idToHex(const QString &idCarteStr) {
    QStringList idCarte = idCarteStr.split(".");
    return  QString::number(idCarte.at(0).toInt(), 16) +
            QString::number(idCarte.at(1).toInt(), 16) +
            QString::number(idCarte.at(2).toInt(), 16) +
            QString::number(idCarte.at(3).toInt(), 16) +
            QString::number(idCarte.at(4).toInt(), 16);
}

void FenPrincipale::activationBoutonsEdition() {
    bEditerAdherent->setEnabled(true);
    bCrediterAdherent->setEnabled(true);
    bSupprimerAdherent->setEnabled(true);
}

void FenPrincipale::desactivationBoutonsEdition() {
    bEditerAdherent->setEnabled(false);
    bCrediterAdherent->setEnabled(false);
    bSupprimerAdherent->setEnabled(false);
}

FenPrincipale::~FenPrincipale() {
    delete serveur;
    serveur = nullptr;
}

