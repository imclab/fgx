/*
 *  fgx.h
 *  fgx
 *
 *  Created by Yves Sablonier, Zurich
 *  Copyright 2011 --- GPL2
 *
 */

#ifndef FGX_H
#define FGX_H


//#include <QtSql/QSqlDatabase> TODO - pedro
//#include <QtSql/QSqlError> TODO - pedro

#include <QtCore/QProcess>

#include <QtGui/QMessageBox>
#include <QtGui/QButtonGroup>
#include <QtGui/QActionGroup>

#include "ui_fgx.h"
#include "xobjects/xsettings.h"

#include "panes/coresettingswidget.h"
#include "panes/timeweatherwidget.h"
#include "aircraft/aircraftwidget.h"
#include "airports/airportswidget.h"
#include "network/networkwidget.h"
#include "panes/advancedoptionswidget.h"
#include "panes/outputpreviewwidget.h"


#include "xwidgets/execontrols.h"


class fgx : public QMainWindow, public Ui::mainWindow
{
	Q_OBJECT
	
protected:
	void closeEvent(QCloseEvent *event);
	
public:

	fgx (QMainWindow *parent = 0);
	~fgx();

	//QSqlDatabase db;
	//bool listchecked;
	
	ExeControls *exeFgfs;
	ExeControls *exeTerraSync;
	ExeControls *exeFgCom;

	Q_PID pid_fg;
	Q_PID pid_terra;
	void kill_process(QString pid);
	
private:
	Ui::mainWindow *ui;
	XSettings settings;

	CoreSettingsWidget *coreSettingsWidget;
	TimeWeatherWidget *timeWeatherWidget;
	AircraftWidget *aircraftWidget;
	AirportsWidget *airportsWidget;
	NetworkWidget *networkWidget;
	AdvancedOptionsWidget *advancedOptionsWidget;
	OutputPreviewWidget *outputPreviewWidget;

	QString fg_args();
	bool validate();
	QActionGroup *actionGroupStyle;

	void load_joysticks();

private slots:

	//** Paths
	//void on_buttonFgFsPath_clicked();
	//void on_buttonFgRootPath_clicked();

	//** Terrasync
	void on_group_box_terrasync_clicked();
	//void on_buttonTerraSyncPath_clicked();
	void on_start_terrasync_clicked();


	void on_buttonCommandPreview_clicked();
	void on_buttonCommandHelp_clicked();

	void on_buttonLoadSettings_clicked();
	void on_buttonSaveSettings_clicked();

	//* FlightGear
	void on_start_fgfs_clicked();

	//** FgCom
	void on_start_fgcom_clicked();

	//void on_groupBoxSetTime_clicked();
	//void on_buttonGroupWeather_buttonClicked(int);
	void on_menuStyle_triggered(QAction *act);

	//void on_buttonGroupTime_buttonClicked(int);


	void on_tabs_currentChanged(int);
	//void show_settings_dialog();
	void load_settings();
	void save_settings();
	void initialize();


	void on_actionAboutFGX_triggered();
	void on_actionAboutQT_triggered();
	void on_actionQuit_triggered();

	void update_pids();
};



#endif
