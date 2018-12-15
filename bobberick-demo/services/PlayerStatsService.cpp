#include "PlayerStatsService.h"
#include <algorithm>
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SaveService.h"

void PlayerStatsService::init()
{
	if (xp > 0)
	{
		xpTotal += xp;
		saveMeta();
	}
	xp = 0;
	shdActive = false;
	fireCooldown = 0;

	normalWeapon = WeaponComponent("", "Training Bow of Nothing", false, 5, 30, "bullet", "characterShooting");
	magicWeapon = WeaponComponent("", "Training Staff of Nothing", true, 10, 60, "bolt", "characterCasting");
	comparingWeapon = WeaponComponent("", "", false, 0, 0, "", "");

	hp = hpMax = getHPvalue(false);
	atMin = getATminValue(false);
	atMax = getATmaxValue(false);
	shdTime = shdTimeMax = getSHDvalue(false);
	shdRecov = getSHDrecovValue(false);
}

void PlayerStatsService::setStats(const int hp, const int hpMax, const int atMin, const int atMax,
                                  const double shdTime, const double shdTimeMax, const double shdRecov,
                                  const int xp)
{
	PlayerStatsService::hp = hp;
	PlayerStatsService::hpMax = hpMax;
	PlayerStatsService::atMin = atMin;
	PlayerStatsService::atMax = atMax;
	PlayerStatsService::shdTime = shdTime;
	PlayerStatsService::shdTimeMax = shdTimeMax;
	PlayerStatsService::shdRecov = shdRecov;
	PlayerStatsService::xp = xp;
}

void PlayerStatsService::setWeapons(WeaponComponent normal, WeaponComponent magic)
{
	normalWeapon = normal;
	magicWeapon = magic;
}

void PlayerStatsService::setMagicWeapon(WeaponComponent weapon)
{
	magicWeapon = weapon;
}

void PlayerStatsService::setNormalWeapon(WeaponComponent weapon)
{
	normalWeapon = weapon;
}

void PlayerStatsService::equipComparingWeapon() {
	if (compareTime > 0 && !compareConfirmed) {
			if (comparingWeapon.isMagic) {
			magicWeapon = comparingWeapon;
		} else {
			normalWeapon = comparingWeapon;
		}
		compareTime = 0;
		compareConfirmed = true;
	}
}

void PlayerStatsService::setMetaStats(const int xpTotal, const int hpLv, const int atLv,
                                      const int shdTimeLv, const int shdRecovLv)
{
	PlayerStatsService::xpTotal = xpTotal;
	PlayerStatsService::hpLv = hpLv;
	PlayerStatsService::atLv = atLv;
	PlayerStatsService::shdTimeLv = shdTimeLv;
	PlayerStatsService::shdRecovLv = shdRecovLv;
}

void PlayerStatsService::update()
{
	if (xp > 999999)
	{
		xp = 999999;
	}
	if (hp > 0)
	{
		// Shield recovery freezes when the player is dead.
		if (shdActive)
		{
			shdTime -= 1;
			if (shdTime <= 0)
			{
				shdActive = false;
			}
		}
		else
		{
			// The shield mode only recovers when inactive.
			shdTime += shdRecov;
			if (shdTime > shdTimeMax)
			{
				shdTime = shdTimeMax;
			}
		}
		if (fireCooldown > 0)
		{
			fireCooldown--;
		}
	}
	else
	{
		shdActive = false;
		shdTime = 0;
		hp = 0;
	}
	if (compareTime > 0) {
		compareTime--;
	}
}

void PlayerStatsService::getHit(double attack)
{
	if (!shdActive)
	{
		hp -= attack;
		if (hp < 0)
		{
			hp = 0;
		}
	}
}

void PlayerStatsService::heal(const int amount)
{
	hp += amount;
	if (hp > hpMax)
	{
		hp = hpMax;
	}
}

int PlayerStatsService::attack(const bool magic)
{
	if (fireCooldown <= 0)
	{
		int basePow = generator.getRandomNumber(atMin, atMax);
		if (magic)
		{
			fireCooldown = magicWeapon.fireDelay;
			return basePow + magicWeapon.power;
		}
		else
		{
			fireCooldown = normalWeapon.fireDelay;
			return basePow + normalWeapon.power;
		}
	}
	else
	{
		return -1; // Cannot fire a bullet yet.
	}
}

void PlayerStatsService::toggleShield()
{
	if (!shdActive && shdTime / shdTimeMax >= 0.5)
	{
		shdActive = true;
	}
	else if (shdActive)
	{
		shdActive = false;
	}
}

