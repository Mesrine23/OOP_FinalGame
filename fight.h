#pragma once
#include <iostream>
#include <string>
#include "living.h"
using namespace std;

void fight(Hero**,unsigned);
void attackhero(Hero*,Monster*,unsigned&);
void attackmonster(Hero*,Monster*,unsigned&);
void victory(Hero**,unsigned);
unsigned spellhero(Hero*,Monster*,unsigned&);
unsigned damage(unsigned,unsigned);
void regen(Hero**,unsigned);
void revall(Hero**,unsigned);