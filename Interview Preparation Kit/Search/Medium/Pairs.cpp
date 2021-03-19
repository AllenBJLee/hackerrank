#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the pairs function below.
int pairs(int k, vector<int> arr) {
    // 조건
    //  - arr 안에 있어있는 값을 t 로 정의
    //    - t 는 모두 다른 값이다.
    //    - arr 안에 들어있는 타겟의 값은 0 < t < 2^31 - 1 이다. (signed int 범위 안에 있다)
    
    vector< bool > vecSorted( pow( 2, 31 ), false );
    
    // arr 를 돌면서 있는 값을 true 로 체크해준다.
    for( const auto& t : arr ) {
        vecSorted[t] = true;
    }
    
    int nResult = 0;
    
    // k 값과 t 값을 더한 값이 배열에 존재한다면 성공
    for( const auto& t : arr ) {
        if( true == vecSorted[k + t] ) {
            ++nResult;
        }
    }
    
    return nResult;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int result = pairs(k, arr);

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
