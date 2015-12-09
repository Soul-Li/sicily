#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

//快速乘法，没搞懂
long long mul(long long a, long long b, long long mod) {
    long long c = 0;
    const int base = 2;
    for (; b != 0; b /= base) {
        c += (b % base) * a;
        c %= mod;
        a = (a * base) % mod;
    }
    return c;
}

long long cube(long long x, long long mod){
    return mul(mul(x,x,mod), x, mod);
}

int main () {
    int t, length;
    // result ——记录最终结果
    // remain ——当前的需要比较的尾数
    long long result, remain, power, step;
    char str[11];

    scanf("%d",&t);
    while( t-- ){
        scanf("%s",&str);
        length = strlen(str);
        result = remain = str[length-1] - '0';
        power = 10;

        // 只需要从右往左比较尾数，前一位尾数相等了就比较下一位
        // 一开始，1^3尾数为1,3^3尾数为7,7^3尾数为3,9^3尾数为9
        if( result == 3 ) result = 7;
        else if( result == 7 ) result = 3;

        for( int i = length - 2; i >= 0; --i ){
            remain += (str[i] - '0') * power;
            step = power;
            power *= 10;
            // 如果当前不符合，那么在当前位上面再加1，即将result增加一个step
            while( cube(result,power) != remain ){
                result += step;
            }
        }
        printf("%lld\n",result);
    }

    return 0;
}
