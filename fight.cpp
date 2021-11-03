#include <iostream>
#include <string>
#include "items.h"
#include "spells.h"
#include "living.h"
#include "fight.h"
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>

using namespace std;

void fight(Hero** hero,unsigned n){
    int ndead=0;
    int player;
    string move;
    long now;
    now=time(NULL);
    srand((unsigned int)now);
    unsigned r;
    r=rand()%2; 
    Monster* monster=new Monster;
    if(r==1){
        system("clear");
        cout << "A fight has started!" << endl;
        int lvl;
        lvl=hero[0]->getlvl();
        r=rand()%3;
        if(r==0){
            monster = new Dragon(lvl,n);
            
            cout << "A wild Dragon has appeared!" << endl;
        }
        else if(r==1){
            monster = new Exoskeleton(lvl,n);
            
            cout << "A wild Exosceleton has appeared!" << endl;
        }
        else if(r==2){
            monster = new Spirit(lvl,n);\
            
            cout << "A wild Spirit has appeared!" << endl;
        }
        //sleep(1);
        string name;
        string sd;
        name= monster->getname();
        cout << "You are fighting " << name << endl;
        sleep(1);
        monster->printhealth();
        //Sleep(1000);
        int fl=0;
        int turn=0;
        int health;
        unsigned winhero=0;
        unsigned winmons=0;
        int dead;
        int spot=0;
        unsigned monster_flag;
        unsigned mana;
        int last=turn;
        int pot=0;
        while(fl==0){
            string move;
            if(turn==0){
                cout << endl;
                if(last==1){
                    regen(hero,n);
                }
                if(spot==0){
                    cout << "It's your turn!" << endl;
                    sleep(1);
                }
                else
                {
                    sleep(1);
                    system("clear");
                    spot=0;
                }
                monster->printhealth();
                cout << "Please choose which character you want to use" << endl << endl;
                //sleep(1);
                for(int i=1; i<=n; i++){
                    dead=hero[i-1]->getdead();
                    if(dead==0){
                        name= hero[i-1]->getname();
                        health=hero[i-1]->gethealth();
                        mana=hero[i-1]->getmana();
                        cout << "Press " << i << " for " <<  name << " [Health:" << health << "] [Energy:" << mana << "] " ;
                        hero[i-1]->printclas();
                        //sleep(1);
                    }
                }
                if(ndead==0){
                    cin >> sd;
                    while(sd!="1" && sd!="2" && sd!="3"){
                    cout << "Please choose a number from 1 to " << n << endl;
                    cin >> sd;
                    }
                }else{
                    int flag=1;
                    int na[3];
                    na[2]=0;
                    na[1]=0;
                    na[0]=0;
                    for(int j=0;j<n;j++){
                        na[j]=hero[j]->getdead();
                    }
                    while (flag==1){
                        flag=0;
                        cin >> sd;
                        if(sd!="1" && sd!="2" && sd!="3"){
                            cout << "Please choose a number from 1 to " << n << endl;
                            flag=1;
                        }
                        else if(sd=="1" && na[0]==1){
                            player=stoi(sd);
                            name= hero[player-1]->getname();
                            cout << name << " is dead, please select another character" << endl;
                            flag=1;
                        }else if(sd=="2" && na[1]==1){
                            player=stoi(sd);
                            name= hero[player-1]->getname();
                            cout << name << " is dead, please select another character" << endl;
                            flag=1;
                        }else if(sd=="3" && na[2]==1){
                            player=stoi(sd);
                            name= hero[player-1]->getname();
                            cout << name << " is dead, please select another character" << endl;
                            flag=1;
                        }else if(sd=="3" && n<3){
                            cout << "Please choose a number from 1 to " << n << endl;
                            flag=1;
                        }else if(sd=="2" && n<2){
                            cout << "Please choose a number from 1 to " << n << endl;
                            flag=1;
                        }

                    }
                }
                player=stoi(sd);
                name=hero[player-1]->getname();
                cout << name << " is preparing his next move" << endl;
                //sleep(1);
                cout << "Please select your next move, press [A] to attack, [S] to use spell, [P] to use potion or [Q] to go back" << endl;
                cout << "[A/S/P/Q] ";
                cin >> move;
                //while gia na elegjo oti yparxei
                if(move=="A" or move=="a"){
                    attackhero(hero[player-1],monster,winhero);
                    turn=1;
                }
                if(move=="s" or move=="S"){
                    spot=spellhero(hero[player-1],monster,winhero);
                    if(spot==0){
                        turn=1;
                    }
                    if(spot==1){
                        continue;
                    }
                }
                if(move=="p" or move=="P"){
                    system("clear");
                    spot=hero[player-1]->pothero();
                    if(spot==0){
                        turn=1;
                    }
                    if(spot==1){
                        continue;
                    }
                }
                if(winhero==1){
                    victory(hero,n);
                    fl=1;
                    break;
                }
                monster_flag=monster->getf();
                if(last==1){
                    if(monster_flag==1){
                        monster->changelow();
                    }
                }
                last=0;
            }
            else if(turn==1){
                last=1;
                winmons=0;
                cout << endl;
                sleep(1);
                name=monster->getname();
                cout << "It's " << name << "'s turn!" << endl;
                attackmonster(hero[player-1],monster,winmons);
                turn=0;
                if(winmons==1){
                    ndead++;
                    hero[player-1]->dead();
                    if(ndead==n){
                        cout << endl;
                        for(int i=1; i<20; i++){
                            cout << "+" ;
                        }
                        cout << endl;
                        cout << "+ Everyone died +" << endl;
                        cout << "+ You lost this fight +" << endl;
                        for(int i=1; i<20; i++){
                            cout << "+" ;
                        }
                        cout << endl;
                        fl=2;
                        revall(hero,n);
                    }
                    else if(ndead<n)
                    {
                        cout << endl;
                        for(int i=1; i<20; i++){
                            cout << "+" ;
                        }
                        cout << endl;
                        name=hero[player-1]->getname();
                        cout << name << " has died" << endl;
                        for(int i=1; i<20; i++){
                            cout << "+" ;
                        }
                        cout << endl;
                    }
                    winmons=0;
                }
                sleep(1);
            }
        }
    }
}

