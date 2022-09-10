#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 1000;

int cmd_key = -1;
int sl;

typedef struct ck
{
    char name[10];
    float open[10], close[10];
    int ngayTang;
    struct ck *left, *right;
} ck;

ck *root;

ck *makeNode(char *name, float open0, float close0)
{
    ck *a = (ck *)malloc(sizeof(ck));
    strcpy(a->name, name);
    a->open[0] = open0;
    a->close[0] = close0;
    for (int i = 1; i < 10; i++)
    {
        a->open[i] = 0;
        a->close[i] = 0;
    }
    a->ngayTang = 0;
    a->left = NULL;
    a->right = NULL;
    return a;
}

ck *addNode(ck *r, char *name, float open0, float close0)
{
    if (r == NULL)
        return makeNode(name, open0, close0);
    int c = strcmp(r->name, name);
    if (c > 0)
        r->left = addNode(r->left, name, open0, close0);
    else if (c < 0)
        r->right = addNode(r->right, name, open0, close0);
    return r;
}

ck *find(ck *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c == 0)
        return r;
    if (c > 0)
        return find(r->left, name);
    else
        return find(r->right, name);
    return NULL;
}

void readFile()
{
    FILE *f = fopen("data.txt", "r");
    fscanf(f, "%d", &sl);
    for (int i = 0; i < sl; i++)
    {
        char name[10];
        float close0, open0;
        fscanf(f, "%s%f%f", name, &open0, &close0);
        root = addNode(root, name, open0, close0);
    }

    for (int i = 1; i < 10; i++)
    {
        for (int j = 0; j < sl; j++)
        {
            char name[10];
            float open, close;
            fscanf(f, "%s%f%f", name, &open, &close);
            ck *a = find(root, name);
            if (a != NULL)
            {
                a->open[i] = open;
                a->close[i] = close;
            }
        }
    }
}

float tbHieu(float a[], float b[])
{
    float sum = 0;
    float hieu = 0;
    for (int i = 0; i < 10; i++)
    {
        hieu = b[i] - a[i];
        sum += hieu;
    }
    return sum / sl;
}

void inOrder(ck *r)
{
    if (r == NULL)
        return;
    inOrder(r->left);
    printf("%-6s %.3f\n", r->name, tbHieu(r->open, r->close));
    inOrder(r->right);
}

void findByName()
{
    printf("Nhap ten ma can tim:");
    char name[10];
    fflush(stdin);
    scanf("%s", name);
    ck *a = find(root, name);
    if (a == NULL)
    {
        printf(" Khong tim thay ma %s\n", name);
        return;
    }
    float min = a->close[0];
    float max = a->close[0];
    for (int i = 1; i < 10; i++)
    {
        if (a->close[i] > max)
            max = a->close[i];
        if (a->close[i] < min)
            min = a->close[i];
    }

    printf("Tim thay ma %s\n", name);
    printf("Gia dong cua cao nhat trong 10 ngay :%.3f\n", max);
    printf("Gia dong cua thap nhap trong 10 ngay :%.3f\n", min);
}

void timXH(ck *r)
{
    if (r == NULL)
        return;
    timXH(r->left);
    float hieu0, hieu1;
    hieu0 = r->close[0] - r->open[0];
    hieu1 = r->close[1] - r->open[1];
    if (hieu0 > 0 && hieu1 > 0)
        printf("%s\n", r->name);
    timXH(r->right);
}
void giaodien()
{
    	printf("========================================\n");
		printf("  CHUONG TRINH CHUNG KHOAN  \n");
		printf("  [1]. Doc file\n");
		printf("  [2]. Tim kiem theo ma chung khoan\n");
		printf("  [3]. Tim kiem ma chung khoan co xu huong tang\n");
		printf("  [4]. Tim ma co so ngay tang lon nhat\n");
		printf("  [5]. Thoat\n");
		printf("=========================================\n");
		printf("Nhap lua chon cua ban: ");
}

void demNgayTang(ck *r)
{
    if (r == NULL)
        return;
    demNgayTang(r->left);
    for (int i = 0; i < 10; i++)
    {
        if (r->close[i] > r->open[i])
            r->ngayTang += 1;
    }
    demNgayTang(r->right);
}

int maxTang = 0;

void MaxTang(ck *r)
{
    if (r == NULL)
        return;
    MaxTang(r->left);
    if (r->ngayTang > maxTang)
        maxTang = r->ngayTang;
    MaxTang(r->right);
}

void inMaxTang(ck *r)
{
    if (r == NULL)
        return;
    inMaxTang(r->left);
    if (r->ngayTang == maxTang)
        printf("%s\n", r->name);
    inMaxTang(r->right);
}

int main()
{

    // Menu
    do
    {
        giaodien();
        scanf("%d", &cmd_key);
        switch (cmd_key)
        {
        case 1:
            readFile();
            inOrder(root);
            getch();
            break;

        case 2:
            findByName();
            getch();
            break;

        case 3:
            printf("Nhung ma xu huong tang trong 2 ngay dau: \n");
            timXH(root);
            getch();
            break;
        case 4:
            demNgayTang(root);
            MaxTang(root);
            inMaxTang(root);
        default:
            break;
        }
    } while (cmd_key != 5);

    printf("Ho va ten: Le Duc Quy\n");
    printf("MSSV: 20205121\n");
    return 0;
}
