#pragma once
#include "Item.h"

class Audio : public Item
{
public:
	Audio(std::string _songer = "", int cTrack = 0, std::string _name = "", int _price = 0, bool _isNew = 0);

	// конструктор копії стандартний підходить memberwise copy
	// Audio(Audio&)

	Audio(Audio &&b);

	void setSonger(std::string _songer);
	void setCountTrack(int cTrack);

	const std::string & getSonger() const;
	int getCountTrack() const;

	friend std::ostream & operator<<(std::ostream & os, const Audio & i);
	
	// оператор присваювання дефолтний підходить memberwise copy
	// Audio& operator=(const Audio& b);

private:
	std::string songer;
	int countTrack;
};

