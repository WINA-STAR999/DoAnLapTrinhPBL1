#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"
#define BLUE    "\033[1;34m"
#define PURPLE  "\033[1;35m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"
#define BEIGE "\033[38;5;230m"
typedef struct {
    char ma[50];
    char ten[256];
    char tapChi[256];
    char loai[50];
    int soXuatBan;
    int tapXuatBan;
    int namXuatBan;
    char nhaXuatBan[256];
    char tacGia[256];
} BaiBao;

typedef struct Node {
    BaiBao data;
    struct Node *next;
} Node;

void xoaXuongDong(char *s) {
    int n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[n - 1] = '\0';
        n--;
    }
}

void chuanHoaChuoi(char *s) {
    int i = 0, j = 0;
    while (isspace((unsigned char)s[i])) i++;
    for (; s[i] != '\0'; i++) {
        if (!(isspace((unsigned char)s[i]) && (j == 0 || isspace((unsigned char)s[j - 1])))) {
            s[j++] = s[i];
        }
    }
    if (j > 0 && isspace((unsigned char)s[j - 1])) j--;
    s[j] = '\0';
}

void vietHoaChuoi(char *s) {
    for (int i = 0; s[i] != '\0'; i++) s[i] = toupper((unsigned char)s[i]);
}

void nhapChuoi(const char *msg, char *s, int size) {
    printf(BLUE "%s" RESET, msg);
    fgets(s, size, stdin);
    xoaXuongDong(s);
    chuanHoaChuoi(s);
}
int nhapLuaChon(void(*menu)());

Node* taoNode(BaiBao x) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = x;
    p->next = NULL;
    return p;
}

int rong(Node *head) {
    return head == NULL;
}

Node* timTheoMa(Node *head, char ma[]) {
    while (head != NULL) {
        if (strcmp(head->data.ma, ma) == 0) return head;
        head = head->next;
    }
    return NULL;
}

void themCuoi(Node **head, BaiBao x) {
    Node *p = taoNode(x);
    if (*head == NULL) {
        *head = p;
        return;
    }
    Node *q = *head;
    while (q->next != NULL) q = q->next;
    q->next = p;
}

int demSoLuong(Node *head) {
    int cnt = 0;
    while (head != NULL) {
        cnt++;
        head = head->next;
    }
    return cnt;
}

void inTieuDe() {
    printf(YELLOW
           "%-9s %-28s %-19s %-10s %-3s %-3s %-4s %-17s %-15s\n"
           RESET,
           "Ma",
           "Ten bai bao",
           "Ten tap chi",
           "Loai",
           "So",
           "Tap",
           "Nam",
           "Nha xuat ban",
           "Tac gia");
}

void inMotBaiBao(BaiBao x) {
    printf(WHITE "%-9s %-28s %-19s %-10s %-3d %-3d %-4d %-17s %-15s" RESET "\n",
           x.ma, x.ten, x.tapChi, x.loai, x.soXuatBan, x.tapXuatBan, x.namXuatBan, x.nhaXuatBan, x.tacGia);
}

void xuatDanhSach(Node *head) {
    if (head == NULL) {
        printf(YELLOW "Danh sach rong!\n" RESET);
        getch();
        return;
    }
    printf(YELLOW "\nDanh sach bai bao:\n" RESET);
    inTieuDe();
    while (head != NULL) {
        inMotBaiBao(head->data);
        head = head->next;
    }
    getch();
}

int nhapSo(const char *prompt) {
    char input[100];
    int number;

    while (1) {
        printf(BLUE "%s" RESET, prompt);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        int isNumber = 1;
        for (int i = 0; i < strlen(input); i++) {
            if (!isdigit((unsigned char)input[i])) {
                isNumber = 0;
                break;
            }
        }

        if (isNumber && strlen(input) > 0) {
            number = atoi(input);
            return number;
        } else {
            printf(RED "Loi: Ban phai nhap mot so hop le!\n" RESET);
        }
    }
}

