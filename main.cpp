#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include "spells.h"
#include "living.h"
#include "fight.h"
#include "items.h"
#include "cell.h"
#include "market.h"

using namespace std;

void uspo(Hero**,unsigned);

int main()
{
    Weapon **weapons = CreateWeapons();
    Armor **armors = CreateArmors();
    Potion **potions = CreatePotions();
    IceSpell **iceSpells = CreateIceSpell();
    FireSpell **fireSpells = CreateFireSpell();
    LightingSpell **lightSpells = CreateLightingSpell();
    Market market(weapons,armors,potions,iceSpells,fireSpells,lightSpells);

    system("clear");
    int SIZE_OF_MAP;
    cout << "Please enter a number from 15-40 to choose the size of your map" << endl;
    cin >> SIZE_OF_MAP;
    while(SIZE_OF_MAP<15 || SIZE_OF_MAP>40 ){
        cout << "Invalid input!" << endl;
        cout << "Please enter a number from 15-40" << endl;
        cin >> SIZE_OF_MAP;
    }
    IceSpell* freeze= new IceSpell("Freeze" , 10 , 1 , 15 , 25 , 30 , 10 , 3);
    FireSpell* fire=new FireSpell("Fireball" , 25 , 2 , 15 , 20 , 25 , 15 , 3);
    LightingSpell* light= new LightingSpell("Spark" , 10 , 1 , 15 , 25 , 15 , 10 , 3);

    Potion** pot = new Potion*[3];
    pot[0] = new Potion("Heal", 15 , 1 , 20 , "Health");
    pot[1] = new Potion("Power", 20 , 1 , 7 , "Strength");
    pot[2] = new Potion("Magic", 20 , 1 , 10 , "Dexterity");
    pot[3] = new Potion("Dodge", 20 , 1 , 6 , "Agility");
    pot[4] = new Potion("Elixir", 15 , 1 , 20 , "Energy");

    Cell*** map=new Cell**[SIZE_OF_MAP];
    for(int i=0; i<SIZE_OF_MAP; i++ ){
        map[i]= new Cell*[SIZE_OF_MAP];
    }
    long now;
    now=time(NULL);
    srand((unsigned int)now);
    unsigned r;
    int health;
    string name;
    int mana;

    for(int i=0; i<SIZE_OF_MAP; i++){
        for(int j=0; j<SIZE_OF_MAP; j++){
            map[i][j]=new Cell(1);
        }
    }

    for(int i=0; i<SIZE_OF_MAP; i++){
        for(int j=0; j<SIZE_OF_MAP; j++){
            if(i==0||i==SIZE_OF_MAP-1){
                map[i][j]->changetype(3);
            }
            else if(j==0||j==SIZE_OF_MAP-1){
                map[i][j]->changetype(3);
            }
            else{
                r=rand()%6;
                if(r==4){
                    map[i][j]->changetype(3);
                    continue;
                }else{
                    r=rand()%8;
                    if(r==3){
                        if(map[i-1][j]->gettype()!=2 && map[i][j-1]->gettype()!=2 && map[i+1][j]->gettype()!=2 
                            && map[i][j+1]->gettype()!=2 && map[i-1][j-1]->gettype()!=2 && map[i+1][j+1]->gettype()!=2 
                            && map[i+1][j-1]->gettype()!=2  && map[i-1][j+1]->gettype()!=2){
                                map[i][j]=new Cell(2);
                                continue;
                        } 
                    }
                }
            }
        }
    }
    //printmap(map,SIZE_OF_MAP);

    system("clear");
    unsigned N_HEROES;
    createHero(N_HEROES);
    Hero** hero=new Hero*[N_HEROES];
    cout << endl << "There are 3 classes: Warrior, Paladin, Sorcerer" << endl;
    cout << "Type [W] for Warrior, [P] for Paladin or [S] for Sorcerer" << endl<<endl;
    string clas;
    for(int i=1; i<=N_HEROES; i++){
        cout << "Please choose the class of your " << i << " character" << endl;
        cout << "[W/P/S] " ;
        cin >> clas;
        while(clas!="W" && clas!= "w" && clas!="P" && clas!="p" && clas!="S" && clas!="s"){
            cout << endl << "Invalid character!" << endl;
            cout << "Please type W for Warrior, P for Paladin or S for Sorcerer" << endl;
            cout << "[W/P/S] " ;
            cin >> clas;
        }
        if(clas=="W" || clas=="w"){
            cout << "Your " << i << " character is a Warrior" << endl;
            hero[i-1]= new Warrior;
            /*hero[i-1]->setspell(freeze);
            hero[i-1]->setspell(fire);
            hero[i-1]->setspell(light);
            hero[i-1]->setpot(pot[0]);
            hero[i-1]->setpot(pot[1]);
            hero[i-1]->setpot(pot[2]);
            hero[i-1]->setpot(pot[3]);   
            hero[i-1]->setpot(pot[4]);*/
        }
        else if(clas=="P" || clas=="p"){
            cout << "Your " << i << " character is a Paladin" << endl;
            hero[i-1]= new Paladin;
            /*hero[i-1]->setspell(freeze);
            hero[i-1]->setspell(fire);
            hero[i-1]->setspell(light);
            hero[i-1]->setpot(pot[0]);
            hero[i-1]->setpot(pot[1]);
            hero[i-1]->setpot(pot[2]);
            hero[i-1]->setpot(pot[3]);   
            hero[i-1]->setpot(pot[4]);*/
        }
        else if(clas=="S" || clas=="s"){
            cout << "Your " << i << " character is a Sorcerer" << endl;
            hero[i-1]= new Sorcerer;
            /*hero[i-1]->setspell(freeze);
            hero[i-1]->setspell(fire);
            hero[i-1]->setspell(light);
            hero[i-1]->setpot(pot[0]);
            hero[i-1]->setpot(pot[1]);
            hero[i-1]->setpot(pot[2]);
            hero[i-1]->setpot(pot[3]);   
            hero[i-1]->setpot(pot[4]);*/
        }
        cout << endl;
    }
    

    for(int j=1; j<SIZE_OF_MAP-1; j++){
        if(map[SIZE_OF_MAP-2][j]->gettype()!=3 && map[SIZE_OF_MAP-2][j-1]->gettype()!=3 && map[SIZE_OF_MAP-2][j+1]->gettype()!=3 && map[SIZE_OF_MAP-2][j]->gettype()!=2){
            map[SIZE_OF_MAP-2][j]->changehero1(SIZE_OF_MAP-2,j);
            break;
        }
    }
    printmap(map,SIZE_OF_MAP);
    
    cout <<  "Please type [W/A/S/D] to move, [I] to open your inventory, [E] to equip an item, [U] to use a potion or [P] to see each characters stats" << endl;
    //cout << "[W/A/S/D/I/U/P]";
    string move;
    cin >> move;
    unsigned m;
    unsigned hi;
    unsigned hj;
    unsigned d=hero[0]->getdeath();
    int lvl;
    while(move!="quit" && move!="exit"){
        while(move!="W" && move!="w" && move!="s" && move!="S" && move!="A" && move!="a" && move!="D" && move!="d" && move!="I" 
            && move!="i" && move!="U" && move!="u" && move!="P" && move!="p" && move!="I" && move!="i" && move!="quit" && move!="exit" && move!="e" && move!="E"){
                cout << endl << "Invalid input!" << endl;
                cout <<  "Please type [W/A/S/D] to move, [I] to open your inventory, [E] to equip an item, [U] to use a potion or [P] to see each characters stats" << endl;
                //cout << "[W/A/S/D/I/U/P]";
                cin >> move;
        }
        if(move=="W" || move=="w" || move=="s" || move=="S" || move=="A" || move=="a" || move=="D" || move=="d"){
            m=moving(map,move);
            map[0][0]->getij(hi,hj); 
            if(m==1){
                if(move=="W" || move=="w"){
                    hi--;
                }else if(move=="s" || move=="S"){
                    hi++;
                }else if(move=="A" || move=="a"){
                    hj--;
                }else if(move=="D" || move=="d"){
                    hj++;
                }
            }
            m=map[hi][hj]->gettype();
            if(m==1){
                fight(hero,N_HEROES);
            }
            if(m==2){
                printmap(map,SIZE_OF_MAP);
                cout << "Do you want to enter the market?" << endl;
                cout << "[Y/N]" ;
                string yn;
                cin >> yn;
                while(yn!= "y" && yn!= "Y" && yn!= "n" && yn!= "N" ){
                    cout << "Plese type [Y] for yes or [N] for no." ;
                    cin >> yn ;
                }
                if(yn== "y" || yn== "Y"){
                    while(1){
                        cout << "Please choose which character you want to use" << endl << endl;
                        //sleep(1);
                        for( int i=1; i<=N_HEROES; i++){
                            name= hero[i-1]->getname();
                            health=hero[i-1]->gethealth();
                            mana=hero[i-1]->getmana();
                            cout << "Press " << i << " for " <<  name << " [Health:" << health << "] [Energy: " << mana << "]" ;
                            hero[i-1]->printclas();
                            //sleep(1);
                            }
                        int he;
                        cin >> he;
                        while(he<=0 || he>N_HEROES){
                            cout << "Please choose a number from 1 to " << N_HEROES << endl;
                            cin >> he;
                        }
                        market.open(hero[he-1]);
                        cout << "Do you want to enter the market again?" << endl;
                        cout << "[Y/N]" ;
                        string yn;
                        cin >> yn;
                        while(yn!= "y" && yn!= "Y" && yn!= "n" && yn!= "N" ){
                            cout << "Plese type [Y] for yes or [N] for no." ;
                            cin >> yn ;
                        }
                        if(yn== "n" || yn== "N"){
                            break;  
                        }
                    }
                }
            }
            d=hero[0]->getdeath();
            if(d>=4){
               break; 
            }
            lvl= hero[0]->getlvl();
            if(lvl>=10){
                break;
            }
            //sleep(1);
            printmap(map,SIZE_OF_MAP);
        }
        if(move=="U" || move=="u"){
            uspo(hero,N_HEROES);
            printmap(map,SIZE_OF_MAP);
        }
        if(move=="E" || move=="e"){
            cout << "Please choose which character you want to use" << endl << endl;
            for( int i=1; i<=N_HEROES; i++){
                name= hero[i-1]->getname();
                health=hero[i-1]->gethealth();
                mana=hero[i-1]->getmana();
                cout << "Press " << i << " for " <<  name << " [Health:" << health << "] [Energy: " << mana << "]" ;
                hero[i-1]->printclas();
                //sleep(1);
            }
            int he;
            cin >> he;
            while(he<=0 || he>N_HEROES){
                cout << "Please choose a number from 1 to " << N_HEROES << endl;
                cin >> he;
            }
            hero[he-1]->equip();
            system("clear");
            printmap(map,SIZE_OF_MAP);
        }
        if(move=="p" || move=="P"){
            system("clear");
            for(int i=0; i<N_HEROES ; i++){
                hero[i]->printclas();
                cout << " ";
                hero[i]->printstats();
            }
            cout << "Press any key to go back" << endl;
            cin >> move;
            printmap(map,SIZE_OF_MAP);
        }
        if(move=="i" || move=="I"){
                cout << "Please choose which character you want to use" << endl << endl;
                //sleep(1);
            for( int i=1; i<=N_HEROES; i++){
                name= hero[i-1]->getname();
                health=hero[i-1]->gethealth();
                mana=hero[i-1]->getmana();
                cout << "Press " << i << " for " <<  name << " [Health:" << health << "] [Energy: " << mana << "]" ;
                hero[i-1]->printclas();
                //sleep(1);
            }
            int he;
            cin >> he;
            while(he<=0 || he>N_HEROES){
                cout << "Please choose a number from 1 to " << N_HEROES << endl;
                cin >> he;
            }
            hero[he-1]->checkInventory();
            system("clear");
            printmap(map,SIZE_OF_MAP);
        }
        cout << endl << "Please type [W/A/S/D] to move, [I] to open your inventory , [U] to use a potion or [P] to see each characters stats" << endl;
        //cout << "[W/A/S/D/I/U/P]";
        cin >> move;
    }
    if(d>=2){
        cout << "++++++++++++++++++++" << endl;
        cout << "++ DEFEAT ++" << endl;
        cout << "++ You lost " << d << " times! ++" << endl;
        cout << "++++++++++++++++++++" << endl<< endl;
    }
    else if(lvl>=10){
        cout << "++++++++++++++++++++" << endl;
        cout << "!! VICTORY !!" << endl;
        cout << "!! You won !!" << endl;
        cout << "++++++++++++++++++++" << endl<< endl;
    }
    cout << "Closing game..." << endl;
    sleep(2);
}

