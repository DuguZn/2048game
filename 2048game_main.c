#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void left_operation(int (*mat)[4], int *score);
void right_operation(int (*mat)[4], int *score);
void up_operation(int (*mat)[4], int *score);
void down_operation(int (*mat)[4], int *score);

void operation_judge(int (*mat)[4], char enter, int *score);

int get_rand(int (*mat)[4]);

char user_tip(int score);

void outp(int (*mat)[4]);

int main()
{
	printf("输入'y'开始游戏, 输入'q'退出\n");
	char enter;
	scanf("%c", &enter);
	if(enter == 'y')
	{
		printf("游戏即将开始...\n");
		Sleep(300);
		printf("初始化...\n");
		//初始化
		Sleep(1000);
		srand((unsigned int)time(NULL));
		
		int score = 0;
		int matrix[4][4];
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
				matrix[i][j] = 0;
		}
		
		printf("游戏开始!\n");
		Sleep(300);
		while(enter != 'q')
		{
			printf("正在添加数字\n");
			Sleep(1500);
			int sign = get_rand(matrix);
			if(sign)
			{
				printf("添加失败,图格已满\n");
				break;
			}
			
			printf("现图格:\n\n");
			Sleep(500);
			outp(matrix);
			Sleep(500);
			
			enter = user_tip(score);
			if(enter == 'q') break;
			
			printf("正在滑动:\n");
			operation_judge(matrix, enter, &score);
			Sleep(700);
			
			printf("得到图格为:\n\n");
			Sleep(300);
			outp(matrix);
			Sleep(300);
		}
		Sleep(300);
		printf("+++最终得分: %d\n", score);
		Sleep(500);
	}
	else printf("游戏结束\n");
	
	return 0;
}

void outp(int (*mat)[4])
{
	for(int i = 0; i < 4; i ++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(j == 0) printf("%3d", mat[i][j]);
			else printf(" %3d", mat[i][j]);
		}
		printf("\n\n");
	}
	printf("\n");	
}

char user_tip(int score)
{
	char enter;
	printf("+++目前得分: %d\n", score);
	Sleep(300);
	printf("请输入你的滑动方向:\n");
	Sleep(200);
	printf("  w向上 s向下\n");
	Sleep(200);
	printf("  a向左 d向右\n");
	Sleep(200);
	printf(" 输入'q'退出游戏\n");
	Sleep(300);
	getchar();
	scanf("%c", &enter);
	while(!(enter == 'q' || enter == 'w' || enter == 'a' || enter == 'd' || enter == 's'))
	{
		printf("输入仅能是q,w,a,s,d中的某一个\n");
		Sleep(500);
		printf("请输入你的滑动方向:\n  w向上 s向下\n  a向左 d向右\n 输入'q'退出游戏\n");
		getchar();
		scanf("%c", &enter);
	}
	return enter;
}

int get_rand(int (*mat)[4])
{
	int sign = 1;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(mat[i][j] == 0)
				sign = 0;
		}
	}
	if(sign) return sign;
	
	int rand_nums[2] = {2, 4};
	int num = rand_nums[rand()%2];
	
	int rand_i = rand()%4;
	int rand_j = rand()%4;
	
	while(mat[rand_i][rand_j] != 0)
	{
		rand_i = rand()%4;
		rand_j = rand()%4;
	}
	mat[rand_i][rand_j] = num;
	
	return sign;
}

void operation_judge(int (*mat)[4], char enter, int *score)
{
	if(enter == 'w') up_operation(mat, score);
	else if(enter == 's') down_operation(mat, score);
	else if(enter == 'a') left_operation(mat, score);
	else if(enter == 'd') right_operation(mat, score);
}

