#include <stdio.h>  
#include <stdlib.h> 
#include<string.h>
#include<memory.h>
#define _CRT_SECURE_NO_WARNINGS 

#define MAX_COUNT 100   

typedef struct StudentData 
{
    int num1;  // 날짜
    
    unsigned int traffic, eat, sparetime, plusmoney,total; 
} S_DATA;


char* GetNextString(char* ap_src_str, char a_delimiter, char* ap_buffer)
{
    // NULL 문자 또는 a_delimiter 문자가 나올때까지 반복하면서 
    // ap_src_str이 가리키는 문자를 ap_buffer가 가리키는 메모리에 복사한다.
    while (*ap_src_str && *ap_src_str != a_delimiter) *ap_buffer++ = *ap_src_str++;

    // 마지막 위치에 있는 문자가 줄바꿈 문자이면 줄바꿈 문자 대신 NULL 문자를 추가한다.
    // 줄바꿈 문자가 아니라면 문자열의 끝에 NULL 문자를 추가한다.
    if (*(ap_buffer - 1) == '\n') *(ap_buffer - 1) = 0;
    else *ap_buffer = 0;

    // ap_src_str 포인터가 가리키는 위치는 문자열 분리에 사용된 a_delimiter 문자의
    // 위치이거나 NULL 문자의 위치입니다. 만약 a_delimiter 문자 위치를 가리킨다면
    // 다음 문자는 ',' 다음 위치에서 진행될 것이기 때문에 건너띈다.
    if (*ap_src_str == a_delimiter) ap_src_str++;

    // 탐색을 완료한 위치의 주소를 반환한다.
    return ap_src_str;
}

// 파일에서 지출 내역의 정보를 읽어서 S_DATA로 선언된 배열에 저장한다.
int ReadData(const char* ap_file_name, S_DATA* ap_data, unsigned int* ap_data_count)
{
    // 읽어들인 데이터의 갯수를 계산하기 위해 시작 주소를 저장한다.
    S_DATA* p_start = ap_data;

    FILE* p_file = NULL;  // 파일을 열어서 사용할 파일 포인터!
    // fopen_s 함수를 사용하여 파일을 텍스트 형식의 읽기 모드로 연다!
    // 이 함수는 파일 열기에 성공했다면 0을 반환한다.
    if (0 == fopen_s(&p_file, ap_file_name, "rt")) {
        // 파일에서 한 줄의 정보를 읽어서 저장할 변수와 
        // 쉼표를 기준으로 분리한 문자열을 저장할 변수
        char one_line_string[128], str[32], * p_pos;
        // 파일에서 한 줄의 데이터를 읽는다. 
        // 하지만 첫 줄은 타이틀 정보라서 처리하지 않고 넘어간다.
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

                // 모든 지출을 합산한다.
                ap_data->total = ap_data->traffic + ap_data->eat + ap_data->sparetime ;
                ap_data++; // 다음 저장 위치로 이동한다.
            }
            // 데이터를 저장한 배열의 시작 주소를 입력이 진행된 주소에 빼면 
            // 입력된 데이터의 개수를 얻을 수 있다.
            *ap_data_count = ap_data - p_start;
        }
        fclose(p_file);  // 파일을 닫는다.
        return 1;  // 파일에서 정보 읽기 성공
    }
    return 0;  // 파일에서 정보 읽기 실패
}


