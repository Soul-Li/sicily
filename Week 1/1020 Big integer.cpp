//������ģ��ʹ���ַ�����ʾ
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char x[401];
int X[401],a[101];
int main(){
    int T, n, i, j, t, b[101];
    scanf("%d", &T);
    for (; T > 0; T--) {
        memset(b,0,sizeof(b));

        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        scanf("%s",x);
        //X[i]��ʾ����ÿλ������
        for (t = 0;x[t]!='\0';t++){
            X[t]=x[t]-'0';
        }
        //ģ����ѧ�е���ģ����
        for(i=0;i<n;i++){
            for(j=0;j<t;j++){
                b[i]=(b[i]*10+X[j])%a[i];
            }
        }
        printf("(");
    for(i=0;i<n-1;i++){
        printf("%d,",b[i]);
    }
        printf("%d)\n",b[n-1]);
    }
    return 0;
}
