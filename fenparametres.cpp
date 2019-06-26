#include "fenparametres.h"
#include <QDialog>

FenParametres::FenParametres(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Plascilab - Paramètres");

    stackingLayout = new QStackedLayout();

    // Page Connexion :

    fConnexion = new QFrame();

    layoutConnexion = new QVBoxLayout();
    layoutBoutons = new QHBoxLayout();
    layoutChamps = new QGridLayout();

    labelConnexion = new QLabel("<strong>Accès aux paramètres :</strong>");
    labelUtilisateur = new QLabel("Utilisateur : ");
    labelMotPasse = new QLabel("Mot de passe : ");

    lineUtilisateur = new QLineEdit();
    lineMotPasse = new QLineEdit();

    lineMotPasse->setEchoMode(QLineEdit::Password);

    bConnexion = new QPushButton("Connexion");
    bAnnuler = new QPushButton("Annuler");

    layoutChamps->addWidget(labelUtilisateur, 0, 0, 1, 1, Qt::AlignLeft);
    layoutChamps->addWidget(labelMotPasse, 1, 0, 1, 1, Qt::AlignLeft);
    layoutChamps->addWidget(lineUtilisateur, 0, 1);
    layoutChamps->addWidget(lineMotPasse, 1, 1);

    layoutBoutons->addWidget(bConnexion);
    layoutBoutons->addWidget(bAnnuler);

    layoutConnexion->addStretch();
    layoutConnexion->addWidget(labelConnexion, 0, Qt::AlignLeft);
    layoutConnexion->addLayout(layoutChamps);
    layoutConnexion->addLayout(layoutBoutons);
    layoutConnexion->addStretch();

    fConnexion->setLayout(layoutConnexion);

    // Page Paramètres

    fParametres = new QFrame();

    layoutParametres = new QVBoxLayout();
    layoutChampsParam = new QGridLayout();
    layoutBoutonsParam = new QHBoxLayout();

    labelParametres = new QLabel("<strong>Paramètres</strong>");
    labelIPSQL = new QLabel("Adresse IP serveur SQL : ");
    labelIPAccueil = new QLabel("Adresse IP PC Accueil : ");
    labelIPRaspberry = new QLabel("Adresse IP Raspberry : ");
    labelPortServeur = new QLabel("Port de communication Raspberry : ");
    labelUtilisateurSQL = new QLabel("Utilisateur base de données : ");
    labelMotPasseSQL = new QLabel("Mot de passe base de données : ");
    labelNomBDD = new QLabel("Base de données : ");

    lineIPSQL = new QLineEdit();
    lineIPAccueil = new QLineEdit();
    lineIPRaspberry = new QLineEdit();
    linePortServeur = new QLineEdit();
    lineUtilisateurSQL = new QLineEdit();
    lineMotPasseSQL = new QLineEdit();
    lineNomBDD = new QLineEdit();

    lineIPSQL->setInputMask("000.000.000.000;0");
    lineIPAccueil->setInputMask("000.000.000.000;0");
    lineIPRaspberry->setInputMask("000.000.000.000;0");
    lineMotPasseSQL->setEchoMode(QLineEdit::Password);

    layoutChampsParam->addWidget(labelIPAccueil, 0, 0);
    layoutChampsParam->addWidget(labelIPRaspberry, 1, 0);
    layoutChampsParam->addWidget(labelIPSQL, 2, 0);
    layoutChampsParam->addWidget(labelNomBDD, 3, 0);
    layoutChampsParam->addWidget(labelUtilisateurSQL, 4, 0);
    layoutChampsParam->addWidget(labelMotPasseSQL, 5, 0);

    layoutChampsParam->addWidget(lineIPAccueil, 0, 1);
    layoutChampsParam->addWidget(lineIPRaspberry, 1, 1);
    layoutChampsParam->addWidget(lineIPSQL, 2, 1);
    layoutChampsParam->addWidget(lineNomBDD, 3, 1);
    layoutChampsParam->addWidget(lineUtilisateurSQL, 4, 1);
    layoutChampsParam->addWidget(lineMotPasseSQL, 5, 1);

    bOK = new QPushButton("OK");

    layoutBoutonsParam = new QHBoxLayout();
    layoutBoutonsParam->addWidget(bOK);

    layoutParametres = new QVBoxLayout();
    layoutParametres->addWidget(labelParametres);
    layoutParametres->addLayout(layoutChampsParam);
    layoutParametres->addLayout(layoutBoutonsParam);

    fParametres->setLayout(layoutParametres);

    stackingLayout->addWidget(fConnexion);
    stackingLayout->addWidget(fParametres);
    stackingLayout->setCurrentIndex(0);

    this->setLayout(stackingLayout);

    connect(bAnnuler, SIGNAL(released()), this, SLOT(reject()));
    connect(bConnexion, SIGNAL(released()), this, SLOT(connexion()));
}

void FenParametres::connexion() {
    if(lineUtilisateur->text() != "root" || lineMotPasse->text() != "root") {
        labelConnexion->setText("Nom d'utilisateur ou mot de passe incorrect");
    }
    else {
        stackingLayout->setCurrentIndex(1);
        layoutBoutonsParam->addWidget(bAnnuler);
    }
}

FenParametres::~FenParametres() {

}
