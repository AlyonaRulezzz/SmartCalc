#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../h_calc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clean_clicked();

    void on_pushButton_dot_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_0_clicked();

    void on_pushButton_open_bracket_clicked();
    void on_pushButton_close_bracket_clicked();
    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_multiple_clicked();
    void on_pushButton_divide_clicked();
    void on_pushButton_degree_clicked();
    void on_pushButton_mod_enum_clicked();
    void on_pushButton_cosinus_clicked();
    void on_pushButton_sinus_clicked();
    void on_pushButton_tangens_clicked();
    void on_pushButton_acosinus_clicked();
    void on_pushButton_asinus_clicked();
    void on_pushButton_atangens_clicked();
    void on_pushButton_sqrt_enum_clicked();
    void on_pushButton_ln_enum_clicked();
    void on_pushButton_log_enum_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_x_clicked();

    void on_pushButton_graph_clicked();

    void on_pushButton_secret_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> x, y;
};
#endif // MAINWINDOW_H
