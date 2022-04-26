#include <stdio.h>  
#include <stdlib.h> 
#include<string.h>
#include<memory.h>
#define _CRT_SECURE_NO_WARNINGS 

#define MAX_COUNT 100   

typedef struct StudentData 
{
    int num1;  // ��¥
    
    unsigned int traffic, eat, sparetime, plusmoney,total; 
} S_DATA;


char* GetNextString(char* ap_src_str, char a_delimiter, char* ap_buffer)
{
    // NULL ���� �Ǵ� a_delimiter ���ڰ� ���ö����� �ݺ��ϸ鼭 
    // ap_src_str�� ����Ű�� ���ڸ� ap_buffer�� ����Ű�� �޸𸮿� �����Ѵ�.
    while (*ap_src_str && *ap_src_str != a_delimiter) *ap_buffer++ = *ap_src_str++;

    // ������ ��ġ�� �ִ� ���ڰ� �ٹٲ� �����̸� �ٹٲ� ���� ��� NULL ���ڸ� �߰��Ѵ�.
    // �ٹٲ� ���ڰ� �ƴ϶�� ���ڿ��� ���� NULL ���ڸ� �߰��Ѵ�.
    if (*(ap_buffer - 1) == '\n') *(ap_buffer - 1) = 0;
    else *ap_buffer = 0;

    // ap_src_str �����Ͱ� ����Ű�� ��ġ�� ���ڿ� �и��� ���� a_delimiter ������
    // ��ġ�̰ų� NULL ������ ��ġ�Դϴ�. ���� a_delimiter ���� ��ġ�� ����Ų�ٸ�
    // ���� ���ڴ� ',' ���� ��ġ���� ����� ���̱� ������ �ǳʶ��.
    if (*ap_src_str == a_delimiter) ap_src_str++;

    // Ž���� �Ϸ��� ��ġ�� �ּҸ� ��ȯ�Ѵ�.
    return ap_src_str;
}

// ���Ͽ��� ���� ������ ������ �о S_DATA�� ����� �迭�� �����Ѵ�.
int ReadData(const char* ap_file_name, S_DATA* ap_data, unsigned int* ap_data_count)
{
    // �о���� �������� ������ ����ϱ� ���� ���� �ּҸ� �����Ѵ�.
    S_DATA* p_start = ap_data;

    FILE* p_file = NULL;  // ������ ��� ����� ���� ������!
    // fopen_s �Լ��� ����Ͽ� ������ �ؽ�Ʈ ������ �б� ���� ����!
    // �� �Լ��� ���� ���⿡ �����ߴٸ� 0�� ��ȯ�Ѵ�.
    if (0 == fopen_s(&p_file, ap_file_name, "rt")) {
        // ���Ͽ��� �� ���� ������ �о ������ ������ 
        // ��ǥ�� �������� �и��� ���ڿ��� ������ ����
        char one_line_string[128], str[32], * p_pos;
        // ���Ͽ��� �� ���� �����͸� �д´�. 
        // ������ ù ���� Ÿ��Ʋ ������ ó������ �ʰ� �Ѿ��.
        if (NULL != fgets(one_line_string, 128, p_file)) {
           
            while (NULL != fgets(one_line_string, 128, p_file)) {
                p_pos = GetNextString(one_line_string, ',', str); 
                ap_data->num1 = atoi(str);  

                


                p_pos = GetNextString(p_pos, ',', str); 
                ap_data->traffic = atoi(str); 

                p_pos = GetNextString(p_pos, ',', str); 
                ap_data->eat = atoi(str); 

                p_pos = GetNextString(p_pos, ',', str); 
                ap_data->sparetime = atoi(str);  

                p_pos = GetNextString(p_pos, ',', str);
                ap_data->plusmoney = atoi(str); 

                // ��� ������ �ջ��Ѵ�.
                ap_data->total = ap_data->traffic + ap_data->eat + ap_data->sparetime ;
                ap_data++; // ���� ���� ��ġ�� �̵��Ѵ�.
            }
            // �����͸� ������ �迭�� ���� �ּҸ� �Է��� ����� �ּҿ� ���� 
            // �Էµ� �������� ������ ���� �� �ִ�.
            *ap_data_count = ap_data - p_start;
        }
        fclose(p_file);  // ������ �ݴ´�.
        return 1;  // ���Ͽ��� ���� �б� ����
    }
    return 0;  // ���Ͽ��� ���� �б� ����
}


