#ifndef FENAJOUTERADHERENT_H
#define FENAJOUTERADHERENT_H

#include "fenadherent.h"

/**
 * @brief La classe FenAjouterAdherent affiche une boîte de dialogue permettant d'ajouter un adhérent
 */

class FenAjouterAdherent : public FenAdherent {
    Q_OBJECT

    public:
        FenAjouterAdherent(QWidget *parent = nullptr);
        ~FenAjouterAdherent();
};

#endif // FENAJOUTERADHERENT_H
