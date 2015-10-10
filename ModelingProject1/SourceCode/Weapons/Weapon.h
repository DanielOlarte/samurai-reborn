#pragma once

namespace Weapons
{
  class Weapon
  {
    public:
     Weapon(int valueDamage);
     ~Weapon(void);

	 int getDamage() { return damage; }

    private:
     int damage;
  };
}
