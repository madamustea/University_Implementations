#include "Service.h"

Service::~Service()
{
	delete savedStatues;
}

void Service::set_file_location(std::string file_location)
{
	this->repository.set_file_location(file_location);
}

void Service::set_mylist_location(std::string mylist_location)
{
	if (mylist_location == "memory")
	{
		this->savedStatues = new MemoryMyList{};
		return;
	}
	string extension = mylist_location.substr(mylist_location.size() - 4);

	if (extension == ".csv")
	{
		this->savedStatues = new CSVmylist{};
	}
	else if (extension == "html")
	{
		this->savedStatues = new HTMLmylist{};
	}
	else if (extension == ".txt")
	{
		this->savedStatues = new CSVmylist{};
	}
	

	this->savedStatues->set_location(mylist_location);
}

void Service::open_file()
{
	this->savedStatues->open();
}

void Service::addGuardainStatue(std::string PowerWordName, std::string Material, int age, std::string CorporealForm)
{
	GuardianStatue newGuardianSttaue{ PowerWordName,Material,age,CorporealForm };
	this->validatorStatue.validate(newGuardianSttaue);
	this->repository.add_repo(newGuardianSttaue);
}

void Service::saveGuardianStatue(std::string PowerWordName)
{
	GuardianStatue savedStatue(PowerWordName, "", 0, "");

	GuardianStatue searched = this->repository.search_repo(savedStatue);
	this->savedStatues->add(searched);
}

void Service::deleteGuardianStatue(std::string PowerWordName)
{
	GuardianStatue searchedGuardianStatue{ PowerWordName,"",0,"" };
	this->repository.delete_repo(searchedGuardianStatue);
}

void Service::updateGuardianStatue(std::string PowerWordName, std::string NewMaterial, int NewAge, std::string NewCorporealForm)
{
	GuardianStatue searchedGuardianStatue{ PowerWordName,NewMaterial,NewAge,NewCorporealForm };
	this->validatorStatue.validate(searchedGuardianStatue);
	this->repository.update_repo(searchedGuardianStatue);

}


vector<GuardianStatue> Service::filteredStatues(std::string material,int age)
{
	vector<GuardianStatue> statues = this->repository.GetStatues();
	vector<GuardianStatue> filtered_list(statues.size());

	auto it = std::copy_if(statues.begin(), statues.end(), filtered_list.begin(), [material, age](GuardianStatue statue) {return (statue.GetMaterial().compare(material)==0 && statue.GetAge()<age); });
	filtered_list.resize(std::distance(filtered_list.begin(), it));  

	

	return filtered_list;
}

GuardianStatue Service::Next()
{
	GuardianStatue nextStatue = this->repository.get_current();
	this->repository.next_repo();
	return nextStatue;
}

GuardianStatue Service::searchStatueWithPowerWordName(std::string PowerWordName)
{
	GuardianStatue searchedGuardianStatue{ PowerWordName,"",0,"" };
	return this->repository.search_repo(searchedGuardianStatue);
}
