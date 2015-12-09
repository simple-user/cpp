#include <iostream>

class Shooter
{
public:
	
	Shooter() : ammoCount(0)
	{	
		std::cout << "c-tor of Sooter! \n";
	}
	
	bool shoot()
	{
		if (ammoCount)
		{
			std::cout << "Shoot with " << name << std::endl;
			ammoCount--;
			return 1;
		}
		std::cout << "We have no ammo!" << std::endl;
		return 0;
	}

	void takeAmmunition(int _count, const char *_name)
	{
		ammoCount += _count;
		strcpy_s(name, _name);
	}

	const char * getName()
	{
		return name;
	}

private:
	char name[20];
	int ammoCount;
};

class Archer : virtual protected Shooter
{
public:
	Archer() {std::cout << "c-tor of Archer! \n";	}

	bool shoot()
	{
		if (Shooter::shoot())
		{
			std::cout << "Shoot was made by Archer" << std::endl;
			return 1;
		}
		return 0;
	}


};

class Ranger : virtual protected Shooter
{
public:
	Ranger() { std::cout << "c-tor of Ranger! \n"; }

	bool shoot()
	{
		if (Shooter::shoot())
		{
			std::cout << "Shoot was made by Ranger" << std::endl;
			return 1;
		}
		return 0;
	}

};

class Catapult : protected Shooter
{
public:
	Catapult() {std::cout << "c-tor of Catapult! \n";	}

	bool shoot()
	{
		if (Shooter::shoot())
		{
			std::cout << "Shoot was made by Catapult" << std::endl;
			return 1;
		}
		return 0;
	}

};

class ArcherTower : protected Archer, protected Ranger
{
public:
	ArcherTower() { std::cout << "c-tor of ArcherTower! \n"; }
	bool shoot()
	{
		std::cout << "ArcherTower try to shoot:" << std::endl;
		if (Archer::shoot() && Ranger::shoot())
			return 1;
		else
			return 0;
	}
};

class Fortress : protected ArcherTower, protected Catapult
{
public:
	Fortress(int countArrow, int countRock) 
	{ 
		std::cout << "c-tor of Fortress! \n";
		ArcherTower::takeAmmunition(countArrow, "arrow");
		Catapult::takeAmmunition(countRock, "rock");
	}

	bool shoot()
	{
		std::cout << "Fortress try to shoot:" << std::endl;
		bool b1 = ArcherTower::shoot(), b2 = Catapult::shoot();
		if ( b1 || b2 )
		{
			std::cout << "Fortress hoot comlpete! \n\n";
			return 1;
		}
		else
			return 0;

	}
};