/**
  mainwindow.h
  Purpose: sets the main window with elements for the game and its description
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>

#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "checkersgame.h"
#include "checkersstate.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    /**
     * @brief startNewGame
     */
	void startNewGame();
    /**
     * @brief endGame
     */
	void endGame();
    /**
     * @brief settings
     */
	void settings();
    /**
     * @brief about
     */
	void about();
    /**
     * @brief gameEnded
     * @param status
     */
	void gameEnded(uint8 status);
private:
	CheckersGame * game;
	SettingsDialog * dialog;
};

#endif // MAINWINDOW_H
