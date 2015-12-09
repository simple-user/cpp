#include "Audio.h"

Audio::Audio(std::string _songer, int cTrack, std::string _name, int _price, bool _isNew)
: songer(std::move(_songer)), countTrack(cTrack), Item(_name, _price, _isNew) {}

Audio::Audio(Audio &&a) : Item(a.name, a.price, a.isNew), songer(std::move(a.songer)), countTrack(a.countTrack) {}


void Audio::setSonger(std::string _songer)
{
	songer = std::move(_songer);
}

void Audio::setCountTrack(int cTrack)
{
	if (cTrack <= 0)
		throw std::invalid_argument("Count of tracks below one!");
	countTrack = cTrack;
}

const std::string & Audio::getSonger() const
{
	return songer;
}

int Audio::getCountTrack() const
{
	return countTrack;
}


std::ostream & operator<<(std::ostream & os, const Audio & i)
{
	// os << "Audio:\n";
	os << "name: " << i.name << ", price: " << (i.price / 100) << '.' << (i.price % 100) << " USD, ";
	os << (i.isNew ? "new" : "pre-owned") << std::endl;
	os << "songer: " << i.songer << ' ' << i.countTrack << " tracks,";
	return os;
}

