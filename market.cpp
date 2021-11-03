#include "items.h"
#include "spells.h"
#include "living.h"
#include "market.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;


void Market::open(Hero* hero)
{
    system("clear");
    while(1)
    {
        system("clear");
        cout << "* Welcome to the MARKET! *" << endl << endl;
        cout << "Your gold: " << hero->getgold() << endl << endl;
        cout << "Press [B] to Buy." << endl;
        cout << "Press [S] to Sell." << endl;
        cout << "Press [Q] to exit the market." << endl;
        cout << endl;
        //char ch;
        //cin >> ch;
        string st;
        cin >> st;
        while(st!="B" && st!="b" && st!="S" && st!="s" && st!="Q" && st!="q")
        //while(ch!='B' && ch!='b' && ch!='S' && ch!='s' && ch!='Q' && ch!='q')
        {
            cout << "Wrong Input! Try Again!" << endl;
            cout << "Your gold: " << hero->getgold() << endl;
            cout << "Press [B] to Buy." << endl;
            cout << "Press [S] to Sell." << endl;
            cout << "Press [Q] to exit the market." << endl;
            cin >> st;
            cout << endl;
        }
        while(1)
        {
            if(st=="B" || st=="b") // buy
            {
                system("clear");
                //cout << endl;
                cout << "Your gold: " << hero->getgold() << endl << endl;
                cout << "For Items, press [I]." << endl;
                cout << "For Spells, press [S]." << endl;
                cout << "To go back, press [Q]" << endl;
                cin >> st;
                //cout << endl;
                while(st!="I" && st!="i" && st!="S" && st!="s" && st!="Q" && st!="q")
                //while(ch!='I' && ch!='i' && ch!='S' && ch!='s' && ch!='Q' && ch!='q')
                {
                    //cout << endl;
                    cout << "Wrong Input! Try Again!" << endl << endl;
                    cout << "Your gold: " << hero->getgold() << endl << endl;
                    cout << "For Items, press [I]." << endl;
                    cout << "For Spells, press [S]." << endl;
                    cout << "To go back, press [Q]" << endl;
                    cin >> st;
                    cout << endl;
                }
                if(st=="I" || st=="i") // items
                {
                    this->printItems();
                    cout << "Your gold: " << hero->getgold() << endl;
                    cout << "Pick an Item or press [Q] to go back!" << endl;
                    string s;
                    cin >> s;
                    if (s=="Q" || s=="q")
                        break;
                    else if (stoi(s)>=1 && stoi(s)<=39)
                    {
                        if(stoi(s)>=1 && stoi(s)<=15)
                        {
                            Weapon* weap = this->buyWeapon(stoi(s)-1,hero);
                            if (weap!=NULL)
                            {
                                //weap->setHalfPrice();
                                hero->giveWeapon(weap);
                            }
                        }
                        else if(stoi(s)>=16 && stoi(s)<=23)
                        {
                            Armor* arm = this->buyArmor(stoi(s)-16,hero);
                            if (arm!=NULL)
                            {
                                //arm->setHalfPrice();
                                hero->giveArmor(arm);
                            }
                        }
                        else
                        {
                            int quant;
                            Potion* pot = this->buyPotion(stoi(s)-24,hero,quant);
                            if (pot!=NULL)
                            {
                                //pot->setHalfPrice();
                                hero->givePotion(pot,quant);
                            }
                        }
                        sleep(1);
                        break;
                    }
                    else
                    {
                        cout << "Wrong input!" << endl;
                        sleep(1);
                        break;
                    }
                }
                else if (st=="S" || st=="s") // spells
                {
                    this->printSpells();
                    cout << "Your gold: " << hero->getgold() << endl;
                    cout << "Pick a Spell or press [Q] to go back!" << endl;
                    string s;
                    cin >> s;
                    if (s=="Q" || s=="q")
                        break;
                    else if (stoi(s)>=1 && stoi(s)<=15)
                    {
                        if(stoi(s)>=1 && stoi(s)<=5)
                        {
                            IceSpell* ice = this->buyIce(stoi(s)-1,hero);
                            if(ice!=NULL)
                            {
                                //ice->setHalfPrice();
                                Spell* sp = ice;
                                hero->giveSpell(sp);
                            }
                        }
                        else if(stoi(s)>=6 && stoi(s)<=10)
                        {
                            FireSpell* fire = this->buyFire(stoi(s)-6,hero);
                            if(fire!=NULL)
                            {
                                //fire->setHalfPrice();
                                Spell* sp = fire;
                                hero->giveSpell(sp);
                            }
                        }
                        else
                        {
                            LightingSpell* light = this->buyLight(stoi(s)-11,hero);
                            if(light!=NULL)
                            {
                                //light->setHalfPrice();
                                Spell* sp = light;
                                hero->giveSpell(sp);
                            }
                        }
                        sleep(1);
                        break;
                    }
                    else
                    {
                        cout << "Wrong input!" << endl;
                        sleep(1);
                        break;
                    }
                }
                else // back
                    { cout << "Going Back!" << endl; break; }
            }
            else if (st=="S" || st=="s") // sell
            {
                system("clear");
                //hero->checkInventory();
                cout << "Your gold: " << hero->getgold() << endl << endl;
                cout << "For your Weapons, press[W]." << endl;
                cout << "For your Armors, press[A]." << endl;
                cout << "For your Potions, press[P]." << endl;
                cout << "For your Spells, press[S]." << endl;
                cout << "To go back, press [Q]" << endl;
                //cout << "Your gold: " << hero->getgold() << endl;
                string s;
                cin >> s;
                while(s!="W" && s!="w" && s!="A" && s!="a" && s!="P" && s!="p" && s!="S" && s!="s" && s!="Q" && s!="q")
                {
                    cout << "Wrong Input! Try Again!" << endl << endl;
                    cout << "Your gold: " << hero->getgold() << endl << endl;
                    cout << "For your Weapons, press[W]." << endl;
                    cout << "For your Armors, press[A]." << endl;
                    cout << "For your Potions, press[P]." << endl;
                    cout << "For your Spells, press[S]." << endl;
                    cout << "To go back, press [Q]" << endl;
                    //cout << "Your gold: " << hero->getgold() << endl;
                    cin >> s;
                }
                if(s=="W" || s=="w")
                {
                    hero->sellWeap();
                }
                if(s=="A" || s=="a")
                {
                    hero->sellArm();
                }
                if(s=="P" || s=="p")
                {
                    hero->sellPot();
                }
                if(s=="S" || s=="s")
                {
                    hero->sellSp();
                }
                sleep(1);
                break;
            }
            else // exit
            {
                cout << "Exiting MARKET..." << endl;
                return;
            }
            //system("clear");    
        }
        //system("clear");
    }
}

