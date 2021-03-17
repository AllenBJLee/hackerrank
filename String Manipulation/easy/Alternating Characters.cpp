#include <bits/stdc++.h>

using namespace std;

// Complete the alternatingCharacters function below.
int alternatingCharacters(string s) {
    // 문제
    //  A, B 로 이루어진 문자열이 주어지며, A B 가 반복되게 만들기 위해서
    //  중간에 중복된 문자를 삭제해야 한다.
    //  삭제한 문자 개수를 반환해보자.
    
    // 해결
    //  선택된 문자를 기준으로 다음 문자가 같으면 삭제, 아니면 문자를 교체해가며 비교한다.
    char chCurrent = '\0';
    int nDeleted = 0;
    
    for( const auto& ch : s ) {
        if( '\0' == chCurrent || chCurrent != ch ) {
            chCurrent = ch;
        } else {
            ++nDeleted;
        }
    }
    
    return nDeleted;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = alternatingCharacters(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
