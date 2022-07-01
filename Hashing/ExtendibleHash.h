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
	void search(int k);
};
std::bitset<8> ExtendibleHash::hash(int k)
{
	long long key = k % 8;
	std::bitset<8> bit(key);
	return bit;
}
ExtendibleHash::ExtendibleHash(): directory(1)
{
	for (int i = 0; i < pow(2, this->directory.getGlobaldepth()); i++)
	{
		this->directory.getDirectory().push_back(new Bucket(1,3));
	}
}
void ExtendibleHash::insert(int k)
{
	std::string bits = hash(k).to_string();
	std::string subBit = bits.substr(bits.size() - this->directory.getGlobaldepth(), this->directory.getGlobaldepth());
	for (int i = 0; i < this->directory.getDirectory().size(); i++)
	{
		if (hash(i).to_string() == subBit && !this->directory.getDirectory()[i]->isFull())
		{
			this->directory.getDirectory()[i]->values[subBit] = k;
			break;
		}
		else
		{
			break;
		}
	}
}
inline void ExtendibleHash::remove(int k)
{
}
inline void ExtendibleHash::search(int k)
{
}
#endif // !EXTENDIBLEHASH_H