BaiBao nhapMotBaiBao(Node *head) {
    BaiBao x;
    while (1) {
        nhapChuoi("Nhap ma bai bao: ", x.ma, sizeof(x.ma));
        if (strlen(x.ma) == 0) {
            printf(RED "Ma khong hop le\n" RESET);
            continue;
        }
        if (timTheoMa(head, x.ma) != NULL) {
            printf(RED "Ma bai bao da ton tai!\n" RESET);
        } else break;
    }
    nhapChuoi("Nhap ten bai bao: ", x.ten, sizeof(x.ten));
    nhapChuoi("Nhap ten tap chi: ", x.tapChi, sizeof(x.tapChi));
    nhapChuoi("Nhap loai tap chi: ", x.loai, sizeof(x.loai));
    vietHoaChuoi(x.loai);
    x.soXuatBan = nhapSo("Nhap so xuat ban: ");
    x.tapXuatBan = nhapSo("Nhap tap xuat ban: ");
    x.namXuatBan = nhapSo("Nhap nam xuat ban: ");
    nhapChuoi("Nhap nha xuat ban: ", x.nhaXuatBan, sizeof(x.nhaXuatBan));
    nhapChuoi("Nhap tac gia: ", x.tacGia, sizeof(x.tacGia));
    return x;
}

void themBaiBao(Node **head) {
    BaiBao x = nhapMotBaiBao(*head);
    themCuoi(head, x);
    printf(GREEN "Them thanh cong!\n" RESET);
    getch();
}

int xoaTheoMa(Node **head, char ma[]) {
    Node *p = *head, *truoc = NULL;
    while (p != NULL) {
        if (strcmp(p->data.ma, ma) == 0) {
            if (truoc == NULL) *head = p->next;
            else truoc->next = p->next;
            free(p);
            return 1;
        }
        truoc = p;
        p = p->next;
    }
    return 0;
}

void menuXoa(Node **head) {
    char ma[50];
    nhapChuoi("Nhap ma bai bao can xoa: ", ma, sizeof(ma));
    if (xoaTheoMa(head, ma)) printf(GREEN "Xoa thanh cong!\n" RESET);
    else printf(RED "Khong tim thay ma bai bao!\n" RESET);
    getch();
}

void timTheoTen(Node *head, char ten[]) {
    int ok = 0;
    while (head != NULL) {
        if (strstr(head->data.ten, ten) != NULL) {
            if (!ok) inTieuDe();
            inMotBaiBao(head->data);
            ok = 1;
        }
        head = head->next;
    }
    if (!ok) printf(RED "Khong tim thay bai bao!\n" RESET);
    getch();
}

void menu_ChonMucSua(){
    printf(PURPLE
"╔════════════════════════════════════════════════════════════╗\n"
"║" YELLOW "                    SUA THONG TIN BAI BAO                   " PURPLE "║\n"
"╠════════════════════════════════════════════════════════════╣\n"
"║ " WHITE "1. Ten bai bao                                             " PURPLE "║\n"
"║ " WHITE "2. Ten tap chi                                             " PURPLE "║\n"
"║ " WHITE "3. Loai tap chi                                            " PURPLE "║\n"
"║ " WHITE "4. So xuat ban                                             " PURPLE "║\n"
"║ " WHITE "5. Tap xuat ban                                            " PURPLE "║\n"
"║ " WHITE "6. Nam xuat ban                                            " PURPLE "║\n"
"║ " WHITE "7. Nha xuat ban                                            " PURPLE "║\n"
"║ " WHITE "8. Tac gia                                                 " PURPLE "║\n"
"║ " WHITE "0. Thoat                                                   " PURPLE "║\n"
"╚════════════════════════════════════════════════════════════╝\n"
RESET);
    printf(BLUE "Nhap lua chon: " RESET);
}

