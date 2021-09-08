/**
* Example of 'Factory' design pattern.
* The original of the study= https://refactoring.guru/design-patterns/factory-method/cpp/example
* This is a simplified and comment lines translated version of original.
*/
#include <iostream>
class Product {
public:
    virtual ~Product() {}
    virtual std::string Operation() const = 0;
};

class ConcreteProduct1 : public Product {
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct1}";
    }
};
class ConcreteProduct2 : public Product {
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct2}";
    }
};

/**
*Creator s�n�f�, Product s�n�f�n�n bir nesnesini d�nd�rmesi beklenen fabrika y�ntemini bildirir. 
*Olu�turucunun alt s�n�flar� genellikle bu y�ntemin uygulanmas�n� sa�lar.
 */

class Creator {

public:
    virtual ~Creator() {};
    virtual Product* FactoryMethod() const = 0;

    std::string SomeOperation() const {
        // Bir product nesnesi olu�turmak i�in fabrika y�ntemini �a��r�r.
        Product* product = this->FactoryMethod();
        // product nesnesini kullan�r.
        std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }
};

/**
 * ConcreteCreator'lar, ortaya ��kan �r�n�n t�r�n� de�i�tirmek i�in 
 * factory y�ntemini ge�ersiz k�lar.
 */
class ConcreteCreator1 : public Creator {
    /**
     * Somut �r�n asl�nda y�ntemden d�nd�r�lse bile, 
     * y�ntemin imzas�n�n hala soyut �r�n t�r�n� kulland���na dikkat edin. 
     * Bu �ekilde Yarat�c�, somut �r�n s�n�flar�ndan ba��ms�z kalabilir.
     */
public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct1();
    }
};

class ConcreteCreator2 : public Creator {
public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct2();
    }
};

/**
 * �stemci kodu, temel arabirimi arac�l���yla da olsa 
 * somut bir olu�turucu �rne�iyle �al���r. 
 * �stemci, temel arabirim arac�l���yla i�erik olu�turucuyla 
 * �al��maya devam etti�i s�rece, 
 * onu herhangi bir olu�turucunun alt s�n�f�ndan ge�irebilirsiniz.
 */
void ClientCode(const Creator& creator) {

    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
        << creator.SomeOperation() << std::endl;
}

/**
 * Uygulama, yap�land�rmaya veya ortama ba�l� olarak bir yarat�c�n�n t�r�n� se�er.
 */

int main() {
    std::cout << "App: Launched with the ConcreteCreator1.\n";
    Creator* creator = new ConcreteCreator1();
    ClientCode(*creator);
    std::cout << std::endl;
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    Creator* creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator;
    delete creator2;
    return 0;
}