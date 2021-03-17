#include <bits/stdc++.h>

using namespace std;

// Complete the repeatedString function below.
long repeatedString(string s, long n) {
    int nStrLengh = s.length();
    
    int nCharACnt = 0;
    // s 에서 a 를 다 찾는다.
    for( auto ch : s ) {
        if( 'a' == ch ) {
            ++nCharACnt;
        }
    }
    
    // 전체 문자열에서 반복되는 개수만큼 결과를 찾는다.
    long nResult = ( n / nStrLengh ) * nCharACnt;
    
    // 남은 부분에서 a 와 매칭되는 결과를 찾는다.
    for( int i = 0; i < ( n % nStrLengh ); ++i ) {
        if( 'a' == s[i] ) {
            ++nResult;
        }
    }
    
    return nResult;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    long n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    long result = repeatedString(s, n);

    fout << result << "\n";

    fout.close();

    return 0;
}
