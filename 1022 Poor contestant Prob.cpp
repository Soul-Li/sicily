#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

/*
 * ��һ:��Ҫ��c++�������������,���֮��scanf��printf���ٶ�Ҫ��ܶ�
 * �ڶ�:��Ŀ���������ܴ�,�ô�ͳ���������sort�����ǹ����˵�,�ض���ʱ
 * ����:һ��ʼҲ�ǳ�ʱ,������get an idea,�������Լ�implement
 *
 * �ⷨ:����2����,һ�����һ��С��,�ڲ���Ĺ����б��ִ�С�ѵ�ƽ��(��С�ѵ�size�ܵ��ڴ�ѻ��߱ȴ�Ѷ�1)
 * �����ܵ�sizeΪ������Ҫȥget mediumʱ�Ϳ���ֱ��ȡС�Ѷ����Ľڵ㼴Ϊ��λ����
 *
 * ��Ҫ����:�����ѽڵ�Ĳ�����϶Ѷ��ڵ��ת��(�漰���ѵĵ���)
 */

struct Acmer {
	char name[15];
	int score;
	Acmer() {}
	Acmer(char s[], int n) {
		strcpy(name, s);
		score = n;
	}
};
//�ڵ�ȽϺ���
bool operator>(const Acmer& a1, const Acmer& a2) {
	return (a1.score > a2.score || (a1.score == a2.score && strcmp(a1.name, a2.name) == 1));
}
bool operator<(const Acmer& a1, const Acmer& a2) {
	return (a1.score < a2.score || (a1.score == a2.score && strcmp(a1.name, a2.name) == -1));
}

Acmer BIG[50005];
Acmer SMALL[50005];
int big_count = 0;
int small_count = 0;

//��ѵĲ���
void big_heap_insert(const Acmer acmer, int low, int high) {
	if (big_count == 0) {
		BIG[big_count++] = acmer;
		return;
	}
	int i = 0;
	for (i = high; i > 0 && BIG[(i-1)/2] < acmer; i = (i-1)/2) {
		BIG[i] = BIG[(i-1)/2];
	}
	BIG[i] = acmer;
	big_count++;
	return;
}

//С�ѵĲ���
void small_heap_insert(const Acmer acmer, int low, int high) {
	if (small_count == 0) {
		SMALL[small_count++] = acmer;
		return;
	}
	int i = 0;
	for (i = high; i > 0 && SMALL[(i-1)/2] > acmer; i = (i-1)/2) {
		SMALL[i] = SMALL[(i-1)/2];
	}
	SMALL[i] = acmer;
	small_count++;
	return;
}

//��ѵĵ���
void big_heap_adjust(const Acmer acmer) {
	int low = 0, large = 2*low+1;
	while (large < big_count) {
		if (large+1 < big_count && BIG[large+1] > BIG[large]) {
			large++;
		}
		if (BIG[large] < acmer) break;
		BIG[low] = BIG[large];
		low = large;
		large = 2*low+1;
	}
	BIG[low] = acmer;
}
//С�ѵĵ���
void small_heap_adjust(const Acmer acmer) {
	int low = 0, small = 2*low+1;
	while (small < small_count) {
		if (small+1 < small_count && SMALL[small+1] < SMALL[small]) {
			small++;
		}
		if (SMALL[small] > acmer) break;
		SMALL[low] = SMALL[small];
		low = small;
		small = 2*low+1;
	}
	SMALL[low] = acmer;
}

//��һ���Զ�����С��
//С��size�������,����Ѷ�������������Ƿ���Ҫ����
//��
//С��size�ȴ�Ѷ�1,��С�Ѷ�������������Ƿ���Ҫ����
//
//����ͼ��������
void Insert(const Acmer acmer) {
	if (big_count == 0 && small_count == 0) {
		small_heap_insert(acmer, 0, small_count);
		return;
	}
	if (big_count == small_count) {
		if (acmer > BIG[0]) {
			small_heap_insert(acmer, 0, small_count);
		} else {
			small_heap_insert(BIG[0], 0, small_count);
			big_heap_adjust(acmer);
		}
	} else if (big_count+1 == small_count) {
		if (acmer < SMALL[0]) {
			big_heap_insert(acmer, 0, big_count);
		} else {
			big_heap_insert(SMALL[0], 0, big_count);
			small_heap_adjust(acmer);
		}
	}
	return;
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int M;
	scanf("%d", &M);
	while (M--) {
		big_count = 0;
		small_count = 0;
		while (1) {
			char ins[10];
			scanf("%s", ins);
			if (strcmp(ins, "Add") == 0) {
				char name[15];
				int n;
				scanf("%s %d", &name, &n);
				Acmer acmer = Acmer(name, n);
				Insert(acmer);
			} else if (strcmp(ins, "Query") == 0) {
				//�������sizeҪ�Ѵ�Ѻ�С�ѵ�size������,��ʼ����ʱ��������
				if ((small_count+big_count) % 2 != 0) {
					printf("%s\n", SMALL[0].name);
				} else {
					printf("No one!\n");
				}
			} else if (strcmp(ins , "End") == 0) {
				if ((small_count+big_count) % 2 != 0) {
					printf("%s is so poor.\n", SMALL[0].name);
				} else {
					printf("Happy BG meeting!!\n");
				}
				break;
			}
		}
		if (M) printf("\n");
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}

