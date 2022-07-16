#ifndef EXTENDIBLEHASH_H
#define EXTENDIBLEHASH_H
#include "Directory.h"
#include <bitset>
class ExtendibleHash
{
private:
	Directory directory;
	std::bitset<8> hash(int k);

public:
	ExtendibleHash();
	void insert(int k);
	void remove(int k);
	bool search(int k);
	void split(int pos);
	void print();
};
std::bitset<8> ExtendibleHash::hash(int k)
{
	long long key = k % 8;
	std::bitset<8> bit(key);
	return bit;
}
ExtendibleHash::ExtendibleHash() : directory(1)
{
}
void ExtendibleHash::insert(int k)
{
	std::string bits = hash(k).to_string();
	std::string subBit = bits.substr(bits.size() - this->directory.getGlobaldepth(), this->directory.getGlobaldepth());
	int pos = std::bitset<5>(subBit).to_ulong();
	if (!this->directory.getDirectory()[pos])
	{
		this->directory.getDirectory()[pos] = new Bucket(this->directory.getGlobaldepth(), 3);
		this->directory.getDirectory()[pos]->values.push_back(k);
		std::cout<<"Key: " << k << " inserted succesfully" <<" at pos: "<< pos << std::endl;
	}
	else if(this->directory.getDirectory()[pos])
	{
		if (!this->directory.getDirectory()[pos]->isFull())
		{
			this->directory.getDirectory()[pos]->values.push_back(k);
			std::cout << "Key: " << k << " inserted succesfully" << " at pos: " << pos << std::endl;
		}
		else
		{
			std::cout << "Bucket Overflow" << std::endl;
			std::cout << "Error inserting element " << k << std::endl;
			this->split(pos);
			this->insert(k);
		}
	}
}
void ExtendibleHash::remove(int k)
{
}
bool ExtendibleHash::search(int k)
{
	std::string bits = hash(k).to_string();
	std::string subBit = bits.substr(bits.size() - this->directory.getGlobaldepth(), this->directory.getGlobaldepth());
	int pos = std::bitset<5>(subBit).to_ulong();
	for (auto val : this->directory.getDirectory()[pos]->values)
	{
		if (val == k)
		{
			return true;
		}
	}
	return false;
}
void ExtendibleHash::split(int pos)
{
	if (this->directory.getGlobaldepth() == this->directory.getDirectory()[pos]->getLocaldepth())
	{
  		this->directory.grow();
		std::vector<int> temp = this->directory.getDirectory()[pos]->values;
		this->directory.getDirectory()[pos]->values.clear();
		for (std::vector<int>::iterator it = temp.begin(); it != temp.end(); it++)
		{
			this->insert((*it));
		}
	}
	else if (this->directory.getGlobaldepth() > this->directory.getDirectory()[pos]->getLocaldepth())
	{

	}
}
void ExtendibleHash::print()
{
	for (long long unsigned int i = 0; i < this->directory.getDirectory().size(); i++)
	{
		if(this->directory.getDirectory()[i])
			if (!this->directory.getDirectory()[i]->values.empty())
			{
				for (long long unsigned int j = 0; j < this->directory.getDirectory()[i]->values.size(); j++)
					std::cout << "Position: " << i << "-->" << this->directory.getDirectory()[i]->values[j] << std::endl;
			}
	}
}
#endif // !EXTENDIBLEHASH_H