#include <bits/stdc++.h>

using namespace std;

// Complete the maxMin function below.
int maxMin(int k, vector<int> arr) {
    // 문제
    //  - arr 의 요소를 k 만큼 선택해 최대값과 최소값을 구한 후
    //    최대값 - 최소값이 가장 작은 수를 구해보자
    // 해결방안
    //  - 숫자를 정렬하면 k 만큼 선택할 때 index 를 움직이며 값차이를 계산하기 편해진다.
    //    정렬 후 index 를 이동하며 값의 차이가 최소일때를 구하면 된다.
    sort( arr.begin(), arr.end() );
    
    
    int nSize = arr.size();
    int nMinResult = arr[k-1] - arr[0];
    int nCalc = 0;
    
    for( int i = k; i < nSize; ++i ) {
        nCalc = arr[i] - arr[i-k+1];
        if( nMinResult > nCalc ) {
            nMinResult = nCalc;
        }
    }
    
    return nMinResult;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int k;
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item;
        cin >> arr_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        arr[i] = arr_item;
    }

    int result = maxMin(k, arr);

    fout << result << "\n";

    fout.close();

    return 0;
}
