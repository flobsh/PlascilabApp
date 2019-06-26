#include "fenajouteradherent.h"

/**
 * @brief Construit une boite de dialogue d'ajout d'adhérent
 * @param parent Widget parent
 */

FenAjouterAdherent::FenAjouterAdherent(QWidget *parent) : FenAdherent(parent) {

    this->setWindowTitle("Ajouter adhérent");

    // Boutons

    bOK->setText("Ajouter adhérent");
}

FenAjouterAdherent::~FenAjouterAdherent() {

}
