#ifndef SERVEUR_H
#define SERVEUR_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class Serveur : public QObject {
    Q_OBJECT

    public:
        Serveur();
        ~Serveur();
        void ouvrir();

    signals:
        void messageServeur(QString const& message);
        void receptionIDCarte(QString const& idCarte);

    private slots:
        void connexion();
        void donneesRecues();
        void deconnexion();

    private:
        QTcpServer *serveur;
        QTcpSocket *client;
        quint16 tailleMessage;




};

#endif // SERVEUR_H
