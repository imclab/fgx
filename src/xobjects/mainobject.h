#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include <QtCore/QObject>


#include <QtGui/QSystemTrayIcon>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QLabel>
#include <QtGui/QWidgetAction>

#include "xobjects/xsettings.h"

#include "xobjects/xsettingsmodel.h"
class XSettingsModel;

#include "xobjects/xprocess.h"
class XProcess;



#include "launcher/launcherwindow.h"
class LauncherWindow;

#include "mpmap/mpmapwidget.h"
#include "mpmap/mpmapxwidget.h"
#include "logs/viewlogswidget.h"
#include "props/propstreewidget.h"
#include "xwidgets/fgxdebugwidget.h"

class MpMapWidget;
class MpMapXWidget;
class ViewLogsWidget;
class PropsTreeWidget;
class FgxDebugWidget;





/*! \class MainObject
 * \brief The MainObject is an extended QObject, and the main "controller" for FGx
 *
 * This is the main object created and called when the app starts in the backgound
 * It manifest itself and is made visible via an icon in the QSystemTrayIcon ie TaskBar
 * All widgets are children to this object and are hidden (at the moment)
 *
 * MainObject also controls the starting and stopping of processes// TBC
 *
 * @author: Peter Morgan
 * @author: Yves Sablonier
 */

class MainObject : public QObject
{
Q_OBJECT
public:
    explicit MainObject(QObject *parent = 0);
    ~MainObject();
	

    XSettings *settings;
	XSettingsModel *S;


	LauncherWindow *launcherWindow;
	MpMapWidget *mpMapWidget;
	MpMapXWidget *mpMapXWidget;
	ViewLogsWidget *viewLogsWidget;
	PropsTreeWidget *propertiesBrowser;
	FgxDebugWidget *fgxDebugWidget;

	XProcess *processFgFs;
	XProcess *processTerraSync;
	XProcess *processFgCom;


    QSystemTrayIcon *trayIcon;
    QMenu *popupMenu;
	
	QMenuBar *menuBar;


    QWidgetAction *actionCallsign;
    QLabel *lblCallsign;

    QAction *actionLauncher;
    QAction *actionMpMap;
	QAction *actionPropsBrowser;
	QAction *actionSetupWizard;

	QAction *actionViewLogs;
	QAction *actionViewFgxDebug;
	QAction *actionDebugMode;



    QAction *actionQuit;




	QString get_fgfs_command();
	QStringList get_fgfs_args();
	QStringList get_env();




signals:
	void show_settings(int);
	void reload_paths();
	void debug_mode(bool enabled);

public slots:

	void initialize();

    void on_tray_icon(QSystemTrayIcon::ActivationReason reason);

    void on_launcher();
    void on_mpmap();
	void on_mpxmap();
    void on_settings();
	void on_settings(int);
	void on_properties_browser();
    void on_quit();
	void show_setup_wizard();

	void on_view_logs();
	void clear_log(QString log_name);
	void add_log(QString log_name, QString data);

	void start_all();
	void start_fgfs();
	void start_fgcom();
	void start_terrasync();
	void stop_all();

	void quit();

	void set_callsign();

	void on_view_fgx_debug();
	void on_debug_mode();
};


#endif // MAINOBJECT_H