void ShowData(S_DATA* ap_data, unsigned int a_count)
{
   
    printf("-----------------------------------------------------------------\n");
    printf("    ��¥        �����   �ĺ�    ������     �ΰ�����     ��/����\n");
    printf("-----------------------------------------------------------------\n");
    
    unsigned int sum = 0;
    unsigned int sum2 = 0;
    for (unsigned int i = 0; i < a_count; i++, ap_data++) {
        // ���� ������ ����Ѵ�.
        printf(" %6d  %12d   %5d   %6d   %9d,  %10d\n",
            ap_data->num1, ap_data->traffic, ap_data->eat, ap_data->sparetime, ap_data->plusmoney,
            ap_data->total);
        sum += ap_data->total; // �Ϻ��� ���� �ջ��Ͽ� �� ���� ����Ѵ�
        sum2 += ap_data->plusmoney;
    }
    printf("-----------------------------------------------------------------\n");
    
    if (a_count > 0) {
        printf("    �� %d ��, �̹��� �� ����= %d, �� ����-�̹��� ����=%d\n", a_count, sum, sum2-sum);
        printf("-----------------------------------------------------------------\n");
    }
}
 
void modifydata(S_DATA* ap_data, unsigned int a_count)
{
    int num1, select;
    printf("������ ������ �л��� �й��� �Է��ϼ��� : ");
    scanf_s("%d", &num1);  // ������ ��¥�� �Է� �޴´�!

    for (unsigned int i = 0; i < a_count; i++, ap_data++) {
        if (ap_data->num1 == num1) {  // ������ ��¥ ������ ã�´�.
            printf("������ �׸��� �����ϼ���.\n");
            printf("1.�����,  2.�ĺ�,  3.������, 4.�ΰ�����\n����: ");
            scanf_s("%d", &select);  // � �׸��� ������ ������ �Է� �޴´�!
            switch (select) {
            case 1:
                printf("������ ����� �Է��ϼ��� : ");
                scanf_s("%d", ap_data->traffic);  
                break;
            case 2:
                printf("������ �ĺ� �Է��ϼ��� : ");
                scanf_s("%d", &ap_data->eat); 
                break;
            case 3:
                printf("������ ������ �Է��ϼ��� : ");
                scanf_s("%d", &ap_data->sparetime); 
                break;
            case 4:
                printf("������ �ΰ����� �Է��ϼ��� : ");
                scanf_s("%d", &ap_data->plusmoney); 
                break;
            }
            if (select >= 1 && select <= 2) {  
                ap_data->total = ap_data->traffic + ap_data->eat + ap_data->sparetime;
            }
            else if (select >= 3) {
                ap_data->total = ap_data->traffic + ap_data->eat + ap_data->sparetime;
            }
            
            return;
        }
        return;
    }
    printf("[����] �Է��� �й��� �л��� �����ϴ�.\n");
}



void AddData() {
    

    char buffer[100];

    FILE* fp = fopen("bank.txt", "a"); //test������ a ���� ����
    printf("��¥,�����, �ĺ�,������,�ΰ����� ������ �Է����ּ���!");
    
        fputs("\n", fp);
   
    
        memset(buffer, 0, sizeof(buffer)); //buffer�� 0���� ä���.
        scanf("%s", buffer);

        fwrite(buffer, 1, strlen(buffer), fp);
        fclose(fp);
    
    
}

int main()
{
    S_DATA data[MAX_COUNT];  // �л� ������ ������ �迭�� ����
    // �л� ����, ���õ� ����� ������ ���� ����
    unsigned int data_count = 0, select = 0;

    // 'data.csv' ���Ͽ��� �л� ������ �о� ���δ�.
    if (ReadData("bank.txt", data, &data_count)) {
        // ����ڰ� 4�� �Է��� ������ ��� �ݺ��Ѵ�.
        while (select != 4) {
            printf("\n\n==========[  �޴�  ]==========\n"); // �޴��� ����Ѵ�.
            printf("1.����� ����\n");
            printf("2.����� �����߰�\n");
            printf("3.����� ����\n");
            printf("4.���α׷� ����\n");

            printf("���� : ");
            // �߸��� �Է¿� ���ؼ� üũ�Ѵ�.
            if (1 == scanf_s("%u", &select)) {
                printf("\n\n");
                // ��ɺ��� �Լ��� ȣ���Ѵ�.
                if (select == 1) ShowData(data, data_count);  // ���� ����
                else if (select == 2) AddData(); // �߰�
                else if (select == 3) modifydata(data, data_count);
            }
            else if(select == 4) {
                // �߸��� �Է��� ���� �޽��� ��� �Ŀ� ǥ���Է� ���۸� ����.
                printf("\n�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��ϼ���.\n\n");
                rewind(stdin);
            }
            else{
            
            }
        }
    }
    else {
        printf("data.csv ������ ���� �����ϴ�. ���� ��θ� Ȯ���ϼ���!!\n");
    }
    return 0;
}