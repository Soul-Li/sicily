#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

/*
 * ��ģ����,��Ŀ�޳�,��ϸ�Ķ�����
 * ��������:
 *     ��һ�����ӵ��52����,�������û����������
 *     ÿ���������Ƶ���ҿ��Ա���(��1��ʼ),û���Ƶ���Ҳ��ܱ���
 *     ����ĳ�����,��������������ƶ���������ͬ,�������Ҳ������һ�����,��ô�������͸���һλ���;��������һ�����,�򽫸��ƶ���
 *     �������ͬ,����ƶ��ϵ��Ʒŵ��Լ��ƶѵĵײ�,������һλ��ҽ���.
 *     ��¼���һ����Ҷ���������,�����������������52,���ÿ�����������ֵ�������,�������unwinnable.
 *
 * ע:���ĳλ��ҵ��ƿ���,������һ�������Ƽ�������ʱ,�����������ϴ��������ּ�1���������´�1��ʼ.
 *
 * unwinnable�����������ж�,������һ�����ƴ���turns��������������ѭ������,��turns����10000ʱ,�жϲ��ܳɹ�
 *
 */

struct player {
	int count;             //��¼ƥ��ʱ������,Ҳ�����ƥ������
	queue<int> cards;      //��¼����ƵĶ���
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
		//ģ�����
		while (turns <= 10000) {

			for (int i = 0; i < playerNum; i++) {
				if (p[i].cards.empty()) continue;
				//������1��ʼ
				p[i].count++;
				if (p[i].count == 14)
					p[i].count = 1;
				//ƥ��ɹ�
				if (p[i].count == p[i].cards.front()) {
					p[i].cards.pop();
					//�����һ�����
					if (i == playerNum-1)
						discard++;
					else
						p[i+1].cards.push(p[i].count);
				} else {
					//���ƶ����Ʒŵ��Ƶ�
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