void left_operation(int (*mat)[4], int *score)
{
	for(int k = 0; k < 4; k++)
	{
		int pos = 0;
		int target_pos = 0;
		int first_step = 1;
		int step_remove_flag[4];
		for(int i = 0; i < 4; i++)
			step_remove_flag[i] = 1;
		
		while(pos != 4)
		{
			while(mat[k][pos] == 0 && pos != 3)
				pos++;
			
			if(first_step)
			{
				mat[k][target_pos] = mat[k][pos];
				if(pos != target_pos) mat[k][pos] = 0;
				pos++;
				first_step = 0;
				continue;
			}
			
			if(mat[k][target_pos] == mat[k][pos] && step_remove_flag[target_pos])
			{
				mat[k][target_pos] *= 2;
				*score += mat[k][target_pos]/2;
				step_remove_flag[target_pos] = 0;
				if(pos != target_pos) mat[k][pos] = 0;
				pos++;
			}
			else
			{
				target_pos++;
				mat[k][target_pos] = mat[k][pos];
				if(pos != target_pos) mat[k][pos] = 0;
				pos++;
			}	
		}
	}
}
void right_operation(int (*mat)[4], int *score)
{
	for(int k = 0; k < 4; k++)
	{
		int pos = 3;
		int target_pos = 3;
		int flag = 1;
		int step_remove_flag[4];
		for(int i = 0; i < 4; i++)
			step_remove_flag[i] = 1;
		
		while(pos != -1)
		{
			while(mat[k][pos] == 0 && pos != 0)
				pos--;
			
			if(flag)
			{
				mat[k][target_pos] = mat[k][pos];
				if(pos != target_pos) mat[k][pos] = 0;
				flag = 0;
				pos--;
				continue;
			}
			
			if(mat[k][target_pos] == mat[k][pos]&& step_remove_flag[target_pos])
			{
				mat[k][target_pos] *= 2;
				*score += mat[k][target_pos]/2;
				step_remove_flag[target_pos] = 0;
				if(pos != target_pos) mat[k][pos] = 0;
				pos--;
			}
			else
			{
				target_pos--;
				mat[k][target_pos] = mat[k][pos];
				if(pos != target_pos) mat[k][pos] = 0;
				pos--;
			}
		}
	}
}
void up_operation(int (*mat)[4], int *score)
{
	for(int k = 0; k < 4; k++)
	{
		int pos = 0;
		int target_pos = 0;
		int flag = 1;
		int step_remove_flag[4];
		for(int i = 0; i < 4; i++)
			step_remove_flag[i] = 1;
		
		while(pos != 4)
		{
			while(mat[pos][k] == 0 && pos != 3)
				pos++;
			
			if(flag)
			{
				mat[target_pos][k] = mat[pos][k];
				if(pos != target_pos) mat[pos][k] = 0;
				flag = 0;
				pos++;
				continue;
			}
			
			if(mat[target_pos][k] == mat[pos][k]&& step_remove_flag[target_pos])
			{
				mat[target_pos][k] *= 2;
				*score += mat[target_pos][k]/2;
				step_remove_flag[target_pos] = 0;
				if(pos != target_pos) mat[pos][k] = 0;
				pos++;
			}
			else
			{
				target_pos++;
				mat[target_pos][k] = mat[pos][k];
				if(pos != target_pos) mat[pos][k] = 0;
				pos++;
			}	
		}
	}
}
void down_operation(int (*mat)[4], int *score)
{
	for(int k = 0; k < 4; k++)
	{
		int pos = 3;
		int target_pos = 3;
		int flag = 1;
		int step_remove_flag[4];
		for(int i = 0; i < 4; i++)
			step_remove_flag[i] = 1;
		
		while(pos != -1)
		{
			while(mat[pos][k] == 0 && pos != 0)
				pos--;
			
			if(flag)
			{
				mat[target_pos][k] = mat[pos][k];
				if(pos != target_pos) mat[pos][k] = 0;
				flag = 0;
				pos--;
				continue;
			}
			
			if(mat[target_pos][k] == mat[pos][k]&& step_remove_flag[target_pos])
			{
				mat[target_pos][k] *= 2;
				*score += mat[target_pos][k]/2;
				step_remove_flag[target_pos] = 0;
				if(pos != target_pos) mat[pos][k] = 0;
				pos--;
			}
			else
			{
				target_pos--;
				mat[target_pos][k] = mat[pos][k];
				if(pos != target_pos) mat[pos][k] = 0;
				pos--;
			}	
		}
	}
}