void Market::printItems()
{
    system("clear");
    cout << "Weapons" << endl << "-------" << endl;
    for(int i=0 ; i<15 ; ++i)
    {
        cout << i+1 << ") ";
        (this->weapons[i])->print();
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Armors" << endl << "------" << endl;
    for(int i=0 ; i<8 ; ++i)
    {
        cout << i+16 << ") ";
        (this->armors[i])->print();
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Potions" << endl << "-------" << endl;
    for(int i=0 ; i<13 ; ++i)
    {
        cout << i+24 << ") ";
        (this->potions[i])->print();
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl; 
}

void Market::printSpells()
{
    system("clear");
    cout << "Ice Spells" << endl << "----------" << endl;
    for(int i=0 ; i<5 ; ++i)
    {
        cout << i+1 << ") ";
        (this->iceSpells[i])->print();
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Fire Spells" << endl << "-----------" << endl;
    for(int i=0 ; i<5 ; ++i)
    {
        cout << i+6 << ") ";
        (this->fireSpells[i])->print();
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Lighting Spells" << endl << "---------------" << endl;
    for(int i=0 ; i<5 ; ++i)
    {
        cout << i+11 << ") ";
        (this->lightSpells[i])->print();
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Weapon* Market::buyWeapon(int i, Hero* hero)
{
    if(hero->getlvl() >= weapons[i]->getLVL())
    {
        if(hero->getgold() >= weapons[i]->getPrice())
        {
            string name = weapons[i]->getName();
            cout << "You just bought " << name << "!" << endl;
            hero->goldredux(weapons[i]->getPrice());
            return weapons[i];
        }
        else
        {
            cout << "Not enough Gold!" << endl;
            return NULL;
        }
    }
    else
    {
        cout << "Not enough Level!" << endl;
        return NULL;
    }
}

Armor* Market::buyArmor(int i, Hero* hero)
{
    if(hero->getlvl() >= armors[i]->getLVL())
    {
        if(hero->getgold() >= armors[i]->getPrice())
        {
            string name = armors[i]->getName();
            cout << "You just bought " << name << "!" << endl;
            hero->goldredux(armors[i]->getPrice());
            return armors[i];
        }
        else
        {
            cout << "Not enough Gold!" << endl;
            return NULL;
        }
    }
    else
    {
        cout << "Not enough Level!" << endl;
        return NULL;
    }
}

Potion* Market::buyPotion(int i, Hero* hero, int& quant)
{
    if(hero->getlvl() >= potions[i]->getLVL())
    {
        cout << "How many potions you need? Give a number between [1,5]" << endl;
        string num;
        cin >> num;
        while(num!="1" && num!="2" && num!="3" && num!="4" && num!="5")
        {
            cout << "Wrong input! Give a number between [1,5]" << endl;
            cin >> num;
        }
        int gold = potions[i]->getPrice() * stoi(num);
        if(hero->getgold() >= gold)
        {
            string name = potions[i]->getName();
            cout << "You just bought " << name << "!" << endl;
            hero->goldredux(gold);
            quant = stoi(num);
            return potions[i];
        }
        else
        {
            cout << "Not enough Gold!" << endl;
            return NULL;
        }
    }
    else
    {
        cout << "Not enough Level!" << endl;
        return NULL;
    }
}

IceSpell* Market::buyIce(int i, Hero* hero)
{
    if(hero->getlvl() >= iceSpells[i]->getLVL())
    {
        if(hero->getgold() >= iceSpells[i]->getPrice())
        {
            string name = iceSpells[i]->getName();
            cout << "You just bought " << name << "!" << endl;
            hero->goldredux(iceSpells[i]->getPrice());
            return iceSpells[i];  
        }
        else
        {
            cout << "Not enough Gold!" << endl;
            return NULL;
        }
    }
    else
    {
        cout << "Not enough Level!" << endl;
        return NULL;
    }
}

FireSpell* Market::buyFire(int i, Hero* hero)
{
    if(hero->getlvl() >= fireSpells[i]->getLVL())
    {
        if(hero->getgold() >= fireSpells[i]->getPrice())
        {
            string name = fireSpells[i]->getName();
            cout << "You just bought " << name << "!" << endl;
            hero->goldredux(fireSpells[i]->getPrice());
            return fireSpells[i];  
        }
        else
        {
            cout << "Not enough Gold!" << endl;
            return NULL;
        }
    }
    else
    {
        cout << "Not enough Level!" << endl;
        return NULL;
    }
}

LightingSpell* Market::buyLight(int i, Hero* hero)
{
    if(hero->getlvl() >= lightSpells[i]->getLVL())
    {
        if(hero->getgold() >= lightSpells[i]->getPrice())
        {
            string name = lightSpells[i]->getName();
            cout << "You just bought " << name << "!" << endl;
            hero->goldredux(lightSpells[i]->getPrice());
            return lightSpells[i];  
        }
        else
        {
            cout << "Not enough Gold!" << endl;
            return NULL;
        }
    }
    else
    {
        cout << "Not enough Level!" << endl;
        return NULL;
    }
}