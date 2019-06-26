#ifndef FENCONNEXION_H
#define FENCONNEXION_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


class FenConnexion : public QDialog {
    Q_OBJECT

    public:
        FenConnexion(QWidget *parent = nullptr);
        QString getUtilisateur() const;
        QString getMotPasse() const;
        ~FenConnexion();

    private:
        QVBoxLayout *layoutConnexion;
        QGridLayout *layoutChamps;
        QHBoxLayout *layoutBoutons;

        QLabel *labelConnexion;
        QLabel *labelUtilisateur;
        QLabel *labelMotPasse;

        QLineEdit *lineUtilisateur;
        QLineEdit *lineMotPasse;

        QPushButton *bConnexion;
        QPushButton *bAnnuler;
};

#endif // FENCONNEXION_H