void attackhero(Hero* hero,Monster* monster,unsigned& def){
    unsigned dmg;
    int health;
    int pot=hero->getpot(0);
    string name;
    name=monster->getname();
    dmg=hero->getattack();
    //sleep(1);
    monster->changehealth(dmg,pot);
    if(pot>0){
        hero->changepot(0);
    }
    sleep(1);
    health=monster->gethealth();
    if(health>0){
        monster->printhealth();
    }
    else
    {
        cout << endl;
        for(int i=1; i<20; i++){
            cout << "+" ;
        }
        cout << endl;
        cout << "You defeated " << name << endl;
        def=1;
    }
}

void attackmonster(Hero* hero,Monster* monster,unsigned& def){
    unsigned dmg;
    int health;
    //sleep(1);
    monster->getdmg(dmg);
    hero->changehealth(dmg);
    sleep(1);
    health=hero->gethealth();
    if(health<=0){
        def=1;
    }
}

void victory(Hero** hero,unsigned n){
    unsigned d;
    string name;
    for(int i=1; i<=n; i++){
        d=hero[i-1]->getdead();
        if(d==0){
            hero[i-1]->levelup();
        }
        else{
            name=hero[i-1]->getname();
            cout << name << " was revived!" << endl;
            hero[i-1]->deadhp();
        }
    }
    cout << "Press any key to continue" << endl;
    string s;
    cin >>  s;
    cout << endl;
}

unsigned spellhero(Hero* hero, Monster* monster, unsigned& def){
    unsigned cur;
    unsigned sp;
    string str;
    unsigned type;
    unsigned energy;
    int health;
    unsigned f;
    unsigned mana;
    unsigned rounds;
    unsigned redux;
    unsigned f2;
    unsigned pot;
    string name;
    name=monster->getname();
    cur=hero->getcurspells();
    if(cur==0){
        cout << "You don't have any spells" << endl;
        return 1;
    }else{
        system("clear");
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        hero->printspells(cur);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl << "Please use the numbers 1-" << cur << " to choose which spell you want to use!" << endl;
        cout << "Or press [Q] to exit" << endl;
        cin >> str;
        string maxs;
        stringstream out;
        out << cur;
        maxs = out.str();
        while(1){
            if(str!="Q" && str!="q"){
                if(str>="1" && str<=maxs ){
                    sp= stoi(str);
                    if(sp<=cur){
                        break;
                    }
                } 
            }else{
                break;
            }
            cout << "Please use the numbers 1-" << cur << " to choose which spell you want to use!" << endl;
            cout << "Or press [Q] to exit" << endl;
            cin >> str;
        }
        if(str=="Q" || str=="q"){
            return 1;
        }
        sp--;
        type = hero->checkspell(sp);
        energy = hero->getenerg(sp);
        mana= hero->getmana();
        f2=monster->checkeff(type);
        if(f2!=0){
            if(mana>=energy){
                hero->setmana(energy);
                pot=hero->getpot(1);
                f=hero->spell(monster,sp,pot);
                if(pot>0){
                    hero->changepot(1);
                }
                if(f==0){
                    health=monster->gethealth();
                    if(health>0){
                        if(f2==1){
                            monster->resetspell(sp);
                        } 
                        hero->spellstats(sp,redux,rounds);
                        monster->setlow(type,redux,rounds);
                        monster->printhealth();
                    }
                    else
                    {
                        cout << endl;
                        for(int i=1; i<20; i++){
                            cout << "+" ;
                        }
                        cout << endl;
                        cout << "You defeated " << name << endl;
                        def=1;
                    }
                }
                return 0;
            }
            else
            {
                cout << "Not enough mana!" << endl;
                return 1;
            }
        }else{
            return 1;
        }
    }

}

unsigned damage(unsigned dmgmax, unsigned dmgmin){
    unsigned gap;
    gap=dmgmax-dmgmin;
    long now;
    now=time(NULL);
    srand((unsigned int)now);
    unsigned r;
    r=rand()%(gap+1);
    return dmgmin+r;
}

void regen(Hero** hero, unsigned n){
    unsigned d;
    for(int i=0; i<n; i++){
        d=hero[i]->getdead();
        if(d==0){
            hero[i]->regen();
        }
    }
}

void revall(Hero** hero,unsigned n){
    string name;
    cout << "Everyone lost half its gold!" << endl;
    unsigned g;
    for(int i=0;i<n;i++){
        name=hero[i]->getname();
        hero[i]->deadhp();
        hero[i]->deadgold();
        g=hero[i]->getgold();
        cout << name << " current gold " << g << endl;
    }
    hero[0]->death();
}