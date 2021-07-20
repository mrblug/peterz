#define _CRT_SECURE_NO_WARNINGS

//���ⲿ�ļ�����ѧ���ɼ����ݻ�������ͳ��ͼ��ͳ�Ʊ�ĳ���
//�ļ���ʽ.txt
//�������£�
//��һ�У�ѧ����
//�ڶ��У���һ��ѧ������
//�����У���һ��ѧ���ɼ�
//�����У��ڶ���ѧ������
//�Դ�����

#include <cstdio>
#include <cstdlib>
#include <cstring>

struct stu {
	char name[128];
	double scores;
	struct stu* next;
};

struct stu* create_list(int n, FILE* data);
void draw(struct stu* head);
void delete_list(struct stu* p);
void show_welcome();

struct stu* create_list(int n, FILE* data) {
	struct stu* head = NULL, * p, * pre = NULL;
	char name_temp[128];
	double scores_temp;
	for (int i = 1; i <= n; ++i) {
		while (fgetc(data) != '\n') continue;
		fgets(name_temp, 128, data);
		name_temp[strlen(name_temp) - 1] = 0;
		if (fscanf(data, "%lf", &scores_temp) != 1)
			exit(EXIT_FAILURE);

		p = (struct stu*)malloc(sizeof(struct stu));
		if (p == NULL) exit(EXIT_FAILURE);
		strcpy(p->name, name_temp);
		p->scores = scores_temp;
		p->next = NULL;

		if (head == NULL) head = p;
		else pre->next = p;
		pre = p;
	}
	return head;
}

void draw(struct stu* head) {
	struct stu* p = head;
	double sum = 0.0;
	int count = 0;
	int statistics[11] = { 0 };
	int stat_max = 0;
	while (p) {
		++count;
		++statistics[(int)(p->scores) / 10];
		sum += p->scores;
		p = p->next;
	}
	printf("Total Number:%d\n", count);
	printf("Average Scores = %.3f\n", sum / count);
	for (int i = 0; i < 11; ++i) {
		if (statistics[i] > stat_max)
			stat_max = statistics[i];
	}

	for (int j = 9; j >= 0; --j) {
		if (!(j % 2)) printf("%6.1lf_ ", double(j) * stat_max / 10.0);
		else printf("        ");
		for (int i = 0; i < 11; ++i) {
			double height = (double)statistics[i] / double(stat_max) * 10.0;
			if (height > double(j) + 0.75) printf("�������� ");
			else if (height > double(j) + 0.5) printf("�~�~�~�~ ");
			else if (height > double(j) + 0.25) printf("�{�{�{�{ ");
			else if (height > double(j)) printf("�x�x�x�x ");
			else printf("     ");
		}
		printf("\n");
	}
	printf("        [0. )");
	for (int i = 1; i <= 10; ++i)
		printf("[%2d.)", i * 10);
	printf("\n   n  =   ");
	for (int i = 0; i <= 10; ++i) {
		printf("%d    ", statistics[i]);
	}
	p = head;
	printf("\n    �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("    �U Index    Name                            Scores   �U\n");
	printf("    �d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
	for (int i = 1; i <= count; ++i, p = p->next)
		printf("    �U %-8d %-32s%6.2lf   �U\n", i, p->name, p->scores);
	printf("    �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
}

void delete_list(struct stu* p) {
	struct stu* temp;
	while (p) {
		temp = p->next;
		free(p);
		p = temp;
	}
}

void show_welcome() {
	printf("Student Scores Analysing Program\n");
	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}

int main() {

	FILE* data;
	char location[256] = { 0 };
	printf("Default location of data is .\\data.txt. Press ENTER to use default location or input a new location:\n");
	fgets(location, 256, stdin);
	location[strlen(location) - 1] = 0;
	if (strcmp(location, "") != 0)
		data = fopen(location, "r+");
	else data = fopen(".\\data.txt", "r+");
	if (data == NULL) exit(EXIT_FAILURE);

	int n;
	if (fscanf(data, "%d", &n) != 1)
		exit(EXIT_FAILURE);
	struct stu* head = create_list(n, data);

	show_welcome();
	draw(head);

	delete_list(head);
	fclose(data);

	return 0;
}
