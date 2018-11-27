/**
  mainwindow.cpp
  Purpose: sets the main window with elements for the game and its description
*/

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setupUi(this);

	game = new CheckersGame;
	dialog = new SettingsDialog;

	// Signal-Slots
	connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

	connect(actionStartNewGame, SIGNAL(triggered()), this, SLOT(startNewGame()));
	connect(actionEndGame, SIGNAL(triggered()), this, SLOT(endGame()));
	connect(actionSettings, SIGNAL(triggered()), this, SLOT(settings()));

	connect(actionAboutCheckers, SIGNAL(triggered()), this, SLOT(about()));
	connect(actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	connect(picture, SIGNAL(mouseClicked(int, int)), game, SLOT(setClicked(int, int)));
	connect(game, SIGNAL(stateChanged(CheckersState *)), picture, SLOT(setState(CheckersState *)));
	connect(game, SIGNAL(vectorChanged(std::vector <point> &)), picture, SLOT(setVector(std::vector <point> &)));
	connect(game, SIGNAL(vectorDeleted()), picture, SLOT(deleteVector()));
//
	connect(game, SIGNAL(gameEnded(uint8)), this, SLOT(gameEnded(uint8)));

	connect(goFirst, SIGNAL(clicked()), game, SLOT(historyShowFirst()));
	connect(goLast, SIGNAL(clicked()), game, SLOT(historyShowLast()));
	connect(goPrev, SIGNAL(clicked()), game, SLOT(historyShowPrev()));
	connect(goNext, SIGNAL(clicked()), game, SLOT(historyShowNext()));

	setWindowTitle(tr("QCheckers"));
	resize(800,600);

	actionEndGame->setEnabled(false);

	goFirst->setEnabled(false);
	goLast->setEnabled(false);
	goPrev->setEnabled(false);
	goNext->setEnabled(false);

}

MainWindow::~MainWindow()
{
	delete game;
	delete dialog;
}

//starts new game
void MainWindow::startNewGame() {
    QSettings settings("Denis","QCheckers");
	actionStartNewGame->setEnabled(false);
	int type = settings.value("type",RUSSIAN).toInt();
	int color = settings.value("color",WHITE).toInt();
	int level = settings.value("depth",3).toInt();
	std::cout << type << " " << color << "\n"; std::cout.flush();
	if(color == WHITE)
		color = BLACK;
	else
		color = WHITE;
	game->setGameType(type);
	picture->setComputerColor(color);
	game->setMaxLevel(level);
	game->startNewGame(color);

	actionEndGame->setEnabled(true);
	goFirst->setEnabled(true);
	goLast->setEnabled(true);
	goPrev->setEnabled(true);
	goNext->setEnabled(true);
}

//ends game
void MainWindow::endGame() {
	actionEndGame->setEnabled(false);
	game->endGame();
	picture->clear();
	actionStartNewGame->setEnabled(true);
	goFirst->setEnabled(false);
	goLast->setEnabled(false);
	goPrev->setEnabled(false);
	goNext->setEnabled(false);
}

// output at the end of the game
void MainWindow::gameEnded(uint8 status) {
	if(status == WHITE)
	QMessageBox::information(this, tr("White win!"),
							tr("White win!") );
	if(status == BLACK)
	QMessageBox::information(this, tr("Black win!"),
                            tr("Black win!") );
}

// output of settings
void MainWindow::settings() {
	dialog->exec();
}

// output of about
void MainWindow::about() {
	QMessageBox::about(this, trUtf8("About QCheckers"),
			   trUtf8(
"<h3 align=center>About QCheckers</h3>"
"<P>Developed by"
"<P align=right>Denis Shesterniak"));
}


