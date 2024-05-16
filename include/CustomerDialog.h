#ifndef CUSTOMERDIALOG_H
#define CUSTOMERDIALOG_H

#include <QDialog>

namespace Ui {
    class CustomerDialog;
}

class CustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerDialog(QWidget *parent = nullptr);
    ~CustomerDialog();

    // setters for ui elements
    void setPersonNr(const QString& personNr);
    void setEmail(const QString& email);
    void setPhone(const QString& phone);
    void setAge(int age);
    void setName(const QString& name);

    // getters for ui elements
    QString getPersonNr() const;
    QString getEmail() const;
    QString getPhone() const;
    int getAge() const;
    QString getName() const;
private:
    Ui::CustomerDialog *ui;
signals:
};

#endif // CUSTOMERDIALOG_H
