#ifndef EDITLEASEDIALOG_H
#define EDITLEASEDIALOG_H

#include "LeaseManager.h"
#include "JsonParser.h"
#include "CarManager.h"
#include "CustomerManager.h"

#include <QDialog>
#include <vector>

namespace Ui {
class EditLeaseDialog;
}

class EditLeaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditLeaseDialog(const Car& carRef, const Customer& customerRef, Lease& selectedLease, QWidget *parent = nullptr);
    ~EditLeaseDialog();

private:
    void updateCustomerInfoTable();
    void updateCarInfoTable();

    Ui::EditLeaseDialog *ui;
    Lease& selectedLease;
    const Car& carRef;
    const Customer& customerRef;
};

#endif // EDITLEASEDIALOG_H
