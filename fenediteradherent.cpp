#include "fenediteradherent.h"

/**
 * @brief Construit une boite de dialogue d'ajout d'adhérent
 * @param parent Widget parent
 */

FenEditerAdherent::FenEditerAdherent(QWidget *parent) : FenAdherent(parent) {

    this->setWindowTitle("Editer adhérent");

    // Suppression des éléments d'abonnement

    layoutFormulaire->addRow("ID carte : ", lineID);
    layoutFormulaire->addRow("Type d'adhésion", comboTypeAdhesion);
    layoutFormulaire->addRow("Nom : ", lineNom);
    layoutFormulaire->addRow("Prénom : ", linePrenom);
    layoutFormulaire->addRow("Désigntion : ", lineDesignation);
    layoutFormulaire->addRow("Adresse : ", lineAdresse);
    layoutFormulaire->addRow("CP : ", lineCP);
    layoutFormulaire->addRow("Ville : ", lineVille);
    layoutFormulaire->addRow("Mail : ", lineMail);
    layoutFormulaire->addRow("N° Téléphone : ", lineTel);

    // Boutons

    bOK->setText("Valider");
}

FenEditerAdherent::~FenEditerAdherent() {

}
