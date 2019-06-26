#include <iostream>
#include <QDataStream>
#include "serveur.h"

Serveur::Serveur() {
    serveur = new QTcpServer();

    client = nullptr;
    tailleMessage = 19;
}

void Serveur::ouvrir() {
    if(!serveur->listen(QHostAddress::Any, 50885)) {
        emit messageServeur("Le serveur n'a pas pu être démarré. Raison : " + serveur->errorString());
    }
    else {
        emit messageServeur("Le serveur a démarré sur le port " + QString::number(serveur->serverPort()));
    }

    connect(serveur, SIGNAL(newConnection()), this, SLOT(connexion()));
}

void Serveur::connexion() {
    emit messageServeur("Un nouveau client vient de se connecter");

    client = serveur->nextPendingConnection();

    connect(client, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(client, SIGNAL(disconnected()), this, SLOT(deconnexion()));
}

void Serveur::donneesRecues() {
    if(client->bytesAvailable() < tailleMessage)
        return;

    QByteArray donnees = client->readAll();
    emit messageServeur("ID Client : " + donnees);
    emit receptionIDCarte(QString(donnees));
}

void Serveur::deconnexion() {
    client->deleteLater();
}

Serveur::~Serveur() {
    delete serveur;
    serveur = nullptr;
    delete client;
    client = nullptr;
}