void suaThongTin(Node *head) {
    char ma[50];
    nhapChuoi("Nhap ma bai bao can sua: ", ma, sizeof(ma));
    Node *p = timTheoMa(head, ma);
    if (p == NULL) {
        printf(RED "Khong tim thay bai bao!\n" RESET);
        getch();
        return;
    }
    int chon;
    do {
        printf(PURPLE "\nThong tin hien tai:\n" RESET);
        inTieuDe();
        inMotBaiBao(p->data);
        do {
            chon = nhapLuaChon(menu_ChonMucSua);
            if (chon < 0 || chon > 8) {
                printf(RED "Lua chon khong hop le!\n" RESET);
            }
        } while (chon < 0 || chon > 8);
        switch (chon) {
            case 1:
                nhapChuoi("Nhap ten bai bao moi: ", p->data.ten, sizeof(p->data.ten));
                printf(GREEN "Sua thanh cong\n" RESET);
                break;

            case 2:
                nhapChuoi("Nhap ten tap chi moi: ", p->data.tapChi, sizeof(p->data.tapChi));
                printf(GREEN "Sua thanh cong\n" RESET);
                break;

            case 3:
                nhapChuoi("Nhap loai tap chi moi: ", p->data.loai, sizeof(p->data.loai));
                
                vietHoaChuoi(p->data.loai);
                
                printf(GREEN "Sua thanh cong\n" RESET);
                break;

            case 4:
                p->data.soXuatBan = nhapSo("Nhap so xuat ban moi: ");
                printf(GREEN "Sua thanh cong!\n" RESET);
                break;

            case 5:
                p->data.tapXuatBan = nhapSo("Nhap tap xuat ban moi: ");
                printf(GREEN "Sua thanh cong!\n" RESET);
                break;

            case 6:
                p->data.namXuatBan = nhapSo("Nhap nam xuat ban moi: ");
                printf(GREEN "Sua thanh cong\n" RESET);
                break;

            case 7:
                nhapChuoi("Nhap nha xuat ban moi: ", p->data.nhaXuatBan, sizeof(p->data.nhaXuatBan));
                printf(GREEN "Sua thanh cong!\n" RESET);
                break;

            case 8:
                nhapChuoi("Nhap tac gia moi: ", p->data.tacGia, sizeof(p->data.tacGia));
                printf(GREEN "Sua thanh cong!\n" RESET);
                break;

            case 0:
                printf(CYAN "Da thoat sua!\n" RESET);
                break;

            default:
                printf(RED "Lua chon khong hop le!\n" RESET);
        }
    } while (chon != 0);
}

typedef struct {
    char key[256];
    int count;
} ThongKeChuoi;

typedef struct {
    int key;
    int count;
} ThongKeNam;

void thongKeTheoLoai(Node *head) {
    ThongKeChuoi ds[1000];
    int n = 0;
    while (head != NULL) {
        int found = -1;
        for (int i = 0; i < n; i++) {
            if (strcmp(ds[i].key, head->data.loai) == 0) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            strcpy(ds[n].key, head->data.loai);
            ds[n].count = 1;
            n++;
        } else {
            ds[found].count++;
        }
        head = head->next;
    }
    printf(YELLOW "\nThong ke theo loai bai bao:\n" RESET);
    printf(YELLOW "Loai               So Luong\n" RESET);
    for (int i = 0; i < n; i++) {
        printf(WHITE "%-18s %d\n" RESET, ds[i].key, ds[i].count);
    }
}

void thongKeTheoNam(Node *head) {
    ThongKeNam ds[1000];
    int n = 0;
    while (head != NULL) {
        int found = -1;
        for (int i = 0; i < n; i++) {
            if (ds[i].key == head->data.namXuatBan) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            ds[n].key = head->data.namXuatBan;
            ds[n].count = 1;
            n++;
        } else {
            ds[found].count++;
        }
        head = head->next;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ds[i].key > ds[j].key) {
                ThongKeNam t = ds[i];
                ds[i] = ds[j];
                ds[j] = t;
            }
        }
    }
    printf(YELLOW "\nThong ke theo nam xuat ban:\n" RESET);
    printf(YELLOW "Nam              So Luong\n" RESET);
    for (int i = 0; i < n; i++) {
        printf(WHITE "%-16d %-15d\n" RESET, ds[i].key, ds[i].count);
    }
}

