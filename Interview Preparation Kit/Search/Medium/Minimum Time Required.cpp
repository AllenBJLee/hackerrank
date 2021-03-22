#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minTime function below.
long minTime(vector<long> machines, long goal) {
    sort( machines.begin(), machines.end() );
    
    long lSum = 0;
    
    int nMachineSize = machines.size();

    // binary search 를 위해 시작값과 최대값을 설정한다.
    long lStartDay = 0;
    long lEndDay = goal * machines[nMachineSize-1];
    long lDay = 0;
    
    long lResult = 0;
    
    // 시작값이 최대값보다 커지면 탐색을 중지한다.
    while( lStartDay < lEndDay ) {
        lSum = 0;
        
        // 시작값과 최대값의 중앙값을 기준으로 검색한다.
        lDay = (lStartDay + lEndDay) / 2;
        
        for( long i = 0; i < nMachineSize; ++i ) {
            lSum += ( lDay / machines[i] );
            if( lSum > goal )
                break;
        }
        
        // 합이 goal 보다 작으면 시작값 위치를 중앙값 +1로 이동한다.
        if( lSum < goal ) {
            // match day 를 찾으면 lStartDay 와 lEndDay 가 같은값이 되므로
            // +1 해서 찾지 않으면 무한루프를 돌게 된다.
            lStartDay = lDay + 1;
        } else {
            lResult = lDay;
            lEndDay = lDay;
        }
    };
    
    return lResult;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nGoal_temp;
    getline(cin, nGoal_temp);

    vector<string> nGoal = split_string(nGoal_temp);

    int n = stoi(nGoal[0]);

    long goal = stol(nGoal[1]);

    string machines_temp_temp;
    getline(cin, machines_temp_temp);

    vector<string> machines_temp = split_string(machines_temp_temp);

    vector<long> machines(n);

    for (int i = 0; i < n; i++) {
        long machines_item = stol(machines_temp[i]);

        machines[i] = machines_item;
    }

    long ans = minTime(machines, goal);

    fout << ans << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
