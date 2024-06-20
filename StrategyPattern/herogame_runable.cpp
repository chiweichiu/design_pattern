#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For std::max

using namespace std;

class Hero;
class attackType {
public:
    virtual void attack(Hero* attacker, Hero* attacked)=0;
};

class Hero {
private:
    string name;
    int HP = 500;
    attackType* type;
public:
    Hero(string name, attackType* attackType) : name(name), type(attackType) {}
    void attack(Hero* attacked) {
        type->attack(this, attacked);
    }
    bool isDead() {
        return HP == 0;
    }
    string getName() { return name; }
    int getHP() { return HP; }
    void damage(int damage) {
        HP -= damage;
        HP = max(0, HP);
        cout << "Hero " << name << " was attacked by " << damage << " damage and HP: " << HP << endl;
    }
};

class waterball : public attackType {
public:
    void attack(Hero* attacker, Hero* attacked) {
        cout << "waterball attack" << endl;
        attacked->damage(attacker->getHP() * 0.5);
    }
};

class fireball : public attackType {
public:
    void attack(Hero* attacker, Hero* attacked) {
        cout << "fireball attack" << endl;
        for (int i = 0; i < 3; i++) {
            attacked->damage(30);
        }
    }
};

class earth : public attackType {
public:
    void attack(Hero* attacker, Hero* attacked) {
        cout << "earth attack" << endl;
        for (int i = 0; i < 10; i++) {
            attacked->damage(20);
        }
    }
};

class Game {
private:
    vector<Hero*> heros;
public:
    Game(Hero* h1, Hero* h2) {
        heros.push_back(h1);
        heros.push_back(h2);
    }
    void start() {
        while (true) {
            if (nextTurn()) break;
        }
    }
private:
    bool nextTurn() {
        cout << "nextTurn" << endl;
        Hero* attacker = heros[0];
        Hero* attacked = heros[1];
        cout << attacker->getName() << " is attacking " << attacked->getName() << endl;
        attacker->attack(attacked);
        cout << "attack-" << endl;

        if (attacked->isDead()) {
            cout << attacked->getName() << " is dead and " << attacker->getName() << " wins." << endl;
            return true;
        }
        swap(heros[0], heros[1]);
        return false;
    }
};

int main()
{
    cout << "new egg" << endl;
    Hero* egg = new Hero("egg", new waterball());
    cout << "new pig" << endl;
    Hero* pig = new Hero("pig", new fireball());
    cout << "new game" << endl;
    Game game(egg, pig);
    cout << "game start" << endl;
    game.start();
    cout << "delete" << endl;
    delete egg;
    delete pig;
    return 0;
}
