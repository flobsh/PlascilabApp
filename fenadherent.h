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
    QString getNom() const;
    QString getPrenom() const;
    QString getMail() const;
    QString getTel() const;
    QString getTypeAbn() const;
    int getNbAbn() const;
    QDate getDateDebutAbn() const;
    QDate getDateFinAbn() const;

    void setID(QString const& id);
    void setNom(QString const& nom);
    void setPrenom(QString const& prenom);
    void setMail(QString const& mail);
    void setTel(QString const& tel);
    void setTypeAbn(QString const& typeAbn);
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
    QLineEdit *lineNom;
    QLineEdit *linePrenom;
    QLineEdit *lineMail;
    QLineEdit *lineTel;
    QSpinBox *spinNbAbn;
    QDateEdit *dateDebutAbn;
    QDateEdit *dateFinAbn;
    QComboBox *comboTypeAbn;

    QPushButton *bOK;
};

#endif // FENADHERENT_H
