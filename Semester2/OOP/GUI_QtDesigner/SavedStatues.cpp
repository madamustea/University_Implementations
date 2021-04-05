#include "SavedStatues.h"
#include <string>
#include <fstream>
#include <Windows.h>


void SavedStatues::add(const GuardianStatue& statue)
{
	vector<GuardianStatue> statues = this->read_from_file();

	for (auto savedStatue : statues)
		if (savedStatue == statue)
			throw std::exception();
	statues.push_back(statue);

	this->write_to_file(statues);
}

std::vector<GuardianStatue> SavedStatues::get_all()
{
	return this->read_from_file();
}

void SavedStatues::set_location(std::string file_location)
{
	this->file_location = file_location;
}

void CSVmylist::write_to_file(std::vector<GuardianStatue> statues)
{
	ofstream FileOut(this->file_location, ios::out);

	for (auto statue : statues) {
		FileOut << statue;
	}
	FileOut.close();
}

std::vector<GuardianStatue> CSVmylist::read_from_file()
{
	ifstream FileIn(this->file_location);
	vector<GuardianStatue> Statues;
	GuardianStatue statueRead;
	if (!FileIn.is_open())ofstream FileIn(this->file_location, ios::out);
	while (FileIn >> statueRead) {
		Statues.push_back(statueRead);

	}
	FileIn.close();
	return Statues;
}

void CSVmylist::open()
{
	ShellExecuteA(NULL, NULL, "notepad.exe", this->file_location.c_str(), NULL, SW_SHOWMAXIMIZED);
}

void HTMLmylist::write_to_file(std::vector<GuardianStatue> statues)
{
	ofstream FileOut(this->file_location, ios::out);
	FileOut << "<!DOCTYPE html>" << "\n";
	FileOut << "<html>" << "\n";
	FileOut << "<head>" << "\n";
	FileOut << "<title>Statues</title>" << "\n";
	FileOut << "</head>" << "\n";
	FileOut << "<body>" << "\n";
	FileOut << "<table border='1'>";
	for (auto statue : statues) {
		FileOut << "<tr>" << "\n";
		FileOut << "<td>" << "\n<!--1-->" << statue.GetPowerWordName() << "\n</td>" << "\n";
		FileOut << "<td>\n<!--2-->" << statue.GetMaterial() << "\n</td>" << "\n";
		FileOut << "<td>\n<!--3-->" << statue.GetAge() << "\n</td>" << "\n";
		FileOut << "<td>\n<!--4-->" << statue.GetCorporealForm() << "\n</td>" << "\n";
		FileOut << "</tr>" << "\n";
	}
	FileOut << "</table>" << "\n";
	FileOut << "</body>" << "\n";
	FileOut << "</html>" << "\n";
	FileOut.close();
}

std::vector<GuardianStatue> HTMLmylist::read_from_file()
{
	string powerWordName, CorporealForm, Material;
	int age = -1;
	bool ok = false;
	vector<GuardianStatue> statues;
	ifstream FileIn(this->file_location);
	string stringToBeRead;
	if (!FileIn.is_open()) {
		ofstream FileIn(this->file_location, ios::out);
	}

	while (getline(FileIn, stringToBeRead))
	{

		if (stringToBeRead.find("<!--") == 0)
		{


			if (stringToBeRead.find("1") == 4) {
				stringToBeRead.erase(0, 8);
				powerWordName = stringToBeRead;

			}
			if (stringToBeRead.find("2") == 4) {
				stringToBeRead.erase(0, 8);
				Material = stringToBeRead;

			}
			if (stringToBeRead.find("3") == 4) {
				stringToBeRead.erase(0, 8);
				age = stoi(stringToBeRead);

			}
			if (stringToBeRead.find("4") == 4) {
				stringToBeRead.erase(0, 8);
				CorporealForm = stringToBeRead;

				ok = true;
			}


		}
		if (ok == true) {

			ok = false;
			GuardianStatue statue{ powerWordName,Material,age,CorporealForm };

			statues.push_back(statue);
		}

	}
	FileIn.close();



	return statues;

}

void HTMLmylist::open()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->file_location.c_str(), NULL, SW_SHOWMAXIMIZED);
}
