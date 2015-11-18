#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>

/*
 * ����������ƶ���ǽ,ǽ�����кܶ�����,ǽ���ƶ�����,�Ʋ�����ʱ��ǽ�Ͳ��ƶ���
 * �����СΪN*M�ĸ���ͼ,n������,��������ǽ���ƶ�(��up,right,down,left)+m(ƫ��)��ʾ
 * ���������n������������λ��
 *
 * ģ�������ӵĹ���
 * Ϊ�˼�ÿ���ƵĹ���(����һ��һ���ƣ��ǲ��Ǻ���?)���ǿ���������÷�����ǽ�����ƶ���������
 * ����:
 *    ��������������ƶ���������,����������Ҫ֪��ÿһ�е������������ֵ,ͨ��getMaxBoxNumByRow()���
 *    �������ƶ������������_right-_left-getMaxBoxNumByRow()��offset���ߵĽ�Сֵ
 *    �ƶ��Ĺ��̱Ƚ�����,�ڳ����ڻ�˵��
 * ���,���ﵽ"done"ʱ,�����ڰ���Ŀ����˳���������е�����,����������ǵ�λ�ü���
 */

using namespace std;

struct Box {
	int x, y;
};

int N, M, n;
int _left, _right, _down, _top;
Box box[11];
int RowBoxNum[21];
int ColBoxNum[21];

int getMaxBoxNumByRow() {
	int max = 0;
	for (int i = 0; i < N; i++) {
		if (RowBoxNum[i] > max)
			max = RowBoxNum[i];
	}
	return max;
}

int getMaxBoxNumByCol() {
	int max = 0;
	for (int i = 0; i < M; i++) {
		if (ColBoxNum[i] > max)
			max = ColBoxNum[i];
	}
	return max;
}

//�ĸ�������ƶ�,�����ƶ����Ⱥ�˳��ͬ,�����������ȹ�ע  ���Ҫ�ƶ�������ǽ  ������
//����Ҫ�����ȿ��ǵ�����������ÿ������/�е���ǰ��,���Ҫ�����������ƶ��еĴ����й�
bool cmpup(const Box& b1, const Box& b2) {
	return (b1.y == b2.y ? b1.x > b2.x : b1.y < b2.y); //xԽ���¿����ײ�
}
bool cmpdown(const Box& b1, const Box& b2) {
	return (b1.y == b2.y ? b1.x < b2.x : b1.y < b2.y); //xԽСԽ��������
}
bool cmpleft(const Box& b1, const Box& b2) {
	return (b1.x == b2.x ? b1.y > b2.y : b1.x < b2.x); //yԽ��Խ�����Ҳ�
}
bool cmpright(const Box& b1, const Box& b2) {
	return (b1.x == b2.x ? b1.y < b2.y : b1.x < b2.x); //yԽСԽ������
}


void move(string direction, int offset) {
	if (direction == "up") {
		int canOff = _down-_top-getMaxBoxNumByCol()+1;
		int realOff = (canOff < offset ? canOff : offset);
		sort(box, box+n, cmpup);

		//�����ƶ���y��ϵ����
		int x, y = -1;
		for (int i = 0; i < n; i++) {
			//�����box[i]������������ǰ������,Ҳ�����������ǽ������
			if (box[i].y != y) {
				y = box[i].y;
				//���������ܵ������Զλ�õ�x
				x = _down-realOff;
			} else {
				//����ͼ��������,�������...
				x--;
			}
			//����������ԭ����λ�ÿ϶���ı�(��ǽ��������),���ﵱǰ��x��λ��
			if (box[i].x > x) {
				RowBoxNum[box[i].x]--;
				box[i].x = x;
				RowBoxNum[box[i].x]++;
			}
		}
	} else if (direction == "down") {
		int canOff = _down-_top-getMaxBoxNumByCol()+1;
		int realOff = (canOff < offset ? canOff : offset);
		sort(box, box+n, cmpdown);
		int x, y = -1;
		//������
		for (int i = 0; i < n; i++) {
			if (box[i].y != y) {
				y = box[i].y;
				x = _top+realOff;
			} else {
				x++;
			}

			if (box[i].x < x) {
				RowBoxNum[box[i].x]--;
				box[i].x = x;
				RowBoxNum[box[i].x]++;
			}
		}
	} else if (direction == "left") {
		int canOff = _right-_left-getMaxBoxNumByRow()+1;
		int realOff = (canOff < offset ? canOff : offset);
		sort(box, box+n, cmpleft);
		int x = -1, y;
		//������
		for (int i = 0; i < n; i++) {
			if (box[i].x != x) {
				x = box[i].x;
				y = _right-realOff;
			} else {
				y--;
			}

			if (box[i].y > y) {
				ColBoxNum[box[i].y]--;
				box[i].y = y;
				ColBoxNum[box[i].y]++;
			}
		}
	} else if (direction == "right") {
		int canOff = _right-_left-getMaxBoxNumByRow()+1;
		int realOff = (canOff < offset ? canOff : offset);
		sort(box, box+n, cmpright);
		int x = -1, y;
		//������
		for (int i = 0; i < n; i++) {
			if (box[i].x != x) {
				x = box[i].x;
				y = _left+realOff;
			} else {
				y++;
			}

			if (box[i].y < y) {
				ColBoxNum[box[i].y]--;
				box[i].y = y;
				ColBoxNum[box[i].y]++;
			}
		}
	}
}
//���º���������,���Ϻ���������


int main() {
	//freopen("in.txt", "r", stdin);

	int T= 0;
	while (1) {
		scanf("%d %d", &N, &M);
		if (N == 0 && M == 0) break;
		T++;
		//���ı߽�ֵ
		_left = 0, _right = M-1, _top = 0, _down = N-1;


		for (int i = 0; i < N; i++) {
			RowBoxNum[i] = 0;
			for (int j = 0; j < M; j++)
				ColBoxNum[j] = 0;
		}
		memset(box, 0, sizeof(box));
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%d %d", &box[i].x, &box[i].y);
			RowBoxNum[box[i].x]++;
			ColBoxNum[box[i].y]++;
		}

		while (1) {
			string direction;
			int m;
			cin >> direction;
			if (direction == "done") {
				printf("Data set %d ends with boxes at locations",T);
				sort(box, box+n, cmpright);
				for (int i = 0; i < n; i++) {
					printf(" (%d,%d)", box[i].x, box[i].y);
				}
				printf(".\n");
				break;
			} else {
				scanf("%d", &m);
				move(direction, m);
			}
		}
	}
	return 0;
}
