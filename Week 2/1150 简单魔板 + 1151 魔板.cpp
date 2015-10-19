#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;

/*
 * ��ħ��:
 *    x = �ϲ�����, y = �²�����
 *    ����洢���϶�ͷ��βָ��,ģ������������
 *    ȱ���Ǽ�֦����Ч�ʹ���,��n�㹻��ʱ���׳�ʱ
 * �Ľ�����:
 *    �ڲ���ǰ�Ĳ��ش����в���һ�������hash������������չ��,��ԭ����״̬�ռ���С��8!
 *    �����ڲ��ع����б�����ñ�����ǰ�������ֱ�ӽ�x,yͨ������չ��ӳ�䵽8!״̬�ռ��в���,�����Ч��
 */

/*
 * x,y ����ǰ�ڵ�����²�����
 * op  ��������һ���ڵ�õ���ǰ�ڵ������еĲ���
 * pre ������һ���ڵ��������е��±�,���ڻ������
 * dep ����ǰ�ڵ����,����ȳ���Nʱ�ڵ㲻��������
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

int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040};    //0~7�Ľ׳�,���ڵõ�����չ��ֵ
bool exist[50000];

//�Ե�ǰ�ڵ����A����
qt opA(const qt QT, int index) {
	qt temp = qt(QT.y, QT.x, 'A', index, QT.dep+1);
	return temp;
}

//�Ե�ǰ�ڵ����B����
qt opB(const qt QT, int index) {
	int a = QT.x % 10, b = QT.y % 10;
	qt temp = qt(a*1000+(QT.x/10), b*1000+(QT.y/10), 'B', index, QT.dep+1);
	return temp;
}

//�Ե�ǰ�ڵ����C����
qt opC(const qt QT, int index) {
	int x1 = QT.x/1000, x2 = (QT.x%1000)/100, x3 = (QT.x%100)/10, x4 = QT.x%10;
	int y1 = QT.y/1000, y2 = (QT.y%1000)/100, y3 = (QT.y%100)/10, y4 = QT.y%10;
	qt temp = qt(x1*1000+y2*100+x2*10+x4, y1*1000+y3*100+x3*10+y4, 'C', index, QT.dep+1);
	return temp;
}

//����չ��
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
	qt qm[81000];                //�洢�ڵ������
	vector<char> sop;            //����õ��ַ�����
	char op = 'A';               //����������ַ�
	bool flag = false;           //�Ƿ��ҵ�����ı��

	while(1) {
		memset(exist, false, sizeof(exist));
		scanf("%d", &N);
		if (N == -1) break;

		int a, b, c, d, end1, end2;

		//��ȡ������Ҫ�õ���״̬
		scanf("%d %d %d %d", &a, &b, &c, &d);
		end1 = a*1000+b*100+c*10+d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		end2 = a*1000+b*100+c*10+d;

		//��ʼ״̬
		qm[0] = qt(1234,8765,' ',-1, 0);
		exist[cantor(12348765)] = true;
		fp = 0;
		rp = 1;

		while (fp != rp) {
			//����Ҫ���жϵ�ǰҪ���д���Ľڵ��Ƿ���Ŀ��ڵ�
			//�����qm[rp]�����ж�,����ʼ�ڵ����Ŀ��ڵ�ʱ�����
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
			//��������ͬ��¼,��ǰ��¼���,����βָ��rp
			if (temp.dep <= N && !exist[cantor(temp.x*10000+temp.y)]) {
				exist[cantor(temp.x*10000+temp.y)] = true;
				qm[rp] = temp;
				rp++;
			}
			//op=='C'ʱ��ʾ��ǰfp��Ӧ�ļ�¼�Ѿ��ֱ𾭹���opA,opB,opC�Ĵ���,�Ӷ�����fpָ��,��������һ����¼���д���
			if (op == 'C') {
				op = 'A';
				fp++;
			} else {
				op++;
			}
		}
		//������
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
