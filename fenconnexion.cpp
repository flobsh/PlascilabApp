#include "fenconnexion.h"

FenConnexion::FenConnexion(QWidget *parent) : QDialog(parent) {

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

    this->setWindowTitle("Connexion à la base de données");
    this->setFixedSize(300, 139);
    this->setLayout(layoutConnexion);

    connect(bAnnuler, SIGNAL(released()), this, SLOT(reject()));
    connect(bConnexion, SIGNAL(released()), this, SLOT(accept()));

}

/**
 * @brief Retourne le nom d'utilisateur inscrit dans la boîte de dialogue
 */

QString FenConnexion::getUtilisateur() const {
    return lineUtilisateur->text();
}

/**
 * @brief Retourne le mot de passe inscrit dans la boîte de dialogue
 */

QString FenConnexion::getMotPasse() const {
    return lineMotPasse->text();
}

FenConnexion::~FenConnexion() {

}
