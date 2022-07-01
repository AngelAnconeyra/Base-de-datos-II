#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "Bucket.h"
#include <vector>
class Directory
{
private:
	int global_depth;
	std::vector<Bucket*> dir;
public:
	Directory(int depth);
	void setGlobaldepth(int depth);
	int getGlobaldepth();
	std::vector<Bucket*> getDirectory();
};
Directory::Directory(int depth) :global_depth(depth){}
void Directory::setGlobaldepth(int depth)
{
	this->global_depth = depth;
}
int Directory::getGlobaldepth()
{
	return this->global_depth;
}
std::vector<Bucket*> Directory::getDirectory()
{
	return this->dir;
}
#endif // !

