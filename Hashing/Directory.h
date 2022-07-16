#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "Bucket.h"
#include <math.h>
class Directory
{
private:
	int global_depth;
	std::vector<Bucket*> dir;
	friend class ExtendibleHash;

public:
	Directory(int depth);
	void setGlobaldepth(int depth);
	int getGlobaldepth();
	std::vector<Bucket*>& getDirectory();
	void grow();
};
Directory::Directory(int depth)
{
	this->global_depth = depth;
	for (int i = 0; i < pow(2, this->global_depth); i++)
	{
		this->dir.push_back(nullptr);
	}
}
void Directory::setGlobaldepth(int depth)
{
	this->global_depth = depth;
}
int Directory::getGlobaldepth()
{
	return this->global_depth;
}
std::vector<Bucket*>& Directory::getDirectory()
{
	return this->dir;
}
void Directory::grow()
{
	this->global_depth++;
	int maximum = pow(2, global_depth) - this->dir.size();
	for (int i = 0; i < maximum; i++)
	{
		this->dir.push_back(nullptr);
	}
}
#endif