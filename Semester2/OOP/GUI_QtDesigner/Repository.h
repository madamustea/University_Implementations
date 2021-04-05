#pragma once
#include"domain.h"
#include<vector>
#include<fstream>
#include "Windows.h"
#include<vector>
#include<exception>
#include<algorithm>
using namespace std;

class RepoMemory
{

protected:
	vector<GuardianStatue> statues;
	int currentIndex;
public:
	virtual void set_file_location(string path) {};
	virtual bool exists(GuardianStatue statue);
	virtual void add_repo(GuardianStatue statue);
	virtual void update_repo(GuardianStatue statue);
	virtual void delete_repo(GuardianStatue statue);
	virtual GuardianStatue search_repo(GuardianStatue statue);
	virtual int GetSizeRepo();
	virtual vector<GuardianStatue> GetStatues();
	virtual void next_repo();
	virtual GuardianStatue get_current();

};