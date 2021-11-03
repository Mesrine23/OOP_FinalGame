#pragma once
#include <iostream>
#include <string>
#include "items.h"
#include "spells.h"
using namespace std;

void createHero(unsigned &);

class Living{
    protected:
        string name;
        unsigned level;
        unsigned healthPower;
    public:
        Living(string n, unsigned lvl, unsigned health) : name(n) , level(lvl) , healthPower(health)
        {
                cout << "Living created not lvl" << endl;
                //cout << level<< endl;
                //cout << healthPower << endl;
            }
        Living(string n)
            :name(n),level(1),healthPower(100){
                cout << "Living created" << endl;
                //cout << level<< endl;
                //cout << healthPower << endl;
            }
        Living(int lvl=1, int health=100)
            :level(lvl),healthPower(health){
                //cout << "Created nothing" << endl;
            }
        int getlvl();
        string getname();
        int gethealth();
        unsigned getlevel();
};


class Monster: public Living{
    protected:
        unsigned dmgmax;
        unsigned dmgmin;
        unsigned armor;
        unsigned dodge;
        unsigned rounds[3];
        unsigned redux[3];
        unsigned redux2=0;
        unsigned flag[3];
    public:
        Monster(unsigned max, unsigned min ,unsigned ar ,unsigned dog)
            :Living(),dmgmax(max),dmgmin(min), armor(ar), dodge(dog){

                cout << "Monster created " << endl;
            }
        Monster(){}
    virtual void print(){};
    void printhealth();
    void changehealth(unsigned,unsigned);
    void getdmg(unsigned&);
    unsigned truehealth(Spell*,unsigned,unsigned);
    void setlow(unsigned,unsigned,unsigned);
    unsigned getf();
    void changelow();
    unsigned checkeff(unsigned);
    void resetspell(unsigned);
};

class Hero: public Living {
    protected:
        unsigned magicPower;
        unsigned strenght;
        unsigned dexterity;
        unsigned agility;
        unsigned xp;
        unsigned gold;
        unsigned armor;
        unsigned fdead;
        unsigned curwep;
        unsigned curarmor;
        unsigned curpot;
        unsigned curspells;
        unsigned maxap;
        Weapon* usableWeap1;
        Weapon* usableWeap2;
        Armor* usableArm;
        Weapon* weapon[15];
        Armor* armorr[8];
        Potion* potion[13];
        unsigned npots[13];
        unsigned pots[3];
        Spell* spells[15];
        static unsigned deaths;
    public:
        Hero(unsigned ap, unsigned ad, unsigned dex, unsigned ag)
            :Living(),magicPower(ap), strenght(ad), dexterity(dex), agility(ag), xp(0), gold(100), armor(0),fdead(0),
                      curwep(0),curarmor(0),curpot(0),curspells(0),maxap(ap){
                          for(int i=0; i<3; i++){
                              pots[i]=0;
                          }
                //cout << "Hero created" << endl;
            }
        unsigned getattack();
        void changehealth(unsigned);
        void levelup();
        void dead();
        unsigned getdead();
        unsigned getcurpot();
        unsigned getcurspells();
        void printspells(int);
        unsigned getgold();
        void setspell(Spell*);
        unsigned checkspell(unsigned);
        void spellstats(unsigned,unsigned&,unsigned&);
        unsigned getenerg(unsigned);
        unsigned getmana();
        unsigned spell(Monster*,unsigned,unsigned);
        void setmana(unsigned);
        void deadhp();
        void deadgold();
        void regen();
        void setpot(Potion*);
        unsigned pothero();
        unsigned usepot(unsigned);
        void death();
        unsigned getdeath();
        unsigned getpot(unsigned);
        void changepot(unsigned);
        void printstats();
        void setgold(int g);
        void goldredux(int i);
        void giveWeapon(Weapon* weap);
        void giveArmor(Armor* arm);
        void givePotion(Potion* pot, int quant);
        void giveSpell(Spell* sp);
        void checkInventory();
        void sellWeap();
        void sellArm();
        void sellPot();
        void sellSp();
        void equip();
        void equip(Weapon* weap);
        void equip(Armor* arm);
        virtual void printclas() =0;
};

