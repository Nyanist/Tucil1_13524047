#include <bits/stdc++.h>
using namespace std;
#define ll long long


string mainString = "", alphabetKey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
set<char> color;

ll n = 0, m = 0;
// ll iter[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main(){
	ifstream fin("input.txt");
	string temp;
	while(getline(fin, temp)){
		if(temp.empty()) break;
		else mainString.append(temp);
		n++;
		if (m == 0) m = temp.size();
		else if (m != temp.size()){
			cout << "Input invalid. Panjang setiap baris harus sama." << '\n';
			ofstream fout("output.txt");
			for(int i=0; i<n; i++) fout << "" << '\n';
			fout.close();
			return 0;
		}
		for (int i = 0; i < m; i++){
			int location = alphabetKey.find(temp[i]);
			if (location == string::npos){
				cout << "Input invalid. Karakter tidak dikenali. List karakter valid: ";
				for(int i=0; i<alphabetKey.size(); i++) cout << alphabetKey[i] << ' ';
				cout << '\n';
				ofstream fout("output.txt");
				for(int i=0; i<n; i++) fout << "" << '\n';
				fout.close();
				return 0;
			}
			else color.insert(temp[i]);
		}
	}
		
	ll colorNum = color.size();
	string cmpr = "", ans = "";

	for (int i=0; i<n; i++){
		cmpr.append(i, '_');
		cmpr.append(1, '#');
		cmpr.append(m-i, '_');
	}
	bool valid = false;
	ll iter = 0;

	time_t startTime, endTime;
	time(&startTime);

    do {
		set<char> unusedColor = color;
		valid = true;
		iter++;
		// iter %= 1000000;

		/**
		 * 0*m ... 0*m+m-1
		 * 1*m ... 1*m+m-1
		 * ...
		 * n*m ... n*m+m-1,
		 * 
		 * i*m ... i*m+j
		 * 
		 * i*m ke bawah, j ke samping (offset)
		 * cek i*m+j dengan i beda, m sama (col)
		 * cek i*m+j dengan i sama, m beda (row)
		 * cek i*m+j dengan i beda 1, m beda 1 (adj)
		 * 
		 */

		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if (cmpr[i*m+j] == '#'){
					
					// Warna sama?
					if (unusedColor.find(mainString[i*m+j]) == unusedColor.end()){
						valid = false;
						break;
					}
					unusedColor.erase(mainString[i*m+j]);

					// Satu row or col?
					for(int k=0; k<n; k++){
						if (k != i && cmpr[k*m+j] == '#'){
							valid = false;
							break;
						}
					}
					for(int k=0; k<m; k++){
						if (k != j && cmpr[i*m+k] == '#'){
							valid = false;
							break;
						}
					}

					// Adjacent?
					if (((i-1)*m + (j-1) >= 0 && cmpr[(i-1)*m + (j-1)] == '#') || ((i-1)*m + (j+1) >= 0 && cmpr[(i-1)*m + (j+1)] == '#')){
						valid = false;
						break;
					}
				}
			}
			if (!valid) break;
		}

		if (!unusedColor.empty()) valid = false;

		if (iter % 1000000 == 0 || valid){
			if (!valid) cout << "Melakukan iterasi..." << '\n';
			else cout << "Solusi valid ditemukan!" << '\n';
			for(int i=0; i<n; i++){
				for(int j=0; j<m; j++){
					if (cmpr[i*m+j] == '#') cout << cmpr[i*m+j];
					else cout << mainString[i*m+j];
				}
				cout << '\n';
			}
			cout << '\n';
			if (valid) ans.append(cmpr);
		}

	} while (next_permutation(cmpr.begin(), cmpr.end()) && !valid);

	time(&endTime);

	if (!valid) cout << "Tidak menemukan solusi valid." << '\n';
	

	cout << "Waktu pencarian: " << difftime(endTime, startTime) << " detik" << '\n';
	cout << "Banyak kasus yang ditinjau: " << iter << '\n';
	cout << "Menyimpan jawaban..." << '\n';
	ofstream fout("output.txt");
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if (ans[i*m+j] == '#') fout << ans[i*m+j];
			else fout << mainString[i*m+j];
		}
		fout << '\n';
	}
	fout << "Waktu pencarian: " << difftime(endTime, startTime) << " detik" << '\n';
	fout << "Banyak kasus yang ditinjau: " << iter << '\n';
	fin.close();
	fout.close();
}