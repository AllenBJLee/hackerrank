#include <bits/stdc++.h>

using namespace std;

struct Node {
    int nValue { 0 };
    Node* pLeft = nullptr;
    Node* pRight = nullptr;
};

void searchTree( Node* pNode, vector<int>& vResult ) {
    if( nullptr == pNode ) {
        return ;
    }
    
    searchTree( pNode->pLeft, vResult );
    vResult.push_back( pNode->nValue );
    searchTree( pNode->pRight, vResult );
}

void swapNode( Node* pNode, int nDepth, int k ) {
    if( nullptr == pNode ) {
        return ;
    }
    
    if( nDepth >= k && 0 == nDepth % k ) {
        Node* pTemp = pNode->pLeft;
        
        pNode->pLeft = pNode->pRight;
        pNode->pRight = pTemp;
    }
    
    swapNode( pNode->pLeft, nDepth + 1, k );
    swapNode( pNode->pRight, nDepth + 1, k );
}

void eraseTree( Node* pNode ) {
    if( nullptr == pNode ) {
        return ;
    }
    
    eraseTree( pNode->pLeft );
    eraseTree( pNode->pRight );
    
    delete pNode;
    pNode = nullptr;
}

/*
 * Complete the swapNodes function below.
 */
vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {
    /*
     * Write your code here.
     */
    
    Node* pRoot = new Node;
    Node* pCurrent = pRoot;
    
    pRoot->nValue = 1;
    
    queue< Node* > qTree;
    
    qTree.push( pRoot );
    
    // tree 를 구성한다.    
    for( auto const& items : indexes ) {
        pCurrent = qTree.front();
        
        qTree.pop();
        
        if( -1 != items[0] ) {
            pCurrent->pLeft = new Node;
            pCurrent->pLeft->nValue = items[0];
            
            qTree.push( pCurrent->pLeft );
        }
        
        if( -1 != items[1] ) {
            pCurrent->pRight = new Node;
            pCurrent->pRight->nValue = items[1];
            
            qTree.push( pCurrent->pRight );
        }
    }
    
    vector< vector<int> > vResult;
    
    // 쿼리에서 k 를 꺼내 swap 하고 결과를 저장한다.
    for( const auto& k : queries ) {
        swapNode(pRoot, 1, k);
        
        vector<int> vSubResult;
        searchTree(pRoot, vSubResult);
        
        vResult.push_back( vSubResult );
    }
    
    // erase all tree
    eraseTree( pRoot );
    
    return vResult;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> indexes(n);
    for (int indexes_row_itr = 0; indexes_row_itr < n; indexes_row_itr++) {
        indexes[indexes_row_itr].resize(2);

        for (int indexes_column_itr = 0; indexes_column_itr < 2; indexes_column_itr++) {
            cin >> indexes[indexes_row_itr][indexes_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int queries_count;
    cin >> queries_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(queries_count);

    for (int queries_itr = 0; queries_itr < queries_count; queries_itr++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[queries_itr] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (int result_row_itr = 0; result_row_itr < result.size(); result_row_itr++) {
        for (int result_column_itr = 0; result_column_itr < result[result_row_itr].size(); result_column_itr++) {
            fout << result[result_row_itr][result_column_itr];

            if (result_column_itr != result[result_row_itr].size() - 1) {
                fout << " ";
            }
        }

        if (result_row_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
