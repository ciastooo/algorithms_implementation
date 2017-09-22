#include <iostream>
using namespace std;
 
class num {
public:
        int a, b;
        void set(num *tab, int *count) {
                cin >> a;
                *(count + a) += 1;
                cin >> b;
        }
};
 
int main()
{
        int n;
        int test;
        cin >> n;
        num *tab = new num[n];
        int *count = new int[n]();
        for (int i = 0; i < n; i++) {
                tab[i].set(tab, count);
        }
        cin >> test;
        if (test == 0) {
                for (int i = 0; i < n; i++) {
                        int j = 0;
                        while (j < count[i]) {
                                cout << i << endl;
                                j++;
                        }
                }
        }
        else {
                num *sorted = new num[n + 1];
                for (int i = 1; i < n; i++) {
                        count[i] += count[i - 1];
                }
                for (int i = n - 1; i >= 0; i--) {
                        int p = count[tab[i].a];
                        count[tab[i].a] -= 1;
                        sorted[p] = tab[i];
                }
                for (int i = 1; i <= n; i++) {
                        cout << sorted[i].a << ',' << sorted[i].b << endl;
                }
                delete[] sorted;
        }
        delete[] tab;
        delete[] count;
        return 0;
}