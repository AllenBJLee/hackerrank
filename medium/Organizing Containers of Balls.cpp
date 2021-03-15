#include <bits/stdc++.h>

using namespace std;

// Complete the organizingContainers function below.
string organizingContainers(vector<vector<int>> container) {
    int nRows = container.size();
    
    int nRowSum = 0;
    int nColSum = 0;
    
    vector< int > nVecRow, nVecCol;
    
    nVecRow.reserve( nRows );
    nVecCol.reserve( nRows );
    
    for( int nRow = 0; nRow < nRows; ++nRow ) {
        nRowSum = 0;
        nColSum = 0;

        // 각 컨테이너에 담긴 공의 개수와 type 별 공의 개수를 계산한다.
        for( int j = 0; j < nRows; ++j ) {
            nRowSum += container[nRow][j];
            nColSum += container[j][nRow];
        }
        
        nVecRow.push_back( nRowSum );
        nVecCol.push_back( nColSum );
    }
    
    // 소트하면 각 컨테이너에 타입별 공이 담기게 된다.
    sort( nVecRow.begin(), nVecRow.end() );
    sort( nVecCol.begin(), nVecCol.end() );
    
    // 소트한 값이 일치하지 않으면 실패
    for( int nRow = 0; nRow < nRows; ++nRow ) {
        if( nVecRow[nRow] != nVecCol[nRow] ) {
            return "Impossible";
        }
    }

    return "Possible";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<vector<int>> container(n);
        for (int i = 0; i < n; i++) {
            container[i].resize(n);

            for (int j = 0; j < n; j++) {
                cin >> container[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        string result = organizingContainers(container);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
