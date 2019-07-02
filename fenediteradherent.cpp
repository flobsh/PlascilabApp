#include "fenediteradherent.h"

/**
 * @brief Construit une boite de dialogue d'ajout d'adhérent
 * @param parent Widget parent
 */

FenEditerAdherent::FenEditerAdherent(QWidget *parent) : FenAdherent(parent) {

    this->setWindowTitle("Editer adhérent");

    // Suppression des éléments d'abonnement

    layoutFormulaire->addRow("Nom : ", lineNom);
    layoutFormulaire->addRow("Prénom : ", linePrenom);
    layoutFormulaire->addRow("Mail : ", lineMail);
    layoutFormulaire->addRow("N° Téléphone : ", lineTel);

    // Boutons

    bOK->setText("Valider");
}

FenEditerAdherent::~FenEditerAdherent() {

}
