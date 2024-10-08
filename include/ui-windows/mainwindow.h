//
// Created by Marcus on 10.05.2024.
//

#ifndef HELLHUB_MAINWINDOW_H
#define HELLHUB_MAINWINDOW_H

#include "../CustomerManager.h"
#include "../JsonParser.h"
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
    MainWindow(JsonParser& jsonParser, std::vector<Customer>& customers, std::vector<Car>& cars, std::vector<Lease>& leases, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_NavTabs_currentChanged(int index);

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

    // Lease related buttons
    void on_NewLeaseBtn_clicked();
    void on_DelLeaseBtn_clicked();
    void on_ClsLeaseBtn_clicked();
    void on_EdtLeaseBtn_clicked();

    // Import and export buttons
    void importAction();
    void exportAction();

private:
    Ui::MainWindow *ui;
    
    // update tables
    void updateCustomerTable();
    void updateCarTable();
    void updateLeaseTable();

    // refference to the vector in main.cpp
    std::vector<Customer>& customersRef;
    std::vector<Car>& carsRef;
    std::vector<Lease>& leasesRef;

    // refference to the json parserq
    JsonParser& jsonParser;
};

#endif //HELLHUB_MAINWINDOW_H
