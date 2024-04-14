#ifndef CALCULATEBUY_H
#define CALCULATEBUY_H

#include <QDialog>

class CalculateBuy
{
public:
    CalculateBuy();
    void ZeroValue();
    uint getSum();
    int getValueOf(int m);
    void calcSumCost(int Mv, int Cv, int Pv, int Nv, int Kv);
    void addToOrder(int t);

private:

    uint sumCost;
    uint Pilesos;
    uint Kruzka;
    uint Microphone;
    uint Kovrik;
    uint Microwave;
};

#endif // CALCULATE_BUY H
