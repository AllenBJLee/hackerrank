#include <bits/stdc++.h>

using namespace std;

// Complete the commonChild function below.
int commonChild(string s1, string s2) {
    // lcs (Longest Common Subsequence) 문제
    // 관련 알고리즘을 알고 있다면 쉽게 풀 수 있다.
    
    int nLength = s1.length();
    
    // lcs 를 구할 수 있는 2차원 배열 준비
    // lcs 알고리즘은 같은 최종 0 를 만났을 때 탐색이 종료되므로
    // 0 행 0열을 0으로 채워야 한다. (종료 조건을 맞추기 위해)
    vector< vector< int > > vecData( nLength + 1, vector<int>( nLength + 1, 0 ) );
    
    // s1 을 기준으로 s2 에 일치하는 문자열이 있는지 체크한다.
    for( int i = 1; i < nLength + 1; ++i ) {
        for( int j = 1; j < nLength + 1; ++j ) {
            if( s1[i-1] == s2[j-1] ) {
                // 일치하면 배열의 i-1, j-1 값 + 1을 해준다.
                vecData[i][j] = vecData[i-1][j-1] + 1;
            } else {
                // 일치하지 않으면 [i][j-1] 과 [i-1][j] 중 큰 값을 배치한다.
                vecData[i][j] = vecData[i][j-1] > vecData[i-1][j] ? vecData[i][j-1] : vecData[i-1][j];
            }
        }
    }
    
    stack< char > sResult;
    
    // 배열의 마지막 행,열 부터 찾아가며 문자열을 찾는다.
    int nRow = vecData.size() - 1;
    int nCol = nRow;
    
    int nFoundResult = vecData[nRow][nCol];
    
    while( nCol > 0 && nRow > 0 ) {
        // 현재 선택된 요소의 값과 일치하는지 비교한다.
        // 비교 대상은 선택된 요소의 윗 Row(nRow-1) 와 좌측 Column(nCol-1) 이다
        if( nFoundResult == vecData[nRow-1][nCol] ) {
            // 윗 row 가 현재값과 일치하면 윗 row 로 이동
            --nRow;
        } else if( nFoundResult == vecData[nRow][nCol-1]) {
            // 좌측 column이 현재값과 일치하면 좌측 column으로 이동
            --nCol;
        } else {
            // 윗 row 와 좌측 column이 현재값과 일치하지 않는다면
            // 현재 문자열을 result에 insert 한다.
            sResult.push( s2[nCol-1] );
            
            // 일치하는 값을 찾지 못했으므로 row 와 col 을 -1 씩해 좌상으로 이동한다.
            nFoundResult = vecData[--nRow][--nCol];
        }
    }
    
    // 이 스택을 pop 해서 문자열에 채우면 lcs 문자열이 된다.   
    return sResult.size();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    fout << result << "\n";

    fout.close();

    return 0;
}
