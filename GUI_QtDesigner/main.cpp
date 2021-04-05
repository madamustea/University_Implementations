#include "Lab12OOP.h"
#include <QtWidgets/QApplication>
#include "domain.h"
#include<fstream>
#include"Repository.h"
#include"RepositoryFile.h"
#include"Service.h"
#include"RepositoryFile.h"
#include "Validator.h"
#include "Lab12OOP.h"
using namespace std;
int main(int argc, char* argv[])
{
	string fileLocation, mylistLocation;


	QApplication a(argc, argv);
	ifstream file("ConfigurationFile.txt");
	if (file.is_open())
	{
		getline(file, fileLocation);
		if (fileLocation == "memory")
		{
			getline(file, mylistLocation);

			RepoMemory repository{};
			ValidatorStatue validatorStatue;
			Service service{ repository, validatorStatue };
			service.set_mylist_location(mylistLocation);
			Lab12OOP GUI{ service };
			GUI.show();
			return a.exec();
		}
		else
		{
			RepoFile repository{};
			ValidatorStatue validatorStatue;
			repository.set_file_location(fileLocation);
			getline(file, mylistLocation);
			Service service{ repository ,validatorStatue };
			service.set_mylist_location(mylistLocation);
			Lab12OOP GUI{ service };
			GUI.show();
			return a.exec();
		}
	}


}
