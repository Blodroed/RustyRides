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

private:
    Ui::CustomerDialog *ui;
};

#endif // CUSTOMERDIALOG_H