//base stats 10
class Warrior: public Hero{
    public:
        Warrior()
            :Hero(80,42,18,8){
                //cout << "Warrior created" << endl;
                string n;
                cout << "Enter the name of your character" << endl;
                cin >> n;
                name = n;
                //cout << name << " " << magicPower << " " <<strenght << " " <<dexterity <<" " << agility <<" " << xp <<" " << gold << endl;
            }
        void printclas(){
            cout << "Warrior" << endl;
        }
};

class Sorcerer: public Hero{
    public:
        Sorcerer()
            :Hero(100,35,40,4){
                //cout << "Sorcerer created" << endl;
                string n;
                cout << "Enter the name of your character" << endl;
                cin >> n;
                name = n;
                //cout << name << " " << magicPower << " " <<strenght << " " <<dexterity <<" " << agility <<" " << xp <<" " << gold << endl;
            }
        void printclas(){
            cout << "Sorcerer" << endl;
        }
};

class Paladin: public Hero{
    public:
        Paladin()
            :Hero(80,42,30,4){
                //cout << "Paladin created" << endl;
                string n;
                cout << "Enter the name of your character" << endl;
                cin >> n;
                name = n;
                //cout << name << " "  << magicPower << " " <<strenght << " " <<dexterity <<" " << agility <<" " << xp <<" " << gold << endl;
            }
        void printclas(){
            cout << "Paladin" << endl;
        }
};

//stats lvl*10?


class Dragon: public Monster{
    public:
        Dragon(int lvl, int n)
            {
                name="Drake";
                level=lvl;
                healthPower=30*n+5*lvl+70*lvl*n;
                dmgmax=20+12*lvl+8*(n+lvl);
                dmgmin=dmgmax*2/3;
                armor=n + 2*lvl/2;
                dodge=lvl*n*2 +3;
                for(int i=0;i <3 ; i++){
                    rounds[i]=0;
                    redux[i]=0;
                    flag[i]=0;
                }
                //cout << "Dragon created" << endl;
                //cout << level << " " << healthPower << " " << dmgmax << " " << dmgmin << " " << armor << " " << dodge << endl;
            }
};

class Exoskeleton: public Monster{
    public:
        Exoskeleton(int lvl, int n)
            {
                name="Exo";
                level=lvl;
                healthPower=30*n+5*lvl+70*lvl*n;
                dmgmax=20+8*lvl+7*(n+lvl);
                dmgmin=dmgmax*2/3;
                armor=n + 2*lvl;
                dodge=lvl*n +3;
                for(int i=0;i <3 ; i++){
                    rounds[i]=0;
                    redux[i]=0;
                    flag[i]=0;
                }
               // cout << "Exoskeleton created" << endl;
                //cout << level << " " << healthPower << " " << dmgmax << " " << dmgmin << " " << armor << " " << dodge << endl;
            }
};

class Spirit: public Monster{
    public:
        Spirit(int lvl, int n)
            {
                name="Spirit";
                level=lvl;
                healthPower=30*n+5*lvl+70*lvl*n;
                dmgmax=20+8*lvl+7*(n+lvl);
                dmgmin=dmgmax*2/3;
                armor=n + 2*lvl/2;
                dodge=(3*lvl*n+3*lvl-4)/2 +3;
                for(int i=0;i <3 ; i++){
                    rounds[i]=0;
                    redux[i]=0;
                    flag[i]=0;
                }
                //cout << "Spirit created" << endl;
                //cout << level << " " << healthPower << " " << dmgmax << " " << dmgmin << " " << armor << " " << dodge << endl;
            }
};
