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
*Creator sýnýfý, Product sýnýfýnýn bir nesnesini döndürmesi beklenen fabrika yöntemini bildirir. 
*Oluþturucunun alt sýnýflarý genellikle bu yöntemin uygulanmasýný saðlar.
 */

class Creator {

public:
    virtual ~Creator() {};
    virtual Product* FactoryMethod() const = 0;

    std::string SomeOperation() const {
        // Bir product nesnesi oluþturmak için fabrika yöntemini çaðýrýr.
        Product* product = this->FactoryMethod();
        // product nesnesini kullanýr.
        std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }
};

/**
 * ConcreteCreator'lar, ortaya çýkan ürünün türünü deðiþtirmek için 
 * factory yöntemini geçersiz kýlar.
 */
class ConcreteCreator1 : public Creator {
    /**
     * Somut ürün aslýnda yöntemden döndürülse bile, 
     * yöntemin imzasýnýn hala soyut ürün türünü kullandýðýna dikkat edin. 
     * Bu þekilde Yaratýcý, somut ürün sýnýflarýndan baðýmsýz kalabilir.
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
 * Ýstemci kodu, temel arabirimi aracýlýðýyla da olsa 
 * somut bir oluþturucu örneðiyle çalýþýr. 
 * Ýstemci, temel arabirim aracýlýðýyla içerik oluþturucuyla 
 * çalýþmaya devam ettiði sürece, 
 * onu herhangi bir oluþturucunun alt sýnýfýndan geçirebilirsiniz.
 */
void ClientCode(const Creator& creator) {

    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
        << creator.SomeOperation() << std::endl;
}

/**
 * Uygulama, yapýlandýrmaya veya ortama baðlý olarak bir yaratýcýnýn türünü seçer.
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