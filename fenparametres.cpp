#include "fenparametres.h"
#include <QDialog>

FenParametres::FenParametres(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Plascilab - Paramètres");

    layoutParametres = new QVBoxLayout;

    gbCommunicationRPi = new QGroupBox("Communication avec le Raspberry Pi");
    gbBaseDonnees = new QGroupBox("Base de données");

    layoutCommunicationRPi = new QFormLayout();
    layoutBaseDonnees = new QFormLayout();

    lineIPAccueil = new QLineEdit();
    lineIPRPi = new QLineEdit();
    lineIPBaseDonnees = new QLineEdit();
    lineUtilisateurBaseDonnees = new QLineEdit();
    lineMotPasseBaseDonnees = new QLineEdit();
    lineNomBaseDonnees = new QLineEdit();

    spinPortTCP = new QSpinBox();
    spinPortTCP->setMaximum(64738);

    layoutCommunicationRPi->addRow("Adresse IP Accueil : ", lineIPAccueil);
    layoutCommunicationRPi->addRow("Adresse IP Raspberry Pi : ", lineIPRPi);
    layoutCommunicationRPi->addRow("Port TCP utilisé : ", spinPortTCP);

    layoutBaseDonnees->addRow("Adresse IP bae de données : ", lineIPBaseDonnees);
    layoutBaseDonnees->addRow("Nom de la base de données : ", lineNomBaseDonnees);
    layoutBaseDonnees->addRow("Utilisateur base de donnée (lecture seule) : ", lineUtilisateurBaseDonnees);
    layoutBaseDonnees->addRow("Mot de passe base de donnée (lecture seule) : ", lineMotPasseBaseDonnees);

    gbCommunicationRPi->setLayout(layoutCommunicationRPi);
    gbBaseDonnees->setLayout(layoutBaseDonnees);

    layoutParametres->addWidget(gbCommunicationRPi);
    layoutParametres->addWidget(gbBaseDonnees);

    bValider = new QPushButton("Valider");
    bAnnuler = new QPushButton("Annuler");

    layoutBoutons = new QHBoxLayout();
    layoutBoutons->addWidget(bValider);
    layoutBoutons->addWidget(bAnnuler);

    layoutParametres->addLayout(layoutBoutons);

    this->setLayout(layoutParametres);

    connect(bAnnuler, SIGNAL(released()), this, SLOT(reject()));
    connect(bValider, SIGNAL(released()), this, SLOT(accept()));
}

QString FenParametres::getIPAccueil() const {
    return lineIPAccueil->text();
}

QString FenParametres::getIPRPi() const {
    return lineIPRPi->text();
}

QString FenParametres::getIPBaseDonnes() const {
    return lineIPBaseDonnees->text();
}

QString FenParametres::getUtilisateurBaseDonnees() const {
    return lineUtilisateurBaseDonnees->text();
}

QString FenParametres::getMotPasseBaseDonnees() const {
    return lineMotPasseBaseDonnees->text();
}

QString FenParametres::getNomBaseDonnees() const {
    return lineNomBaseDonnees->text();
}

int FenParametres::getPortTCP() const {
    return spinPortTCP->value();
}

void FenParametres::setIPAccueil(const QString &ipAccueil) {
    lineIPAccueil->setText(ipAccueil);
}

void FenParametres::setIPRPi(const QString &ipRPi) {
    lineIPRPi->setText(ipRPi);
}

void FenParametres::setIPBaseDonnes(const QString &ipBaseDonnees) {
    lineIPBaseDonnees->setText(ipBaseDonnees);
}

void FenParametres::setUtilisateurBaseDonnees(const QString &utilisateurBaseDonnnees) {
    lineUtilisateurBaseDonnees->setText(utilisateurBaseDonnnees);
}

void FenParametres::setMotPasseBaseDonnees(const QString &motPasseBaseDonnees) {
    lineMotPasseBaseDonnees->setText(motPasseBaseDonnees);
}

void FenParametres::setNomBaseDonnees(const QString &nomBaseDonnees) {
    lineNomBaseDonnees->setText(nomBaseDonnees);
}

void FenParametres::setPortTCP(const int &portTCP) {
    spinPortTCP->setValue(portTCP);
}

void FenParametres::connexion() {

}

FenParametres::~FenParametres() {

}
