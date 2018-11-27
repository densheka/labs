/**
  settingsdialog.h
  Purpose: sets window for settings
*/

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtWidgets/QDialog>
#include <QSettings>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    /**
     * @brief loadSettings
     */
	void loadSettings();
protected:
    /**
     * @brief changeEvent
     * @param e
     */
    void changeEvent(QEvent *e);
private slots:
    /**
     * @brief saveSettings
     */
	void saveSettings();
private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
