#include<iostream>
#include<iomanip>
using namespace std;

/*
 * �������:�������г�����ֱ��,�Լ�����secondsת��Ȧ��,���ߵ�·�̺�ʱ��
 * ��ʽ�����:fixed���setprecision���Կ���С������λ��
 *         ����ʹ��setprecisionֻ�ܿ�����ʾλ��
 */

#define PI 3.1415927         //Բ����
#define IPF 12               //ÿӢ��12Ӣ��
#define FPM 5280             //ÿӢ��5280Ӣ��
#define SPH 3600             //һСʱ3600��
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
