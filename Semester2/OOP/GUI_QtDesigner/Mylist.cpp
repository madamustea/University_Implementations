#include "MyList.h"
#include"Validator.h"
void MemoryMyList::add(const GuardianStatue& statue)
{
	
		for (auto savedStatue : this->savedStatues)
			if (savedStatue == statue)
				throw std::exception();
		this->savedStatues.push_back(statue);
	
}