void menu_ThongKe(){
    printf(PURPLE
"╔════════════════════════════════════════════════════════════╗\n"
"║" YELLOW "                   THONG KE BAI BAO                         " PURPLE "║\n"
"╠════════════════════════════════════════════════════════════╣\n"
"║ " WHITE "1. Thong ke theo loai                                      " PURPLE "║\n"
"║ " WHITE "2. Thong ke theo nam                                       " PURPLE "║\n"
"║ " WHITE "0. Thoat                                                   " PURPLE "║\n"
"╚════════════════════════════════════════════════════════════╝\n"
RESET);
    printf(BLUE "Nhap lua chon: " RESET);
}
void Thongke(Node *head){
    if (head == NULL) {
        printf(YELLOW "Danh sach rong\n" RESET);
        getch();
        return;
    }
    int choice;
    do{
        do{
            choice = nhapLuaChon(menu_ThongKe);
            if (choice < 0 || choice > 2) {
                printf(RED "Lua chon khong hop le!\n" RESET);
            }
        }
        while (choice < 0 || choice > 2);
        switch (choice){
            case 1:
                thongKeTheoLoai(head);
                getch();
                break;
            case 2:
                thongKeTheoNam(head);
                getch();
                break;
            case 0:
            printf(CYAN "Da thoat thanh cong!\n" RESET);
                break;
        }
    } while(choice != 0);
}

int tachDongThanhBaiBao(char *line, BaiBao *x) {
    char *token;
    token = strtok(line, "|");
    if (token == NULL) return 0;
    strcpy(x->ma, token);

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strcpy(x->ten, token);

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strcpy(x->tapChi, token);

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strcpy(x->loai, token);

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    x->soXuatBan = atoi(token);

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    x->tapXuatBan = atoi(token);

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    x->namXuatBan = atoi(token);

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strcpy(x->nhaXuatBan, token);

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strcpy(x->tacGia, token);

    chuanHoaChuoi(x->ma);
    chuanHoaChuoi(x->ten);
    chuanHoaChuoi(x->tapChi);
    chuanHoaChuoi(x->loai);
    vietHoaChuoi(x->loai);
    chuanHoaChuoi(x->nhaXuatBan);
    chuanHoaChuoi(x->tacGia);

    return 1;
}

void giaiPhong(Node **head) {
    Node *p;
    while (*head != NULL) {
        p = *head;
        *head = (*head)->next;
        free(p);
    }
}

void menu_GiaiPhong(){
	printf(PURPLE
"╔════════════════════════════════════════════════════════════╗\n"
"║" YELLOW "          Danh sach hien dang co du lieu!                   " PURPLE "║\n"
"║" YELLOW "    Xoa du lieu cu truoc khi them file moi?                 " PURPLE "║\n"
"╠════════════════════════════════════════════════════════════╣\n"
"║ " WHITE "1. Co                                                      " PURPLE "║\n"
"║ " WHITE "2. Khong                                                   " PURPLE "║\n"
"║ " WHITE "0. Thoat                                                   " PURPLE "║\n"
"╚════════════════════════════════════════════════════════════╝\n"
RESET);
	printf(BLUE "Nhap lua chon: " RESET);
}
void nhapTuFile(Node **head) {
	if (*head != NULL){
		int choice;
		do{
		    choice = nhapLuaChon(menu_GiaiPhong);
		    if (choice < 0 || choice > 2) {
		        printf(RED "Lua chon khong hop le!\n" RESET);
		    }
		} while (choice < 0 || choice > 2);
		switch (choice){
		    case 1:
		        giaiPhong(head);
		        break;
		    case 2:
		        break;
		    case 0:
		        return;
		    }
	}
    char tenFile[256];
    nhapChuoi("Nhap ten file: ", tenFile, sizeof(tenFile));
    FILE *f = fopen(tenFile, "r");
    if (f == NULL) {
        printf(RED "Khong mo duoc file\n" RESET);
        getch();
        return;
    }
    char line[2000];
    int them = 0, trung = 0, loi = 0;
    while (fgets(line, sizeof(line), f) != NULL) {
        xoaXuongDong(line);
        if (strlen(line) == 0) continue;
        BaiBao x;
        if (!tachDongThanhBaiBao(line, &x)) {
            loi++;
            continue;
        }
        if (timTheoMa(*head, x.ma) != NULL) {
            trung++;
            continue;
        }
        themCuoi(head, x);
        them++;
    }
    fclose(f);
    printf(GREEN "Da them %d bai bao, trung ma %d, dong loi %d\n" RESET, them, trung, loi);
	getch();
}

