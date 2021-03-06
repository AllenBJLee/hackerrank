#include <bits/stdc++.h>

using namespace std;

// Complete the countingValleys function below.
int countingValleys(int n, string s) {
    int nHeight = 0;
    int nValley = 0;

    for( auto item : s ) {
        if( 0 == nHeight && 'D' == item ) {
            ++nValley;
        }

        nHeight += ('D' == item ? -1 : 1 );
    }

    return nValley;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    int result = countingValleys(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}