void ShowData(S_DATA* ap_data, unsigned int a_count)
{
   
    printf("-----------------------------------------------------------------\n");
    printf("    날짜        교통비   식비    여가비     부가수입     일/지출\n");
    printf("-----------------------------------------------------------------\n");
    
    unsigned int sum = 0;
    unsigned int sum2 = 0;
    for (unsigned int i = 0; i < a_count; i++, ap_data++) {
        // 지출 내역을 출력한다.
        printf(" %6d  %12d   %5d   %6d   %9d,  %10d\n",
            ap_data->num1, ap_data->traffic, ap_data->eat, ap_data->sparetime, ap_data->plusmoney,
            ap_data->total);
        sum += ap_data->total; // 일별의 돈을 합산하여 총 돈을 계산한다
        sum2 += ap_data->plusmoney;
    }
    printf("-----------------------------------------------------------------\n");
    
    if (a_count > 0) {
        printf("    총 %d 일, 이번달 총 지출= %d, 총 예산-이번달 지출=%d\n", a_count, sum, sum2-sum);
        printf("-----------------------------------------------------------------\n");
    }
}
 
void modifydata(S_DATA* ap_data, unsigned int a_count)
{
    int num1, select;
    printf("정보를 수정할 학생의 학번을 입력하세요 : ");
    scanf_s("%d", &num1);  // 수정할 날짜를 입력 받는다!

    for (unsigned int i = 0; i < a_count; i++, ap_data++) {
        if (ap_data->num1 == num1) {  // 수정할 날짜 정보를 찾는다.
            printf("수정할 항목을 선택하세요.\n");
            printf("1.교통비,  2.식비,  3.여가비, 4.부가수입\n선택: ");
            scanf_s("%d", &select);  // 어떤 항목을 수정할 것인지 입력 받는다!
            switch (select) {
            case 1:
                printf("변경할 교통비를 입력하세요 : ");
                scanf_s("%d", ap_data->traffic);  
                break;
            case 2:
                printf("변경할 식비 입력하세요 : ");
                scanf_s("%d", &ap_data->eat); 
                break;
            case 3:
                printf("변경할 여가비를 입력하세요 : ");
                scanf_s("%d", &ap_data->sparetime); 
                break;
            case 4:
                printf("변경할 부가수입 입력하세요 : ");
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
    printf("[오류] 입력한 학번의 학생이 없습니다.\n");
}



void AddData() {
    

    char buffer[100];

    FILE* fp = fopen("bank.txt", "a"); //test파일을 a 모드로 열기
    printf("날짜,교통비, 식비,여가비,부가수익 순으로 입력해주세요!");
    
        fputs("\n", fp);
   
    
        memset(buffer, 0, sizeof(buffer)); //buffer를 0으로 채운다.
        scanf("%s", buffer);

        fwrite(buffer, 1, strlen(buffer), fp);
        fclose(fp);
    
    
}

int main()
{
    S_DATA data[MAX_COUNT];  // 학생 정보를 저장할 배열을 선언
    // 학생 수와, 선택된 기능을 저장할 변수 선언
    unsigned int data_count = 0, select = 0;

    // 'data.csv' 파일에서 학생 정보를 읽어 들인다.
    if (ReadData("bank.txt", data, &data_count)) {
        // 사용자가 4를 입력할 때까지 계속 반복한다.
        while (select != 4) {
            printf("\n\n==========[  메뉴  ]==========\n"); // 메뉴를 출력한다.
            printf("1.가계부 보기\n");
            printf("2.가계부 내용추가\n");
            printf("3.가계부 변경\n");
            printf("4.프로그램 종료\n");

            printf("선택 : ");
            // 잘못된 입력에 대해서 체크한다.
            if (1 == scanf_s("%u", &select)) {
                printf("\n\n");
                // 기능별로 함수를 호출한다.
                if (select == 1) ShowData(data, data_count);  // 성적 보기
                else if (select == 2) AddData(); // 추가
                else if (select == 3) modifydata(data, data_count);
            }
            else if(select == 4) {
                // 잘못된 입력은 오류 메시지 출력 후에 표준입력 버퍼를 비운다.
                printf("\n잘못된 값을 입력했습니다. 다시 입력하세요.\n\n");
                rewind(stdin);
            }
            else{
            
            }
        }
    }
    else {
        printf("data.csv 파일을 열수 없습니다. 파일 경로를 확인하세요!!\n");
    }
    return 0;
}