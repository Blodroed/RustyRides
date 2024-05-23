//
// Created by Marcus on 14.05.2024.
//

#ifndef HELLHUB_AREYOUSUREDIALOG_H
#define HELLHUB_AREYOUSUREDIALOG_H

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

#endif //HELLHUB_AREYOUSUREDIALOG_H
