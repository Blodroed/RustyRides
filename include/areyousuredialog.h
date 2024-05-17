//
// Created by Marcus on 14.05.2024.
//

#ifndef AREYOUSUREDIALOG_H
#define AREYOUSUREDIALOG_H

#include <QDialog>

namespace Ui {
class AreYouSureDialog;
}

class AreYouSureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AreYouSureDialog(QWidget *parent = nullptr);
    ~AreYouSureDialog();

private:
    Ui::AreYouSureDialog *ui;
};

#endif // AREYOUSUREDIALOG_H
