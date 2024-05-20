#ifndef LEASEDIALOG_H
#define LEASEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class LeaseDialog;
}
QT_END_NAMESPACE

class LeaseDialog : public QDialog
{
    Q_OBJECT

public:
    LeaseDialog(QWidget *parent = nullptr);
    ~LeaseDialog();

private:
    Ui::LeaseDialog *ui;
};
#endif // LEASEDIALOG_H
