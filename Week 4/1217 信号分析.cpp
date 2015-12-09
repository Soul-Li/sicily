#include <stdio.h>
#include <iostream>

using namespace std;

/*
 * 枚举0~2^32之间的数字（二进制表示）为回文且小于L的数字个数
 * 因为是回文，所以只需要枚举其左半部分,也就是0~2^16这个范围
 * 然后根据左半部分构造整个回文数，小于L的话ans加1
 * 注意构造时要分两种情况，即原回文是偶数位数还是奇数位数(最中间那个会重复)
 */

unsigned long L;
int ans;

unsigned long reverse(unsigned long n) {
    unsigned long ret = 0;
    while (n>0) {
        ret = (ret<<1)|(n&1);
        n >>= 1;
    }
    return ret;
}

void cal(unsigned long n) {
    if (n == 0) return;
    unsigned long temp = n, l = 0;
    while (temp > 0) {
        temp >>= 1;
        l++;
    }
    // 下面的构造方法表示形如abba和aba的两种形式
    // 最终结果为偶数长度
    temp = (n<<l)|reverse(n);
    if (temp<=L) ans++;
    // 最终结果为奇数长度
    temp = (n<<(l-1))|reverse(n>>1);
    if (temp<=L) ans++;
    return;
}
void dfs(unsigned long n, unsigned long lev) {
    if (lev == 0) {
        cal(n);
        return;
    }
    dfs(n<<1, lev-1);
    dfs((n<<1)+1, lev-1);
    return;
}

int main() {
    cin >> L;
    ans = 0;
    dfs(0, 16);
    cout << ans << endl;
}
