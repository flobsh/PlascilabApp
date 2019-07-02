#include "fenajouteradherent.h"

/**
 * @brief Construit une boite de dialogue d'ajout d'adhérent
 * @param parent Widget parent
 */

FenAjouterAdherent::FenAjouterAdherent(QWidget *parent) : FenAdherent(parent) {

    this->setWindowTitle("Ajouter adhérent");

    // Mise en place du layout

    layoutFormulaire->addRow("ID : ", lineID);
    layoutFormulaire->addRow("Nom : ", lineNom);
    layoutFormulaire->addRow("Prénom : ", linePrenom);
    layoutFormulaire->addRow("Mail : ", lineMail);
    layoutFormulaire->addRow("N° Téléphone : ", lineTel);
    layoutFormulaire->addRow("Type d'abonnement : ", comboTypeAbn);
    layoutFormulaire->addRow("Nombre d'abonnements : ", spinNbAbn);
    layoutFormulaire->addRow("Début abonnement : ", dateDebutAbn);
    layoutFormulaire->addRow("Fin abonnement : ", dateFinAbn);

    // Boutons

    bOK->setText("Ajouter adhérent");
}

FenAjouterAdherent::~FenAjouterAdherent() {

}
