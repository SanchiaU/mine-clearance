#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define ROW 10 //定义行列的常量
#define COL 10
#define MineNum 10
#define ImgSize 40 //图片宽度

//定义图片资源
IMAGE imgs[12];
void loadResource() {
	for (int i = 0; i < 12; i++) {
		char imgPath[50] = { 0 };
		sprintf_s(imgPath, "./images/%d.jpg",i);
		loadimage(&imgs[i], imgPath, ImgSize, ImgSize);
		/*putimage(i * 35, 0, imgs + i);*/
	}
	
}

void show(int map[][COL]);
void init(int map[][COL]);
void draw(int map[][COL]);
void mouseMsg(ExMessage* msg, int map[][COL]);
void boomBlank(int map[][COL], int row, int col);
int judge(int map[][COL],int row, int col);

int main() {
	//窗口创建
	initgraph(400, 400,EX_SHOWCONSOLE);
	////播放开始音乐
	mciSendString("open ./images/start.mp3",NULL,0,NULL);
	mciSendString("play ./images/start.mp3", NULL, 0, NULL);

	//扫雷地图
	int map[ROW][COL] = {0};
	init(map);

	//游戏主循环
	while (true) {
		//处理消息
		ExMessage msg;
		while (peekmessage(&msg, WH_MOUSE)) {
			switch(msg.message){
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
				mouseMsg(&msg, map);
				int ret = judge(map, msg.y /ImgSize,msg.x / ImgSize );  //点击判断结合
				if (ret == -1) {
					draw(map);
					int select = MessageBox(GetHWnd(), "很遗憾你输了，是否选择再来一局", "you are lose", MB_OKCANCEL);
					if (select == IDOK) {
						//初始化
						init(map);
					}
					else {
						exit(0);
					}
				}
				else if (ret == 1) {
				
				}
				printf("judege: %d\n", ret);
				system("cls");
				show(map);
				break;
			}
		}


		draw(map);
	}
	//show(map);

	getchar();
	return 0;
}

void show(int map[][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			printf(" %2d", map[i][k]);
		}
		printf("\n");
	}

}
//初始化数据
void init(int map[][COL]){
	loadResource();
	//设置随机种子
	srand((unsigned)time(NULL));
	//随机设置10个雷 用-1表示

	//初始化
	memset(map, 0, sizeof(int)*ROW*COL);

	for (int i = 0; i < MineNum;) {
		
		//数组的有效下标[0,9]
		int r = rand()% ROW;
		int c = rand()% COL;
		if (map[r][c] == 0) {
			map[r][c] = -1;
			i++;
			//只用没有雷的地方才设置雷
		}
		
	}

	//周围+1
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			if (map[i][k] == -1) {
				for (int r = i - 1; r <= i + 1; r++) {
					for (int c = k - 1; c <= k + 1; c++) {
						//周围+1
						if (r>=0 && r<ROW && c>=0 && c<COL) {
							if (map[r][c] != -1) {
								++map[r][c];
							}
							
						}
					}
				}
				
				
			}
		}
	}

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			map[i][k] += 20;
		}
	}

}
//绘制

void draw(int map[][COL]) {
	//贴图,根据map里的数据，贴对应的图片
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			if (map[i][k]>=0 && map[i][k]<=8) { //[0,8]
				putimage(k* ImgSize,i* ImgSize,&imgs[map[i][k]]);
			}
			else if(map[i][k]==-1) {
				putimage(k * ImgSize, i * ImgSize, &imgs[9]);
			}
			else if (map[i][k] >= 19 && map[i][k] <= 28) {
				putimage(k * ImgSize, i * ImgSize, &imgs[10]);
			}
			else if(map[i][k]>=39) {
				putimage(k * ImgSize, i * ImgSize, &imgs[11]);
			}
		}
	}
}

void mouseMsg(ExMessage* msg, int map[][COL]) {
	
	//鼠标位置
	int c = msg->x/ ImgSize;
	int r = msg->y/ ImgSize;
	//printf("%d %d\n", msg->x, msg->y);
	
	//左键
	if (msg->message == WM_LBUTTONDOWN) {
		
		if (map[r][c]>=19 && map[r][c]<=28) {
			map[r][c] -= 20;
			/*system("cls");
			show(map);*/
			boomBlank(map, r, c);
		}
	}
	//右键标记
	else if (msg->message == WM_RBUTTONDOWN) {
		if (map[r][c] >= 19 && map[r][c] <= 28) {
			map[r][c] += 20;
			/*system("cls");
			show(map);*/
		}
		else if (map[r][c] >= 39) {
			map[r][c] -= 20;
			/*system("cls");
			show(map);*/
		}
	}



}

//点击空白格子
void boomBlank(int map[][COL],int row,int col) {
	//判断是否是空白格子
	if (map[row][col] == 0) {
		for (int r = row - 1; r <= row + 1; r++) {
			for (int c = col - 1; c <= col + 1; c++) {
				if((r>=0 && r<ROW && c>=0 && c<COL)&&(map[r][c] >= 19&& map[r][c] <=28)) {
					map[r][c] -= 20;
					boomBlank(map, r, c);
				}
			}
		}
	}
}

//结束
int judge(int map[][COL],int row ,int col) {
	//点到了雷，结束 -1
	if(map[row][col]==-1|| map[row][col]==19) {
		return -1;
	}

	//点到了格子0，win1
	int cnt = 0;
	for(int i = 0;i<ROW;i++){
		for (int k = 0; k < COL; k++) {
			if (map[i][k]>=0 && map[i][k]<=0) {
				++cnt;
			}
		}
	}
	if (ROW * COL - MineNum == cnt) {
		return 1;
	}
	

	//正常
	return 0;

}