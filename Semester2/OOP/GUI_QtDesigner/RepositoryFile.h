#pragma once
#include"domain.h"
#include<vector>
#include<fstream>
#include "Windows.h"
#include<vector>
#include"Repository.h"
#include<exception>
#include<algorithm>
using namespace std;

class RepoFile : public RepoMemory
{

protected:
	std::string path;
public:
	vector<GuardianStatue> read_from_file(string path);
	void write_to_file(string path, vector<GuardianStatue> statues);
	void set_file_location(string path)override;
	bool exists(GuardianStatue statue)override;
	virtual void add_repo(GuardianStatue statue)override;
	void update_repo(GuardianStatue statue)override;
	void delete_repo(GuardianStatue statue)override;
	GuardianStatue search_repo(GuardianStatue statue)override;
	int GetSizeRepo()override;
	vector<GuardianStatue> GetStatues()override;
	void next_repo()override;
	void open() { ShellExecuteA(NULL, NULL, "notepad.exe", this->path.c_str(), NULL, SW_SHOWMAXIMIZED); };
	GuardianStatue get_current()override;

};