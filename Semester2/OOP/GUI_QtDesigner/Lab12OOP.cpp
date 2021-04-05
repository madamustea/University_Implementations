#include "Lab12OOP.h"
#include"Validator.h"
#include<qmessagebox.h>
Lab12OOP::Lab12OOP(Service& service, QWidget* parent)
	: QMainWindow(parent),service{service}
{
    ui.setupUi(this);
	this->populate_list();
	this->mode = "A";
	//this->populate_mylist();
	this->connectSignalsAndSlots();
}

void Lab12OOP::populate_list()
{
	this->ui.listOfStatues->clear();
	vector<GuardianStatue> statues = this->service.Get_Statues();
	for (GuardianStatue statue : statues) {
		this->ui.listOfStatues->addItem(QString::fromStdString(statue.GetPowerWordName() + " " + statue.GetMaterial() + " " + to_string(statue.GetAge()) + " " + statue.GetCorporealForm()));
	}
}

int Lab12OOP::get_selectedIndex()
{
	QModelIndexList selectedIndexes = this->ui.listOfStatues->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->ui.lineEditPowerWordName->clear();
		this->ui.lineEditMaterial->clear();
		this->ui.lineEditAge->clear();
		this->ui.lineEditCorporealForm->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void Lab12OOP::connectSignalsAndSlots()
{
	QObject::connect(this->ui.listOfStatues, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->get_selectedIndex();
		if (selectedIndex < 0)return;
		GuardianStatue statue = this->service.Get_Statues()[selectedIndex];
		this->ui.lineEditPowerWordName->setText(QString::fromStdString(statue.GetPowerWordName()));
		this->ui.lineEditMaterial->setText(QString::fromStdString(statue.GetMaterial()));
		this->ui.lineEditAge->setText(QString::fromStdString(to_string(statue.GetAge())));
		this->ui.lineEditCorporealForm->setText(QString::fromStdString(statue.GetCorporealForm()));

	});
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &Lab12OOP::addStatue);
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &Lab12OOP::updateStatue);
	QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &Lab12OOP::deleteStatue);
	QObject::connect(this->ui.NextButton, &QPushButton::clicked, this, &Lab12OOP::nextStatue);
	QObject::connect(this->ui.SaveButton, &QPushButton::clicked, this, &Lab12OOP::saveStatue);
	QObject::connect(this->ui.FilterButton, &QPushButton::clicked, this, &Lab12OOP::filterByMaterialAndAge);
	QObject::connect(this->ui.OpenButton, &QPushButton::clicked, this, &Lab12OOP::open);
	QObject::connect(this->ui.switch_2, &QPushButton::clicked, this, &Lab12OOP::switchMode);
}

void Lab12OOP::deleteStatue()
{
	if (this->mode.compare("B") == 0) { QMessageBox::critical(this, "Error", "We are in mode B!"); }
	int selectedIndex = this->get_selectedIndex();
	if (selectedIndex < 0) {
		QMessageBox::critical(this, "Error", "No statue was selected!");
		return;
	}
	GuardianStatue statue = this->service.Get_Statues()[selectedIndex];
	try {
		this->service.deleteGuardianStatue(statue.GetPowerWordName());
	}
	catch (...) {
		QMessageBox::critical(this, "Error", "Inexisting statue!");
	}
	this->populate_list();
}

void Lab12OOP::addStatue()
{	if(this->mode.compare("B")==0){ QMessageBox::critical(this, "Error", "We are in mode B!"); }
	std::string PowerWordName = this->ui.lineEditPowerWordName->text().toStdString();
	std::string material = this->ui.lineEditMaterial->text().toStdString();
	int age = this->ui.lineEditAge->text().toInt();
	std::string CorporealForm = this->ui.lineEditCorporealForm->text().toStdString();
	try {
		this->service.addGuardainStatue(PowerWordName, material, age, CorporealForm);
	}
	catch (ValidationException& Exception) {
		QMessageBox::critical(this, "Error", Exception.what());
	}
	catch (...) {
		QMessageBox::critical(this, "Error", "Existing statue!");
	}
	this->populate_list();
	int LastElement = this->service.Get_Statues().size() - 1;
	this->ui.listOfStatues->setCurrentRow(LastElement);
}

