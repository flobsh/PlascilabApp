#ifndef FENPARAMETRES_H
#define FENPARAMETRES_H

#include <QDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

class FenParametres : public QDialog {
    Q_OBJECT

public:
    FenParametres(QWidget *parent = nullptr);

    QString getIPAccueil() const;
    QString getIPRPi() const;
    QString getIPBaseDonnes() const;
    QString getUtilisateurBaseDonnees() const;
    QString getMotPasseBaseDonnees() const;
    QString getNomBaseDonnees() const;
    int getPortTCP() const;

    void setIPAccueil(QString const& ipAccueil);
    void setIPRPi(QString const& ipRPi);
    void setIPBaseDonnes(QString const& ipBaseDonnees);
    void setUtilisateurBaseDonnees(QString const& utilisateurBaseDonnees);
    void setMotPasseBaseDonnees(QString const& motPasseBaseDonnee);
    void setNomBaseDonnees(QString const& nomBaseDonnees);
    void setPortTCP(int const& portTCP);

    ~FenParametres();

public slots:
    void connexion();

private:
    QVBoxLayout *layoutParametres;
    QHBoxLayout *layoutBoutons;

    QFormLayout *layoutBaseDonnees;
    QFormLayout *layoutCommunicationRPi;

    QGroupBox *gbBaseDonnees;
    QGroupBox *gbCommunicationRPi;

    QLineEdit *lineIPAccueil;
    QLineEdit *lineIPRPi;
    QLineEdit *lineIPBaseDonnees;
    QLineEdit *lineUtilisateurBaseDonnees;
    QLineEdit *lineMotPasseBaseDonnees;
    QLineEdit *lineNomBaseDonnees;

    QSpinBox *spinPortTCP;

    QPushButton *bValider;
    QPushButton *bAnnuler;

};


#endif // FENPARAMETRES_H
