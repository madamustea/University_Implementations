#pragma once
#include "domain.h"

#include <vector>

class MyList
{
public:

	virtual void add(const GuardianStatue& statue) = 0;
	virtual std::vector<GuardianStatue> get_all() = 0;


	virtual void set_location(std::string file_location) = 0;
	virtual void open() = 0;
};


class MemoryMyList :public MyList
{
private:
	std::vector<GuardianStatue> savedStatues;

public:

	void add(const GuardianStatue& statue);
	std::vector<GuardianStatue> get_all() { return savedStatues; };

	void set_location(std::string file_location) {};
	void open() {};
};