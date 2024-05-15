//
// Created by Marcus on 10.05.2024.
//

#ifndef HELLHUB_MAINWINDOW_H
#define HELLHUB_MAINWINDOW_H

#include "../include/customerManager.h"
#include "../include/JsonParser.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(JsonParser& jsonParser, std::vector<Customer>& customers, QWidget *parent = nullptr);
    ~MainWindow();


// Worth noting: These autogenerate upon assigning a button to a slot in the UI designer
private slots:
    // Customer related buttons
        void on_NewCustBtn_clicked();
        void on_EdtCustBtn_clicked();
        void on_DelCustBtn_clicked();

    // TODO: Buttons for the other two tabs

private:
    Ui::MainWindow *ui;
    customerManager custManager;
    void updateCustomerTable();

    JsonParser& jsonParser;
};

#endif // HELLHUB_MAINWINDOW_H
