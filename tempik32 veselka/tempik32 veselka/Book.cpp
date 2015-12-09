#include "Book.h"

Book::Book(std::string publ, std::string auth, std::string _name, int _price, bool _isNew)
: publication(std::move(publ)), author(std::move(auth)), Item(_name, _price, _isNew) {}

Book::Book(Book &&b) : Item(b.name, b.price, b.isNew), publication(std::move(b.publication)), author(std::move(b.author)) {}

void Book::setPublication(std::string publ)
{
	publication = std::move(publ);
}

void Book::setAuthor(std::string auth)
{
	author = std::move(auth);
}

const std::string & Book::getPublication() const
{
	return publication;
}
const std::string & Book::getAuthor() const
{
	return author;
}

std::ostream & operator<<(std::ostream & os, const Book & i)
{
	// os << "Book:\n";
	os << "name: " << i.name << ", price: " << (i.price / 100) << '.' << (i.price % 100) << " USD, ";
	os << (i.isNew ? "new" : "pre-owned") << std::endl;
	os << "author: " << i.author << ", publisher: " << i.publication;
	return os;
}