bool PlayerStatsService::upgradeHPlevel()
{
	if (getHPcost() > -1 && xpTotal >= getHPcost())
	{
		xpTotal -= getHPcost();
		hpLv++;
		init();
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerStatsService::upgradeATlevel()
{
	if (getATcost() > -1 && xpTotal >= getATcost())
	{
		xpTotal -= getATcost();
		atLv++;
		init();
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerStatsService::upgradeSHDlevel()
{
	if (getSHDcost() > -1 && xpTotal >= getSHDcost())
	{
		xpTotal -= getSHDcost();
		shdTimeLv++;
		init();
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerStatsService::upgradeSHDrecovLevel()
{
	if (getSHDrecovCost() > -1 && xpTotal >= getSHDrecovCost())
	{
		xpTotal -= getSHDrecovCost();
		shdRecovLv++;
		init();
		return true;
	}
	else
	{
		return false;
	}
}

// Getters
int PlayerStatsService::getHP() const
{
	return hp;
}

int PlayerStatsService::getHPmax() const
{
	return hpMax;
}

int PlayerStatsService::getATmin() const
{
	return atMin;
}

int PlayerStatsService::getATmax() const
{
	return atMax;
}

double PlayerStatsService::getSHD() const
{
	return shdTime;
}

int PlayerStatsService::getSHDmax() const
{
	return shdTimeMax;
}

double PlayerStatsService::getSHDrecov() const
{
	return shdRecov;
}

bool PlayerStatsService::getSHDactive() const
{
	return shdActive;
}

int PlayerStatsService::getXPtotal() const
{
	return xpTotal;
}

int PlayerStatsService::getHPlevel() const
{
	return hpLv;
}

int PlayerStatsService::getATlevel() const
{
	return atLv;
}

int PlayerStatsService::getSHDlevel() const
{
	return shdTimeLv;
}

int PlayerStatsService::getSHDrecovLevel() const
{
	return shdRecovLv;
}

int PlayerStatsService::getHPcost() const
{
	if (getHPvalue(true) != -1)
	{
		return getHPvalue(true) * 10;
	}
	else
	{
		return -1;
	}
}

int PlayerStatsService::getATcost() const
{
	if (getATminValue(true) != -1)
	{
		return static_cast<int>(pow(getATminValue(true) * 1000, 1.1));
	}
	else
	{
		return -1;
	}
}

int PlayerStatsService::getSHDcost() const
{
	if (getSHDvalue(true) != -1)
	{
		return static_cast<int>(pow((getSHDlevel() + 1) * 90, 1.6));
	}
	else
	{
		return -1;
	}
}

int PlayerStatsService::getSHDrecovCost() const
{
	if (getSHDrecovValue(true) != -1)
	{
		return static_cast<int>(pow((getSHDrecovLevel() + 1) * 120, 1.6));
	}
	else
	{
		return -1;
	}
}

int PlayerStatsService::getHPvalue(bool next) const
{
	if (!next)
	{
		return (int)std::min(100 * (pow(1.1, hpLv)), 500000.0);
	}
	else
	{
		if (getHPvalue(false) < 500000)
		{
			return (int)std::min(100 * (pow(1.1, hpLv + 1)), 500000.0);
		}
		else
		{
			return -1;
		}
	}
}

int PlayerStatsService::getATminValue(bool next) const
{
	if (!next)
	{
		return (int)std::min(pow(atLv + 1, 1.3), 400.0);
	}
	else
	{
		if (getATminValue(false) < 400)
		{
			return (int)std::min(pow(atLv + 2, 1.3), 400.0);
		}
		else
		{
			return -1;
		}
	}
}

int PlayerStatsService::getATmaxValue(bool next) const
{
	int value = getATminValue(next);
	if (value > -1)
	{
		value = static_cast<int>((value * 1.5) + 1);
	}
	return std::min(value, 600);
}

int PlayerStatsService::getSHDvalue(bool next) const
{
	if (!next)
	{
		return (int)std::min(120 + (10 * pow(shdTimeLv, 0.9)), 999.0);
	}
	else
	{
		if (getSHDvalue(false) < 999)
		{
			return (int)std::min(120 + (10 * pow(shdTimeLv + 1, 0.9)), 999.0);
		}
		else
		{
			return -1;
		}
	}
}

double PlayerStatsService::getSHDrecovValue(bool next) const
{
	if (!next)
	{
		return std::min(0.1 + ((shdRecovLv) * 0.01), 1.0);
	}
	else
	{
		if (getSHDrecovValue(false) < 1)
		{
			return std::min(0.1 + ((shdRecovLv + 1) * 0.01), 1.0);
		}
		else
		{
			return -1;
		}
	}
}

void PlayerStatsService::changeHPmax(const int amount)
{
	hpMax += amount;
	if (hpMax < 1)
	{
		hpMax = 1;
	}
	if (hpMax > 999999)
	{
		hpMax = 999999;
	}
	if (hp > hpMax)
	{
		hp = hpMax;
	}
}

void PlayerStatsService::changeATmin(const int amount)
{
	atMin += amount;
	if (atMin < 0)
	{
		atMin = 0;
	}
	if (atMin > atMax)
	{
		atMin = atMax;
	}
}

void PlayerStatsService::changeATmax(const int amount)
{
	atMax += amount;
	if (atMax < 1)
	{
		atMax = 1;
	}
	if (atMin > atMax)
	{
		atMin = atMax;
	}
}

void PlayerStatsService::setSHD(const int amount)
{
	shdTime = amount;
}

void PlayerStatsService::save()
{
	auto& save = ServiceManager::Instance()->getService<SaveService>();

	save.keep<int>("hp", getHP());
	save.keep<int>("hpMax", getHPmax());
	save.keep<int>("atMin", getATmin());
	save.keep<int>("atMax", getATmax());
	save.keep<double>("shdTime", shdTime);
	save.keep<double>("shdTimeMax", getSHDmax());
	save.keep<double>("shdRecov", getSHDrecov());
	save.keep<int>("xp", xp);

	save.keep<bool>("w1IsMagic", normalWeapon.isMagic);
	save.keep<int>("w1Power", normalWeapon.power);
	save.keep<int>("w1FireDelay", normalWeapon.fireDelay);
	save.keep<std::string>("w1BulletTexture", normalWeapon.bulletTexture);
	save.keep<std::string>("w1TextureID", normalWeapon.textureID);
	save.keep<std::string>("w1Name", normalWeapon.name);
	save.keep<std::string>("w1AttackingTextureID", normalWeapon.attackingTextureID);

	save.keep<bool>("w2IsMagic", magicWeapon.isMagic);
	save.keep<int>("w2Power", magicWeapon.power);
	save.keep<int>("w2FireDelay", magicWeapon.fireDelay);
	save.keep<std::string>("w2BulletTexture", magicWeapon.bulletTexture);
	save.keep<std::string>("w2TextureID", magicWeapon.textureID);
	save.keep<std::string>("w2Name", magicWeapon.name);
	save.keep<std::string>("w2AttackingTextureID", magicWeapon.attackingTextureID);

	save.flush();
}

void PlayerStatsService::load()
{
	auto& save = ServiceManager::Instance()->getService<SaveService>();
	save.load();

	setStats(
		save.get<int>("hp"),
		save.get<int>("hpMax"),
		save.get<int>("atMin"),
		save.get<int>("atMax"),
		save.get<double>("shdTime"),
		save.get<double>("shdTimeMax"),
		save.get<double>("shdRecov"),
		save.get<int>("xp")
	);

	normalWeapon = WeaponComponent(
		save.get<std::string>("w1TextureID"),
		save.get<std::string>("w1Name"),
		save.get<bool>("w1IsMagic"),
		save.get<int>("w1Power"),
		save.get<int>("w1FireDelay"),
		save.get<std::string>("w1BulletTexture"),
		save.get<std::string>("w1AttackingTextureID")
	);

	magicWeapon = WeaponComponent(
			save.get<std::string>("w2TextureID"),
			save.get<std::string>("w2Name"),
			save.get<bool>("w2IsMagic"),
			save.get<int>("w2Power"),
			save.get<int>("w2FireDelay"),
			save.get<std::string>("w2BulletTexture"),
			save.get<std::string>("w2AttackingTextureID")
	);
}

bool PlayerStatsService::validateSave() const
{
	auto& save = ServiceManager::Instance()->getService<SaveService>();

	return save.has("hp")
	&& save.has("hpMax")
	&& save.has("atMin")
	&& save.has("atMax")
	&& save.has("shdTimeMax")
	&& save.has("shdRecov")
	&& save.has("w1IsMagic")
	&& save.has("w1IsMagic")
	&& save.has("w1FireDelay")
	&& save.has("w1BulletTexture")
	&& save.has("w1TextureID")
	&& save.has("w1AttackingTextureID")
	&& save.has("w1Name")
	&& save.has("w2IsMagic")
	&& save.has("w2Power")
	&& save.has("w2FireDelay")
	&& save.has("w2BulletTexture")
	&& save.has("w2TextureID")
	&& save.has("w2AttackingTextureID")
   	&& save.has("w2Name");
}

void PlayerStatsService::saveMeta()
{
	auto& save = ServiceManager::Instance()->getService<SaveService>();

	save.keep<int>("xpTotal", getXPtotal());
	save.keep<int>("hpLv", getHPlevel());
	save.keep<int>("atLv", getATlevel());
	save.keep<int>("shdTimeLv", getSHDlevel());
	save.keep<int>("shdRecovLv", getSHDrecovLevel());

	save.flush();
}

void PlayerStatsService::wipeMeta()
{
	xpTotal = 0;
	hpLv = 0;
	atLv = 0;
	shdTimeLv = 0;
	shdRecovLv = 0;

	saveMeta();
}

void PlayerStatsService::loadMeta()
{
	auto& save = ServiceManager::Instance()->getService<SaveService>();
	save.load();

	setMetaStats(
		save.get<int>("xpTotal"),
		save.get<int>("hpLv"),
		save.get<int>("atLv"),
		save.get<int>("shdTimeLv"),
		save.get<int>("shdRecovLv")
	);
}

bool PlayerStatsService::validateSaveMeta() const
{
	auto& save = ServiceManager::Instance()->getService<SaveService>();

	return save.has("xpTotal")
		&& save.has("hpLv")
		&& save.has("atLv")
		&& save.has("shdTimeLv")
		&& save.has("shdRecovLv");
}