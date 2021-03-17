#include <bits/stdc++.h>

using namespace std;

// Complete the makeAnagram function below.
int makeAnagram(string a, string b) {
    // 문제
    //  문자열 a,b 에서 겹치는 char 외 다른 char 를 제거한다.
    //  제거된 char 의 개수를 구해보자.

    // 해결
    //  문자열 a,b 에 들어있는 모든 문자 개수를 구하고
    //  각각의 문자 개수에서 차이나는 숫자만큼 더하면 해결된다.

    vector<int> vecA( 26, 0 ), vecB( 26, 0 );
    
    for( const auto& c : a ) {
        ++vecA[c-'a'];
    }
    
    for( const auto& c : b ) {
        ++vecB[c-'a'];
    }
    
    int nDeleted = 0;
    
    for( int i = 0; i < 26; ++i ) {
        if( vecA[i] != vecB[i] ) {
            nDeleted += abs( vecA[i] - vecB[i] );
        }
    }
    
    return nDeleted;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a;
    getline(cin, a);

    string b;
    getline(cin, b);

    int res = makeAnagram(a, b);

    fout << res << "\n";

    fout.close();

    return 0;
}