void Lab12OOP::updateStatue()
{
	if (this->mode.compare("B") == 0) { QMessageBox::critical(this, "Error", "We are in mode B!"); }
	int selectedIndex = this->get_selectedIndex();
	if (selectedIndex < 0) {
		QMessageBox::critical(this, "Error", "No statue was selected!");
		return;
	}
	GuardianStatue statue = this->service.Get_Statues()[selectedIndex];
	std::string PowerWordName = statue.GetPowerWordName();
	std::string material = this->ui.lineEditMaterial->text().toStdString();
	int age = this->ui.lineEditAge->text().toInt();
	std::string CorporealForm = this->ui.lineEditCorporealForm->text().toStdString();
	try {
		this->service.updateGuardianStatue(PowerWordName, material, age, CorporealForm);
	}
	catch (ValidationException & Exception) {
		QMessageBox::critical(this, "Error", Exception.what());
	}
	
	this->populate_list();
	int LastElement = this->service.Get_Statues().size() - 1;
	this->ui.listOfStatues->setCurrentRow(LastElement);
}

void Lab12OOP::nextStatue()
{
	if (this->mode.compare("A") == 0) { QMessageBox::critical(this, "Error", "We are in mode A!"); }
	GuardianStatue statue = this->service.Next();
	this->ui.lineEditPowerWordNameModeB->setText(QString::fromStdString(statue.GetPowerWordName()));
	this->ui.lineEditMaterialModeB->setText(QString::fromStdString(statue.GetMaterial()));
	this->ui.lineEditAgeModeB->setText(QString::fromStdString(to_string(statue.GetAge())));
	this->ui.lineEditCorporealFormModeB->setText(QString::fromStdString(statue.GetCorporealForm()));
}

void Lab12OOP::populate_mylist()
{
	this->ui.Mylist->clear();
	vector<GuardianStatue> statues = this->service.GetSavedStatues();
	for (GuardianStatue statue : statues) {
		this->ui.Mylist->addItem(QString::fromStdString(statue.GetPowerWordName() + " " + statue.GetMaterial() + " " + to_string(statue.GetAge()) + " " + statue.GetCorporealForm()));
	}
}

void Lab12OOP::saveStatue()
{
	if (this->mode.compare("A") == 0) { QMessageBox::critical(this, "Error", "We are in mode A!"); }
	std::string PowerWordName = this->ui.lineEditPowerWordNameModeB->text().toStdString();
	std::string material = this->ui.lineEditMaterialModeB->text().toStdString();
	int age = this->ui.lineEditAgeModeB->text().toInt();
	std::string CorporealForm = this->ui.lineEditCorporealFormModeB->text().toStdString();
	try {
		this->service.saveGuardianStatue(PowerWordName);
	}
	catch (ValidationException & Exception) {
		QMessageBox::critical(this, "Error", Exception.what());
	}
	catch (...) {
		QMessageBox::critical(this, "Error", "Existing statue!");
	}
	this->populate_mylist();
	int LastElement = this->service.GetSavedStatues().size() - 1;
	this->ui.Mylist->setCurrentRow(LastElement);

}

void Lab12OOP::filterByMaterialAndAge()
{
	if (this->mode.compare("A") == 0) { QMessageBox::critical(this, "Error", "We are in mode A!"); }
	QMessageBox messageBox;
	std::string material = this->ui.lineEditMaterialModeB->text().toStdString();
	int age = this->ui.lineEditAgeModeB->text().toInt();
	
		vector<GuardianStatue> statues = this->service.filteredStatues(material, age);
	
	for (GuardianStatue statue : statues) {
		
		//messageBox.setText(QString::fromStdString(statue.GetPowerWordName() + " " + statue.GetMaterial() + " " + to_string(statue.GetAge()) + " " + statue.GetCorporealForm()));
		QMessageBox::information(this, "Filtered statues", QString::fromStdString(statue.GetPowerWordName() + " " + statue.GetMaterial() + " " + to_string(statue.GetAge()) + " " + statue.GetCorporealForm()));
		
	}
	
}

void Lab12OOP::open()
{
	this->service.open();
}

void Lab12OOP::switchMode()
{
	if (this->mode.compare("A") == 0) {
		this->mode = "B";
		this->ui.listOfStatues->clear();
		this->ui.lineEditAge->clear();
		this->ui.lineEditMaterial->clear();
		this->ui.lineEditPowerWordName->clear();
		this->ui.lineEditCorporealForm->clear();
		this->populate_mylist();
	}
	else if (this->mode.compare("B") == 0) {
		this->mode = "A";
		this->ui.Mylist->clear();
		this->ui.lineEditAgeModeB->clear();
		this->ui.lineEditCorporealFormModeB->clear();
		this->ui.lineEditMaterialModeB->clear();
		this->ui.lineEditPowerWordNameModeB->clear();
		this->populate_list();
	}
}
