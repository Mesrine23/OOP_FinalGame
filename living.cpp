#include <iostream>
#include <string>
#include "items.h"
#include "spells.h"
#include "living.h"
#include "fight.h"
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
using namespace std;


unsigned Hero::deaths=0;

void createHero(unsigned &N){
    cout << "Please enter 1-3 depending on how many characters you want to have" << endl;
    //cin >> N;
    string N1;
    cin >> N1;
    while(N1!="1" && N1!="2" && N1!="3"){
        cout << "Please choose a number from 1 to 3" << endl;
        cin >> N1;
    }
    N=stoi(N1);
}

int Living::getlvl(){
    return level;
}

string Living::getname(){
    return name;
}

int Living::gethealth(){
    return healthPower;
}

void Monster::printhealth(){
    cout << "Remaining health [" << healthPower << "] " << endl;
}

unsigned Hero::getattack(){
    return strenght;
}

void Monster::changehealth(unsigned dmg,unsigned pot){
    long now;
    now=time(NULL);
    srand((unsigned int)now);
    unsigned r;
    r=rand()%99;
    r++;
    if(r<=dodge){
        cout << name << " dogded your attack!" << endl;
    }
    else{
        int loss;
        loss=dmg+pot-armor;
        if(loss<=0){
            cout << "Your attack dealt 0 damage!" << endl;
        }
        else if(pot==0)
        {
            cout << "Your attack dealt " << loss << " damage" << endl;
            healthPower-= loss;
        }
        else{
            cout << "Your attack dealt " << loss << " (" << dmg-armor << "+"<< pot << ") damage" << endl;
            healthPower-= loss;
        }
    }
    
}

void Monster::getdmg(unsigned& dmg){
    dmg=damage(dmgmax,dmgmin);
}

void Hero::changehealth(unsigned dmg){
    long now;
    now=time(NULL);
    srand((unsigned int)now);
    unsigned r;
    r=rand()%100;
    if(r+pots[2]<=agility){
        cout << name << " dogded the attack!  ";
        if(pots[2]>0){
            cout << "Agility " << r+pots[2] << " (" << r << "+" << pots[2] << ")";
        }
        cout << endl;
    }
    else{
        int loss;
        loss=dmg-armor;
        if(loss<=0){
            cout << name << " received 0 damage!" << endl;
        }
        else{
            cout << name << " received " << loss << " damage" << endl;
            healthPower-= loss;
        }
    }
    pots[2]=0;
}

void Hero::levelup(){
    int s;
    cout << name << " gained 75 Gold!" << endl;
    gold+=75;
    xp+=1000;
    cout << name << " gained 1000 xp!" << endl;
    while(xp>=1000){
        xp-=1000;
        cout << name << " leveled up and is now level " << ++level << endl;
    }
    agility=agility*130/100;
    dexterity=dexterity*130/100;
    strenght=strenght*130/100;
    healthPower+=level*100/3;
    if(healthPower>level*100){
        healthPower=level*100;
    }
    maxap=maxap+50;
    magicPower=magicPower+50;
}

void Hero::dead(){
    fdead=1;
}

unsigned Hero::getdead(){
    return fdead;
}

unsigned Living::getlevel(){
    return level;
}

unsigned Hero::getgold(){
    return gold;
}

unsigned Hero::getcurpot(){
    return curpot;
}

unsigned Hero::getcurspells(){
    return curspells;
}

void Hero::printspells(int cur){
    for(int i=0; i<cur; i++){
        cout << i+1 << " " ;
        spells[i]->fprint();
    }
}

void Hero::setspell(Spell* spell){
    spells[curspells++]=spell;
}

unsigned Hero::checkspell(unsigned cur){
    return spells[cur]->type();
}

void Hero::goldredux(int i){ 
    this->gold -= i; 
}

void Hero::giveWeapon(Weapon* weap)
{
    //weap->setHalfPrice();
    this->weapon[curwep] = weap;
    curwep++;
}

