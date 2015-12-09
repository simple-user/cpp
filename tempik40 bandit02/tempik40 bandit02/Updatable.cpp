#include "Updatable.h"

Updatable::Updatable( clock_t period )
{
	setPeriod( period );
}


clock_t	Updatable::setPeriod( clock_t period )
{
	clock_t oldPeriod = this->_clcPeriod;

	checkPeriod( period );
	this->_clcPeriod = period;
	this->_clcNextAction = clock() + period;

	return oldPeriod;
}


clock_t	Updatable::getPeriod()
{
	return this->_clcPeriod;
}


// повертає true, якщо настав час діяти, і визначає момент наступної дії
bool Updatable::isTimeToAction()
{

	if( clock() >= this->_clcNextAction )
	{
		this->_clcNextAction += this->_clcPeriod;
		return true;
	}

	return false;
}


void Updatable::checkPeriod(clock_t period)
{
	if (period < 2)
		throw std::invalid_argument(std::string("ERROR: Period must be more than 2 -- Updatable( ") + std::to_string(period) + ")");
}

