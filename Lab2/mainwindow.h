/**
  mainwindow.h
  Purpose: Shows and operates with random event generator

  @author densheka
  @version 1.0
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "randomnumbergenerator.h"
#include "eventrepresenter.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * gets a random number
     *
     * @brief on_GetRandomButton_clicked
     */
    void on_GetRandomButton_clicked();
    /**
     * gets random events
     *
     * @brief on_GetModelListPushButton_clicked
     */
    void on_GetModelListPushButton_clicked();
    /**
     * adds an event to the list
     *
     * @brief on_AddEventPushButton_clicked
     */
    void on_AddEventPushButton_clicked();
    /**
     * generates random points of a set on a plane
     *
     * @brief on_GenerateRandomPointPushButton_clicked
     */
    void on_GenerateRandomPointPushButton_clicked();

private:

    Ui::MainWindow *ui;
private:

    std::vector<EventRepresenter> _vec;

};

#endif // MAINWINDOW_H
