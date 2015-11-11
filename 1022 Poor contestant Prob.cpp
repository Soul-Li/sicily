#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

/*
 * 第一:不要用c++的流作输入输出,相比之下scanf与printf的速度要快很多
 * 第二:题目的数据量很大,用传统的排序或者sort函数是过不了的,必定超时
 * 敌三:一开始也是超时,从网上get an idea,不过是自己implement
 *
 * 解法:建立2个堆,一个大堆一个小堆,在插入的过程中保持大小堆的平衡(即小堆的size总等于大堆或者比大堆多1)
 * 这样总的size为奇数需要去get medium时就可以直接取小堆顶部的节点即为中位数。
 *
 * 主要操作:两个堆节点的插入加上堆顶节点的转移(涉及到堆的调整)
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
//节点比较函数
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

//大堆的插入
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

//小堆的插入
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

//大堆的调整
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
//小堆的调整
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

//第一个自动插入小堆
//小堆size与大堆相等,按大堆顶的情况来决定是否需要调整
//或
//小堆size比大堆多1,按小堆顶的情况来决定是否需要调整
//
//画个图就明白了
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
				//这里计算size要把大堆和小堆的size加起来,开始做的时候忘记了
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

