#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<list>
#include<iomanip>
#define x first
#define y second
#define pii pair<int, int>
#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN = 1000;

struct row {
    int childId;          // �Ӳ˵�ָ��
    int expandLength;     // �Ӳ˵����� 
    row():childId(-1),expandLength(0) {};
    row(int _id):childId(_id),expandLength(0) {};
};

struct section {
    vector< row > rows;   // ������row���
    int selfLength;       // ����ĳ��� s1
    int expandLength;     // չ���Ӳ˵�֮��ĳ��� sr1
    int delta;            // �Ӳ˵�֮��ĳ���������Ĳ�ֵ ?
    section():selfLength(0),expandLength(0),delta(0) {};
};

struct panel {
    vector< section > sections; // ������section���
    vector< int > rowIds;       // ����ʱ��panel�ڵ�rowId
};

panel panels[ MAXN ];

void dealPanel(panel &p) {
    // this row does not lead to a new panel
    if ( (int) p.rowIds.size() == 0 ) return ;

    p.sections.push_back(section());
    int sectionId = 0;

    // ����һ��ĩβ0�����㴦�����һ��section
    p.rowIds.push_back(0);

    // ���γ�ÿһ��section
    for (int i = 0; i != (int) p.rowIds.size(); ++i)
        if (p.rowIds[i] != 0) {
            p.sections[ sectionId ].rows.push_back( row(p.rowIds[i]) );
        }   else {
            // �µ�section
            p.sections.push_back(section());
            sectionId++;
        }
    return ;
}
bool sortByExpandLength(row x, row y) {
    return x.expandLength > y.expandLength;
}

bool sortByDelta(section x, section y) {
    return x.delta > y.delta;
}

int getExpandLength(panel &p)
{

    // ret��ʼ��Ϊ0��ret��ʾ��panel����Сչ������
    int ret = 0;

    // ö��ÿһ��section
    for (int i = 0; i != (int) p.sections.size(); ++i)
    {

        // �����section�ڵ�ÿһ��row���Ӳ˵�
        for (int j = 0; j != (int) p.sections[i].rows.size(); ++j)
            p.sections[i].rows[j].expandLength = getExpandLength( panels[ p.sections[i].rows[j].childId ] );

        // ����row��expandLength��section�ڵ�row��������
        sort(p.sections[i].rows.begin(), p.sections[i].rows.end(), sortByExpandLength);

        // ����õ�section��ֵ
        p.sections[i].selfLength = (int) p.sections[i].rows.size();
        p.sections[i].expandLength = p.sections[i].selfLength; // չ��ֵ����ΪselfLength

        // ö��ÿһ��row���ҵ�չ��ֵ������Ϊsection��չ��ֵ
        for (int j = 0; j != (int) p.sections[i].rows.size(); ++j)
            if (p.sections[i].expandLength < j + p.sections[i].rows[j].expandLength)
                p.sections[i].expandLength = j + p.sections[i].rows[j].expandLength;

        // ����section��?ֵ
        p.sections[i].delta = p.sections[i].expandLength - p.sections[i].selfLength;

        // �ۼ�panel�����е�row������Ϊ��С��ret
        ret += p.sections[i].selfLength;
    }

    // ����section��?ֵ��������
    sort(p.sections.begin(), p.sections.end(), sortByDelta);

    // now��¼��ǰsection����ʼ����
    int now = 0;

    // ö��ÿһ��section���ҵ�չ��ֵ������Ϊpanel��չ��ֵ
    for (int i = 0; i != (int) p.sections.size(); ++i)
    {
        if (ret < now + p.sections[i].expandLength)
            ret = now + p.sections[i].expandLength;

        // �ۼ�Ϊ��һ��section����ʼ����
        now += p.sections[i].selfLength;
    }

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
    // ����ÿһ��panel�����
    int n;
    cin >> n;
    int id, numOfIds;
    // one line for root panel, n lines for n rows.
    for (int i = 0; i <= n; ++i) {
        cin >> numOfIds;
        while (numOfIds--) {
            cin >> id;
            if (id == 0) ++numOfIds; // not a real row
            panels[i].rowIds.push_back(id);
        }
        dealPanel( panels[i] );    // ����panel�����
    }
    cout << getExpandLength( panels[0] ) << endl;
}