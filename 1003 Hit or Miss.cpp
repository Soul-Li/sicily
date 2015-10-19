#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

/*
 * 纯模拟题,题目巨长,仔细阅读即可
 * 大致题意:
 *     第一个玩家拥有52张牌,其他玩家没有牌在手上
 *     每个手里有牌的玩家可以报数(从1开始),没有牌的玩家不能报数
 *     对于某个玩家,报的数字如果跟牌顶的数字相同,如果该玩家不是最后一个玩家,那么将该牌送给下一位玩家;如果是最后一个玩家,则将该牌丢掉
 *     如果不相同,则把牌顶上的牌放到自己牌堆的底部,继续下一位玩家叫牌.
 *     记录最后一个玩家丢掉的牌数,如果丢掉的牌数等于52,输出每个玩家最后离手的那张牌,否则输出unwinnable.
 *
 * 注:如果某位玩家的牌空了,当他下一次再有牌继续叫牌时,报的数字是上次所报数字加1而不是重新从1开始.
 *
 * unwinnable的条件很难判断,这里用一个叫牌次数turns来决定允许的最大循环次数,当turns超过10000时,判断不能成功
 *
 */

struct player {
	int count;             //记录匹配时的数字,也是最后匹配数字
	queue<int> cards;      //记录玩家牌的队列
	player() {
		count = 0;
	}
};

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int n, c = 0;
	scanf("%d", &n);
	while (n--) {

		c++;
		int playerNum;
		scanf("%d", &playerNum);
		player p[10];
		//initialize
		for (int i = 0; i <= 51; i++) {
			int t;
			scanf("%d", &t);
			p[0].cards.push(t);
		}

		bool finish = false;
		int turns = 0, discard = 0;
		//模拟过程
		while (turns <= 10000) {

			for (int i = 0; i < playerNum; i++) {
				if (p[i].cards.empty()) continue;
				//报数从1开始
				p[i].count++;
				if (p[i].count == 14)
					p[i].count = 1;
				//匹配成功
				if (p[i].count == p[i].cards.front()) {
					p[i].cards.pop();
					//是最后一个玩家
					if (i == playerNum-1)
						discard++;
					else
						p[i+1].cards.push(p[i].count);
				} else {
					//把牌顶的牌放到牌底
					p[i].cards.push(p[i].cards.front());
					p[i].cards.pop();
				}
			}

			turns++;
			if (discard == 52) {
				finish = true;
				break;
			}
		}

		if (finish) {
			printf("Case %d:", c);
			for (int i = 0; i < playerNum; i++) {
				printf(" %d",p[i].count);
			}
			printf("\n");
		} else {
			printf("Case %d: unwinnable\n", c);
		}
	}
	return 0;
}
