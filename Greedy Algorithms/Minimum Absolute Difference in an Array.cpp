#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumAbsoluteDifference function below.
int minimumAbsoluteDifference(vector<int> arr) {
    // 문제
    //  - 배열의 모든 원소를 두개씩 묶어 두 숫자의 차이값중 가장 작은 값을 찾는다.
    // 풀의 의도
    //  - 두 숫자 차이가 가장 작은 경우를 찾는 것이기 때문에 배열을 정렬하고
    //  - 인덱스를 증가시키며 숫자를 뺐을 때 가장 작은값을 찾으면 해결된다.
    sort( arr.begin(), arr.end() );
    
    int nResult = 0;
    
    int nSize = arr.size();
    
    nResult = abs(arr[0] - arr[1]);
    
    for( int i = 1; i < nSize - 1; ++i ) {
        if( nResult > abs( arr[i] - arr[i+1] ) ) {
            nResult = abs( arr[i] - arr[i+1] );
        }
    }
    
    return nResult;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int result = minimumAbsoluteDifference(arr);

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
