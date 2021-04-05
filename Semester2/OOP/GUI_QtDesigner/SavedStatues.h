#pragma once
#include "domain.h"
#include "Mylist.h"
#include <vector>
using namespace std;

class SavedStatues : public MyList
{
protected:
	std::string file_location;

public:
	
	void add(const GuardianStatue& statue);

	
	std::vector<GuardianStatue> get_all();


	void set_location(std::string file_location);


	virtual void write_to_file(std::vector<GuardianStatue> statues) = 0;
	
	virtual std::vector<GuardianStatue> read_from_file() = 0;

	virtual void open() = 0;


	virtual ~SavedStatues() {};
};


class CSVmylist : public SavedStatues
{
public:

	void write_to_file(std::vector<GuardianStatue> statues) override;
	std::vector<GuardianStatue> read_from_file() override;

	void open() override;

	~CSVmylist() {};
};

class HTMLmylist : public SavedStatues
{
public:

	void write_to_file(std::vector<GuardianStatue> statues) override;
	std::vector<GuardianStatue> read_from_file() override;

	void open() override;


	~HTMLmylist() {};
};

