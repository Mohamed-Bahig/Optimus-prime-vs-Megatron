#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
class Weapon {
    protected  :
        string name;
        int damage;
        int accuracy;
    public:
        Weapon(string name, int damage, int accuracy) : name(name), damage(damage) ,accuracy(accuracy){}
        virtual bool didHit() {
            int roll = rand() % 100 + 1; 
           return roll <= accuracy;
        }
        string getName() const { return name; }
        int getDamage() const { return damage; }
};
class Character {
    protected  :
        string name;
        int health;
        vector<Weapon> weapons;
    public:
    Character(string name, int health) : name(name), health(health) {}
    virtual void attack(Character &opponent) = 0;
    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }
    bool isAlive() const { return health > 0; }
    string getName() const { return name; }
    int getHealth() const { return health; }
};
    class OptimusPrime : public Character {
    public :
        OptimusPrime() : Character("Optimus Prime", 100)     {
            weapons.emplace_back("Ion rifle", 6, 100);
            weapons.emplace_back("Energon swords", 12, 80);
            weapons.emplace_back("Shoulder canon", 45, 50);
        }
        void attack(Character &opponent) override {
            Weapon &weapon = weapons[rand() % weapons.size()];
            cout << name << " attacks " << opponent.getName() << " with " << weapon.getName() << "!" << endl;
            if(weapon.didHit()) {
                opponent.takeDamage(weapon.getDamage());
                cout << "Hit! " << opponent.getName() << " takes " << weapon.getDamage() << " damage." << endl;
            } else {
                cout << "Missed!" << endl;
            }
        }
    };
    class Megatron : public Character {
    public :
        Megatron() : Character("Megatron", 100) {
            weapons.emplace_back("Fusion cannon", 9, 90);
            weapons.emplace_back("Fusion sword", 18, 70);
            weapons.emplace_back("Tank mode", 60, 15);
        }
        void attack(Character &opponent) override {
            Weapon &weapon = weapons[rand() % weapons.size()];
            cout << name << " attacks " << opponent.getName() << " with " << weapon.getName() << "!" << endl;
            if(weapon.didHit()) {
                opponent.takeDamage(weapon.getDamage());
                cout << "Hit! " << opponent.getName() << " takes " << weapon.getDamage() << " damage." << endl;
            } else {
                cout << "Missed!" << endl;
            }
        }

    };
    class fight {
    public:     
        void startFight(Character &c1, Character &c2) {
        cout << "The battle begins between " << c1.getName() << " and " << c2.getName() << "!" << endl;
            while(c1.isAlive() && c2.isAlive()) {
                c1.attack(c2);
                cout << c1.getName() << " Health: " << c1.getHealth() << ", " << c2.getName() << " Health: " << c2.getHealth() << endl;
                if(c2.isAlive()) {
                    c2.attack(c1);
                    cout << c1.getName() << " Health: " << c1.getHealth() << ", " << c2.getName() << " Health: " << c2.getHealth() << endl;
                }
               }
               cout << "-------------------------------The battle is over!-------------------------------" << endl;
            cout << (c1.isAlive() ? c1.getName() : c2.getName()) << " wins the battle!" << endl;
        }
        };
    int main() {
        srand(static_cast<unsigned int>(time(0)));
        OptimusPrime optimus;
        Megatron megatron;
        fight battle;   
        battle.startFight(optimus, megatron);
    return 0;
}
