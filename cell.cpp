#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "spells.h"
#include "living.h"
#include "fight.h"
#include "items.h"
#include "cell.h"

unsigned Cell::hi=0;
unsigned Cell::hj=0;


void Cell::print(){
    if(type==1){
        if(hero==1){
            cout << "|";
            cout << "(P)";
        }else{
            cout << "|   ";
        }
    }else if(type==2){
        if(hero==1){
            cout << "|M/P"; 
        }else{
            cout << "| M ";
        }
    }else if(type==3){
            cout << "XXXX"; 
    }
}

void printmap(Cell*** map, unsigned SIZE_OF_MAP){
    system("clear");
    cout << endl;
    cout << endl;
    cout << endl;
    for(int i=0; i<SIZE_OF_MAP; i++){
        cout << "\t" ;
        for(int j=0; j<SIZE_OF_MAP; j++){
            map[i][j]->print();
        }
        cout << endl;
    }
    cout << endl;
}

unsigned Cell::gettype(){
    return type;
}

void Cell::changetype(unsigned n){
    type=n;
}

void Cell::changehero0(){
    hero=0;
}

void Cell::changehero1(unsigned i, unsigned j){
    hero=1;
    hi=i;
    hj=j;
}

void Cell::getij(unsigned& i, unsigned&j){
    i=hi;
    j=hj;
}

unsigned moving(Cell*** map,string m){
    unsigned hi,hj;
    map[0][0]->getij(hi,hj);
    if(m=="s" || m=="S")
    {
        if(map[hi+1][hj]->gettype()==3)
        {
            cout << "Can't go there" << endl;
            sleep(1);
            return 1;

        }else{
            map[hi][hj]->changehero0();
            map[hi+1][hj]->changehero1(hi+1,hj);
            return 0;
        }
    }
    else if(m=="w" || m=="W")
    {
        if(map[hi-1][hj]->gettype()==3)
        {
            cout << "Can't go there" << endl;
            return 1;

        }else{
            map[hi][hj]->changehero0();
            map[hi-1][hj]->changehero1(hi-1,hj);
            return 0;
        }
    }
    else if(m=="A" || m=="a")
    {
        if(map[hi][hj-1]->gettype()==3)
        {
            cout << "Can't go there" << endl;
            return 1;

        }else{
            map[hi][hj]->changehero0();
            map[hi][hj-1]->changehero1(hi,hj-1);
            return 0;
        }
    }
    else
    {
        if(map[hi][hj+1]->gettype()==3)
        {
            cout << "Can't go there" << endl;
            return 1;

        }else{
            map[hi][hj]->changehero0();
            map[hi][hj+1]->changehero1(hi,hj+1);
            return 0;
        }
    }
}