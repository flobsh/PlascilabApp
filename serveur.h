#ifndef SERVEUR_H
#define SERVEUR_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class Serveur : public QObject {
    Q_OBJECT

    public:
        Serveur(int portTCP);
        ~Serveur();
        void ouvrir();
        void reouvrir();
        void setPortTCP(int portTCP);

    signals:
        void messageServeur(QString const& message);
        void receptionIDCarte(QString const& idCarte);

    private slots:
        void connexion();
        void donneesRecues();
        void deconnexion();

    private:
        int portTCP;
        QTcpServer *serveur;
        QTcpSocket *client;
        quint16 tailleMessage;




};

#endif // SERVEUR_H
