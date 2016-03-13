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
    int childId;          // 子菜单指针
    int expandLength;     // 子菜单长度 
    row():childId(-1),expandLength(0) {};
    row(int _id):childId(_id),expandLength(0) {};
};

struct section {
    vector< row > rows;   // 包含的row情况
    int selfLength;       // 自身的长度 s1
    int expandLength;     // 展开子菜单之后的长度 sr1
    int delta;            // 子菜单之后的长度与自身的差值 ?
    section():selfLength(0),expandLength(0),delta(0) {};
};

struct panel {
    vector< section > sections; // 包含的section情况
    vector< int > rowIds;       // 读入时该panel内的rowId
};

panel panels[ MAXN ];

void dealPanel(panel &p) {
    // this row does not lead to a new panel
    if ( (int) p.rowIds.size() == 0 ) return ;

    p.sections.push_back(section());
    int sectionId = 0;

    // 加入一个末尾0，方便处理最后一个section
    p.rowIds.push_back(0);

    // 依次出每一个section
    for (int i = 0; i != (int) p.rowIds.size(); ++i)
        if (p.rowIds[i] != 0) {
            p.sections[ sectionId ].rows.push_back( row(p.rowIds[i]) );
        }   else {
            // 新的section
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

    // ret初始化为0，ret表示该panel的最小展开长度
    int ret = 0;

    // 枚举每一个section
    for (int i = 0; i != (int) p.sections.size(); ++i)
    {

        // 处理该section内的每一个row的子菜单
        for (int j = 0; j != (int) p.sections[i].rows.size(); ++j)
            p.sections[i].rows[j].expandLength = getExpandLength( panels[ p.sections[i].rows[j].childId ] );

        // 根据row的expandLength对section内的row进行排序
        sort(p.sections[i].rows.begin(), p.sections[i].rows.end(), sortByExpandLength);

        // 处理得到section的值
        p.sections[i].selfLength = (int) p.sections[i].rows.size();
        p.sections[i].expandLength = p.sections[i].selfLength; // 展开值至少为selfLength

        // 枚举每一个row，找到展开值最大的作为section的展开值
        for (int j = 0; j != (int) p.sections[i].rows.size(); ++j)
            if (p.sections[i].expandLength < j + p.sections[i].rows[j].expandLength)
                p.sections[i].expandLength = j + p.sections[i].rows[j].expandLength;

        // 计算section的?值
        p.sections[i].delta = p.sections[i].expandLength - p.sections[i].selfLength;

        // 累加panel内所有的row行数作为最小的ret
        ret += p.sections[i].selfLength;
    }

    // 根据section的?值进行排序
    sort(p.sections.begin(), p.sections.end(), sortByDelta);

    // now记录当前section的起始行数
    int now = 0;

    // 枚举每一个section，找到展开值最大的作为panel的展开值
    for (int i = 0; i != (int) p.sections.size(); ++i)
    {
        if (ret < now + p.sections[i].expandLength)
            ret = now + p.sections[i].expandLength;

        // 累加为下一个section的起始行数
        now += p.sections[i].selfLength;
    }

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
    // 读入每一个panel的情况
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
        dealPanel( panels[i] );    // 处理panel的情况
    }
    cout << getExpandLength( panels[0] ) << endl;
}