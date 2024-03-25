#include <string>
#include <iostream>

using namespace std ;

// 联合体的定义
union CardId {
    short shortV;
    int intV;
    long longV;
};

int main() {
    CardId card;
    card.shortV = 12;
    cout << "1, card.shortV = 12" << endl;
    cout << "card.shortV = " << card.shortV << endl;
    cout << "card.intV = " << card.intV << endl;
    cout << "card.longV = " << card.longV << endl << endl;

    card.intV = 23456;
    cout << "2, set card.intV = 23456" << endl;
    cout << "card.shortV = " << card.shortV << endl;
    cout << "card.intV = " << card.intV << endl;
    cout << "card.longV = " << card.longV << endl << endl;

    card.longV = 34567;
    cout << "3 set card.longV = 34567" << endl;
    cout << "card.shortV = " << card.shortV << endl;
    cout << "card.msisdn = " << card.intV << endl;
    cout << "card.longV = " << card.longV << endl << endl;


}