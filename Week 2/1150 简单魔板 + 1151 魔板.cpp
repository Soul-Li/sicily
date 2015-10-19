#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;

/*
 * 简单魔板:
 *    x = 上层数字, y = 下层数字
 *    数组存储加上队头队尾指针,模拟广度优先搜索
 *    缺点是剪枝策略效率过低,当n足够大时容易超时
 * 改进策略:
 *    在插入前的查重处理中采用一种特殊的hash函数——康托展开,将原来的状态空间缩小到8!
 *    而且在查重过程中避免采用遍历当前数组而是直接将x,y通过康托展开映射到8!状态空间中查找,提高了效率
 */

/*
 * x,y 代表当前节点的上下层数字
 * op  代表由上一个节点得到当前节点所进行的操作
 * pre 代表上一个节点在数组中的下标,用于回溯输出
 * dep 代表当前节点深度,当深度超过N时节点不插入数组
 */
struct qt {
	int x;
	int y;
	char op;
	int pre;
	int dep;
	qt() { }
	qt(int X, int Y, char OP, int PRE, int DEP) {
		x = X;
		y = Y;
		op = OP;
		pre = PRE;
		dep = DEP;
	}
};

int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040};    //0~7的阶乘,用于得到康托展开值
bool exist[50000];

//对当前节点进行A操作
qt opA(const qt QT, int index) {
	qt temp = qt(QT.y, QT.x, 'A', index, QT.dep+1);
	return temp;
}

//对当前节点进行B操作
qt opB(const qt QT, int index) {
	int a = QT.x % 10, b = QT.y % 10;
	qt temp = qt(a*1000+(QT.x/10), b*1000+(QT.y/10), 'B', index, QT.dep+1);
	return temp;
}

//对当前节点进行C操作
qt opC(const qt QT, int index) {
	int x1 = QT.x/1000, x2 = (QT.x%1000)/100, x3 = (QT.x%100)/10, x4 = QT.x%10;
	int y1 = QT.y/1000, y2 = (QT.y%1000)/100, y3 = (QT.y%100)/10, y4 = QT.y%10;
	qt temp = qt(x1*1000+y2*100+x2*10+x4, y1*1000+y3*100+x3*10+y4, 'C', index, QT.dep+1);
	return temp;
}

//康托展开
int cantor(long num) {
	int temp[8];
	for (int i = 7; i >= 0; i--) {
		temp[i] = num%10;
		num = num/10;
	}
	for (int i = 0; i < 8; i++) {
		int n = 0;
		for (int j = i+1; j < 8; j++) {
			if (temp[j] < temp[i]) n++;
		}
		num += n*fac[7-i];
	}
	return num;
}

int main() {
	int N, fp, rp;
	qt qm[81000];                //存储节点的数组
	vector<char> sop;            //输出用的字符数组
	char op = 'A';               //代表操作的字符
	bool flag = false;           //是否找到结果的标记

	while(1) {
		memset(exist, false, sizeof(exist));
		scanf("%d", &N);
		if (N == -1) break;

		int a, b, c, d, end1, end2;

		//获取最终需要得到的状态
		scanf("%d %d %d %d", &a, &b, &c, &d);
		end1 = a*1000+b*100+c*10+d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		end2 = a*1000+b*100+c*10+d;

		//初始状态
		qm[0] = qt(1234,8765,' ',-1, 0);
		exist[cantor(12348765)] = true;
		fp = 0;
		rp = 1;

		while (fp != rp) {
			//首先要对判断当前要进行处理的节点是否是目标节点
			//如果对qm[rp]进行判断,当初始节点就是目标节点时会出错
			if (qm[fp].x == end1 && qm[fp].y == end2) {
				flag = true;
				break;
			}
			qt temp;
			switch(op) {
			case 'A':
				temp = opA(qm[fp], fp);
				break;
			case 'B':
				temp = opB(qm[fp], fp);
				break;
			case 'C':
				temp = opC(qm[fp], fp);
				break;
			default:
				break;
			}
			//不存在相同记录,当前记录入队,更新尾指针rp
			if (temp.dep <= N && !exist[cantor(temp.x*10000+temp.y)]) {
				exist[cantor(temp.x*10000+temp.y)] = true;
				qm[rp] = temp;
				rp++;
			}
			//op=='C'时表示当前fp对应的记录已经分别经过了opA,opB,opC的处理,从而更新fp指针,继续对下一个记录进行处理
			if (op == 'C') {
				op = 'A';
				fp++;
			} else {
				op++;
			}
		}
		//结果输出
		if (flag) {
			while (qm[fp].pre != -1) {
			sop.push_back(qm[fp].op);
			fp = qm[fp].pre;
			}
			cout << sop.size() << " ";
			for (int i = sop.size()-1; i >= 0; i--) {
				cout << sop[i];
			}
			cout << endl;
		} else {
			cout << "-1" << endl;
		}
		flag = false;
		op = 'A';
		sop.clear();
	}
}