void xuatRaFile(Node *head) {
    char tenFile[256];
    nhapChuoi("Nhap ten file can xuat: ", tenFile, sizeof(tenFile));
    FILE *f = fopen(tenFile, "w");
    if (f == NULL) {
        printf(RED "Khong tao duoc file\n" RESET);
        getch();
        return;
    }
    while (head != NULL) {
        fprintf(f, "%s|%s|%s|%s|%d|%d|%d|%s|%s\n",
                head->data.ma,
                head->data.ten,
                head->data.tapChi,
                head->data.loai,
                head->data.soXuatBan,
                head->data.tapXuatBan,
                head->data.namXuatBan,
                head->data.nhaXuatBan,
                head->data.tacGia);
        head = head->next;
    }
    fclose(f);
    printf(GREEN "Xuat file thanh cong!\n" RESET);
    getch();
}

void hoanViDuLieu(BaiBao *a, BaiBao *b) {
    BaiBao t = *a;
    *a = *b;
    *b = t;
}

void sapXepTheoNam(Node *head) {
    for (Node *p = head; p != NULL; p = p->next) {
        for (Node *q = p->next; q != NULL; q = q->next) {
            if (p->data.namXuatBan > q->data.namXuatBan) {
                hoanViDuLieu(&p->data, &q->data);
            }
        }
    }
    printf(CYAN "Sap xep theo nam thanh cong!\n" RESET);
}

void sapXepTheoTen(Node *head) {
    for (Node *p = head; p != NULL; p = p->next) {
        for (Node *q = p->next; q != NULL; q = q->next) {
            if (strcmp(p->data.ten, q->data.ten) > 0) {
                hoanViDuLieu(&p->data, &q->data);
            }
        }
    }
    printf(CYAN "Sap xep theo ten thanh cong!\n" RESET);
}

void menu_SapXep(){
    printf(PURPLE
"╔════════════════════════════════════════════════════════════╗\n"
"║" YELLOW "                    SAP XEP BAI BAO                         " PURPLE "║\n"
"╠════════════════════════════════════════════════════════════╣\n"
"║ " WHITE "1. Sap xep theo nam                                        " PURPLE "║\n"
"║ " WHITE "2. Sap xep theo ten                                        " PURPLE "║\n"
"║ " WHITE "0. Thoat                                                   " PURPLE "║\n"
"╚════════════════════════════════════════════════════════════╝\n"
RESET);
    printf(BLUE "Nhap lua chon: " RESET);
}
void menuSapXep(Node *head) {
    if (head == NULL) {
        printf(YELLOW "Danh sach rong!\n" RESET);
        getch();
        return;
    }
    int chon;
    while(1){
        do{
            chon = nhapLuaChon(menu_SapXep);
            if (chon < 0 || chon > 2) {
                printf(RED "Lua chon khong hop le!\n" RESET);
            }
        }
        while (chon < 0 || chon > 2);
        if (chon == 1) {
			sapXepTheoNam(head);
            xuatDanhSach(head);
			getch();
		}
        else if (chon == 2) {
			sapXepTheoTen(head);
            xuatDanhSach(head);
			getch();
		}
        else if (chon == 0){
            printf(CYAN "Da thoat thanh cong!\n" RESET);
            break;
        };
    }
}

