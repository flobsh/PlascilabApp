#include "fenajouterbeneficiaire.h"

FenAjouterBeneficiaire::FenAjouterBeneficiaire(QWidget *parent) : FenAdherent(parent) {

    this->setWindowTitle("Ajouter bénéficiaire");

    // Mise en place du layout

    layoutFormulaire->addRow("Nom : ", lineNom);
    layoutFormulaire->addRow("Prénom : ", linePrenom);

    // Boutons

    bOK->setText("Ajouter bénéficiaire");

    this->setFixedSize(320, 139);

}
