//
// Created by Marcus on 10.05.2024.
//

#ifndef HELLHUB_MAINWINDOW_H
#define HELLHUB_MAINWINDOW_H

#include "../include/customerManager.h"
#include "../include/JsonParser.h"
#include <QMainWindow>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(JsonParser& jsonParser, std::vector<Customer>& customers, std::vector<Car>& cars, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
            void on_tabWidget_currentChanged(int index);

    // Worth noting: These autogenerate upon assigning a button to a slot in the UI designer
private slots:
    // Customer related buttons
    void on_NewCustBtn_clicked();
    void on_EdtCustBtn_clicked();
    void on_DelCustBtn_clicked();

    // Car related buttons
    void on_NewCarBtn_clicked();
    void on_EdtCarBtn_clicked();
    void on_DelCarBtn_clicked();

    // TODO: Buttons for the other two tabs

private:
    Ui::MainWindow *ui;
    void updateCustomerTable();
    void updateCarTable();

    std::vector<Customer>& customersRef;
    std::vector<Car>& carsRef;

    JsonParser& jsonParser;
};

#endif //HELLHUB_MAINWINDOW_H
