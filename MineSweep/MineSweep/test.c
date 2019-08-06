#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// �����ͼ
#define MAX_ROW 6
#define MAX_COL 6
// ����Ĭ�ϵĵ�����Ϊ 10
#define DEFAULT_MINE_COUNT 4

void Init(char show_map[MAX_ROW + 2][MAX_COL + 2], char mine_map[MAX_ROW + 2][MAX_COL + 2]) {
	for (int row = 0; row < MAX_ROW + 2; ++row) {
		for (int col = 0; col < MAX_COL + 2; ++col) {
			show_map[row][col] = '*';
		}
	}
	for (int row = 0; row < MAX_ROW + 2; ++row) {
		for (int col = 0; col < MAX_COL + 2; ++col) {
			mine_map[row][col] = ' ';
		}
	}
	// ������� N ����(����),�ŵ�������
	int mine_count = DEFAULT_MINE_COUNT;
	while (mine_count > 0) {
		int row = rand() % MAX_ROW + 1;
		int col = rand() % MAX_COL + 1;
		// ��ǰλ���Ѿ�������
		if (mine_map[row][col] == '1') {
			continue;
		}
		mine_map[row][col] = '1';
		--mine_count;
	}
}
void DisplayMap(char show_map[MAX_ROW + 2][MAX_COL + 2]) {
	printf("    ");
	// ��ӡ��һ��������
	for (int col = 1; col <= MAX_COL; ++col) {
		printf("%d ", col);
	}
	printf("\n");
	// ��ӡ�ϱ߿�
	for (int col = 1; col <= MAX_COL; ++col) {
		printf("___");
	}
	printf("\n");
	// ���д�ӡ����ĵ�ͼ
	for (int row = 1; row <= MAX_COL; ++row) {
		printf("%02d |", row);
		for (int col = 1; col <= MAX_COL; ++col) {
			printf("%c ", show_map[row][col]);
		}
		printf("\n");
	}
}
// ����������� mine_map ������ row, col λ������Χ�м�����,�ѽ��д�� show_map λ����
void UpdateShowMap(char show_map[MAX_ROW + 2][MAX_COL + 2], char mine_map[MAX_ROW + 2][MAX_COL + 2], int row, int col) {
	int mine_count = 0;
	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = col - 1; j <= col + 1; j++) {
			if (mine_map[i][j] == '1') {
				mine_count++;
			}
			continue;
		}
	}
	show_map[row][col] = '0' + mine_count;
}

//void UpdateShowMap(char show_map[MAX_ROW + 2][MAX_COL + 2], char mine_map[MAX_ROW + 2][MAX_COL + 2], int row, int col)
////����minemap��������(row��col)����Χ���׵�����
////���д����Ӧ��showmap��
//{
//	int mine_count = 0;
//	//���ڼ��˱߿��������µ����겻��Խ��
//	mine_count = mine_map[row - 1][col - 1] - '0'
//		+ mine_map[row - 1][col] - '0'
//		+ mine_map[row - 1][col + 1] - '0'
//		+ mine_map[row][col - 1] - '0'
//		+ mine_map[row][col + 1] - '0'
//		+ mine_map[row + 1][col - 1] - '0'
//		+ mine_map[row + 1][col] - '0'
//		+ mine_map[row + 1][col + 1] - '0';
//	show_map[row][col] = '0' + mine_count;//mine_count ��һ��int����ֵ�������ַ�������һ���ַ�0
//}

void Game() {
	// 1. ʹ��������ά����ֱ��ʾ �����չʾ�ĵ�ͼ �� ���󣨴��߿�
	// show_map:  *(��û�ƿ���λ��)  '1''2'(�Ѿ��ƿ���λ��)
	char show_map[MAX_ROW + 2][MAX_COL + 2];
	// mine_map:  '1'(�ǵ���)  '0'(���ǵ���)
	char mine_map[MAX_ROW + 2][MAX_COL + 2];
	// �հ׸���
	int blank_count = 0;
	// 2. ��ʼ��������ͼ
	Init(show_map, mine_map);
	// 3. ��ӡ��ͼ����ȫû�б����ƿ��ģ�
	printf("\n");
	DisplayMap(show_map);
	while (1) {
		// 4. ��Ϸ��ʼ��������������겢�ж������Ƿ�Ϸ�
		int row, col;
		printf("\n���������꣺ ");
		scanf("%d %d", &row, &col);
		printf("\n");
		if (row < 1 || row > MAX_ROW || col < 1 || col > MAX_COL) {
			printf("\n�������벻�Ϸ�,����������!\n");
			continue;
		}
		// 5. �ж���Ϸ�Ƿ����������Ƿ����).�������,��Ϸ����;���û����,�ж��Ƿ��ƿ����и���
		if (mine_map[row][col] == '1') {
			printf("\n��Ϸ����!\n");
			printf("\n");
			DisplayMap(mine_map);
			break;
		}
		++blank_count;
		if (blank_count == MAX_ROW * MAX_COL - DEFAULT_MINE_COUNT) {
			printf("\nɨ�׳ɹ�!\n");
			DisplayMap(mine_map);
			break;
		}
		// 6. û���׵�����£�ͳ�Ƹ�λ����Χ�м����ף����Ұ�������ָ��µ���ͼ��
		UpdateShowMap(show_map, mine_map, row, col);
		DisplayMap(show_map);
	}
}
// �������ں���
void Start() {
	printf("  ==============\n");
	printf("   1. ��ʼ��Ϸ��\n");
	printf("   0. �˳���Ϸ��\n");
	printf("  ==============\n");
	printf("\n����������ѡ��:  ");
	int choice = 0;
	scanf("%d", &choice);
	while (1) {
		if (choice == 1) {
			Game();
		}
		break;
	}
}
int main() {
	Start();
	system("pause");
	return 0;
}