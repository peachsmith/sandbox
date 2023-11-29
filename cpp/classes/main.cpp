#include <iostream>
#include <cstring>

#define BAGEL_NAME_SIZE 32

enum Flavor
{
    PLAIN = 0,
    BLUEBERRY,
    CINNAMON,
    BAGEL_FLAVOR_MAX
};

class Data
{
public:
    int num;

    Data()
    {
    }

    Data(int num)
    {
        this->num = num;
    }
};

// a plain old regular class
class Bagel
{
private:
    static const char *BagelNames[4];

    // A common convention is to use the m_ prefix for member variables.
    int m_ID;

    // This creates an instance of the Data class.
    // If this instance is not created in a member initializer list, it will
    // be instantiated with the default constructor.
    Data m_Data;

public:
    char Name[BAGEL_NAME_SIZE];
    int Price;

    // default constructor
    // This will be present event if we don't define it.
    // When using a member initializer list, the members should be initialized
    // in the order they were declared.
    Bagel() : m_ID(0), m_Data(0xBEEF) // member initializer list
    {
        Name[0] = '\0';
    }

    // parameterized constructor
    Bagel(int id)
    {
        m_ID = id;
        Name[0] = '\0';
    }

    // destructor (automatically called when the class is deleted)
    ~Bagel()
    {
    }

    Bagel(int id, int price, enum Flavor name)
    {
        m_ID = id;
        Price = price;
        name = name >= BAGEL_FLAVOR_MAX ? BAGEL_FLAVOR_MAX : name;

        size_t l = strlen(BagelNames[name]);
        for (size_t i = 0; i < l; i++)
        {
            Name[i] = BagelNames[name][i];
        }
        Name[l] = '\0';
    }

    void Describe()
    {
        std::cout << "ID: " << m_ID << ", name: " << Name << ", price: " << Price << std::endl;
    }
};

const char *Bagel::BagelNames[4] = {"plain",
                                    "blueberry",
                                    "cinnamon",
                                    "none"};

class Fish
{
public:
    void Bloop()
    {
        std::cout << "bloop" << std::endl;
    }

    // A virtual function may be overridden.
    virtual void Floop()
    {
        std::cout << "floop from a generic fish" << std::endl;
    }

    // A pure virtual function has no default implementation.
    // Classes that inherit from this class are required to provide an
    // implementation in order to be instantiated.F
    virtual void Sploop() = 0;

    // Protected stuff is accessible by classes that inherit from this class.
protected:
    int m_ID;
};

class Amberjack : public Fish
{
public:
    Amberjack()
    {
        m_ID = 1; // m_ID is inherited from the Fish class
    }

    void DefineAmberjack()
    {
        std::cout << "[ID: " << m_ID << "] An amberjack wears a plaid shirt and chops amber." << std::endl;
    }

    // The override keyword is optional here, but it's usefule
    // for reminding ourselves that a function has been overridden.
    // The use of the override keyword is considered a C++11 extension
    // and may require additional compiler options on certain platforms.
    void Floop() // override
    {
        std::cout << "floop, but from an amberjack" << std::endl;
    }

    void Sploop() // override
    {
        std::cout << "The amberjack gladly implemented the Sploop method." << std::endl;
    }
};

class Gar : public Fish
{
public:
    Gar()
    {
        m_ID = 2; // m_ID is inherited from the Fish class
    }

    void DefineGar()
    {
        std::cout << "[ID: " << m_ID << "] A gar is stored in a garage." << std::endl;
    }

    void Sploop() // override
    {
        std::cout << "The gar begrudgingly implemented the Sploop method." << std::endl;
    }
};

void doFishThings(Fish *fish)
{
    fish->Bloop();
    fish->Floop();
    fish->Sploop();
}

int main()
{
    //------------------------------------------------------------------------
    // class basics

    Bagel noBagel;
    Bagel plainBagel(1, 100, PLAIN);
    Bagel blueberryBagel(2, 314, BLUEBERRY);
    Bagel cinnamonBagel(3, 250, CINNAMON);

    noBagel.Describe();
    plainBagel.Describe();
    blueberryBagel.Describe();
    cinnamonBagel.Describe();

    //------------------------------------------------------------------------
    // inheritance

    Amberjack amber;
    Gar gar;

    amber.DefineAmberjack();
    doFishThings(&amber);

    gar.DefineGar();
    doFishThings(&gar);

    return 0;
}