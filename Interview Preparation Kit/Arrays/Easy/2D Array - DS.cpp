#include <bits/stdc++.h>

using namespace std;

// Complete the hourglassSum function below.
int hourglassSum(vector<vector<int>> arr) {
    // 문제
    //  6x6 array 가 주어지고
    //  모래시계 모양으로 요소를 더해 가장 큰 값을 찾는 문제
    // 해결
    //  모래시계 모양으로 값을 더해서 그냥 큰 값을 찾으면 된다.

    int nResult = -9 * 7;   // 조건으로 주어진 가장 작은 값
    
    int nSum = 0;
    for( int nIndex = 0; nIndex < 4; ++nIndex ) {
        
        for( int j = 0; j < 4; ++j ) {
            nSum = arr[nIndex+1][j+1];

            for( int k = 0; k < 3; ++k ) {
                nSum += arr[nIndex][j+k];
                nSum += arr[nIndex+2][j+k];
            }
            
            if( nResult < nSum ) {
                nResult = nSum;
            }
        }
    }

    return nResult;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> arr(6);
    for (int i = 0; i < 6; i++) {
        arr[i].resize(6);

        for (int j = 0; j < 6; j++) {
            cin >> arr[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = hourglassSum(arr);

    fout << result << "\n";

    fout.close();

    return 0;
}
