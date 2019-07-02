#include <QCoreApplication>
#include <QApplication>
#include "serveur.h"
#include "fenprincipale.h"
#include "fenajouteradherent.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FenPrincipale fenetre;
    fenetre.resize(1600,900);

    fenetre.show();

    return app.exec();
}
