#include <iostream>
#include <cmath>

using namespace std;

/*
 * �� n! < 2^k ������n
 * �ⷨ: ָ��ת����������log
 *     log(n)+log(n-1)+...+log(1) < k*log(2)
 */

int main() {
    int year;
    while (cin >> year && year != 0) {
        if (year < 1960 || year > 2160) break;
        int k = 4 << ((year-1960)/10);
        int ans = 1;
        double sum = 0;
        for (int i = 1; ; ++i) {
            sum += log(i);
            if (sum/log(2) > k)
                break;
            ans = i;
        }
        cout << ans << endl;
    }
}