void uspo(Hero** hero, unsigned N_HEROES){
    int sp;
    system("clear");
    int health;
    int mana;
    string name;
    for(int i=0;i <N_HEROES ; i++){
        name= hero[i]->getname();
        health=hero[i]->gethealth();
        mana=hero[i]->getmana();
        cout << "Press " << i+1 << " for " <<  name << " [Health:" << health << "] [Energy: " << mana << "]" ;
        hero[i]->printclas();
    }            
    cout << endl << "Please use the numbers 1-" << N_HEROES << " to choose which character you want to use!" << endl;
    cout << "Or press [Q] to exit" << endl;
    string str;
    cin >> str;
    string maxs;
    stringstream out;
    out << N_HEROES;
    maxs = out.str();
    int fp=0;
    while(fp==0){
        if(str!="Q" && str!="q"){
            if(str>="1" && str<=maxs){
                sp= stoi(str);
                if(sp<=N_HEROES){
                    fp=1;
                    break;
                }
            } 
        }else{
            fp=2;
            break;
        }
        cout << "Please use the numbers 1-" << N_HEROES << " to choose which potion you want to use!" << endl;
        cout << "Or press [Q] to exit" << endl;
        cin >> str;
    }
    if(fp==1){
        hero[sp-1]->pothero();
    }   
}