void Hero::giveArmor(Armor* arm)
{
    //arm->setHalfPrice();
    this->armorr[curarmor] = arm;
    curarmor++;
}

void Hero::givePotion(Potion* pot, int quant)
{
    int flag=0;
    //pot->setHalfPrice();
    for(int i=0 ; i<curpot ; ++i)
    {
        if(potion[i]->getName() == pot->getName())
        {
            npots[i] += quant;
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        this->potion[curpot] = pot;
        npots[curpot] = quant;
        curpot++;
    }
}

void Hero::giveSpell(Spell* sp)
{
    //sp->setHalfPrice();
    this->spells[curspells] = sp;
    curspells++;
}

void Hero::setgold(int g)
{ this->gold += g; }

void Hero::sellWeap()
{
    cout << "Your gold: " << this->getgold() << endl << endl;
    if (curwep==0)
        cout << "~You don't have any Weapons!~" << endl;
    else
    {
        for(int i=0 ; i<curwep ; ++i)
        {
            cout << i+1 << ") ";
           weapon[i]->print();
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Give the number of the Weapon you want to sell!" << endl;
    cout << "Otherwise, press [Q] to exit!" << endl;
    string s;
    cin >> s;
    if(s=="Q" || s=="q")
        return;
    else
    {
        if(stoi(s)>curwep || stoi(s)<0)
        {
            cout << "No such Weapon Found!" << endl;
            return;
        }
        else
        {
            int cur = stoi(s);
            int g = weapon[cur-1]->getPrice();
            this->setgold(g/2);
            if(cur==(curwep))
            {
                weapon[cur-1]=NULL;
                curwep--;
            }
            else{
                weapon[cur-1] = weapon[--curwep];
                weapon[curwep]=NULL;
            }
        }
    }
}

void Hero::sellArm()
{
    cout << "Your gold: " << this->getgold() << endl << endl;
    if(curarmor==0)
        cout << "~You don't have any Armors!~" << endl;
    else
    {
        for(int i=0 ; i<curarmor ; ++i)
        {
            cout << i+1 << ") ";
            armorr[i]->print();
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Give the number of the Armor you want to sell!" << endl;
    cout << "Otherwise, press [Q] to exit!" << endl;
    string s;
    cin >> s;
    if(s=="Q" || s=="q")
        return;
    else
    {
        if(stoi(s)>curarmor || stoi(s)<0)
        {
            cout << "No such Armor Found!" << endl;
            return;
        }
        else
        {
            int cur = stoi(s);
            int g = armorr[cur-1]->getPrice();
            this->setgold(g/2);
            if(cur==(curarmor))
            {
                armorr[cur-1]=NULL;
                curarmor--;
            }
            else{
                armorr[cur-1] = armorr[--curarmor];
                armorr[curarmor]=NULL;
            }
        }
    }
}

void Hero::sellPot()
{
    cout << "Your gold: " << this->getgold() << endl << endl;
    if(curpot==0)
        cout << "~You don't have any Potions!~" << endl;
    else
    {
        for(int i=0 ; i<curpot ; ++i)
        {
            cout << i+1 << ") [x" << npots[i] << "] "; 
            potion[i]->print();
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Give the number of the Potion you want to sell!" << endl;
    cout << "Otherwise, press [Q] to exit!" << endl;
    string s;
    cin >> s;
    if(s=="Q" || s=="q")
        return;
    else
    {
        if(stoi(s)>curpot || stoi(s)<0)
        {
            cout << "No such Potion Found!" << endl;
            return;
        }
        else
        {
            int cur = stoi(s);
            if(cur==curpot)
            {
                if(npots[cur-1]>1)
                {
                    cout << "How many you want to Sell?" << endl;
                    int q;
                    cin >> q;
                    while(q>npots[cur-1])
                    {
                        cout << "Not enough Potions!" << endl;
                        cout << "Your remainings are: " << npots[cur-1] << endl;
                        cout << "Try again!" << endl;
                        cin >> q;
                    }
                    npots[cur-1] -= q;
                    int g = potion[cur-1]->getPrice() * q;
                    this->setgold(g/2);
                    if(npots[cur-1]==0)
                    {
                        potion[cur-1]=NULL;
                        curpot--; 
                    }
                }
                else
                {
                    potion[cur-1]=NULL;
                    curpot--; 
                }
            }
            else
            {
                if(npots[cur-1]>1)
                {
                    cout << "How many you want to Sell?" << endl;
                    int q;
                    cin >> q;
                    while(q>npots[cur-1])
                    {
                        cout << "Not enough Potions!" << endl;
                        cout << "Your remainings are: " << npots[cur-1] << endl;
                        cout << "Try again!" << endl;
                        cin >> q;
                    }
                    npots[cur-1] -= q;
                    int g = potion[cur-1]->getPrice() * q;
                    this->setgold(g/2);
                    if(npots[cur-1]==0)
                    {
                        potion[cur-1] = potion[--curpot];
                        npots[cur-1] = npots[curpot];
                        npots[curpot]=0;
                        potion[curpot]=NULL;
                    }
                }
                else
                {
                    potion[cur-1] = potion[--curpot];
                    npots[cur-1] = npots[curpot];
                    npots[curpot]=0;
                    potion[curpot]=NULL;
                }
            }
        }
    }
}

void Hero::sellSp()
{
    cout << "Your gold: " << this->getgold() << endl << endl;
    if(curspells==0)
        cout << "~You don't have any Spells!~" << endl;
    else
    {
        for(int i=0 ; i<curspells ; ++i)
        {
            cout << i+1 << ") ";
            spells[i]->print();
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Give the number of the Spell you want to sell!" << endl;
    cout << "Otherwise, press [Q] to exit!" << endl;
    string s;
    cin >> s;
    if(s=="Q" || s=="q")
        return;
    else
    {
        if(stoi(s)>curspells || stoi(s)<0)
        {
            cout << "No such Spell Found!" << endl;
            return;
        }
        else
        {
            int cur = stoi(s);
            int g = spells[cur-1]->getPrice();
            this->setgold(g/2);
            if(cur==curspells)
            {
                spells[cur-1]=NULL;
                curspells--;
            }
            else
            {
                spells[cur-1] = spells[--curspells];
                spells[curspells]=NULL;
            }
        }
    }
}

void Hero::checkInventory()
{
    system("clear");
    //cout << "This is your Inventory!" << endl << endl;
    string nam = this->getname();
    cout << "*" << nam << "'s Inventory!*" << endl << endl;
    if(this->curwep!=0)
    {
        cout << "Weapons" << endl << "-------" << endl;
        for(int i=0 ; i<curwep ; ++i)
        {
            cout << "-> ";
            (this->weapon[i])->print();
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "~No Weapons Found!~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    if(this->curarmor!=0)
    {
        cout << "Armors" << endl << "------" << endl;
        for(int i=0 ; i<curarmor ; ++i)
        {
            cout << "-> ";
            (this->armorr[i])->print();
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "~No Armors Found!~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    if(this->curpot!=0)
    {
        cout << "~Potions" << endl << "-------" << endl;
        for(int i=0 ; i<curpot ; ++i)
        {
            cout << "-> ";
            (this->potion[i])->print();
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "~No Armors Found!~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    if(this->curspells!=0)
    {
        cout << "Spells" << endl << "------" << endl;
        for(int i=0 ; i<curspells ; ++i)
        {
           cout << "-> ";
           (this->spells[i])->print();
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "~No Spells Found!~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    cout << endl << "Press any key to exit!" << endl;
    string s;
    cin >> s;
    sleep(1);
}

void Hero::equip()
{
    system("clear");
    cout << "What you want to equip?" << endl << endl;
    cout << "Press [W] for Weapons." << endl;
    cout << "Press [A] for Armors." << endl;
    string s;
    cin >> s;
    while(s!="W" && s!="w" && s!="A" && s!="a")
    {
        cout << "Wrong input! Try Again!" << endl;
        cout << "Press [W] for Weapons." << endl;
        cout << "Press [A] for Armors." << endl;
    }
    if(s=="W" || s=="w")
    {
        if(curwep==0)
        {
            cout << "You don't have any Weapons to equip!" << endl;
            return;
        }
        else
        {
            for(int i=0 ; i<curwep ; ++i)
            {
                cout << i+1 << ") ";
                weapon[i]->print();
            }
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "Give the number of the Weapon you want to equip!" << endl;
            cout << "Otherwise press [Q] to exit!" << endl;
            string n;
            cin >> n;
            if(n=="Q" || n=="q")
                return;
            else
            {
                while(stoi(n)>curwep)
                {
                    cout << "Wrong input! Try again!" << endl;
                    cin >> n;
                }
                this->equip(weapon[stoi(n)-1]);
            }
        }

    }
    else if(s=="A" || s=="a")
    {
        if(curarmor==0)
        {
            cout << "You don't have any Armors to equip!" << endl;
            return;
        }
        else
        {
            for(int i=0 ; i<curarmor ; ++i)
            {
                cout << i+1 << ") ";
                armorr[i]->print();
            }
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "Give the number of the Armor you want to equip!" << endl;
            cout << "Otherwise press [Q] to exit!" << endl;
            string n;
            cin >> n;
            if(n=="Q" || n=="q")
                return;
            else
            {
                while(stoi(n)>curarmor)
                {
                    cout << "Wrong input! Try again!" << endl;
                    cin >> n;
                }
                this->equip(armorr[stoi(n)-1]);
            }
        }
    }
    else
        return;
}

void Hero::equip(Weapon* weap)
{
    if(weap->getHands()==2) // two-handed weapon
    {
        if(this->usableWeap1!=NULL)
        {
            this->strenght -= usableWeap1->getSTR();
            this->dexterity -= usableWeap1->getDEXT();
            this->agility -= usableWeap1->getAGIL();
            usableWeap1 = weap;
            this->strenght += usableWeap1->getSTR();
            this->dexterity += usableWeap1->getDEXT();
            this->agility += usableWeap1->getAGIL();
            cout << "Done!" << endl;
            sleep(1);
        }
        else
        {
            usableWeap1 = weap;
            this->strenght += usableWeap1->getSTR();
            this->dexterity += usableWeap1->getDEXT();
            this->agility += usableWeap1->getAGIL();
            cout << "Done!" << endl;
            sleep(1);
        }
        if(this->usableWeap2!=NULL)
        {
            this->strenght -= usableWeap2->getSTR();
            this->dexterity -= usableWeap2->getDEXT();
            this->agility -= usableWeap2->getAGIL();
            usableWeap2 = weap;
            cout << "Done!" << endl;
            sleep(1);
        }
        else
        {
            usableWeap2 = weap;
            cout << "Done!" << endl;
            sleep(1);
        }  
    }
    else // single-handed weapon
    {
        if(usableWeap1==NULL && usableWeap2==NULL) // no weapons
        {
            usableWeap1 = weap;
            this->strenght += usableWeap1->getSTR();
            this->dexterity += usableWeap1->getDEXT();
            this->agility += usableWeap1->getAGIL();
            cout << "Done!" << endl;
            sleep(1);
        }
        else if(usableWeap1==NULL && usableWeap2!=NULL) // 1 weap
        {
            usableWeap1 = weap;
            this->strenght += usableWeap1->getSTR();
            this->dexterity += usableWeap1->getDEXT();
            this->agility += usableWeap1->getAGIL();
            cout << "Done!" << endl;
            sleep(1);
        }
        else if(usableWeap1!=NULL && usableWeap2==NULL)
        {
            usableWeap2 = weap;
            this->strenght += usableWeap2->getSTR();
            this->dexterity += usableWeap2->getDEXT();
            this->agility += usableWeap2->getAGIL();
            cout << "Done!" << endl;
            sleep(1);
        }
        else
        {
            cout << "Both hands have a Weapon!" << endl << endl;
            cout << "1) ";
            usableWeap1->print();
            cout << "2) ";
            usableWeap2->print();
            cout << endl;
            weap->print();
            cout << endl << "Which of the two Weapons you want to replace? (1,2)" << endl;
            cout << "If none, press [Q]." << endl;
            string s;
            cin>>s;
            while(s!="1" && s!="2" && s!="Q" && s!="q")
            {
                cout << "Wrong input! Try Again!" << endl;
                cin >> s;
            }
            if(s=="Q" || s=="q")
                return;
            else
            {
                if(stoi(s)==1)
                {
                    this->strenght -= usableWeap1->getSTR();
                    this->dexterity -= usableWeap1->getDEXT();
                    this->agility -= usableWeap1->getAGIL();
                    usableWeap1 = weap;
                    this->strenght += usableWeap1->getSTR();
                    this->dexterity += usableWeap1->getDEXT();
                    this->agility += usableWeap1->getAGIL();
                    cout << "Done!" << endl;
                    sleep(1);
                }
                else
                {
                    this->strenght -= usableWeap2->getSTR();
                    this->dexterity -= usableWeap2->getDEXT();
                    this->agility -= usableWeap2->getAGIL();
                    usableWeap2 = weap;
                    this->strenght += usableWeap2->getSTR();
                    this->dexterity += usableWeap2->getDEXT();
                    this->agility += usableWeap2->getAGIL();
                    cout << "Done!" << endl;
                    sleep(1);
                }
            }
        }
    }
}

void Hero::equip(Armor* arm)
{
    if(this->usableArm!=NULL)
    {
        this->armor -= usableArm->getREDUX();
    }
    this->usableArm = arm;
    this->armor += usableArm->getREDUX();
    cout << "Done!" << endl;
    sleep(1);
}


void Hero::spellstats(unsigned sp,unsigned& red,unsigned& rou){
    spells[sp]->getstats(red ,rou);
}

unsigned Monster::truehealth(Spell* spel,unsigned dex,unsigned pot){
    long now;
    now=time(NULL);
    srand((unsigned int)now);
    unsigned r;
    r=rand()%100;
    if(r<=dodge){
        //sleep(1);
        cout << name << " dogded your spell!" << endl;
        return 1;
    }
    else{
        unsigned max;
        unsigned min;
        spel->getdmg(max,min);
        unsigned dmg;
        dmg=damage(max,min);
        if(pot==0){
            healthPower=healthPower-dmg-dex;
            cout << "Your spell dealt " << dmg+dex << " (" << dmg << "+" << dex << ") damage!" << endl;
        }
        else{
            healthPower=healthPower-dmg-dex-pot;
            cout << "Your spell dealt " << dmg+dex+pot << " (" << dmg << "+" << dex << "+"<< pot << ") damage!" << endl; 
        }
        sleep(1);
        
        return 0;
    }
}

unsigned Hero::getenerg(unsigned sp){
    return spells[sp]->getenergy();
}

unsigned Hero::getmana(){
    return magicPower;
}

unsigned Hero::spell(Monster* monster,unsigned sp,unsigned pot){
    return monster->truehealth(spells[sp],dexterity,pot);
}

void Hero::setmana(unsigned energy){
    magicPower-=energy;
}

void Monster::setlow(unsigned type, unsigned red, unsigned roun){
    flag[type-1]=1;
    rounds[type-1]=roun;
    //sleep(1);
    if(type==1){
        redux[type-1]=red;
        if(armor>redux[type-1]){
            armor-=redux[type-1];
        }
        else{
            redux[type-1]=armor;
            armor=0;
        }
        cout << name << "'s armor reduced by " << redux[type-1] << " for " << rounds[type-1] << " rounds" << endl;
        sleep(1);
    }
    else if(type==2){
        redux[type-1]=red;
        if(redux[type-1]<dmgmax && redux[type-1]<dmgmin){
            dmgmax-=redux[type-1];
            dmgmin-=redux[type-1];
        }
        else{
            redux[type-1]=dmgmax;
            redux2=dmgmin;
            dmgmax=10;
            dmgmin=0;
        }
        
        cout << name << "'s damage reduced by " << redux[type-1] << " for " << rounds[type-1] << " rounds" << endl;
        sleep(1);
    }
    else if(type==3){
        redux[type-1]=red;
        if(redux[type-1]<dodge){
            dodge-=redux[type-1];
        }
        else{
            redux[type-1]=dodge;
            dodge=0;
        }
        cout << name << "'s agility reduced by " << redux[type-1] << " for " << rounds[type-1] << " rounds" << endl;
        sleep(1);
    }
    roun++;
}

unsigned Monster::getf(){
    unsigned f=0;
    for(int i=0; i<3 ; i++){
        if(flag[i]!=0){
            f=1;
        }
    }
    return f;
}

void Monster::changelow(){
    for(int i=0; i<3; i++){
        if(flag[i]==1){
            rounds[i]--;
            if(rounds[i]==0){
                flag[i]=0;
                if(i==0){
                    cout << "~~~Firespell's armor reduction effects are over!~~~" << endl;
                    armor+=redux[i];
                }
                if(i==1){
                    cout << "~~~Icepell's damage reduction effects are over!~~~" << endl;
                    if(dmgmin==0){
                        dmgmax=redux[i];
                        dmgmin=redux2;
                    }
                    else{
                        dmgmax+=redux[i];
                        dmgmin+=redux[i];
                    }   
                }
                if(i==2){
                    cout << "~~~Lightingpell's agility reduction effects are over!~~~" << endl;
                    dodge+=redux[i];
                }   
            }
        }
    }
}

void Hero::deadhp(){
    healthPower=level*100/2;
    fdead=0;
}

void Hero::deadgold(){
    gold=gold/2;
}

void Hero::regen(){
    unsigned hp;
    unsigned man;
    hp=level*5;
    man=level*6;
    if((hp+healthPower)<level*100){
        healthPower+=hp;
    }
    else{
        healthPower=level*100;
    }
    if((man+magicPower)<maxap){
        magicPower+=man;
    }
    else{
        magicPower=maxap;
    }
}

unsigned Monster::checkeff(unsigned t){
    t--;
    if(flag[t]==1){
        string y;
        cout << "The same effect is already active!" << endl;
        cout << "Using the same-type effect again will remove the previous effect and set the new one" << endl;
        cout << "Do you wish to proceed?" << endl;
        cout << "[Y/N]" << endl;
        cin >> y;
        while(y!="y" && y!="Y" && y!="n" && y!="N"){
            cout << "Please type Y for Yes or N for No" << endl;
            cin >> y;
        }
        if(y=="y" || y=="Y"){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 3;
    }
}

void Monster::resetspell(unsigned i){
    if(i==0){
        cout << "~~~Previous effects removed~~~" << endl;
        armor+=redux[i];
    }
    if(i==1){
        cout << "~~~Previous effects removed~~~" << endl;
        if(dmgmin==0){
            dmgmax=redux[i];
            dmgmin=redux2;
        }
        else{
            dmgmax+=redux[i];
            dmgmin+=redux[i];
        }   
    }
    if(i==2){
        cout << "~~~Previous effects removed~~~" << endl;
        dodge+=redux[i];
    }
}

void Hero::setpot(Potion* pot){
    npots[curpot]=2;
    potion[curpot++]=pot;
}

unsigned Hero::pothero(){
    string str;
    if(curpot==0){
        cout << "You don't have any potions!" << endl;
        return 1;
    }
    else{
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        for(int i=0; i<curpot; i++){
            cout << i+1;
            potion[i]->fprint();
            cout << " (x" << npots[i] << ")" << endl;
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        int sp;
        cout << endl << "Please use the numbers 1-" << curpot << " to choose which potion you want to use!" << endl;
        cout << "Or press [Q] to exit" << endl;
        cin >> str;
        string maxs;
        stringstream out;
        out << curpot;
        maxs = out.str();
        while(1){
            if(str!="Q" && str!="q"){
                if(str>="1" && str<=maxs){
                    sp= stoi(str);
                    if(sp<=curpot){
                        break;
                    }
                } 
            }else{
                break;
            }
            cout << "Please use the numbers 1-" << curpot << " to choose which potion you want to use!" << endl;
            cout << "Or press [Q] to exit" << endl;
            cin >> str;
        }
        if(str=="Q" || str=="q"){
            return 1;
            
        }
        return usepot(--sp);
    }
     
}

unsigned Hero::usepot(unsigned cur){
    string type;
    unsigned boost;
    unsigned f=0;
    boost=potion[cur]->getboost();
    type=potion[cur]->gettype();
    if(type=="Health")
    {
        if((boost+healthPower)<level*100){
            healthPower+=boost;
            
        }
        else if(healthPower==level*100)
        {
            cout << "Your healthPower is already full" << endl;
            f=1;
            return 1;
        }
        else
        {
            healthPower=level*100;
            
        }
    }
    else if(type=="Energy")
    {
        if((boost+magicPower)<maxap)
        {
            magicPower+=boost;
            
        }
        else if(magicPower==maxap)
        {
            cout << "Your magicPower is already full" << endl;
            return 1;
            
        }
        else
        {
            magicPower=maxap;
            
        }
    }
    else if(type=="Strength")
    {
        if(pots[0]>0){
            cout << "Another same-type potion is already active" << endl;
            return 1;
        }
        else
        {
            pots[0]=boost;
        }
    }
    else if(type=="Dexterity")
    {
        if(pots[1]>0){
            cout << "Another same-type potion is already active" << endl;
            return 1;
        }
        else
        {
            pots[1]=boost;
        }
    }
    else
    {
        if(pots[2]>0){
            cout << "Another same-type potion is already active" << endl;
            return 1;
        }
        else
        {
            pots[2]=boost;
        }
    }
    if(npots[cur]>1)
    {
            npots[cur]--;
    }
    else{
        if(cur==(curpot-1))
        {
            potion[cur]=nullptr;
            curpot--;
        }
        else
        {
            potion[cur]=potion[--curpot];
            npots[cur]=npots[curpot];
            potion[curpot]=nullptr;
        }
    }
    return 0;
}

void Hero::death(){
    deaths++;
}

unsigned Hero::getdeath(){
    return deaths;
}

unsigned Hero::getpot(unsigned n){
    return pots[n];
}

void Hero::changepot(unsigned n){
    pots[n]=0;
}

void Hero::printstats(){
    cout << "Name: " << name << endl;
    cout << "   Health: [" << healthPower << "/" << level*100 << "] " << endl;
    cout << "   Energy: [" << magicPower << "/" << maxap << "] " << endl;
    cout << "   Strenght: [" << strenght << "] " << endl;
    cout << "   Dexterity: [" << dexterity << "] " << endl;
    cout << "   Agility: [" << agility << "] " << endl;
    cout << "   Armor: [" << armor << "] " <<  endl;
    cout << "   Level: [" << level << "] " <<  endl;
    cout << "   Experience: [" << xp <<"/1000] " <<  endl;
    cout << "   Gold: [" <<gold << "]" << endl;
    cout << endl;
}