#include <iostream>
#include <fstream> //load input file and create output file
#include <string>
#include <vector> //C++ vector is needed for appending items
#include <algorithm> //sort the final result

using namespace std;

int main(int argc, char *argv[])
{
    int buffer;
    fstream fin;
    fstream fout;

    fin.open(argv[1], fstream::in);

    int n, chords_number; //number of points and chords
    
    fin >> buffer;

    n = buffer;

    chords_number = n/2;

    vector<int> target(n, 0);

    for(int i = 0; i < chords_number ; i++)
    {
        fin >> buffer;
	int start = buffer;

        fin >> buffer;
        
	int end = buffer;
        target[start] = end;
        target[end] = start;
    }

    
    vector<vector <int>> M; // Store the number of chords
    vector<vector <vector <int> > > table; // Store the chords of MPS problem 

    for(int i = 1 ; i <= n ; i++)
    {
	
	vector <int> row(i, 0);
	M.push_back(row);
	
	vector <int> emptyvec;
	vector <vector <int>> row_table(i, emptyvec);
	table.push_back(row_table);
    }

    M[0][0] = 0;

    for(int i = 1 ; i < n ; i++)
    {	
	int *ref;
    	ref = &M[0][0];	
	M[i][i] = *ref;
    }

    for(int len = 1 ; len < n ; len++)
    {
        for(int i = 0 ; i < n - len ; i++)
        {
            int j = i + len;
	    int k = target[j];
	    int *M_ref; // Store entries of same M-values by referencing
	    vector<int> *table_ref;

            if(k < i || k > j)
            {
		if(M[j - 1][i] >= M[j][i + 1])
		{
		    M_ref = &M[j - 1][i];
		    M[j][i] = *M_ref;

		    table_ref = &table[j - 1][i];
		    table[j][i] = *table_ref;
		}
		else
		{
		    M_ref  = &M[j][i + 1];
		    M[j][i] = *M_ref;

		    table_ref = &table[j][i + 1];
		    table[j][i] = *table_ref;
		}
            }    
	    else if(i < k && k < j)
            {    
		if((M[k - 1][i] + M[j][k] >= M[j - 1][i]) && (M[k - 1][i] + M[j][k] >= M[j][i + 1]))
		{
		    M[j][i] = M[k - 1][i] + M[j][k];
		    
		    if(M[k - 1][i] != 0)
		    	table[j][i].insert(table[j][i].end(), table[k - 1][i].begin(), table[k - 1][i].end());
		
		    if(M[j][k] != 0)
		    	table[j][i].insert(table[j][i].end(), table[j][k].begin(), table[j][k].end());
		    

		}
		else if(M[j - 1][i] > M[k - 1][i] + M[j][k])
		{
		    M_ref = &M[j - 1][i];
		    M[j][i] = *M_ref;

		    table_ref = &table[j - 1][i];
		    table[j][i] = *table_ref;

		}
		else if(M[j][i + 1] > M[k - 1][i] + M[j][k])
		{
		    M_ref = &M[j][i + 1];
		    M[j][i] = *M_ref;

		    table_ref = &table[j][i + 1];
		    table[j][i] = *table_ref;		    
		}
		

            }
	    else if(k == i)
            {
		M[j][i] = M[j - 1][i] + 1;
		table[j][i] = {i};
		
		
		if(M[j - 1][i] != 0)
		    table[j][i].insert(table[j][i].end(), table[j - 1][i].begin(), table[j - 1][i].end());	    
	    }
                
            //Fill M(i, j), then find M(0, n - 1)
        }
    }

    
    sort(table[n - 1][0].begin(), table[n - 1][0].end());

    fout.open(argv[2], fstream::out);

    fout << M[n - 1][0] << "\n";
    
    for(int i = 0 ; i < table[n - 1][0].size() ; i++)
        fout << table[n - 1][0][i] << " " << target[table[n - 1][0][i]] << "\n"; 

    fin.close();
    fout.close();

    return 0;
}

