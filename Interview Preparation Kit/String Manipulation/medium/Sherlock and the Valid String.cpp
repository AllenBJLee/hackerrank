#include <bits/stdc++.h>

using namespace std;

// Complete the isValid function below.
string isValid(string s) {
    // 문제 
    //  주어진 문자열 S 에서 단 하나의 문자만 지웠을 때
    //  모든 문자의 개수가 동일해지는지 파악해보자
    // 해결방안
    //  주어진 문자를 모두 카운팅하고
    //  문자열 개수별로 정렬한 다음
    //    문자 개수의 종류가 2개를 초과하면 무조건 실패
    //    문자 개수의 종류가 1개면 성공
    //    문자 개수가 2개인데
    //      문자 개수가 1개인 종류가 딱 1케이스만 존재하면 성공
    //      문자 개수가 연달아 이어지는 케이스면서 더 높은 개수를 소유한 케이스가 1개일때 성공
    //  나머지는 실패로 본다.
    
    vector<int> nVec(26, 0);
    
    int nMax = 0;
    
    for( const auto& ch : s ) {
        ++nVec[ch-'a'];
    }
    
    map< int, int > mapCount;
    map< int, int >::iterator it;
    
    for( const auto& i : nVec ) {
        if( 0 < i ) {
            it = mapCount.find( i );
            
            if( it != mapCount.end() ) {
                ++(it->second);
            } else {
                mapCount.insert( pair< int, int >(i, 1) );
            }
        }
    }
    
    // 모든 문자 개수가 2개를 초과하면 NO
    if( 2 < mapCount.size() ) {
        return "NO";
    } else if( 1 == mapCount.size() ) { // 1개의 종류만 있을 경우 YES
        return "YES";
    }
    
    map< int, int >::iterator itNext;
    
    it = mapCount.begin();
    
    itNext = it;
    ++itNext;
    
    // 1개의 출현 빈도를 가진 케이스가 1개면 얘만 지워주면 되므로 성공
    if( ( 1 == it->first && 1 == it->second ) ) {
        return "YES";
    }
    else if( 1 == itNext->first - it->first &&
            ( 1 == itNext->second ) ) {
        // 출현 빈도가 낮은 케이스와 높은 케이스의 차이가 1이고
        // 출현 빈도가 높은 케이스가 딱 1건일 경우만 성공
        return "YES";
    }
    
    // 나머지는 다 실패
    return "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
