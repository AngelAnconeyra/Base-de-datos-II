#ifndef BUCKET_H
#define BUCKET_H

#include <iostream>
#include <map>
#include <vector>
class Bucket
{
private:
	int local_depth;
	std::vector<int> values;
	int size;
	friend class ExtendibleHash;
	friend class Directory;
public:
	Bucket(int depth, int max_size);
	void setLocaldepth(int depth);
	int& getLocaldepth();
	bool isFull();
	void clear();
};
Bucket::Bucket(int depth, int max_size) : local_depth(depth), size(max_size)
{
}
void Bucket::setLocaldepth(int depth)
{
	this->local_depth = depth;
}
int& Bucket::getLocaldepth()
{
	return this->local_depth;
}
bool Bucket::isFull()
{
	if (this->values.size() == this->size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Bucket::clear()
{
	this->values.clear();
}

#endif // !BUCKET_H

