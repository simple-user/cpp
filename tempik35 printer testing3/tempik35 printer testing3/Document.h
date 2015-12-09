#pragma once
#include <string>
#include <array>

enum Owner { BOSS, BOOKER, CLERK, STUDENT, PUPIL, CHILD, BABY };

class Document
{
public:
	Document() {};
	Document(std::string dn, size_t s, Owner ow) : name(dn), size(s), owner(ow) {};

	const std::string & getName() const
	{
		return name;
	}

	size_t getSize() const
	{
		return size;
	}

	Owner getOwner() const
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

