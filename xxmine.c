#include<stdio.h>
#include<stlib.h>
#include<time>
#define ROW 10 //�������еĳ���
#define COL 10
#define MineNum 10

void show(int map[][COL]);

int main() {
	//ɨ�׵�ͼ
	int map[ROW][COL];
	init(map);
	show(map);
	return 0;
}

void show(int map[][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			printf(" %d", map[i][k]);
		}
		printf("\n");
	}

}
//��ʼ������
void init(int map[][COL]) {
	//�������10���� ��-1��ʾ
	for (int i = 0; i < MineNum; i++) {

		//�������Ч�±�[0,9]

		map[r][c] = -1;
	}
}