#include <stdio.h>
#include <iostream>

using namespace std;

/*
 * ö��0~2^32֮������֣������Ʊ�ʾ��Ϊ������С��L�����ָ���
 * ��Ϊ�ǻ��ģ�����ֻ��Ҫö������벿��,Ҳ����0~2^16�����Χ
 * Ȼ�������벿�ֹ���������������С��L�Ļ�ans��1
 * ע�⹹��ʱҪ�������������ԭ������ż��λ����������λ��(���м��Ǹ����ظ�)
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
    // ����Ĺ��췽����ʾ����abba��aba��������ʽ
    // ���ս��Ϊż������
    temp = (n<<l)|reverse(n);
    if (temp<=L) ans++;
    // ���ս��Ϊ��������
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
