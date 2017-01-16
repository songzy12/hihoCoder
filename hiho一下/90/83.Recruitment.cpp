#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int kMaxN = 105, kMaxB = 1005;
int dpf[kMaxN][kMaxB], dpm[kMaxN][kMaxB];//dpf[i][j]������Ů��ӦƸ����ѡȡi���������ܺ�Ϊjʱ�����������
unsigned long long idf[kMaxN][kMaxB][2];//��¼Ů��ѡȡ���
unsigned long long idm[kMaxN][kMaxB][2];//��¼����ѡȡ���
int N, X, Y, B, V, S;
char G[2];
int ans_v = 0, ans_s = 0;//���������ܹ���
unsigned long long ans_id[2] = { 0 };//��ѡȡ���
void DP()
{
    dpf[0][0] = dpm[0][0] = 0;
    int cnt_f = 0, cnt_m = 0, sum_s = 0;
    for (int i = 1; i <= N; i++)
    {
        scanf("%s %d %d", G, &V, &S);
        sum_s += S;
        sum_s = min(sum_s, B);
        if (G[0] == 'F')
        {
            cnt_f++;
            cnt_f = min(cnt_f, Y);//���ѡȡYλ
            for (int j = cnt_f; j >= 1; j--)
            {
                for (int k = sum_s; k >= S; k--)
                {
                    if (dpf[j - 1][k - S] < 0)
                        continue;
                    if (dpf[j - 1][k - S] + V > dpf[j][k])
                    {
                        dpf[j][k] = dpf[j - 1][k - S] + V;
                        idf[j][k][0] = idf[j - 1][k - S][0];
                        idf[j][k][1] = idf[j - 1][k - S][1];
                        if (i <= 50)
                            idf[j][k][0] |= 1LL << (i - 1);//ѡ�е�iλ
                        else
                            idf[j][k][1] |= 1LL << (i - 1 - 50);//ѡ�е�iλ
                    }
                }
            }
        }
        else
        {
            cnt_m++;
            cnt_m = min(cnt_m, X);
            for (int j = cnt_m; j >= 1; j--)
            {
                for (int k = sum_s; k >= S; k--)
                {
                    if (dpm[j - 1][k - S] < 0)
                        continue;
                    if (dpm[j - 1][k - S] + V > dpm[j][k])
                    {
                        dpm[j][k] = dpm[j - 1][k - S] + V;
                        idm[j][k][0] = idm[j - 1][k - S][0];
                        idm[j][k][1] = idm[j - 1][k - S][1];
                        if (i <= 50)
                            idm[j][k][0] |= 1LL << (i - 1);
                        else
                            idm[j][k][1] |= 1LL << (i - 1 - 50);
                    }
                }
            }
        }
    }
}
void Match()
{
    for (int i = 0; i <= B; i++)
    {
        if (dpf[Y][i] == -1)
            continue;
        for (int j = 0; j + i <= B; j++)
        {
            if (dpm[X][j] == -1)
                continue;
            if (dpf[Y][i] + dpm[X][j] > ans_v)//������ǿ
            {
                ans_v = dpf[Y][i] + dpm[X][j];
                ans_s = i + j;
                ans_id[0] = idf[Y][i][0] | idm[X][j][0];
                ans_id[1] = idf[Y][i][1] | idm[X][j][1];
            }
            else if (dpf[Y][i] + dpm[X][j] == ans_v && (i + j) < ans_s)//������ͬ�������ʸ���
            {
                ans_s = i + j;
                ans_id[0] = idf[Y][i][0] | idm[X][j][0];
                ans_id[1] = idf[Y][i][1] | idm[X][j][1];
            }
            else if (dpf[Y][i] + dpm[X][j] == ans_v && (i + j) == ans_s)//�����͹��ʶ���ͬ
            {
                int id0 = idf[Y][i][0] | idm[X][j][0];
                int id1 = idf[Y][i][1] | idm[X][j][1];
                if (ans_id[0] > id0)//����ǰ
                {
                    ans_id[0] = id0;
                    ans_id[1] = id1;
                }
                else if (ans_id[1] > id1)//����ǰ
                {
                    ans_id[0] = id0;
                    ans_id[1] = id1;
                }
            }
        }
    }
}
void FormatOut()
{
    printf("%d %d\n", ans_v, ans_s);
    for (int i = 1; i <= 50; i++)
    {
        if (ans_id[0] & 1)
            printf("%d ", i);
        ans_id[0] >>= 1;
    }
    for (int i = 51; i <= 100; i++)
    {
        if (ans_id[1] & 1)
            printf("%d ", i);
        ans_id[1] >>= 1;
    }
}
int main()
{
    memset(dpf, -1, sizeof(dpf));
    memset(dpm, -1, sizeof(dpm));
    memset(idf, 0, sizeof(idf));
    memset(idm, 0, sizeof(idm));
    scanf("%d %d %d %d", &N, &X, &Y, &B);
    DP();
    Match();
    FormatOut();
    return 0;
}