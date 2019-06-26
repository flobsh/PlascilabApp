#ifndef FENEDITERADHERENT_H
#define FENEDITERADHERENT_H

#include "fenadherent.h"

/**
 * @brief La classe FenAjouterAdherent affiche une boîte de dialogue permettant d'ajouter un adhérent
 */

class FenEditerAdherent : public FenAdherent {
    Q_OBJECT

    public:
        FenEditerAdherent(QWidget *parent = nullptr);
        ~FenEditerAdherent();
};

#endif // FENEDITERADHERENT_H
