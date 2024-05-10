//
// Created by Marcu on 10.05.2024.
//

#ifndef HELLHUB_MAINWINDOW_H
#define HELLHUB_MAINWINDOW_H

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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
            void on_NewCustBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // HELLHUB_MAINWINDOW_H