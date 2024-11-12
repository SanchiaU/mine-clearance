#include<stdio.h>
#include<stlib.h>
#include<time>
#define ROW 10 //定义行列的常量
#define COL 10
#define MineNum 10

void show(int map[][COL]);

int main() {
	//扫雷地图
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
//初始化数据
void init(int map[][COL]) {
	//随机设置10个雷 用-1表示
	for (int i = 0; i < MineNum; i++) {

		//数组的有效下标[0,9]

		map[r][c] = -1;
	}
}