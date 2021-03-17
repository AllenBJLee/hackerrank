#include <bits/stdc++.h>

using namespace std;

//#define RESULT_MINE
#define RESULT_DISCUSSIONS


#if defined( RESULT_DISCUSSIONS )
struct CHAR_DATA {
    char ch;
    int nRepeated;
};

// Complete the substrCount function below.
long substrCount(int n, string s) {
    // 알고리즘
    // 1. 연속된 문자열이 반복될 경우 이를 special substring 으로 계산하는 공식
    // 원문
    // For a string with n characters, we can make a total of n*(n+1)/2 substrings.
    // Note substrings keep the same order and don't skip characters.
    // For instance, aaaa will make a, aa, aa, aa, aaa, aaa and aaaa
    // This is because, for a string of size n we can make n - 1 substrings of size 2 and n - 2 substrings of size 3 and so on.
    // This can be generalized as n-(k-1) where k is the length of the substring.
    // So total number of substrings (of all lenghts) is then n-1 + n-2 + ... + n - (k-1) + ... + n - (n-1).
    // This when written in reverse is same as 1 + 2 + ... + n-2 + n-1 + n.
    // The sum of an arithmetic sequence is = n*(first+last)/2. Therefore, the sum of above sequence is n*(1+n)/2

    // 번역기
    // n 개의 문자가있는 문자열의 경우 총 n * (n + 1) / 2 개의 하위 문자열을 만들 수 있습니다.
    // 하위 문자열은 동일한 순서를 유지하고 문자를 건너 뛰지 않습니다.
    // 예를 들어, aaaa는 a, aa, aa, aa, aaa, aaa 및 aaaa를 만듭니다.
    // 이것은 크기 n의 문자열에 대해 크기 2의 n-1 개의 하위 문자열과 크기 3의 n-2 개의 하위 문자열을 만들 수 있기 때문입니다.
    // 이것은 n- (k-1)로 일반화 할 수 있습니다.
    // 여기서 k는 부분 문자열의 길이입니다. 따라서 (모든 길이의) 총 부분 문자열 수는 n-1 + n-2 + ... + n-(k-1) + ... + n-(n-1)입니다.
    // 반대로 쓸 때 이것은 1 + 2 + ... + n-2 + n-1 + n과 같습니다.
    // 산술 시퀀스의 합은 = n * (첫 번째 + 마지막) / 2입니다. 따라서 위 시퀀스의 합은 n * (1 + n) / 2

    // 2. 문자열 중앙값만 다른 연속되는 문자열을 구하는 방법
    // 문자열을 순서대로 반복되는 회수를 기록해 나열한 후 Current 와 Current + 2가 같은 문자고 Current + 1 이 다른 문자이며,
    // Current + 1 이 단 1개의 문자만 소유할 경우를 체크한다.
    // 그리고 Current 와 Current + 2 중 문자열 개수가 작은 쪽의 개수만 카운팅하면 된다.
    // ex) "aabaaa" 가 있을 때
    //  [ {"a", 2}, {"b", 1}, {"a", 3} ] 으로 정리된다.
    //  이때 찾을 수 있는 결과는 "aabaa", "aba" 가 되므로 Current( {"a", 2} )의 2개를 추가해주면 된다.
    
    vector<CHAR_DATA> vecData;

    char chCurrent = s[0];
    int nSize = s.size();

    vecData.push_back( { chCurrent, 1 } );

    // 문자열을 순회하면서 반복되는 문자열을 순서대로 정리한다.
    for( int nIndex = 1; nIndex < nSize; ++nIndex ) {
        if( chCurrent == s[nIndex] ) {
            ++(vecData[vecData.size()-1].nRepeated);
        } else {
            chCurrent = s[nIndex];
            vecData.push_back( { chCurrent, 1 } );
        }
    }

    long lResult = 0;
    
    nSize = vecData.size();

    for( int nIndex = 0; nIndex < nSize; ++nIndex ) {
        // 알고리즘 1에 해당하는 값을 더해준다
        lResult += ( vecData[nIndex].nRepeated * ( 1 + vecData[nIndex].nRepeated ) / 2 );

        if( nIndex + 2 < nSize ) {
            // 알고리즘 2에 해당하는 값을 추가로 찾아 더해준다
            if( vecData[nIndex].ch == vecData[nIndex+2].ch &&       // Current 와 Current + 2 의 문자가 같고
                1 == vecData[nIndex+1].nRepeated ) {    // 중간에 낀 문자의 개수가 1개일 때
                lResult += ( vecData[nIndex].nRepeated < vecData[nIndex+2].nRepeated ? vecData[nIndex].nRepeated : vecData[nIndex+2].nRepeated );
            }
        }
    }

    return lResult;    
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    long result = substrCount(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}

// 아래 풀이는 문제를 보고 문제에서 제시한대로 알고리즘을 작성한 결과
// 다 통과는 하지만 뭔가 더 산뜻한 (시간복잡도 적게 먹는) 방법이 있을 것 같아
// Discussion 을 둘러보고 새로 만들어 보기로 결정

#elif defined( RESULT_MINE )
enum CompResult {
    CompSucceed = 0,
    CompFailedButNeedMore,
    CompDoNotContinue
};

CompResult comp( const string& s ) {
    int nLen = s.size();
    
    if( 1 == nLen ) {
        return CompSucceed;
    }
    
    map< char, int > mapComp;
    map< char, int >::iterator it;
    
    for( int nIndex = 0; nIndex < s.size(); ++nIndex ) {
        it = mapComp.find( s[nIndex] );
        
        if( it == mapComp.end() ) {
            // first find
            if( 2 == mapComp.size() ) {
                return CompDoNotContinue;
            }
            
            mapComp.insert( pair< char, int >( s[nIndex], 1 ) );
        }
        else {
            ++(it->second);
        }
    }
    
    // 조사 결과 1개의 문자로만 이루어지면 성공
    if( 1 == mapComp.size() ) {
        return CompSucceed;
    }
    
    it = ++(mapComp.begin());    
    if( 1 < mapComp.begin()->second && 1 < it->second ) {
        // 두개 문자 모두 2개 이상일 경우 더이상 비교하지 않는다.
        return CompDoNotContinue;
    }
    
    if( 0 != nLen % 2 ) {
        // 문자열이 홀수개인 경우
        
        if( 1 == mapComp.find( s[0] )->second ) {
            // 시작 문자가 1개고 반복된 문자가 2개면 더이상 비교할 필요가 없다.
            return CompDoNotContinue;
        }
        
        // 미들에 다른 문자열이 존재하면 우선 성공        
        if( s[0] != s[nLen/2] ) {
            return CompSucceed;
        }
    }
    
    // 모든 조건에 만족하지 않으면 계속 비교해본다.
    return CompFailedButNeedMore;
}


// Complete the substrCount function below.
long substrCount(int n, string s) {
    int nSize = s.size();
    
    long lResult = 0;
    
    CompResult enCompResult = CompFailedButNeedMore;
    
    string strComp;
    
    strComp.reserve( s.size() + 1 );
    
    for( int nIndex = 0; nIndex < nSize; ++nIndex ) {
        for( int j = 0; j < nSize - nIndex; ++j ) {
            strComp = s.substr( nIndex, j + 1 );
            
            enCompResult = comp( strComp );
            
            if( CompSucceed == enCompResult ) {
                ++lResult;
            } else if( CompDoNotContinue == enCompResult ) {
                break;
            }
        }
    }
    
    return lResult;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    long result = substrCount(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}

#endif