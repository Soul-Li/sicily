#include<iostream>
#include<iomanip>
using namespace std;

/*
 * 理解题意:给出自行车车轮直径,以及给定seconds转的圈数,求走的路程和时速
 * 格式化输出:fixed配合setprecision可以控制小数点后的位数
 *         单纯使用setprecision只能控制显示位数
 */

#define PI 3.1415927         //圆周率
#define IPF 12               //每英尺12英寸
#define FPM 5280             //每英里5280英尺
#define SPH 3600             //一小时3600秒
int main() {
	int revolutions, count = 0;
	float diameter, time;
	while (1) {
		count++;
		cin >> diameter >> revolutions >> time;
		if (revolutions == 0) break;
		float distance = PI*diameter*revolutions/IPF/FPM;
		cout << fixed;
		cout << setprecision(2);
		cout << "Trip #" << count << ": " << distance << " " << distance*SPH/time << endl;
	}
}
