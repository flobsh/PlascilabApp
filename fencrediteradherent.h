#ifndef FENCREDITERADHERENT_H
#define FENCREDITERADHERENT_H

#include "fenadherent.h"

/**
 * @brief La classe FenAjouterAdherent affiche une boîte de dialogue permettant d'ajouter un adhérent
 */

class FenCrediterAdherent : public FenAdherent {
    Q_OBJECT

    public:
        FenCrediterAdherent(QWidget *parent = nullptr);
        ~FenCrediterAdherent();
};

#endif // FENCREDITERADHERENT_H
