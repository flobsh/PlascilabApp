#ifndef FENAJOUTERADHERENT_H
#define FENAJOUTERADHERENT_H

#include "fenadherent.h"
#include "serveur.h"

/**
 * @brief La classe FenAjouterAdherent affiche une boîte de dialogue permettant d'ajouter un adhérent
 */

class FenAjouterAdherent : public FenAdherent {
    Q_OBJECT

public:
    FenAjouterAdherent(QWidget *parent = nullptr);
    FenAjouterAdherent(QWidget *parent, Serveur *serveur);
    ~FenAjouterAdherent();

public slots:
    void badgeID(QString const& donnees);

private:
    Serveur *serveur;

};

#endif // FENAJOUTERADHERENT_H
