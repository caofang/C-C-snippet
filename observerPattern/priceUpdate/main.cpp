
#include "Subject.h"
#include "Shop.h"
#include "DummyProduct.h"
#include <iostream>

using namespace std;
int main(int argc, char* argv[])
{
    DummyProduct product1;

                    
    // We have four shops wanting to keep updated price set by product1 owner
    Shop shop1("Shop 1");
    Shop shop2("Shop 2");

    product1.Attach(&shop1);
    product1.Attach(&shop2);


    //Now lets try changing the products price, this should update the shops automatically
    product1.ChangePrice(11.0f);

    cout<< "shop1 price: " << shop1.getPrice() << "\n";
    //Now shop2 is not interested in new prices so they unsubscribe
    product1.Detach(&shop2);            

    //Now lets try changing the products price again
    product1.ChangePrice(26.0f);

    return 0;
}