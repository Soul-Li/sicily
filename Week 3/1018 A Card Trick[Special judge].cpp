
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

/*
 * 模拟即可，卡牌魔术
 * 题意：52张牌,助手抽5张,助手看牌后,把一张牌给观众,其余的给魔术师,一次一张
 * 牌的从小到大的顺序为AC,AD,AH,AS,2C,2D,...,KH,KS
 * 魔术师要做的是:
 * 1.记住第一张牌的大小和花色
 * 2.在余下的三张牌内,找出最小的牌所在的位置(1,2 or 3)加到第一步的牌的点数上面
 * 3.如果剩下两张牌不是按从小到大顺序排的话,再加3到第一步的点数上
 * 4.那么观众手上那张卡的花色就与第一步的卡相同,值与第三步的值相同
 * 例如 QH,10D,10C,4D,那么观众手上就是5H
 *
 * 那么你的工作就是做助手的工作,让魔术师能够按上面的流程推出来那张卡
 *
 * 解法:利用next_permutation()函数来求出符合要求的序列。
 *
 * 注意:此处模拟,使用数组n来作为card数组的index来判断序列是否符合要去,这样比直接用法card的全排列要方便
 *     输出的时候要输出卡牌(AC而不是1C)
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

//卡牌的比较函数
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
