#ifndef FENADHERENT_H
#define FENADHERENT_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QDateEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>

class FenAdherent : public QDialog {
    Q_OBJECT

public:
    FenAdherent(QWidget *parent = nullptr);
    ~FenAdherent();

    QString getID() const;
    QString getTypeAdhesion() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getDesignation() const;
    QString getAdresse() const;
    QString getCP() const;
    QString getVille() const;
    QString getMail() const;
    QString getTel() const;
    QString getAbonnement() const;
    int getNbAbn() const;
    QDate getDateDebutAbn() const;
    QDate getDateFinAbn() const;

    void setID(QString const& id);
    void setTypeAdhesion(QString const& typeAdhesion);
    void setNom(QString const& nom);
    void setPrenom(QString const& prenom);
    void setDesignation(QString const& designation);
    void setAdresse(QString const& adresse);
    void setCP(QString const& cp);
    void setVille(QString const& ville);
    void setMail(QString const& mail);
    void setTel(QString const& tel);
    void setAbonnement(QString const& abonnement);
    void setNbAbn(int const& nbAbn);
    void setDateDebutAbn(QDate const& dateDebut);
    void setDateFinAbn(QDate const& dateFin);

private slots:
    void changementAbonnement();
    void changementDateDebut();
    void changementDateFin();

private:
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutBoutons;


    QPushButton *bAnnuler;

protected:
    QFormLayout *layoutFormulaire;
    QLineEdit *lineID;
    QComboBox *comboTypeAdhesion;
    QLineEdit *lineNom;
    QLineEdit *linePrenom;
    QLineEdit *lineDesignation;
    QLineEdit *lineAdresse;
    QLineEdit *lineCP;
    QLineEdit *lineVille;
    QLineEdit *lineMail;
    QLineEdit *lineTel;
    QComboBox *comboAbonnement;
    QSpinBox *spinNbAbn;
    QDateEdit *dateDebutAbn;
    QDateEdit *dateFinAbn;

    QPushButton *bOK;
};

#endif // FENADHERENT_H
