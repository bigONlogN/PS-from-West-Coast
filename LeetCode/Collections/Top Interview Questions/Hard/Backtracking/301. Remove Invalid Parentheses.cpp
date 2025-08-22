#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

void maxRemove(int& removeOpen, int& removeClose, const string& s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(')
            removeOpen++;
        if (s[i] == ')') {
            if (removeOpen) removeOpen--;
            else removeClose++;
        }
    }
}

void backtrack(const string& s, vector<string>& result, string& temp, int s_idx, int ropen, int rclose, int t_judge, const int& t_max) {
    int s_left = s.length() - s_idx;
    int t_left = t_max - temp.length();
    if (t_judge < 0 || t_left > s_left || t_judge > s_left || t_judge > t_left || ropen + rclose > s_left) return;
    if (s_idx == s.length()) {
        if (!rclose && !ropen) {
            result.push_back(temp);
        }
        return;
    }
    char s_cur = s[s_idx];
    bool isOpen = s_cur == '(', isClose = s_cur == ')', isNonParen = !isOpen && !isClose;
    int judge_diff;
    if (isNonParen) judge_diff = 0;
    else isOpen ? judge_diff = 1 : judge_diff = -1;

    temp.push_back(s_cur);
    backtrack(s, result, temp, s_idx + 1, ropen, rclose, t_judge + judge_diff, t_max);
    temp.pop_back();
    if (isOpen && ropen || isClose && rclose)
        if (!temp.length() || s_cur != temp[temp.length() -1]) // prevent duplicated result(successive parentheses makes duplicated result)
            backtrack(s, result, temp, s_idx + 1, isOpen ? ropen - 1 : ropen, isClose ? rclose - 1 : rclose, t_judge, t_max);
}

vector<string> removeInvalidParentheses(string s) {
    vector<string> result;
    string temp;
    int removeOpen = 0, removeClose = 0, t_max;
    maxRemove(removeOpen, removeClose, s);
    t_max = s.length() - removeOpen - removeClose;
    backtrack(s, result, temp, 0, removeOpen, removeClose, 0, t_max);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    vector<string> result = removeInvalidParentheses("))667(((()))899((");
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << '\n';
    }
    return 0;
}
