#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    char c[256];
    while (scanf("%c", &c[0]) && c[0] != '#') {
        int sum = 0;
        sum += c[0]-64;
        for (int i = 1; scanf("%c", &c[i]) && c[i] != '\n'; i++) {
            sum += (c[i] == ' ' ? 0 : c[i]-64)*(i+1);
        }
        printf("%d\n", sum);
    }
    return 0;
}
