#include<iostream>
#include <time.h>
#include<cmath>
using namespace std;

int main()
{
    srand(time(NULL));

    int x, y, sum, counter  =  0;

    for (int i = 1; i < 6; i++)
    {
        cout << "Attempt" << endl;
        cout << "input X:";
        cin >> x;
        cout << "input Y:";
        cin >> y;
        x = x + (rand() % 11) - 5;
        y = y + (rand() % 11) - 5;
        cout << "Shot coords: (" << x << "," << y << ")" << endl << endl;
        counter = 5 - (int)sqrt(pow(x,2)+pow(y,2));
        if (((counter>>(sizeof(int) * 8 - 1))&1) == 0)
        {
            sum += counter;
        }
    }

     if (sum >= 10) cout <<"You Win! Your score: " << sum;
     else cout<<"Loser! Your score: " << sum ;

    return 0;
}
