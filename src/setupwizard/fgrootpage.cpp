

#include <QtCore/QFile>
#include <QtGui/QGridLayout>
#include <QtGui/QFileDialog>

#include "setupwizard/fgrootpage.h"

FgRootPage::FgRootPage(MainObject *mob, QWidget *parent) :
    QWizardPage(parent)
{
	mainObject = mob;

	setTitle("Select FlightGear Data directory ");
	setSubTitle("Select the default or a custom path to FG_ROOT");


	QGridLayout *gridLayout = new QGridLayout();
	setLayout(gridLayout);

	//= Default Path
	int row = 0;
	radioDefault = new QRadioButton();
	radioDefault->setText("Use default path");
	gridLayout->addWidget(radioDefault, row, 0, 1, 3);
	connect(radioDefault, SIGNAL(toggled(bool)), this, SLOT(on_default_toggled(bool)));

	//= default help label
	row++;
	lblDefault = new QLabel("--");
	gridLayout->addWidget(lblDefault, row, 1, 1, 2);

	//= Custom path
	row++;
	radioCustom = new QRadioButton();
	radioCustom->setText("Select custom path");
	radioCustom->setChecked(true);
	gridLayout->addWidget(radioCustom, row, 0, 1, 3);

	//= select custom path
	row++;
	txtFgRoot = new QLineEdit("");
	gridLayout->addWidget(txtFgRoot, row, 1, 1, 1);
	connect(txtFgRoot, SIGNAL(textChanged(QString)), this, SLOT(check_paths()));

	//= Dropdown button for path
	buttSelect = new QToolButton();
	gridLayout->addWidget(buttSelect, row, 2);
	buttSelect->setIcon(QIcon(":/icon/black"));
	connect( buttSelect, SIGNAL(clicked()),
			 this,		 SLOT(on_select_path()) );

	//= custom help label
	row++;
	lblCustom = new QLabel("--");
	gridLayout->addWidget(lblCustom, row, 1, 1, 2);

	gridLayout->setColumnStretch(0,1);
	gridLayout->setColumnStretch(1,6);
	gridLayout->setColumnStretch(2,0);


	registerField("use_default_fgroot", radioDefault);
	registerField("fgroot_custom_path", txtFgRoot);

}

void FgRootPage::on_select_path()
{
	QString dirPath = QFileDialog::getExistingDirectory(this, tr("Select FG_ROOT directory"),
														 txtFgRoot->text(), QFileDialog::ShowDirsOnly);
	if(dirPath.length() > 0){
		txtFgRoot->setText(dirPath);
	}
	check_paths();
}

//===================================================
//= initializePage
void FgRootPage::initializePage()
{
	radioDefault->setChecked( mainObject->settings->value("use_default_fgroot", "1").toBool() );
	lblDefault->setText( mainObject->settings->fg_root_default() );
	txtFgRoot->setText( mainObject->settings->value("fgroot_custom_path").toString() );
}


void FgRootPage::check_paths()
{
	//= Check the default path
	QString default_path = mainObject->settings->fg_root_default();
	bool default_exists = QFile::exists(default_path);
	QString lbl_default(default_path);
	lbl_default.append( default_exists ? " - Ok" : " - Not Found" );
	QString style_default("");

	if(radioDefault->isChecked()){
		style_default.append(default_exists ? "color:green;" : "color:#990000;");
	}else{
		style_default.append("color:#444444;");
	}
	lblDefault->setText(lbl_default);
	lblDefault->setStyleSheet(style_default);

	//= Check Custom Path
	if(radioCustom->isChecked()){
		QString custom_path = txtFgRoot->text().trimmed();
		if(custom_path.size() == 0){
			lblCustom->setText("Select a path");
			lblCustom->setStyleSheet("color: #000099;");
		}else{
			bool custom_exists = QFile::exists(custom_path);
			lblCustom->setText(custom_exists ? "Ok" : "Not found");
			lblCustom->setStyleSheet(custom_exists ?  "color: green;" : "color:#990000;");
		}
	}else{
		lblCustom->setText("");
	}
}

//====================================================
//= ValidatePage
bool FgRootPage::validatePage()
{
	check_paths();
	if(radioDefault->isChecked()){
		//TODO vaidate default path
		return true;
	}
	if(QFile::exists(txtFgRoot->text())){
		// TODO - check its executable
		return true;
	}else{
		txtFgRoot->setFocus();
		lblCustom->setText("File does not exist");
	}
	return false;
}


void FgRootPage::on_default_toggled(bool state){
	Q_UNUSED(state);
	bool def = radioDefault->isChecked();

	txtFgRoot->setDisabled(def);
	buttSelect->setDisabled( def);
	if(def == false){
		txtFgRoot->setFocus();
	}
	check_paths();
}
