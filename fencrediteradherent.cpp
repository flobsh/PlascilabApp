#include "fencrediteradherent.h"

/**
 * @brief Construit une boite de dialogue d'ajout d'adhérent
 * @param parent Widget parent
 */

FenCrediterAdherent::FenCrediterAdherent(QWidget *parent) : FenAdherent(parent) {

    this->setWindowTitle("Créditer adhérent");

    // Suppression des éléments d'édition d'adhérent

    layoutFormulaire->removeWidget(lineID);
    layoutFormulaire->removeWidget(lineNom);
    layoutFormulaire->removeWidget(linePrenom);
    layoutFormulaire->removeWidget(lineMail);
    layoutFormulaire->removeWidget(lineTel);

    // Boutons

    bOK->setText("Créditer");
}

FenCrediterAdherent::~FenCrediterAdherent() {

}
