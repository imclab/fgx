


#include <QGridLayout>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QProgressDialog>

#include "setupwizard/confirmpage.h"
#include "xwidgets/xgroupboxes.h"


#include "airports/airportsdata.h"
#include "aircraft/aircraftdata.h"

/*! \class ConfirmPage
 * @author: Peter Morgan
 * \brief The page that actually writes paths out, and reloads the cache.
 *
 * The validatePage() function is where the write is actually done.
 */


ConfirmPage::ConfirmPage(MainObject *mob, QWidget *parent) :
    QWizardPage(parent)
{

	mainObject = mob;

	setTitle("Finish Setup");
	setSubTitle("Click the finish button to run");


	QVBoxLayout *mainLayout = new QVBoxLayout();
	setLayout(mainLayout);


	XGroupVBox *grpFgExe = new XGroupVBox("FlightGear Executable");
	mainLayout->addWidget(grpFgExe);
	lblFgExeUsingDefault = new QLabel();
	grpFgExe->addWidget(lblFgExeUsingDefault);
	lblFgExePath = new QLabel();
	grpFgExe->addWidget(lblFgExePath);



	XGroupVBox *grpFgRoot = new XGroupVBox("FlightGear Data");
	mainLayout->addWidget(grpFgRoot);
	lblFgRootUsingDefault = new QLabel();
	grpFgRoot->addWidget(lblFgRootUsingDefault);
	lblFgRootPath = new QLabel();
	grpFgRoot->addWidget(lblFgRootPath);


	//= Terrasync
	XGroupVBox *grpTerrasync = new XGroupVBox("TerraSync");
	mainLayout->addWidget(grpTerrasync);
	lblUsingTerraSync = new QLabel();
	grpTerrasync->addWidget(lblUsingTerraSync);
	lblTerraSyncPath = new QLabel();
	grpTerrasync->addWidget(lblTerraSyncPath);



	//= Import Cache Data ============
	XGroupGBox *grpImports = new XGroupGBox("Reload Cached Data");
	mainLayout->addWidget(grpImports);

	//== Aircraft ==
	int row = 0;
	checkBoxImportAircaft = new QCheckBox("Import Aircraft");
	grpImports->addWidget(checkBoxImportAircaft, row, 0, 1, 2);
	checkBoxImportAircaft->setChecked(true);


	//== Airports ==
	row++;
	checkBoxImportAirports = new QCheckBox("Import Airports");
	grpImports->addWidget(checkBoxImportAirports, row, 0, 1, 2);
	checkBoxImportAirports->setChecked(true);
	connect(checkBoxImportAirports, SIGNAL(clicked()), this, SLOT(on_import_airports()));

	//= IACO Only
	row++;
	radioIcaoOnly = new QRadioButton();
	grpImports->addWidget(radioIcaoOnly, row, 1, 1, 1);
	radioIcaoOnly->setText("Import major airports only");
	radioIcaoOnly->setChecked(true);

	//= All Airports
	row++;
	radioAllAirports = new QRadioButton();
	grpImports->addWidget(radioAllAirports, row, 1, 1, 1);
	radioAllAirports->setText("Import all airports, seaports, heliports");

	grpImports->gridLayout->setColumnStretch(0, 1);
	grpImports->gridLayout->setColumnStretch(1, 10);
}


void ConfirmPage::on_import_airports(){
	radioIcaoOnly->setEnabled(checkBoxImportAirports->isChecked());
	radioAllAirports->setEnabled(checkBoxImportAirports->isChecked());
}

//===================================================
//= initializePage
void ConfirmPage::initializePage()
{

	if(field("fgfs_use_default").toBool()){
		lblFgExeUsingDefault->setText("Using Default Path");
		lblFgExePath->setText(mainObject->settings->fgfs_default_path());
	}else{
		lblFgExeUsingDefault->setText("Using Custom Path");
		lblFgExePath->setText(field("fgfs_custom_path").toString());
	}

	if(field("fgroot_use_default").toBool()){
		lblFgRootUsingDefault->setText("Using Default Data Path");
		lblFgRootPath->setText(mainObject->settings->fgroot_default_path());
	}else{
		lblFgRootUsingDefault->setText("Using Custom Data Path");
		lblFgRootPath->setText(field("fgroot_custom_path").toString());
	}

	if(field("terrasync_enabled").toBool()){
		lblUsingTerraSync->setText("Using Terrasync");
		lblTerraSyncPath->setText(field("terrasync_path").toString());
	}else{
		lblUsingTerraSync->setText("No Terrasync");
		lblTerraSyncPath->setText("");
	}

	//= Check is an airport update is required ie fg root has changed
	bool airports_update = false;
	if(field("fgroot_use_default").toBool() != mainObject->settings->fgroot_use_default()){
		// not the same as last time
		airports_update = true;

	}else if(field("fgfs_use_default").toBool() &&
			 field("fgroot_custom_path").toString() != mainObject->settings->value("fgroot_custom_path")){
		// custom path has changed
		airports_update = true;
	}
	checkBoxImportAirports->setText(airports_update ? "Import Airports - recommended" : "Import Airports");
	checkBoxImportAirports->setChecked(airports_update);

	//= Check is an aircraft update is required ie fgdata changed
	bool aircraft_update = false;
	if(field("terrasync_enabled").toBool() != mainObject->settings->terrasync_enabled()){
		// not the same as last time
		aircraft_update = true;

	}else if(field("terrasync_enabled").toBool() &&
			 field("terrasync_path").toString() != mainObject->settings->value("terrasync_path")){
		// terrasync path changed
		aircraft_update = true;
	}
	checkBoxImportAircaft->setText(aircraft_update ? "Import Aircraft - recommended" : "Import Aircraft");
	checkBoxImportAircaft->setChecked(aircraft_update);

	radioIcaoOnly->setChecked(mainObject->settings->value("last_import_icao_checked", "1").toBool());
	on_import_airports();
	return;
}


//===================================================
//= validate - and Write out main settings
bool ConfirmPage::validatePage()
{

	mainObject->settings->setValue("fgfs_use_default", field("fgfs_use_default"));
	mainObject->settings->setValue("fgfs_custom_path", field("fgfs_custom_path"));

	mainObject->settings->setValue("fgroot_use_default", field("fgroot_use_default"));
	mainObject->settings->setValue("fgroot_custom_path", field("fgroot_custom_path"));

	mainObject->settings->setValue("terrasync_enabled", field("terrasync_enabled"));
	mainObject->settings->setValue("terrasync_path", field("terrasync_path"));

	mainObject->settings->setValue("last_import_icao_checked", radioIcaoOnly->isChecked());

	mainObject->settings->sync();

	QProgressDialog progress(this);
	progress.setFixedWidth(400);
	progress.setWindowIcon(QIcon(":/icon/import"));

	bool cancelled = false;
	if(checkBoxImportAirports->isChecked()){
		cancelled = AirportsData::import(progress, mainObject, radioIcaoOnly->isChecked());
	}
	if(cancelled){
		return false;
	}
	if(cancelled == false && checkBoxImportAircaft->isChecked()){
		AircraftData::import(progress, mainObject);
	}
	return true;
}