void timTheoNhaXuatBan(Node *head, char nhaXuatBan[]) {
    int ok = 0;
    while (head != NULL) {
        if (strstr(head->data.nhaXuatBan, nhaXuatBan) != NULL) {
            if (!ok) inTieuDe();
            inMotBaiBao(head->data);
            ok = 1;
        }
        head = head->next;
    }
    if (!ok) printf(RED "Khong tim thay bai bao\n" RESET);
}

void timTheoTacGia(Node *head, char tacGia[]) {
    int ok = 0;
    while (head != NULL) {
        if (strstr(head->data.tacGia, tacGia) != NULL) {
            if (!ok) inTieuDe();
            inMotBaiBao(head->data);
            ok = 1;
        }
        head = head->next;
    }
    if (!ok) printf(RED "Khong tim thay bai bao\n" RESET);
}

void timTheoNam(Node *head, int nam) {
    int ok = 0;
    while (head != NULL) {
        if (head->data.namXuatBan == nam) {
            if (!ok) inTieuDe();
            inMotBaiBao(head->data);
            ok = 1;
        }
        head = head->next;
    }
    if (!ok) printf(RED "Khong tim thay bai bao\n" RESET);
}

void menu_TimKiem(){
    printf(PURPLE
"╔════════════════════════════════════════════════════════════╗\n"
"║" YELLOW "                   TIM KIEM BAI BAO                         " PURPLE "║\n"
"╠════════════════════════════════════════════════════════════╣\n"
"║ " WHITE "1. Tim theo ma                                             " PURPLE "║\n"
"║ " WHITE "2. Tim theo ten                                            " PURPLE "║\n"
"║ " WHITE "3. Tim theo nam xuat ban                                   " PURPLE "║\n"
"║ " WHITE "4. Tim theo nha xuat ban                                   " PURPLE "║\n"
"║ " WHITE "5. Tim theo tac gia                                        " PURPLE "║\n"
"║ " WHITE "0. Thoat                                                   " PURPLE "║\n"
"╚════════════════════════════════════════════════════════════╝\n"
RESET);
    printf(BLUE "Nhap lua chon: " RESET);
}
void menuTimKiem(Node *head) {
    int chon;
    while(1){
        do{
            chon = nhapLuaChon(menu_TimKiem);
            if (chon < 0 || chon > 5) {
                printf(RED "Lua chon khong hop le!\n" RESET);
            }
        }
        while (chon < 0 || chon > 5);
        if (chon == 1) {
            char ma[50];
            nhapChuoi("Nhap ma bai bao: ", ma, sizeof(ma));
            Node *p = timTheoMa(head, ma);
            if (p == NULL) {
                printf(RED "Khong tim thay bai bao!\n" RESET);
                getch();
            }
            else {
                inTieuDe();
                inMotBaiBao(p->data);
                getch();
            }
        }
        else if (chon == 2) {
            char ten[256];
            nhapChuoi("Nhap ten bai bao can tim: ", ten, sizeof(ten));
            timTheoTen(head, ten);
        }
        else if (chon == 3) {
            int nam;
            nam = nhapSo("Nhap nam xuat ban can tim: ");
            timTheoNam(head, nam);
            getch();
        }
        else if (chon == 4) {
            char nhaXuatBan[256];
            nhapChuoi("Nhap nha xuat ban can tim: ", nhaXuatBan, sizeof(nhaXuatBan));
            timTheoNhaXuatBan(head, nhaXuatBan);
            getch();
        }
        else if (chon == 5) {
            char tacGia[256];
            nhapChuoi("Nhap tac gia can tim: ", tacGia, sizeof(tacGia));
            timTheoTacGia(head, tacGia);
            getch();
        }
        else if (chon == 0){
            printf(CYAN "Da thoat thanh cong!\n" RESET);
            break;
        }
}
}

