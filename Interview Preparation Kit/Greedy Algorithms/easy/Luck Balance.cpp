#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the luckBalance function below.
int luckBalance(int k, vector<vector<int>> contests) {
    // 문제
    //  - 중요한 컨테스트중 주어진 K 만큼 이기고 나머지 중요한 컨테스트에선 이기지 못한다고
    //    가정했을 때 가장 높은 luck balance 는 얼마인지 계산해보자.
    // 해결 방안
    //  - 우선 모든 luck 포인트를 합치고
    //  - (중요한 경기수 - 무조건 이겨야 하는 대회) 만큼 가장 작은값을 뺀다.
    
    int nLuckResult = 0;
    int nImportCnt = 0;
    
    vector<int> nVecImportant;
    
    nVecImportant.reserve( contests.size() );
    
    for( auto cont : contests ) {
        if( 1 == cont[1] ) {
            // 중요한 컨테스트
            nVecImportant.push_back( cont[0] );
            ++nImportCnt;
        }
        
        nLuckResult += cont[0];
    }
    
    sort( nVecImportant.begin(), nVecImportant.end() );
    
    for( int i = 0; i < nImportCnt - k; ++i ) {
        // luck 전체를 더할 때 한번 구했으므로 2배를 뺀다.
        nLuckResult -= ( nVecImportant[i] * 2 );
    }
    
    return nLuckResult;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    vector<vector<int>> contests(n);
    for (int i = 0; i < n; i++) {
        contests[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> contests[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = luckBalance(k, contests);

    fout << result << "\n";

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
