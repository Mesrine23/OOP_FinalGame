#pragma once
#include <string>
#include <iostream>

using namespace std;

class Spell {
    protected:
        string name;
        int price;
        int minLVL;
        int maxdmg;
        int mindmg;
        int energy;
    public:
        Spell(string nam, int prc, int lvl, int min, int max, int nrg) : name(nam),price(prc),minLVL(lvl),maxdmg(max),mindmg(min),energy(nrg)
        {};
        virtual void print() = 0;
        int getLVL();
        int getPrice();
        string getName();
        virtual void fprint()=0; // ars
        virtual unsigned type()=0; // ars
        unsigned getenergy(); // ars
        void getdmg(unsigned&,unsigned&); // ars
        virtual void getstats(unsigned&,unsigned&)=0; // ars
};

class IceSpell : public Spell {
    private:
        int redux;
        int rounds;
    public:
        IceSpell(string nam, int prc, int lvl, int min, int max, int nrg, int redx, int rnds) : Spell(nam , prc , lvl , min , max , nrg) , redux(redx) , rounds(rnds)
        { /*cout << "New IceSpell!\n" << endl;*/ };
        virtual void print();
        virtual void fprint(); //ars
        virtual unsigned type(); // ars
        void getstats(unsigned&,unsigned&); //ars
};

class FireSpell : public Spell {
    private:
        int redux;
        int rounds;
    public:
        FireSpell(string nam, int prc, int lvl, int min, int max, int nrg, int armor, int rnds) : Spell(nam , prc , lvl , min , max , nrg) , redux(armor) , rounds(rnds)
        { /*cout << "New FireSpell!\n" << endl;*/ };
        virtual void print();
        virtual void fprint(); // ars
        virtual unsigned type(); //ars
        void getstats(unsigned&,unsigned&); //ars
};

class LightingSpell : public Spell {
    private:
        int redux;
        int rounds;
    public:
        LightingSpell(string nam, int prc, int lvl, int min, int max, int nrg, int agility, int rnds) : Spell(nam , prc , lvl , min , max , nrg) , redux(agility) , rounds(rnds)
        { /*cout << "New LightingSpell!\n" << endl;*/ };
        virtual void print();
        virtual void fprint(); // ars
        virtual unsigned type(); // ars
        void getstats(unsigned&,unsigned&); // ars
};

IceSpell** CreateIceSpell();
FireSpell** CreateFireSpell();
LightingSpell** CreateLightingSpell();