void menu() {
    printf(CYAN
"╔════════════════════════════════════════════════════════════╗\n"
"║" YELLOW "                 QUAN LY BAI BAO KHOA HOC                 " CYAN "  ║\n"
"╠════════════════════════════════════════════════════════════╣\n"
"║ " WHITE "1. Nhap danh sach bai bao tu file                        " CYAN "  ║\n"
"║ " WHITE "2. Xuat danh sach bai bao ra man hinh                    " CYAN "  ║\n"
"║ " WHITE "3. Them mot bai bao                                      " CYAN "  ║\n"
"║ " WHITE "4. Xoa bai bao theo ma                                   " CYAN "  ║\n"
"║ " WHITE "5. Tim kiem bai bao                                      " CYAN "  ║\n"
"║ " WHITE "6. Sua thong tin bai bao                                 " CYAN "  ║\n"
"║ " WHITE "7. Thong ke bai bao                                      " CYAN "  ║\n"
"║ " WHITE "8. Xuat du lieu ra file                                  " CYAN "  ║\n"
"║ " WHITE "9. Sap xep bai bao                                       " CYAN "  ║\n"
"║ " WHITE "0. Thoat                                                 " CYAN "  ║\n"
"╚════════════════════════════════════════════════════════════╝\n"
RESET);

printf(BLUE "Nhap lua chon: " RESET);
} 

int nhapLuaChon(void(*menu)()){
    char s[100];

    while(1){
        menu();
        fgets(s, sizeof(s), stdin);

        s[strcspn(s, "\n")] = '\0';

        if(s[0] == '\0'){
            printf(RED "Khong duoc de trong!\n" RESET);
            continue;
        }

        int i = 0;
        while(s[i]!= '\0'){
            if(!isdigit(s[i])){
                printf(RED "Nhap sai! Chi duoc nhap so.\n" RESET);
                break;
            }
            i++;
        }

        if(s[i] != '\0'){
            continue;
        }

        return atoi(s);
    }
}

void gioiThieu() {
    printf(BLUE
    "╔════════════════════════════════════════════════════════════╗\n"
    "║                                                            ║\n"
    "║" YELLOW "               DE TAI: QUAN LY BAI BAO KHOA HOC          " BLUE "   ║\n"
    "║                                                            ║\n"
    "╠════════════════════════════════════════════════════════════╣\n"
    "║" CYAN "                    THANH VIEN NHOM                      " BLUE "   ║\n"
    "╠════════════════════════════════════════════════════════════╣\n"
    "║ " WHITE "1. UNG NHO PHONG                          " GREEN "25T_DT1" BLUE "          ║\n"
    "║ " WHITE "2. TRAN NGOC HIEU                         " GREEN "25T_DT1" BLUE "          ║\n"
    "╚════════════════════════════════════════════════════════════╝\n"
    RESET);

    getch();
}

int main() {
	SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    gioiThieu();
    Node *head = NULL;
    int chon;
    do {
   	chon = nhapLuaChon(menu);
    switch (chon) {
        case 1:
            nhapTuFile(&head);
            break;
        case 2:
            xuatDanhSach(head);
            break;
        case 3:
            themBaiBao(&head);
            break;
        case 4:
            menuXoa(&head);
            break;
        case 5:
            menuTimKiem(head);
            break;
        case 6:
            suaThongTin(head);
            break;
        case 7:
            Thongke(head);
            break;
        case 8:
            xuatRaFile(head);
            break;
        case 9:
            menuSapXep(head);
            break;
        case 0:
            printf(CYAN "Da thoat chuong trinh!\n" RESET);
            break;
        default:
            printf(RED "Lua chon khong hop le!\n" RESET);
            break;
    }
} while (chon != 0);
    giaiPhong(&head);
    return 0;
}

