#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int cnt, arr_cnt, k, x;
    int res = 999999;
    vector<int> tmp_arr;
    int tmp_num, cur_min_cnt = 0;
    int cur_min_num;
    set<int> st;
    while (cin >> cnt) { // 注意 while 处理多个 case
        while (cnt--) {
            cin >> arr_cnt;
            cin >> k;
            cin >> x;
            int n = arr_cnt;
            while (arr_cnt--) {
                cin >> tmp_num;
                tmp_arr.push_back(tmp_num);
                if (tmp_num <= n) {
                    st.insert(tmp_num);
                }
            }
            for (int i = 1; i < (int)st.size(); i++) {
                if (st.count(i) == 0) {
                    cur_min_cnt = i;
                    break;
                }
            }
            if (cur_min_cnt == 0)
                cur_min_cnt = st.size();
            cur_min_num = k * cur_min_cnt;
            cout << "cur_min_cnt:" << cur_min_cnt << endl;
            cout << "all cost" << cur_min_num << endl;
            res = min(res, cur_min_num);
            for (int i = 0; i < tmp_arr.size(); i++) {
                if (tmp_arr[i] < cur_min_cnt) {
                    cur_min_cnt = tmp_arr[i];
                    cur_min_num = k * cur_min_cnt + x * (i + 1);
                    cout << "rm cost aaa" << cur_min_num << endl;
                    res = min(res, cur_min_num);
                } else {
                    cur_min_num = k * cur_min_cnt + x * (i + 1);
                    cout << "rm cost bbb" << cur_min_num << endl;
                    res = min(res, cur_min_num);
                }
            }
            cout << res << endl;
        }
    }
}
// 64 位输出请用 printf("%lld")