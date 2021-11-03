#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include "spells.h"
#include "living.h"
#include "fight.h"
#include "items.h"

class Cell{
    private:
        unsigned hero;
        unsigned type;
        static unsigned hi;
        static unsigned hj;
    public:
        Cell(unsigned t)
            :hero(0),type(t){
                //cout << "Cell created" << endl;
            }
        void print();
        unsigned gettype();
        void changetype(unsigned);
        void changehero1(unsigned,unsigned);
        void changehero0();
        void getij(unsigned&,unsigned&);  
};

unsigned moving(Cell***,string);
void printmap(Cell***,unsigned);