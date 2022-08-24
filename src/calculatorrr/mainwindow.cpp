#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../h_calc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clean_clicked()  /* clean */
{
    ui->label->clear();
}

void MainWindow::on_pushButton_dot_clicked()  /* numbers and dot */
{
    ui->label->setText(ui->label->text() + '.');
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->label->setText(ui->label->text() + '1');
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->setText(ui->label->text() + '2');
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->label->setText(ui->label->text() + '3');
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->label->setText(ui->label->text() + '4');
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->label->setText(ui->label->text() + '5');
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->label->setText(ui->label->text() + '6');
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->label->setText(ui->label->text() + '7');
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->label->setText(ui->label->text() + '8');
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->label->setText(ui->label->text() + '9');
}

void MainWindow::on_pushButton_0_clicked()
{
    ui->label->setText(ui->label->text() + '0');
}

void MainWindow::on_pushButton_open_bracket_clicked()  /* functions, brackets and operations */
{
    ui->label->setText(ui->label->text() + '(');
}

void MainWindow::on_pushButton_close_bracket_clicked()
{
    ui->label->setText(ui->label->text() + ')');
}

void MainWindow::on_pushButton_plus_clicked()
{
    ui->label->setText(ui->label->text() + '+');
}

void MainWindow::on_pushButton_minus_clicked()
{
    ui->label->setText(ui->label->text() + '-');
}

void MainWindow::on_pushButton_multiple_clicked()
{
    ui->label->setText(ui->label->text() + '*');
}

void MainWindow::on_pushButton_divide_clicked()
{
    ui->label->setText(ui->label->text() + '/');
}

void MainWindow::on_pushButton_degree_clicked()
{
    ui->label->setText(ui->label->text() + '^');
}

void MainWindow::on_pushButton_mod_enum_clicked()
{
    ui->label->setText(ui->label->text() + "mod");
}

void MainWindow::on_pushButton_cosinus_clicked()
{
    ui->label->setText(ui->label->text() + "cos");
}

void MainWindow::on_pushButton_sinus_clicked()
{
    ui->label->setText(ui->label->text() + "sin");
}

void MainWindow::on_pushButton_tangens_clicked()
{
    ui->label->setText(ui->label->text() + "tan");
}

void MainWindow::on_pushButton_acosinus_clicked()
{
    ui->label->setText(ui->label->text() + "acos");
}

void MainWindow::on_pushButton_asinus_clicked()
{
    ui->label->setText(ui->label->text() + "asin");
}

void MainWindow::on_pushButton_atangens_clicked()
{
    ui->label->setText(ui->label->text() + "atan");
}

void MainWindow::on_pushButton_sqrt_enum_clicked()
{
    ui->label->setText(ui->label->text() + "sqrt");
}

void MainWindow::on_pushButton_ln_enum_clicked()
{
    ui->label->setText(ui->label->text() + "ln");
}

void MainWindow::on_pushButton_log_enum_clicked()
{
    ui->label->setText(ui->label->text() + "log");
}


void MainWindow::on_pushButton_equal_clicked()  /* = */
{
    QString str1 = ui->label->text();
    QByteArray ba = str1.toLocal8Bit();
    char *func = ba.data();

//    check_error(func);

    if (!check_error(func))
    {
        double res = calc(reverse_input(push_to_ready(reverse_input(parser(func, 0)))));

        ui->label->setText(QString::number(res, 'g', 8));
    } else {
        ui->label->clear();
        ui->label->setText(ui->label->text() + "Invalid value");
    }
}

void MainWindow::on_pushButton_x_clicked()  /* x */
{
    ui->label->setText(ui->label->text() + "x");
}



void MainWindow::on_pushButton_graph_clicked()  /* graph */
{
   ui->graphicsView->clearGraphs();
   ui->graphicsView->xAxis->setRange(-20, 20);
   ui->graphicsView->yAxis->setRange(-20, 20);
//   ui->graphicsView->addGraph();


//   double x = -50;
   double y2 = 0;
   double delta = 0.1;

//   struct list parsed_list;
//   struct list rpn_list;
//   QString str1 = ui->lineEdit->text();
//   QByteArray ba = str1.toLocal8Bit();
//   char *func = ba.data();

//   parsed_list = parse_source(func);
//   int err = check_parse_errors(&parsed_list);
//   if (err) {
//       ui->result_label->setText("Unknown lexema");
//   } else {
//       rpn_list = rpn(&parsed_list);


       QString str1 = ui->label->text();
       QByteArray ba = str1.toLocal8Bit();
       char *func = ba.data();

       for (double i = -20; i <= 20; (i += delta)) {
//           y = executor(&rpn_list, x);
           x.push_back(i);
           y2 = calc(reverse_input(push_to_ready(reverse_input(parser(func, i)))));
           y.push_back(y2);
//           x += delta;
       }
       ui->graphicsView->addGraph();
       ui->graphicsView->graph(0)->addData(x, y);
       ui->graphicsView->replot();
       x.clear();
       y.clear();
//   }
}

void MainWindow::on_pushButton_secret_clicked()  /* ))) */
{
    ui->label->clear();
    ui->label->setText(ui->label->text() + "Прекрасно выглядишь=)");
}

