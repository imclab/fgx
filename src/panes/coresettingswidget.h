#ifndef CORESETTINGSWIDGET_H
#define CORESETTINGSWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QComboBox>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>
#include <QtGui/QGroupBox>
#include <QtGui/QButtonGroup>
#include <QtGui/QRadioButton>
#include <QToolButton>

#include "xobjects/mainobject.h"
#include "xwidgets/xgroupboxes.h"
#include "xwidgets/xmessagelabel.h"

class MainObject;

class CoreSettingsWidget : public QWidget
{
Q_OBJECT
public:
	explicit CoreSettingsWidget(MainObject *mOb, QWidget *parent = 0);

	MainObject *mainObject;
	
	XMessageLabel *messageLabel;


	//* Callsign
	QLineEdit *txtCallSign;

	//* Screen
	QComboBox *comboScreenSize;
	QCheckBox *checkBoxDisableSplashScreen;
	QCheckBox *checkBoxFullScreenStartup;


	//* MpMap
	QCheckBox *checkBoxShowMpMap;
	QComboBox *comboMpMapServer;


	//** Paths
	QButtonGroup *buttonGroupPaths;
	XGroupHBox *groupBoxFgFs;
	XGroupHBox *groupBoxFgRoot;

	QLineEdit *lineEditFgFsPath;
	QLineEdit *lineEditFgRootPath;
	QToolButton *buttonSetFgfsPath;
	QToolButton *buttonSetFgRootPath;
	QLabel *labelFgfsProgram;
	QLabel *labelFgfsCheck;
	
	QLabel *labelFgRootData;
	QLabel *labelFgRootCheck;
	
	QCheckBox *checkBoxUseTerrasync;
	QLabel *labelTerrasyncProgram;
	QLabel *labelTerrasyncCheck;
	QToolButton *buttonSetTerrasyncExePath;
	QToolButton *buttonSetTerrasyncDataPath;
	
	QLabel *labelTerrasyncData;
	QLabel *labelTerrasyncDataCheck;
	
	QLineEdit *lineEditTerraSyncDataPath;
	QLineEdit *lineEditTerraSyncExePath;
	
	QCheckBox *checkBoxUseCustomScenery;
	QLabel *labelCustomScene;
	QLabel *labelCustomSceneCheck;
	QLineEdit *lineEditCustomScenePath;
	QToolButton *buttonSetCustomSceneryPath;
	
	QLabel *labelFGComExeInfo;
	QLineEdit *lineEditFGComExePath;
	
	//* Controls
	QLabel *labelInputs;

	//* Functions
	void initialize();
	QString validate();


signals:
	void setx(QString option, bool enabled, QString value);


public slots:

	void on_callsign_changed(QString);

	void on_screensize();
	void on_checkbox_splash_screen();

	void on_show_mp_map();
	
	void on_terrasync_enabled();
	void terrasync_enabled_checkstate();
	void on_custom_scenery_enabled();
	void custom_scenery_enabled_checkstate();

	void load_joysticks();

	void on_upx(QString option, bool enabled, QString value);
	
	// Path checks
	void fgfs_check_path();
	void fgroot_check_path();
	void terrasync_exe_check_path();
	void terrasync_data_check_path();
	void custom_scenery_check_path();
	
	// "Set" buttons
	void on_select_fgfsbutton();
	void on_select_fgrootbutton();
	void on_select_terrasyncexebutton();
	void on_select_terrasyncdatabutton();
	void on_select_customscenerybutton();
	
	// Emit settings when changed
	void fgfs_set_path();
	void fgroot_set_path();
	void terrasyncexe_set_path();
	void terrasyncdata_set_path();
	void customscenery_set_path();	
};

#endif // CORESETTINGSWIDGET_H
