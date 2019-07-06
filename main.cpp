#include <QCoreApplication>
#include <QApplication>
#include "serveur.h"
#include "fenajouteradherent.h"
#include "fenplascilabapp.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FenPlascilabApp fenetre;
    fenetre.resize(1600,900);

    fenetre.show();

    return app.exec();
}
