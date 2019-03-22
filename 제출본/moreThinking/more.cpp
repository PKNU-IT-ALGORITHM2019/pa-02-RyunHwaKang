#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

typedef struct dot {
	int x;
	int y;
}Dot;

int N;
Dot *data;
int *tmpOrder;
int *shortestOrder;

void swapData(int k, int i);
double shortestTourDist(int k, double currnetDist, double shortestDist);
void swapTmpOrder(int k, int i);
double getDist(int index1, int index2);
void copyOrder();


void main() {
	double start, end;
	start = clock();

	FILE *fp = fopen("input6.txt", "r");
	fscanf(fp, "%d", &N);

	//N의 수만큼 동적할당
	data = (Dot *)malloc(N * sizeof(Dot));
	tmpOrder = (int *)malloc(N * sizeof(int));
	shortestOrder = (int *)malloc(N * sizeof(int));

	//파일 읽고 데이터 저장
	int index = 0;
	while (index < N) {
		fscanf(fp, "%d", &data[index].x);
		fscanf(fp, "%d", &data[index].y);
		tmpOrder[index] = index;	//tmpOrder을 0~(N-1) 점 순서로 초기화시켜 둠
		index++;
	}
	fclose(fp);

	//제일 짧은 투어의 거리를 구해 return
	double shortestDist = shortestTourDist(0, 0, -1);	//처음 시작은 k = 0, 처음 길이는 0, -1 : shortestDist가 아직 없음을 나타냄.
														
	//정답 출력
	printf("%.14lf\n[%d", shortestDist, shortestOrder[0]);
	for (int i = 1; i < N - 1; i++)
		printf(", %d", shortestOrder[i]);
	printf(", %d]\n", shortestOrder[N - 1]);

	//메모리 해제
	free(data);
	free(tmpOrder);
	free(shortestOrder);

	end = clock();
	printf("걸린 시간 : %5.2lf\n", ((end - start) / CLOCKS_PER_SEC));
}


double shortestTourDist(int k, double currentDist, double shortestDist) {
	if ((shortestDist > 0) && (currentDist >= shortestDist)) 
		return -1;
	if (k == N) {
//		for (int i = 0; i < N; i++)
//			printf("%d ", tmpOrder[i]);
//		printf(" currentDist : %.14lf, shortestDist : %.14lf\n", currentDist, shortestDist);
		currentDist += getDist(N - 1, 0);
		if ((shortestDist > 0) && (currentDist >= shortestDist))
			return -1;
		if (shortestDist < 0) {
			shortestDist = currentDist;
			copyOrder();
		}
		else if (currentDist < shortestDist) {
			shortestDist = currentDist;
			copyOrder();
		}
//		for (int i = 0; i < N; i++)
//			printf("%d ", shortestOrder[i]);
//		printf("\n");
		return shortestDist;
	}
	for (int i = k; i < N; i++) {
		swapData(k, i);
		swapTmpOrder(k, i);

		double dist = 0;
		if (k == 0)//처음 점에서는 거리 구하지 않음.
			dist = 0;
		else//지금의 점과 이전의 점의 거리 구함.
			dist = getDist(k - 1, k);

		double tmp = shortestTourDist(k + 1, currentDist + dist, shortestDist);

		
		swapData(k, i);
		swapTmpOrder(k, i);

		if (tmp < 0) 
			break;
		else
			shortestDist = tmp;
	}
	return shortestDist;

}


//data자리 바꿈
void swapData(int k, int i) {
	int x, y;
	x = data[k].x;
	y = data[k].y;
	data[k].x = data[i].x;
	data[k].y = data[i].y;
	data[i].x = x;
	data[i].y = y;
}

void swapTmpOrder(int k, int i) {
	int tmp = tmpOrder[k];
	tmpOrder[k] = tmpOrder[i];
	tmpOrder[i] = tmp;
}



double getDist(int index1, int index2) {
	double dist = 0;
	double x_2 = pow((data[index1].x - data[index2].x), 2);
	double y_2 = pow((data[index1].y - data[index2].y), 2);
	dist += sqrt( x_2 + y_2);
	return dist;
}


void copyOrder() {
	for (int i = 0; i < N; i++)
		shortestOrder[i] = tmpOrder[i];
}
