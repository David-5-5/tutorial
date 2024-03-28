#include <string>
#include <iostream>

using namespace std ;

// union type
union CardId {
    short shortV;
    int intV;
    long longV;
};

typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, int len) 
{
     int i;
     for (i = 0; i < len; i++)
           printf(" %.2x", start[i]);
     printf("\n");
}

int main() {
    
    CardId card;
    card.longV = 55;
    card.intV = 44;
    card.shortV = 12;
    show_bytes((byte_pointer) &card, sizeof(card));
    cout << "1, card.shortV = 12" << endl;
    cout << "sizeof = " << sizeof(card) << endl;
    cout << "card.shortV = " << card.shortV << endl;
    cout << "card.intV = " << card.intV << endl;
    cout << "card.longV = " << card.longV << endl << endl;

    card.intV = 2100000000;
    show_bytes((byte_pointer) &card, sizeof(card));
    cout << "2, card.intV = 2100000000" << endl;
    cout << "sizeof = " << sizeof(card) << endl;
    cout << "card.shortV = " << card.shortV << endl;
    cout << "card.intV = " << card.intV << endl;
    cout << "card.longV = " << card.longV << endl << endl;

    card.longV = 21000000000000;
    show_bytes((byte_pointer) &card, sizeof(card));
    cout << "3 card.longV = 21000000000000" << endl;
    cout << "sizeof = " << sizeof(card) << endl;
    cout << "card.shortV = " << card.shortV << endl;
    cout << "card.msisdn = " << card.intV << endl;
    cout << "card.longV = " << card.longV << endl << endl;

}