#ifndef CUSTOMERDIALOG_H
#define CUSTOMERDIALOG_H

#include <QWidget>
#include <QDialog>

namespace Ui {
    class Customer;
}

class CustomerDialog : public QWidget
{
    Q_OBJECT
public:
    explicit CustomerDialog(QWidget *parent = nullptr);

private:
    Ui::Customer *ui;
signals:
};

#endif // CUSTOMERDIALOG_H
