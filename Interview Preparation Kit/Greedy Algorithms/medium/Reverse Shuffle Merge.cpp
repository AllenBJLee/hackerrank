#include <bits/stdc++.h>

using namespace std;

// Complete the reverseShuffleMerge function below.
string reverseShuffleMerge(string s) {
    // 문제 설명
    //  - 문자열 A 가 주어지고 A1 = reverse(A), A2 = shuffle(A) 인 상황
    //  - S == merge( A1, A2 ) 이며, 조건을 만족하는 S 의 사전적 순서 최소값을 찾는 문제
    // 해결 방안
    //  - 문제 샘플을 보면 A2 는 merge 될 때도 shuffle 을 하는 것으로 파악된다.
    //  - 때문에 reverse A1 을 찾아야 한다.
    //  - 문자열 A 가 두개이기 때문에 모든 char 는 A 요소의 *2 개 만큼 존재하게 된다.

    //  - 문자열은 모두 소문자이므로
    //  - 26개 배열을 만들고 char 를 찾아 0-a, 1-b, ... 25-z 에 맞춰 개수를 확인한다.
    
    
    // 1차 생각 : reverse는 항상 연결된 문자라고 이해했을 때 풀이
    //  - A 를 구성하는 char 모두를 만족할 경우 원하는 문자열이 된다.
    //  - 뒤에서부터 순차적으로 Elements Vector 의 조건을 만족할때만 string 에 추가해
    //  - 모든 조건에 만족하는지 확인해본다.
// #define RESULT_1

#define RESULT_2    

#if defined( RESULT_1 )
    string strResult;
    
    vector<int> nVecElements( 26, 0 );
    vector<int> nVecComp( 26, 0 );

    // 요소를 찾는다.
    for( const auto& c : s ) {
        ++nVecElements[c-'a'];
    }
    
    // 모든 요소는 1/2 개 만큼 존재해야 A 를 만족하므로 개수를 1/2로 모두 나눈다.
    for( auto& i : nVecElements ) {
        i = i / 2;
    }
    
    int nStrALength = s.size() / 2;
    
    string strCmp;
        
    int arrComp[26];
    int nIdx = 0;
    char chNow = '\0';
    
    bool bMatched = false;
    
    // reverse 된 문자열을 찾아야 하기 때문에
    // 마지막 문자에서부터 비교해본다.
    for( int i = s.size() - 1; i  >= nStrALength - 1; --i ) {
        nVecComp = nVecElements;
        bMatched = true;
        
        strCmp.clear();
        strCmp.reserve( nStrALength );
        
        // 마지막 문자열에서 하나씩 선택
        for( nIdx = 0; nIdx < nStrALength; ++nIdx ) {
            chNow = s[i - nIdx];
            strCmp.push_back( chNow );
            if( 0 > --nVecComp[chNow-'a'] ) {
                break;
            }
        }
        
        // 만들어진 문자열이 조건에 일치하는지 파악한다.
        for( const auto& i : nVecComp ) {
            if( 0 != i ) {
                bMatched = false;
                break;
            }
        }
        
        if( false == bMatched ) {
            // 찾아낸 문자열이 조건에 일치하지 않으므로 다시 찾는다.
            continue;
        }
        else {
            if( 0 == strResult.length() || strResult > strCmp ) {
                strResult = strCmp;
                
                //printf( "%s\n", strResult.c_str() );
            }
        }
    }

    return strResult;
#elif defined(RESULT_2)

    // 문제풀이 2
    // 결국 reverse 된 문자열 사이 사이에 shuffle 이 일어난 문자열이 끼어들기 때문에
    // 그때 그때 조건에 맞는 최상의 결과를 조합해 내야 한다.
    
    // 1. element 조건에 만족하는지 비교하며 데이터를 추가/삭제해볼 stack 이 필요하다.
    // 2. element 를 추가할 수 있는지 비교하기 위한 Remain/Skip 이 필요하다.
    //  - remain 은 Reverse(A), Skip은 Shuffle(A) 에 각각 매칭된다고 판단.
    // 3. 문자열을 뒤에서부터 체크하며 다음 조건으로 비교해본다.
    //  - 이미 선택조건에 의해 Remain 에 해당하는 문자열이 존재하는가?
    //  - Remain 에 해당하는 문자열이 현재 선택된 조건의 문자열보다 큰가?
    //  - Remain 에 더 추가할 수 있는가?
    //  - 위 세개를 다 만족하며 Skip 할 수 있는가?
    // 4. 3번에 해당하면 stack 에서 pop 해 skip 한다.
    //  - 결국 그때 그때 가장 최적의 조건에 해당하는 문자열을 찾아 stack 에 넣어둔다.

    vector<int> nVecRemains( 26, 0 );
    vector<int> nVecSkip( 26, 0 );

    // 요소를 찾는다.
    for( const auto& c : s ) {
        ++nVecRemains[c-'a'];
    }
    
    // 모든 요소는 1/2 개 만큼 존재해야 A 를 만족하므로 개수를 1/2로 모두 나눈다.
    for( auto& i : nVecRemains ) {
        i = i / 2;
    }
    
    // 문자열 Remain 과 Skip 은 같은 Char를 보유해야 한다.
    nVecSkip = nVecRemains;
    
    // 문자를 넣고 뺄 스택 하나를 준비한다.
    stack<char> stChar;
    
    for( int nIdx = s.size() - 1; nIdx >= 0; --nIdx ) {
        
        // stack 이 비어있지 않다면 아래 조건을 만족할 때 까지 현재 선택한 문자와 비교해
        // skip 할지 아닐지 결정한다.
        while( false == stChar.empty() &&  // 스택에 이미 선택된 문자가 존재하고
            stChar.top() > s[nIdx] &&   // 현재 선택한 문자가 기존에 선택한 문자보다 앞서며
            nVecRemains[s[nIdx]-'a'] > 0 && // 아직 remain 할 문자열이 남아있고
            nVecSkip[stChar.top() - 'a'] > 0 // 기존에 선택한 문자를 아직 스킵할 수 있다면
        ) {
            // stack 에 기록했던 문자는 skip 조건에 해당한다.
            ++nVecRemains[stChar.top() - 'a'];
            --nVecSkip[stChar.top() - 'a'];
            stChar.pop();
        }
        
        // 위 while 문을 통과한 현재 문자열을 stack 에 추가할지 skip 할지 결정한다.
        if( nVecRemains[ s[nIdx] -'a' ] > 0 ) {
            stChar.push(s[nIdx]);
            --nVecRemains[s[nIdx] - 'a'];
        } else {
            --nVecSkip[s[nIdx] - 'a'];
        }
    }
    
    int nResultLength = s.size()/2;
    string strResult( nResultLength, '\0' );
    
    for( int nIdx = nResultLength - 1; nIdx >= 0; --nIdx ) {
        strResult[nIdx] = stChar.top();
        stChar.pop();
    }
    
    return strResult;
#endif
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = reverseShuffleMerge(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
