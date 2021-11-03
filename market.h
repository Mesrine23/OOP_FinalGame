#pragma once
#include <iostream>
#include <string>
#include "items.h"
#include "spells.h"
#include "living.h"

using namespace std;

class Market{
    private:
        Weapon **weapons; 
        Armor **armors;
        Potion **potions;
        IceSpell **iceSpells;
        FireSpell **fireSpells;
        LightingSpell **lightSpells;
    public:
        Market(Weapon** wp, Armor** arm, Potion** pot, IceSpell** ice, FireSpell** fire, LightingSpell** light) : weapons(wp), armors(arm), potions(pot), iceSpells(ice), fireSpells(fire), lightSpells(light)
        { /*cout << "Market Constructed!" << endl;*/ }
        void open(Hero* hero);
        void print();
        void printItems();
        void printSpells();
        //void print(string type);
        Weapon* buyWeapon(int i, Hero* hero);
        Armor* buyArmor(int i, Hero* hero);
        Potion* buyPotion(int i, Hero* hero, int& quant);
        IceSpell* buyIce(int i, Hero* hero);
        FireSpell* buyFire(int i, Hero* hero);
        LightingSpell* buyLight(int i, Hero* hero);
};