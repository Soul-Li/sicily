
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

/*
 * ģ�⼴�ɣ�����ħ��
 * ���⣺52����,���ֳ�5��,���ֿ��ƺ�,��һ���Ƹ�����,����ĸ�ħ��ʦ,һ��һ��
 * �ƵĴ�С�����˳��ΪAC,AD,AH,AS,2C,2D,...,KH,KS
 * ħ��ʦҪ������:
 * 1.��ס��һ���ƵĴ�С�ͻ�ɫ
 * 2.�����µ���������,�ҳ���С�������ڵ�λ��(1,2 or 3)�ӵ���һ�����Ƶĵ�������
 * 3.���ʣ�������Ʋ��ǰ���С����˳���ŵĻ�,�ټ�3����һ���ĵ�����
 * 4.��ô�����������ſ��Ļ�ɫ�����һ���Ŀ���ͬ,ֵ���������ֵ��ͬ
 * ���� QH,10D,10C,4D,��ô�������Ͼ���5H
 *
 * ��ô��Ĺ������������ֵĹ���,��ħ��ʦ�ܹ�������������Ƴ������ſ�
 *
 * �ⷨ:����next_permutation()�������������Ҫ������С�
 *
 * ע��:�˴�ģ��,ʹ������n����Ϊcard�����index���ж������Ƿ����Ҫȥ,������ֱ���÷�card��ȫ����Ҫ����
 *     �����ʱ��Ҫ�������(AC������1C)
 */

struct Card {
	int num;
	char suit;
	string toString() {
		string s = "";
		if (num == 1) s+='A';
		if (num >= 2 && num <= 9) s+=(char)('0'+num);
		if (num == 10) s += "10";
		if (num == 11) s += 'J';
		if (num == 12) s += 'Q';
		if (num == 13) s += 'K';
		s += suit;
		return s;
	}
};

//���ƵıȽϺ���
bool operator< (const Card& card1, const Card& card2) {
	if (card1.num < card2.num) return true;
	else if (card1.num == card2.num) {
		return (card1.suit < card2.suit);
	} else {
		return false;
	}
}

int cmp(const Card& card1, const Card& card2, const Card& card3) {
	if (card1 < card2 && card1 < card3) return 1;
	if (card2 < card1 && card2 < card3) return 2;
	if (card3 < card1 && card3 < card2) return 3;
}

int main() {
	//freopen("in.txt", "r", stdin);
	int T;
	Card card[6];
	string c;
	scanf("%d", &T);
	for (int casenum = 1; casenum <= T; casenum++) {
		int index[5] = {1,2,3,4,5};
		for (int i = 1; i <= 5; i++) {
			cin >> c;
			if (c.length() == 3) {
				card[i].num = 10;
				card[i].suit = c[2];
			} else {
				if (c[0] == 'A') card[i].num = 1;
				if (c[0] == 'J') card[i].num = 11;
				if (c[0] == 'Q') card[i].num = 12;
				if (c[0] == 'K') card[i].num = 13;
				if (c[0] >= '2' && c[0] <= '9') card[i].num = c[0]-'0';
				card[i].suit = c[1];
			}
		}
		do {
			if (card[index[0]].suit != card[index[1]].suit) continue;
			int temp1 = card[index[1]].num+6, temp2 = card[index[0]].num;
			if (temp1 % 13 < temp2) continue;
			//printf("%d ",temp1);
			//printf("%d \n",temp2);

			int add = cmp(card[index[2]], card[index[3]], card[index[4]]);
			if (add == 1) add += (card[index[4]] < card[index[3]] ? 3 : 0);
			if (add == 2) add += (card[index[4]] < card[index[2]] ? 3 : 0);
			if (add == 3) add += (card[index[3]] < card[index[2]] ? 3 : 0);

			if ((card[index[1]].num+add) % 13 == card[index[0]].num) break;
		} while (next_permutation(index, index+5));
		printf("Problem %d:", casenum);
		for (int i = 0; i < 5; i++) {
			cout << " " << card[index[i]].toString();
		}
		printf("\n");
	}
}
