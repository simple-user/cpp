#pragma once
#include <string>
#include <array>

enum Owner { BOSS, BOOKER, CLERK, STUDENT, PUPIL, CHILD, BABY };

class Document
{
public:
	Document() {};
	Document(std::string dn, size_t s, Owner ow) : name(dn), size(s), owner(ow) {};

	const std::string & getName()
	{
		return name;
	}

	size_t getSize()
	{
		return size;
	}

	Owner getOwner()
	{
		return owner;
	}

	friend bool operator < (const Document &doc1, const Document &doc2)
	{
		return doc1.owner > doc2.owner;
	}

	friend bool operator > (const Document &doc1, const Document &doc2)
	{
		return doc1.owner < doc2.owner;
	}



private:
	std::string name;
	size_t      size;
	Owner	    owner;
	
	
};

