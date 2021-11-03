#include "items.h"
#include "spells.h"
#include "living.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Weapon** CreateWeapons()
{
    Weapon** weap = new Weapon*[15];
    //Weapon(NAME , PRICE , LEVEL , DAMAGE , HANDS , TYPE)
    weap[0] = new Weapon("Sword", 20 , 2 , 20 , 1 , 1); // + strength
    weap[1] = new Weapon("DualSword", 45 , 4 , 60 , 2 , 1); // ++ strength
    weap[2] = new Weapon("Catalyst", 20 , 2 , 20 , 1 , 2); // + dexterity
    weap[3] = new Weapon("DualCatalyst", 45 , 4 , 60 , 2 , 2); // ++ dexterity
    weap[4] = new Weapon("Escapist", 20 , 2 , 10 , 1 , 3); // + agility
    weap[5] = new Weapon("Dodger", 45 , 4 , 25 , 20 , 3); // ++ agility
    weap[6] = new Weapon("Katana", 30 , 3 , 20 , 1 , 4 , 5); // + strength|agility
    weap[7] = new Weapon("Niten Ichi-ryu", 50 , 4 , 45 , 2 , 4 , 10); // ++ strength|agility
    weap[8] = new Weapon("Zweihander", 60 , 7 , 65 , 2 , 4 , 15); // +++ strength|agility
    weap[9] = new Weapon("Nirvana", 30 , 3 , 20 , 1 , 5 , 5); // + dexterity|agility
    weap[10] = new Weapon("MiracleRod", 50 , 5 , 45 , 2 , 5 , 10); // ++ dexterity|agility
    weap[11] = new Weapon("Sheen" , 60 , 7 , 65 , 2 , 5 , 15); // +++ dexterity|agility
    weap[12] = new Weapon("Excalibur" , 30 , 3 , 20 , 1 , 6 , 5); // + strength|dexterity
    weap[13] = new Weapon("SoulEater" , 50 , 5 , 45 , 2 , 6 , 10); // ++ strength|dexterity
    weap[14] = new Weapon("Cthulhu" , 60 , 7 , 65 , 2 , 6 , 15); // +++ strength|dexterity

    //cout << "Weapons Created!" << endl;
    return weap;
}

Armor** CreateArmors()
{
    Armor** arms = new Armor*[8];
    //Armor(NAME , PRICE , LEVEL , REDUCTION)
    arms[0] = new Armor("Armor2" , 10 , 2 , 8);
    arms[1] = new Armor("Armor3" , 20 , 2 , 16);
    arms[2] = new Armor("Armor4" , 30 , 2 , 24);
    arms[3] = new Armor("Armor5" , 40 , 2 , 32);
    arms[4] = new Armor("Armor6" , 50 , 2 , 40);
    arms[5] = new Armor("Armor7" , 60 , 2 , 48); 
    arms[6] = new Armor("Armor8" , 65 , 2 , 56);
    arms[7] = new Armor("Armor9" , 70 , 2 , 64);

    //cout << "Armor Created!" << endl;
    return arms;
}

Potion** CreatePotions()
{
    Potion** pot = new Potion*[13];
    //Potion(NAME , PRICE , LEVEL , BOOST, TYPE)
    pot[0] = new Potion("Heal", 15 , 1 , 20 , "Health");
    pot[1] = new Potion("MegaHeal", 35 , 1 , 50 , "Health");
    pot[2] = new Potion("Elixir", 15 , 1 , 20 , "Energy");
    pot[3] = new Potion("MegaElixir", 35 , 5 , 50 , "Energy");
    pot[4] = new Potion("Power", 20 , 1 , 10 , "Strength");
    pot[5] = new Potion("SuperPower", 40 , 4 , 20 , "Strength");
    pot[6] = new Potion("HyperPower", 50 , 6 , 30 , "Strength");
    pot[7] = new Potion("Magic", 20 , 1 , 10 , "Dexterity");
    pot[8] = new Potion("SuperMagic", 40 , 4 , 20 , "Dexterity");
    pot[9] = new Potion("HyperMagic", 50 , 6 , 30 , "Dexterity");
    pot[10] = new Potion("Dodge", 20 , 1 , 10 , "Agility");
    pot[11] = new Potion("SuperDodge", 40 , 4 , 20 , "Agility");
    pot[12] = new Potion("HyperDodge", 50 , 6 , 40 , "Agility");
   
    //cout << "Potions Created!" << endl;
    return pot;
}

void Weapon::print()
{
    cout << this->name << " | " << this->price << "$ | " << this->minLVL << " Level | ";
    if (this->type == 1)
        cout << this->Str << " Strength | ";
    else if (this->type == 2)
        cout << this->Dext << " Dexterity | ";
    else if (this->type == 3)
        cout << this->Agil << " Agility | ";
    else if (this->type == 4)
        cout << this->Str << " Strength & " << this->Agil << " Agility | ";
    else if (this->type == 5)
        cout << this->Dext << " Dexterity & " << this->Agil << " Agility | ";
    else 
        cout << this->Str << " Strength & " << this->Dext << " Dexterity | ";
    
    if(this->hands==1)
        cout << "1 Hand" << endl;
    else
        cout << "2 Hands" << endl;
}

void Armor::print()
{
    cout << this->name << " | " << this->price << "$ | " << this->minLVL << " Level | " << this->dmgREDUX << " Resist" << endl;
}

void Potion::print()
{
    cout << this->name << " | " << this->price << "$ | " << this->minLVL << " Level | " << this->boost;
    if(this->type=="Health")
        cout << " Health" << endl;
    else if(this->type=="Energy")
        cout << " Energy" << endl;
    else if(this->type=="Strength")
        cout << " Strength" << endl;
    else if(this->type=="Dexterity")
        cout << " Dexterity" << endl;
    else if (this->type=="Agility")
        cout << " Agility" << endl;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int Item::getLVL()
{ return this->minLVL; }

int Item::getPrice()
{ return this->price; }

string Item::getName()
{ return this->name; }

/*void Item::setHalfPrice()
{ this->price = (this->price)/2; }*/

int Weapon::getHands()
{ return this->hands; }

int Armor::getREDUX()
{ return this->dmgREDUX; }

int Weapon::getSTR()
{ return this->Str; }

int Weapon::getDEXT()
{ return this->Dext; }

int Weapon::getAGIL()
{ return this->Agil; }

void Potion::fprint(){
    cout <<" " << this->name << " | " << this->type << " +"  << this->boost << " | ";
}

string Potion::gettype(){
    return type;
}

unsigned Potion::getboost(){
    return boost;
}

