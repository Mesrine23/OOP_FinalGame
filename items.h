#pragma once
#include <string>
#include <iostream>

using namespace std;



class Item {
    protected:
        string name;
        int price;
        int minLVL;
    public:
        Item(string nam, int prc, int lvl) : name(nam) , price(prc) , minLVL(lvl)
        { /*cout << "Item created" << endl;*/ };
        virtual void print() = 0;
        int getLVL();
        int getPrice();
        string getName();
        //void setHalfPrice();
};

class Weapon : public Item {
    private:
        int Str;
        int Dext; 
        int Agil;
        int hands;
        int type;
    public:
        Weapon(string nam, int prc, int lvl, int stat, int hnd, int t, int sec=0) : Item(nam , prc , lvl) , hands(hnd) , type(t)
        { 
            if(type==1)
            {
                this->Str = stat;
                this->Dext = 0;
                this->Agil = 0;
            }
            else if(type==2)
            {
                this->Str = 0;
                this->Dext = stat;
                this->Agil = 0;
            }
            else if(type==3)
            {
                this->Str = 0;
                this->Dext = 0;
                this->Agil = stat;
            }
            else if(type==4)
            {
                this->Str = stat;
                this->Dext = 0;
                this->Agil = sec;
            }
            else if(type==5)
            {
                this->Str = 0;
                this->Dext = stat;
                this->Agil = sec;
            }
            else
            {
                this->Str = stat;
                this->Dext = sec;
                this->Agil = 0;
            }
        }
        virtual void print();
        int getHands();
        int getSTR();
        int getDEXT();
        int getAGIL();
        
};

class Armor : public Item {
    private:
        int dmgREDUX;
    public:
        Armor(string nam, int prc, int lvl, int redux) : Item(nam , prc , lvl) , dmgREDUX(redux)
        { /*cout << "New Armor!\n" << endl;*/ };
        virtual void print();
        int getREDUX();
};

class Potion : public Item {
    private:
        int boost;
        string type;
    public:
        Potion(string nam, int prc, int lvl, int bst, string t) : Item(nam , prc , lvl) , boost(bst) , type(t)
        { /*cout << this->name << " -> " << this->price << " -> " << this->minLVL << " -> " << this->boost << endl;*/ };
        virtual void print();
        void fprint(); // ars
        string gettype(); // ars 
        unsigned getboost(); // ars
};

Weapon** CreateWeapons();
Armor** CreateArmors();
Potion** CreatePotions();