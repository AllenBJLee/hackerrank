#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the whatFlavors function below.
void whatFlavors(vector<int> cost, int money) {
    // 문제
    //  - 소지한 돈과 아이스크림 가격이 주어지며
    //  - 두명의 친구가 아이스크림을 살 수 있는 최적의 값을 찾아보자.
    //  - 단, 최적의 아이스크림 결과는 항상 유니크함을 보장한다.

    // 해결
    //  - 문제 이름이 Hash Table 이기 때문에 간단하게 map 으로 해결 가능
    //  - map key:cost, value:vector<index> 로 지정해서
    //  - 아이스크림 가격을 순해해 hash table 을 만들고
    //  - hash table key 값을 순차적으로 검색하며 최적의 값을 찾아낸다.
    
    // first - price, second - index array
    map< int, vector<int> > mapData;
    
    map< int, vector<int> >::iterator it;
    
    int nSize = cost.size();
    
    // hash table 을 구축한다.
    for( int nIndex = 0; nIndex < nSize; ++nIndex ) {
        it = mapData.find( cost[nIndex] );
        
        if( it == mapData.end() ) {
            // 새로운 아이템
            mapData.insert( pair< int, vector<int> >( cost[nIndex], vector<int>( 1, nIndex ) ) );
        } else {
            // 이미 존재하는 아이템
            it->second.push_back( nIndex );
        }
    }
    
    int nRemainCost = 0;
    
    map< int, vector<int> >::iterator itFind;
    
    vector<int> vecResult( 2, 0 );
    
    // 최적의 값을 찾아본다.
    for( it = mapData.begin(); it != mapData.end(); ++it ) {
        nRemainCost = money - it->first;
        
        itFind = mapData.find( nRemainCost );
        
        if( itFind == mapData.end() ) {
            // 0 로 일치하는 아이템이 없다.
        } else if( itFind == it && 2 == itFind->second.size() ) {
            // 결과는 항상 유니크함을 보장하기 때문에 동일한 값을 가진 가격이 2개가 존재할 수 있다.

            // 일치하는 값을 찾았으나 중복 아이템이다
            // second 개수가 두개라면 반환 가능
            vecResult[0] = itFind->second[0]+1;
            vecResult[1] = itFind->second[1]+1;
            break;
        } else {
            vecResult[0] = it->second[0]+1;
            vecResult[1] = itFind->second[0]+1;
            break;
        }
    }
    
    sort( vecResult.begin(), vecResult.end() );
    
    printf( "%d %d\n", vecResult[0], vecResult[1] );
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int money;
        cin >> money;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string cost_temp_temp;
        getline(cin, cost_temp_temp);

        vector<string> cost_temp = split_string(cost_temp_temp);

        vector<int> cost(n);

        for (int i = 0; i < n; i++) {
            int cost_item = stoi(cost_temp[i]);

            cost[i] = cost_item;
        }

        whatFlavors(cost, money);
    }

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
