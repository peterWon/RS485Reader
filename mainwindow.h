#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void doRtuQuery();
    void doTcpQuery();

private:
    Ui::MainWindow *ui;
    QPushButton *pbRtu;
    QPushButton *pbTcp;
};

#endif // MAINWINDOW_H
