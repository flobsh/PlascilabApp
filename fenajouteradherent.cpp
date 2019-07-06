#include "fenajouteradherent.h"
#include "fenplascilabapp.h"

/**
 * @brief Construit une boite de dialogue d'ajout d'adhérent
 * @param parent Widget parent
 */

FenAjouterAdherent::FenAjouterAdherent(QWidget *parent) : FenAdherent(parent) {

    this->setWindowTitle("Ajouter adhérent");

    // Mise en place du layout

    layoutFormulaire->addRow("ID carte : ", lineID);
    layoutFormulaire->addRow("Type d'adhésion", comboTypeAdhesion);
    layoutFormulaire->addRow("Nom : ", lineNom);
    layoutFormulaire->addRow("Prénom : ", linePrenom);
    layoutFormulaire->addRow("Désigntion : ", lineDesignation);
    layoutFormulaire->addRow("Adresse : ", lineAdresse);
    layoutFormulaire->addRow("CP", lineCP);
    layoutFormulaire->addRow("Ville", lineVille);
    layoutFormulaire->addRow("Mail : ", lineMail);
    layoutFormulaire->addRow("N° Téléphone : ", lineTel);
    layoutFormulaire->addRow("Type d'abonnement : ", comboAbonnement);
    layoutFormulaire->addRow("Nombre d'abonnements : ", spinNbAbn);
    layoutFormulaire->addRow("Début abonnement : ", dateDebutAbn);
    layoutFormulaire->addRow("Fin abonnement : ", dateFinAbn);

    // Boutons

    bOK->setText("Ajouter adhérent");
}

FenAjouterAdherent::FenAjouterAdherent(QWidget *parent, Serveur *serveur) : FenAjouterAdherent(parent) {

    this->serveur = serveur;

    connect(serveur, SIGNAL(receptionIDCarte(QString)), this, SLOT(badgeID(QString)));

}

void FenAjouterAdherent::badgeID(const QString &donnees) {
    lineID->setText(FenPlascilabApp::idToHex(donnees));
}

FenAjouterAdherent::~FenAjouterAdherent() {
    delete serveur;
}
