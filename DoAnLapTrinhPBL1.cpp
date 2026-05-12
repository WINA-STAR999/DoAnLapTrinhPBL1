#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    printf("%s", msg);
    fgets(s, size, stdin);
    xoaXuongDong(s);
    chuanHoaChuoi(s);
}

int nhapLuaChon(){
    char s[100];

    while(1){
        fgets(s, sizeof(s), stdin);

        s[strcspn(s, "\n")] = '\0';

        if(s[0] == '\0'){
            printf("Khong duoc de trong!\n");
            printf("Nhap lua chon: ");
            continue;
        }

        int i = 0;
        while(s[i] != '\0'){
            if(!isdigit(s[i])){
                printf("Nhap sai! Chi duoc nhap so.\n");
                printf("Nhap lua chon: ");
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
    printf("\n%-12s %-25s %-20s %-12s %-10s %-10s %-10s %-20s %-25s\n",
           "Ma", "Ten bai bao", "Ten tap chi", "Loai", "So", "Tap", "Nam", "Nha xuat ban", "Tac gia");
}

void inMotBaiBao(BaiBao x) {
    printf("%-12s %-25s %-20s %-12s %-10d %-10d %-10d %-20s %-25s\n",
           x.ma, x.ten, x.tapChi, x.loai, x.soXuatBan, x.tapXuatBan, x.namXuatBan, x.nhaXuatBan, x.tacGia);
}

void xuatDanhSach(Node *head) {
    if (head == NULL) {
        printf("\nDanh sach rong\n");
        return;
    }
    inTieuDe();
    while (head != NULL) {
        inMotBaiBao(head->data);
        head = head->next;
    }
}

BaiBao nhapMotBaiBao(Node *head) {
    BaiBao x;
    while (1) {
        nhapChuoi("Nhap ma bai bao: ", x.ma, sizeof(x.ma));
        if (strlen(x.ma) == 0) {
            printf("Ma khong hop le\n");
            continue;
        }
        if (timTheoMa(head, x.ma) != NULL) {
            printf("Ma bai bao da ton tai\n");
        } else break;
    }
    nhapChuoi("Nhap ten bai bao: ", x.ten, sizeof(x.ten));
    nhapChuoi("Nhap ten tap chi: ", x.tapChi, sizeof(x.tapChi));
    nhapChuoi("Nhap loai tap chi: ", x.loai, sizeof(x.loai));
    vietHoaChuoi(x.loai);
    printf("Nhap so xuat ban: ");
    scanf("%d", &x.soXuatBan);
    printf("Nhap tap xuat ban: ");
    scanf("%d", &x.tapXuatBan);
    printf("Nhap nam xuat ban: ");
    scanf("%d", &x.namXuatBan);
    getchar();
    nhapChuoi("Nhap nha xuat ban: ", x.nhaXuatBan, sizeof(x.nhaXuatBan));
    nhapChuoi("Nhap tac gia: ", x.tacGia, sizeof(x.tacGia));
    return x;
}

void themBaiBao(Node **head) {
    BaiBao x = nhapMotBaiBao(*head);
    themCuoi(head, x);
    printf("Them thanh cong\n");
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
    if (xoaTheoMa(head, ma)) printf("Xoa thanh cong\n");
    else printf("Khong tim thay ma bai bao\n");
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
    if (!ok) printf("Khong tim thay bai bao\n");
}


void suaThongTin(Node *head) {
    char ma[50];
    nhapChuoi("Nhap ma bai bao can sua: ", ma, sizeof(ma));
    Node *p = timTheoMa(head, ma);
    if (p == NULL) {
        printf("Khong tim thay bai bao\n");
        return;
    }

    int chon;
    do {
        printf("\nThong tin hien tai:\n");
        inTieuDe();
        inMotBaiBao(p->data);

        printf("\n===== CHON MUC CAN SUA =====\n");
        printf("1. Ten bai bao\n");
        printf("2. Ten tap chi\n");
        printf("3. Loai tap chi\n");
        printf("4. So xuat ban\n");
        printf("5. Tap xuat ban\n");
        printf("6. Nam xuat ban\n");
        printf("7. Nha xuat ban\n");
        printf("8. Tac gia\n");
        printf("0. Thoat sua\n");
        printf("Nhap lua chon: ");
        scanf("%d", &chon);
        getchar();

        if (chon == 1) {
            nhapChuoi("Nhap ten bai bao moi: ", p->data.ten, sizeof(p->data.ten));
            printf("Sua thanh cong\n");
        }
        else if (chon == 2) {
            nhapChuoi("Nhap ten tap chi moi: ", p->data.tapChi, sizeof(p->data.tapChi));
            printf("Sua thanh cong\n");
        }
        else if (chon == 3) {
            nhapChuoi("Nhap loai tap chi moi: ", p->data.loai, sizeof(p->data.loai));
            vietHoaChuoi(p->data.loai);
            printf("Sua thanh cong\n");
        }
        else if (chon == 4) {
            printf("Nhap so xuat ban moi: ");
            scanf("%d", &p->data.soXuatBan);
            getchar();
            printf("Sua thanh cong\n");
        }
        else if (chon == 5) {
            printf("Nhap tap xuat ban moi: ");
            scanf("%d", &p->data.tapXuatBan);
            getchar();
            printf("Sua thanh cong\n");
        }
        else if (chon == 6) {
            printf("Nhap nam xuat ban moi: ");
            scanf("%d", &p->data.namXuatBan);
            getchar();
            printf("Sua thanh cong\n");
        }
        else if (chon == 7) {
            nhapChuoi("Nhap nha xuat ban moi: ", p->data.nhaXuatBan, sizeof(p->data.nhaXuatBan));
            printf("Sua thanh cong\n");
        }
        else if (chon == 8) {
            nhapChuoi("Nhap tac gia moi: ", p->data.tacGia, sizeof(p->data.tacGia));
            printf("Sua thanh cong\n");
        }
        else if (chon == 0) {
            printf("Da thoat sua\n");
        }
        else {
            printf("Lua chon khong hop le\n");
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
    printf("\nThong ke theo loai bai bao:\n");
    for (int i = 0; i < n; i++) {
        printf("%-15s : %d\n", ds[i].key, ds[i].count);
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
    printf("\nThong ke theo nam xuat ban:\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d : %d\n", ds[i].key, ds[i].count);
    }
}

void Thongke(Node *head){
    if (head == NULL) {
        printf("Danh sach rong\n");
        return;
    }
    int choice;
    do{
    	printf("1.Thong ke theo loai\n");
    	printf("2.Thong ke theo nam\n");
    	printf("0.Thoat\n");
    	printf("Nhap lua chon: ");
        do{
            choice = nhapLuaChon();
            if (choice < 0 || choice > 2) {
                printf("Lua chon khong hop le!\n");
                printf("Nhap lua chon: ");
            }
        }
        while (choice < 0 || choice > 2);
        switch (choice){
            case 1:
                thongKeTheoLoai(head);
                break;
            case 2:
                thongKeTheoNam(head);
                break;
            case 0:
            printf("Da thoat thanh cong!\n");
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

void nhapTuFile(Node **head) {
    char tenFile[256];
    nhapChuoi("Nhap ten file: ", tenFile, sizeof(tenFile));
    FILE *f = fopen(tenFile, "r");
    if (f == NULL) {
        printf("Khong mo duoc file\n");
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
    printf("Da them %d bai bao, trung ma %d, dong loi %d\n", them, trung, loi);
}

void xuatRaFile(Node *head) {
    char tenFile[256];
    nhapChuoi("Nhap ten file can xuat: ", tenFile, sizeof(tenFile));
    FILE *f = fopen(tenFile, "w");
    if (f == NULL) {
        printf("Khong tao duoc file\n");
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
    printf("Xuat file thanh cong\n");
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
    printf("Sap xep theo nam thanh cong\n");
}

void sapXepTheoTen(Node *head) {
    for (Node *p = head; p != NULL; p = p->next) {
        for (Node *q = p->next; q != NULL; q = q->next) {
            if (strcmp(p->data.ten, q->data.ten) > 0) {
                hoanViDuLieu(&p->data, &q->data);
            }
        }
    }
    printf("Sap xep theo ten thanh cong\n");
}

void menuSapXep(Node *head) {
    if (head == NULL) {
        printf("Danh sach rong\n");
        return;
    }
    int chon;
    while(1){
        printf("\n1. Sap xep theo nam\n");
        printf("2. Sap xep theo ten\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon: ");
        do{
            chon = nhapLuaChon();
            if (chon < 0 || chon > 2) {
                printf("Lua chon khong hop le!\n");
                printf("Nhap lua chon: ");
            }
        }
        while (chon < 0 || chon > 2);
        if (chon == 1) sapXepTheoNam(head);
        else if (chon == 2) sapXepTheoTen(head);
        else if (chon == 0){
            printf("Da thoat thanh cong!");
            break;
        };
    }
}

void giaiPhong(Node **head) {
    Node *p;
    while (*head != NULL) {
        p = *head;
        *head = (*head)->next;
        free(p);
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
    if (!ok) printf("Khong tim thay bai bao\n");
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
    if (!ok) printf("Khong tim thay bai bao\n");
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
    if (!ok) printf("Khong tim thay bai bao\n");
}

void menuTimKiem(Node *head) {
    int chon;
    while(1){
        printf("\n1. Tim theo ma\n");
        printf("2. Tim theo ten\n");
        printf("3. Tim theo nam xuat ban\n");
        printf("4. Tim theo nha xuat ban\n");
        printf("5. Tim theo tac gia\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon: ");
        do{
            chon = nhapLuaChon();
            if (chon < 0 || chon > 5) {
                printf("Lua chon khong hop le!\n");
                printf("Nhap lua chon: ");
            }
        }
        while (chon < 0 || chon > 5);
        if (chon == 1) {
            char ma[50];
            nhapChuoi("Nhap ma bai bao: ", ma, sizeof(ma));
            Node *p = timTheoMa(head, ma);
            if (p == NULL) printf("Khong tim thay bai bao\n");
            else {
                inTieuDe();
                inMotBaiBao(p->data);
            }
        }
        else if (chon == 2) {
            char ten[256];
            nhapChuoi("Nhap ten bai bao can tim: ", ten, sizeof(ten));
            timTheoTen(head, ten);
        }
        else if (chon == 3) {
            int nam;
            printf("Nhap nam xuat ban can tim: ");
            scanf("%d", &nam);
            getchar();
            timTheoNam(head, nam);
        }
        else if (chon == 4) {
            char nhaXuatBan[256];
            nhapChuoi("Nhap nha xuat ban can tim: ", nhaXuatBan, sizeof(nhaXuatBan));
            timTheoNhaXuatBan(head, nhaXuatBan);
        }
        else if (chon == 5) {
            char tacGia[256];
            nhapChuoi("Nhap tac gia can tim: ", tacGia, sizeof(tacGia));
            timTheoTacGia(head, tacGia);
        }
        else if (chon == 0){
            printf("Da thoat thanh cong!");
            break;
        }
}
}

void menu() {
    printf("\n========== QUAN LY BAI BAO KHOA HOC ==========\n");
    printf("1. Nhap danh sach bai bao tu file\n");
    printf("2. Xuat danh sach bai bao ra man hinh\n");
    printf("3. Them mot bai bao\n");
    printf("4. Xoa bai bao theo ma\n");
    printf("5. Tim kiem bai bao\n");
    printf("6. Sua thong tin bai bao\n");
    printf("7. Thong ke bai bao\n");
    printf("8. Xuat du lieu ra file\n");
    printf("9. Sap xep bai bao\n");
    printf("0. Thoat\n");
    printf("Nhap lua chon: ");
}

int nhapLuaChonMenu(){
    char s[100];

    while(1){
        fgets(s, sizeof(s), stdin);

        s[strcspn(s, "\n")] = '\0';

        if(s[0] == '\0'){
            printf("Khong duoc de trong!\n");
            menu();
            continue;
        }

        int i = 0;
        while(s[i] != '\0'){
            if(!isdigit(s[i])){
                printf("Nhap sai! Chi duoc nhap so.\n");
                menu();
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
int main() {
    Node *head = NULL;
    int chon;
    do {
    menu();
   	chon = nhapLuaChonMenu();
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
            printf("Da thoat chuong trinh!\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
            break;
    }
} while (chon != 0);
    giaiPhong(&head);
    return 0;
}
