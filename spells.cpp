#include "items.h"
#include "spells.h"
#include "living.h"
#include <iostream>
#include <string>

using namespace std;

IceSpell** CreateIceSpell()
{
    IceSpell** ice = new IceSpell*[5];
    //IceSpell(NAME , PRICE , LEVEL , dmgMIN , dmgMAX , ENERGY , REDUX , ROUNDS)
    ice[0] = new IceSpell("Freeze" , 10 , 1 , 15 , 25 , 15 , 10 , 3);
    ice[1] = new IceSpell("Wave" , 25 , 2 , 25 , 40 , 25 , 15 , 3);
    ice[2] = new IceSpell("Frostbite" , 40 , 4 , 40 , 65 , 30 , 20 , 2);
    ice[3] = new IceSpell("Tsunami" , 50 , 5 , 65 , 85 , 40 , 23 , 2);
    ice[4] = new IceSpell("Blizzard" , 60 , 7 , 85 , 110 , 50 , 25 , 2);

    //cout << "Ice Spells Created!" << endl;
    return ice;
}

FireSpell** CreateFireSpell()
{
    FireSpell** fire = new FireSpell*[5];
    //FireSpell(NAME , PRICE , LEVEL , dmgMIN , dmgMAX , ENERGY , REDUX , ROUNDS)
    fire[0] = new FireSpell("Flame" , 10 , 1 , 15 , 25 , 15 , 10 , 3);
    fire[1] = new FireSpell("Fireball" , 25 , 2 , 25 , 40 , 25 , 15 , 3);
    fire[2] = new FireSpell("Explosion" , 40 , 4 , 40 , 65 , 30 , 20 , 2);
    fire[3] = new FireSpell("Flamethrower" , 50 , 5 , 65 , 85 , 40 , 23 , 2);
    fire[4] = new FireSpell("Inferno" , 60 , 7 , 85 , 110 , 50 , 25 , 2);

    //cout << "Fire Spells Created!" << endl;
    return fire;
}

LightingSpell** CreateLightingSpell()
{
    LightingSpell** light = new LightingSpell*[5];
    //LightingSpell(NAME , PRICE , LEVEL , dmgMIN , dmgMAX , ENERGY , REDUX , ROUNDS)
    light[0] = new LightingSpell("Spark" , 10 , 1 , 15 , 25 , 15 , 10 , 3);
    light[1] = new LightingSpell("Pika" , 25 , 2 , 25 , 40 , 25 , 15 , 3);
    light[2] = new LightingSpell("Beam" , 40 , 4 , 40 , 65 , 30 , 20 , 2);
    light[3] = new LightingSpell("Thunder" , 50 , 5 , 65 , 85 , 40 , 23 , 2);
    light[4] = new LightingSpell("Thunderbolt" , 60 , 7 , 85 , 110 , 50 , 25 , 2);

    //cout << "Lighting Spells Created!" << endl;
    return light;
}

void IceSpell::print()
{
    cout << this->name << " | " << this->price << "$ | " << this->minLVL << " Level |  Damage Range (" << this->mindmg << "," << this->maxdmg << ") | " << this->energy << " Energy | " << this->redux << " Damage Reduction | " << this->rounds << " Rounds" << endl; 
}

void IceSpell::fprint(){
    cout << "IceSpell " << this->name << " | Damage Range (" << this->mindmg << "," << this->maxdmg << ") | " << this->energy << " Energy | " << this->redux << " Damage Reduction | " << this->rounds << " Rounds" << endl;
}

void FireSpell::print()
{
    cout << this->name << " | " << this->price << "$ | " << this->minLVL << " Level | Damage Range (" << this->mindmg << "," << this->maxdmg << ") | " << this->energy << " Energy | " << this->redux << " Armor Reduction | " << this->rounds << " Rounds" << endl; 
}

void FireSpell::fprint(){
    cout << "FireSpell " << this->name << " | Damage Range (" << this->mindmg << "," << this->maxdmg << ") | " << this->energy << " Energy | " << this->redux << " Armor Reduction | " << this->rounds << " Rounds" << endl;
}
void LightingSpell::print()
{
    cout << this->name << " | " << this->price << "$ | " << this->minLVL << " Level | Damage Range (" << this->mindmg << "," << this->maxdmg << ") | " << this->energy << " Energy | " << this->redux << " Agility Reduction | " << this->rounds << " Rounds" << endl; 
}

void LightingSpell::fprint(){
    cout << "LightingSpell " << this->name << " | Damage Range (" << this->mindmg << "," << this->maxdmg << ") | " << this->energy << " Energy | " << this->redux << " Agility Reduction | " << this->rounds << " Rounds" << endl;
}

unsigned IceSpell::type(){
    return 2;
}

unsigned FireSpell::type(){
    return 1;
}

unsigned LightingSpell::type(){
    return 3;
}

unsigned Spell::getenergy(){
    return energy;
}


void Spell::getdmg(unsigned& max,unsigned& min){
    max=maxdmg;
    min=mindmg;
}

void FireSpell::getstats(unsigned& re, unsigned& rou){
    re=redux;
    rou=rounds;
}

void IceSpell::getstats(unsigned& re, unsigned& rou){
    re=redux;
    rou=rounds;
}

void LightingSpell::getstats(unsigned& re, unsigned& rou){
    re=redux;
    rou=rounds;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int Spell::getLVL()
{ return this->minLVL; }

int Spell::getPrice()
{ return this->price; }

string Spell::getName()
{ return this->name; }

/*void Spell::setHalfPrice()
{ this->price = (this->price)/2; }*/