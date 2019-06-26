#ifndef FENPARAMETRES_H
#define FENPARAMETRES_H

#include <QDialog>
#include <QStackedLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class FenParametres : public QDialog {
    Q_OBJECT

    public:
        FenParametres(QWidget *parent = nullptr);
        ~FenParametres();

    public slots:
        void connexion();

    private:
        QStackedLayout *stackingLayout;

        QFrame *fConnexion;
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

        QFrame *fParametres;
        QVBoxLayout *layoutParametres;
        QGridLayout *layoutChampsParam;
        QHBoxLayout *layoutBoutonsParam;
        QLabel *labelParametres;
        QLabel *labelIPSQL;
        QLabel *labelIPRaspberry;
        QLabel *labelIPAccueil;
        QLabel *labelPortServeur;
        QLabel *labelUtilisateurSQL;
        QLabel *labelMotPasseSQL;
        QLabel *labelNomBDD;
        QLineEdit *lineIPSQL;
        QLineEdit *lineIPRaspberry;
        QLineEdit *lineIPAccueil;
        QLineEdit *linePortServeur;
        QLineEdit *lineUtilisateurSQL;
        QLineEdit *lineMotPasseSQL;
        QLineEdit *lineNomBDD;
        QPushButton *bOK;
};


#endif // FENPARAMETRES_H
