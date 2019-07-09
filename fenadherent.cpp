#include "fenadherent.h"

FenAdherent::FenAdherent(QWidget *parent) : QDialog(parent) {

    // Formulaire d'ajout

    layoutFormulaire = new QFormLayout();

    lineID = new QLineEdit();
    lineID->setMaxLength(10);

    comboTypeAdhesion = new QComboBox();
    comboTypeAdhesion->addItem("Individuelle");
    comboTypeAdhesion->addItem("Famille");
    comboTypeAdhesion->addItem("Association");
    comboTypeAdhesion->addItem("Entreprise");

    lineNom = new QLineEdit();
    lineNom->setMaxLength(40);

    linePrenom = new QLineEdit();
    linePrenom->setMaxLength(40);

    lineDesignation = new QLineEdit();
    lineDesignation->setMaxLength(80);

    lineAdresse = new QLineEdit();
    lineAdresse->setMaxLength(240);

    lineCP = new QLineEdit();
    lineCP->setMaxLength(5);

    lineVille = new QLineEdit();
    lineVille->setMaxLength(40);

    lineMail = new QLineEdit();
    lineMail->setMaxLength(80);

    lineTel = new QLineEdit();
    lineTel->setMaxLength(40);

    spinNbAbn = new QSpinBox();
    spinNbAbn->setMinimum(1);

    dateDebutAbn = new QDateEdit();
    dateDebutAbn->setCalendarPopup(true);
    dateDebutAbn->setDisplayFormat("dd/MM/yyyy");
    dateDebutAbn->setDate(QDate::currentDate());

    dateFinAbn = new QDateEdit();
    dateFinAbn->setCalendarPopup(true);
    dateFinAbn->setDisplayFormat("dd/MM/yyyy");

    comboAbonnement = new QComboBox();
    comboAbonnement->addItem("Aucun");
    comboAbonnement->addItem("Mois");
    comboAbonnement->addItem("Année");
    comboAbonnement->addItem("Autre");

    // Boutons

    layoutBoutons = new QHBoxLayout();

    bOK = new QPushButton("OK");
    bAnnuler = new QPushButton("Annuler");

    layoutBoutons->addWidget(bOK);
    layoutBoutons->addWidget(bAnnuler);

    // Layout principal

    layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addLayout(layoutFormulaire);
    layoutPrincipal->addLayout(layoutBoutons);

    this->setLayout(layoutPrincipal);
    changementAbonnement();

    connect(comboAbonnement, SIGNAL(currentIndexChanged(int)), this, SLOT(changementAbonnement()));
    connect(spinNbAbn, SIGNAL(valueChanged(int)), this, SLOT(changementAbonnement()));
    connect(dateDebutAbn, SIGNAL(dateChanged(QDate)), this, SLOT(changementDateDebut()));
    connect(dateFinAbn, SIGNAL(dateChanged(QDate)), this, SLOT(changementDateFin()));
    connect(bAnnuler, SIGNAL(released()), this, SLOT(reject()));
    connect(bOK, SIGNAL(released()), this, SLOT(accepter()));
}

void FenAdherent::changementAbonnement() {
    if(comboAbonnement->currentIndex() == 0) {
        dateDebutAbn->setEnabled(false);
        dateFinAbn->setEnabled(false);
        spinNbAbn->setEnabled(false);
    }
    else {
        dateDebutAbn->setEnabled(true);
        dateFinAbn->setEnabled(true);

        if(comboAbonnement->currentIndex() == 1) {
            spinNbAbn->setEnabled(true);
            dateFinAbn->setDate(dateDebutAbn->date().addMonths(spinNbAbn->value()));
        }
        else if(comboAbonnement->currentIndex() == 2) {
            spinNbAbn->setEnabled(true);
            dateFinAbn->setDate(dateDebutAbn->date().addYears(spinNbAbn->value()));
        }
        else if(comboAbonnement->currentIndex() == 3) {
            spinNbAbn->setEnabled(false);
            spinNbAbn->setValue(1);
            dateDebutAbn->setDate(QDate::currentDate());
            dateFinAbn->setDate(QDate::currentDate());
        }
    }

}

void FenAdherent::changementDateDebut() {
    if(comboAbonnement->currentIndex() == 1) {
        dateFinAbn->setDate(dateDebutAbn->date().addMonths(spinNbAbn->value()));
    }
    else if(comboAbonnement->currentIndex() == 2) {
        dateFinAbn->setDate(dateDebutAbn->date().addYears(spinNbAbn->value()));
    }
}

void FenAdherent::changementDateFin() {
    if(comboAbonnement->currentIndex() == 1) {
        dateDebutAbn->setDate(dateFinAbn->date().addMonths(-spinNbAbn->value()));
    }
    else if(comboAbonnement->currentIndex() == 2) {
        dateDebutAbn->setDate(dateFinAbn->date().addYears(-spinNbAbn->value()));
    }
}

void FenAdherent::accepter() {
    accept();
}

QString FenAdherent::getID() const {
    return lineID->text().toUpper();
}

QString FenAdherent::getTypeAdhesion() const {
    return comboTypeAdhesion->currentText();
}

QString FenAdherent::getNom() const {
    return lineNom->text();
}

QString FenAdherent::getPrenom() const {
    return linePrenom->text();
}

QString FenAdherent::getDesignation() const {
    return lineDesignation->text();
}

QString FenAdherent::getAdresse() const {
    return lineAdresse->text();
}

QString FenAdherent::getCP() const {
    return lineCP->text();
}

QString FenAdherent::getVille() const {
    return lineVille->text();
}

QString FenAdherent::getMail() const {
    return lineMail->text();
}

QString FenAdherent::getTel() const {
    return lineTel->text();
}

QString FenAdherent::getAbonnement() const {
    return comboAbonnement->currentText();
}

int FenAdherent::getNbAbn() const {
    return spinNbAbn->value();
}

QDate FenAdherent::getDateDebutAbn() const {
    return dateDebutAbn->date();
}

QDate FenAdherent::getDateFinAbn() const {
    return dateFinAbn->date();
}

FenAdherent::~FenAdherent() {

}

void FenAdherent::setID(const QString &id) {
    lineID->setText(id);
}

void FenAdherent::setTypeAdhesion(const QString &typeAdhesion) {
    comboTypeAdhesion->setCurrentText(typeAdhesion);
}

void FenAdherent::setNom(const QString &nom) {
    lineNom->setText(nom);
}

void FenAdherent::setPrenom(const QString &prenom) {
    linePrenom->setText(prenom);
}

void FenAdherent::setDesignation(const QString &designation) {
    lineDesignation->setText(designation);
}

void FenAdherent::setAdresse(const QString &adresse) {
    lineAdresse->setText(adresse);
}

void FenAdherent::setCP(const QString &cp) {
    lineCP->setText(cp);
}

void FenAdherent::setVille(const QString &ville) {
    lineVille->setText(ville);
}

void FenAdherent::setMail(const QString &mail) {
    lineMail->setText(mail);
}

void FenAdherent::setTel(const QString &tel) {
    lineTel->setText(tel);
}

void FenAdherent::setAbonnement(const QString &abonnement) {
    comboAbonnement->setCurrentText(abonnement);
}

void FenAdherent::setNbAbn(const int &nbAbn) {
    spinNbAbn->setValue(nbAbn);
}

void FenAdherent::setDateDebutAbn(const QDate &dateDebut) {
    dateDebutAbn->setDate(dateDebut);
}

void FenAdherent::setDateFinAbn(const QDate &dateFin) {
    dateFinAbn->setDate(dateFin);
}
