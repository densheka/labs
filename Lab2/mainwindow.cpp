/*!
  mainwindow.cpp
  Purpose: Shows and operates with random event generator

  @author densheka
  @version 1.0
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "randomnumbergenerator.h"
#include <QDebug>
#include <QValidator>
#include <QMessageBox>
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->MinLineEdit->setValidator(new QIntValidator(ui->MinLineEdit));
    ui->MaxLineEdit->setValidator(new QIntValidator(ui->MaxLineEdit));
    ui->CountOfTimesLineEdit->setValidator(new QIntValidator(ui->MaxLineEdit));
    ui->PointsNumberLineEdit->setValidator(new QIntValidator(ui->MaxLineEdit));
    ui->ChanceLineEdit->setValidator(new QIntValidator(0, 100, ui->MaxLineEdit));

    ui->MinXLineEdit->setValidator(new QIntValidator(ui->MinXLineEdit));
    ui->MinYLineEdit->setValidator(new QIntValidator(ui->MinYLineEdit));
    ui->MaxXLineEdit->setValidator(new QIntValidator(ui->MaxXLineEdit));
    ui->MaxYLineEdit->setValidator(new QIntValidator(ui->MaxYLineEdit)); //installation of validation on lineEdits, so that the user does not enter incorrect information
    this->setFixedSize(size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

//gets a random number
void MainWindow::on_GetRandomButton_clicked()
{
    ui->ResultLineEdit->clear();
    bool left, right;
    auto l = ui->MinLineEdit->text().toInt(&left);
    auto r = ui->MaxLineEdit->text().toInt(&right);
    if(l < r)
    {
        RandomNumberGenerator g;
        ui->ResultLineEdit->setText(QString::number(g.GetRandomInt(l, r)));
    }
}

//gets random events
void MainWindow::on_GetModelListPushButton_clicked()
{
    if(ui->CountOfTimesLineEdit->text() == "" ||
            ui->CountOfTimesLineEdit->text() == "0" ||
            _vec.size() == 0)
        return;

    QString text;
    RandomNumberGenerator g;
    for(int i = 0; i < ui->CountOfTimesLineEdit->text().toInt(); ++i)
    {
        text += QString("Iteration : %1\n").arg(i + 1);
        for(unsigned int y = 0; y < _vec.size(); ++y)
        {
            if(_vec[y].chance() >= g.GetRandomInt(0, 100)) //check: event will fall or not
            {
                text += _vec[y].text() + "\n";

            }
        }
    }

    QMessageBox *msg = new QMessageBox();
    msg->setWindowTitle("Events list");
    msg->setText(text);

    msg->exec();

    delete msg;

}

//adds an event to the list
void MainWindow::on_AddEventPushButton_clicked()
{
    EventRepresenter event(ui->ChanceLineEdit->text().toInt(), ui->EventBodyLineEdit->text());
    _vec.push_back(event); //add event to list
    ui->EventsComboBox->addItem(event.text(), QVariant::fromValue(event));
}

//generates random points of a set on a plane
void MainWindow::on_GenerateRandomPointPushButton_clicked()
{
    if(ui->PointsNumberLineEdit->text() == "" ||
            ui->PointsNumberLineEdit->text() == "0")
        return;

    QString text;
    RandomNumberGenerator g;
    for(int i = 0; i < ui->PointsNumberLineEdit->text().toInt(); ++i)
    {
        text+= QString::number(i + 1) + ": ";
        text+= QString("x: %1   y: %2 \n"). //format string to record the result
                arg(QString::number(g.GetRandomInt(ui->MinXLineEdit->text().toInt(),
                                                   ui->MaxXLineEdit->text().toInt())),
                    QString::number(g.GetRandomInt(ui->MinYLineEdit->text().toInt(),
                                                   ui->MaxYLineEdit->text().toInt())));
    }

    QMessageBox *msg = new QMessageBox();
    msg->setWindowTitle("Generated points");
    msg->setText(text);

    msg->exec();
}
