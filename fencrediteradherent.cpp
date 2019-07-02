#include "fencrediteradherent.h"

/**
 * @brief Construit une boite de dialogue d'ajout d'adhérent
 * @param parent Widget parent
 */

FenCrediterAdherent::FenCrediterAdherent(QWidget *parent) : FenAdherent(parent) {

    this->setWindowTitle("Créditer adhérent");

    // Mise en place du layout

    layoutFormulaire->addRow("Type d'abonnement : ", comboTypeAbn);
    layoutFormulaire->addRow("Nombre d'abonnements : ", spinNbAbn);
    layoutFormulaire->addRow("Début abonnement : ", dateDebutAbn);
    layoutFormulaire->addRow("Fin abonnement : ", dateFinAbn);

    // Boutons

    bOK->setText("Créditer");
}

FenCrediterAdherent::~FenCrediterAdherent() {

}
