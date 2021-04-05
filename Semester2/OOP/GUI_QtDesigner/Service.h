#pragma once
#include"domain.h"
#include"RepositoryFile.h"
#include"SavedStatues.h"
#include"MyList.h"
#include"Repository.h"
#include "Validator.h"



class Service {
private:
	RepoMemory& repository;
	ValidatorStatue& validatorStatue;
	MyList* savedStatues;

public:
	Service(RepoMemory& new_repository,ValidatorStatue& validator) : repository{ new_repository }, validatorStatue{ validator } {this->savedStatues = nullptr; }
	~Service();


	// Sets the file in which the data is kept
	void set_file_location(std::string file_location);
	// Sets location to keep the saved data
	void set_mylist_location(std::string mylist_location);

	void open_file();

	
	/*input- PowerWordName-string,Material-string,age-integer,CorporealForm-string
	 output-creates a guardian statue with that data and adds it to the array.*/
	void addGuardainStatue(std::string PowerWordName, std::string Material, int age, std::string CorporealForm);
	/*input- guardianSTatue-GuardianStatue
	output-adds to the new array the object
	*/
	void saveGuardianStatue(std::string PowerWordName);
	
	/*input- PowerWordName-string
	 output- finds the guardian statue with the guiven power word name and removes it from the array.*/
	void deleteGuardianStatue(std::string PowerWordName);
	/*input- PowerWordName-string,NewMaterial-string,NewAge-integer,NewCorporealForm-string
	 output-finds the guardian statue with the guiven power word name and removes it from the array.
	*/
	
	void updateGuardianStatue(std::string PowerWordName, std::string NewMaterial, int NewAge, std::string NewCorporealForm);
	
	vector<GuardianStatue> Get_Statues() {
		return this->repository.GetStatues();
	}
	
	int GetNumberStatues() {
		return this->repository.GetSizeRepo();
	}
	
	vector<GuardianStatue> GetSavedStatues() {
		
		return this->savedStatues->get_all();
	}
	vector<GuardianStatue> filteredStatues(std::string material, int age);
	void open() {
		this->savedStatues->open();
	}
	

	/*Finds the statue with a given Power word name.
	  input - PowerWordName-string
	  output - the statue.*/

	GuardianStatue Next();


	GuardianStatue searchStatueWithPowerWordName(std::string PowerWordName);
	


};
