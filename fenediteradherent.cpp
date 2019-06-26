#include "fenediteradherent.h"

/**
 * @brief Construit une boite de dialogue d'ajout d'adhérent
 * @param parent Widget parent
 */

FenEditerAdherent::FenEditerAdherent(QWidget *parent) : FenAdherent(parent) {

    this->setWindowTitle("Editer adhérent");

    // Suppression des éléments d'abonnement

    layoutFormulaire->removeWidget(comboTypeAbn);
    layoutFormulaire->removeWidget(spinNbAbn);
    layoutFormulaire->removeWidget(dateDebutAbn);
    layoutFormulaire->removeWidget(dateFinAbn);

    // Boutons

    bOK->setText("Valider");
}

FenEditerAdherent::~FenEditerAdherent() {

}
