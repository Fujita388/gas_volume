#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <typeinfo>
#include <cmath>
#include "split.h"


using namespace std;


vector<int> buf;
vector<vector<int>> array_desc(3);  // デカルト積の配列
// デカルト積を求める関数
void desc(int i, const int size, const int range_start, const int range_end) {
	buf.resize(3);
	if (i == size) {
		for (int i = 0; i < size; i++) {
			array_desc[i].push_back(buf[i]);
		}
	}
	else {
		for(int j = range_start; j <= range_end; ++j) {
			buf[i] = j;
			desc(i+1, size, range_start, range_end);
		}
	}
}


// 気相体積を測定する関数
void gas_volume(double d, double thresh) {
//	ifstream ifile("rescale01.lammpstrj");  // 読み込むファイルのパスを指定
	ifstream ifile("test.lammpstrj");  // 読み込むファイルのパスを指定
	ofstream ofile("test.dat");  // 書き出すファイルのパスを指定

	const int N = 4000;
	int num_atoms;  // 粒子数
	double L;  // ボックスサイズ
	double V = pow(d, 3.0);  // セルの体積
	int num_cell;  // セルの一次元の個数
	int index = 0;  // dumpfileの各行の通し番号
	int i_step = 0;  // step内でのインデックス 
	string str_dump;
	double pos_data[N][3];  // 1stepあたりの粒子の座標データの配列→vectorへ

	while (getline(ifile, str_dump)) {  // ifileを1行ずつstr_dumpに読み込む
		if (index == 3) {
			num_atoms = stoi(str_dump);  
		}
		if (index == 5) {
			L = stod(split(str_dump, ' ')[1]);  
			num_cell = (int)(L / d);  

			desc(0, 3, 0, num_cell-1);  // デカルト積
		}
		if (split(str_dump, ' ').size() == 5) {  // 座標データの行の場合
			i_step += 1;

			// pos_data[][]にstep内の座標データを保存
			pos_data[i_step-1][0] = stod(split(str_dump, ' ')[2]) * L;  // 元のサイズにリスケール
			pos_data[i_step-1][1] = stod(split(str_dump, ' ')[3]) * L;  
			pos_data[i_step-1][2] = stod(split(str_dump, ' ')[4]) * L;

			/////座標データから密度計算//////
			if (i_step == num_atoms) {  // 1step終わったらセルごとに密度計算し、気泡体積割合を算出
				int gas = 0;  // 閾値以下のセルを気泡としてカウント
				for (int i = 0; i < array_desc[0].size(); i++) {
					double x_cell = d * array_desc[0][i];
					double y_cell = d * array_desc[1][i];
					double z_cell = d * array_desc[2][i];
					int n = 0;  // セル内の粒子数
					for (int j = 0; j < num_atoms; j++) {
						bool X = (x_cell <= pos_data[j][0]) && (pos_data[j][0] < x_cell + d);  
						bool Y = (y_cell <= pos_data[j][1]) && (pos_data[j][1] < y_cell + d);
						bool Z = (z_cell <= pos_data[j][2]) && (pos_data[j][2] < z_cell + d);
						if (X && Y && Z) {
							n += 1;
						}
					}
					double rho = n / V;  // セルの密度
//					ofile << rho << '\n';
					if (rho <= thresh) {
						gas += 1;
					}
				}
				ofile << ((double)(gas)/(double)(pow(num_cell, 3))) << '\n';  // 気泡/全体
				i_step = 0;  // i_stepを初期化
			}
		}
		index += 1;
	}
}


int main() {
//	gas_volume(1.4875, 0.1);
	gas_volume(1.7, 0.1);
	return 0;
}
