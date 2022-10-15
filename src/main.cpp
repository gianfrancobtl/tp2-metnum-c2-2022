#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>      
#include "pca.h"
#include "knn.h"
#include "eigen.h"

using namespace std; // usando espacio de nombres STD

Matrix load_csv(const std::string &path ) {
        ifstream indata;
        indata.open(path);
        string line;
        vector<double> values;
        uint rows = 0;

	// Saltear encabezados:
	getline(indata, line);
	stringstream lineStream(line);
	string cell;
	while (std::getline(lineStream, cell, ',')) { }

	// Tomar datos:
	while (std::getline(indata, line)) {
	    std::stringstream lineStream(line);
	    std::string cell;
	    while (std::getline(lineStream, cell, ',')) {
		values.push_back(std::stod(cell));
	    }
	    ++rows;
	}
	
	cout<<"load_csv - values: ";
	for(int i=0;i<50;i++)cout<<values[i]<<",";
	cout<<"... - values.size: "<<values.size()<<endl;

	return Eigen::Map
	<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>
	(values.data(), rows, values.size() / rows);
}

void save_to_file(std::string name, Vector content) {
	//preparo archivo salida para escritura
	std::ofstream archivoDeSalida;
	archivoDeSalida.setf(std::ios::fixed, std::ios::floatfield); // tipo salida
	archivoDeSalida.precision(15); // cant decimales
	archivoDeSalida.open(name);
	for (unsigned int i = 0; i < content.rows(); i++) {
		archivoDeSalida << (unsigned int) content[i] << endl;
	}
	archivoDeSalida.close();

}

int main(int argc, char** argv){

	cout << "¡Hola, mundo!" << endl;

	// argumentos
	// 0 - main
	// 1 - Train: Archivo de casos de Train
	// 2 - alpha: cantidad de componentes en PCA. 0 significa No aplicar PCA
	// 3 - k: cantidad de vecinos en KNN
	// 4 - Test: Archivo de casos de Test
	// 5 - Out: Archivo de salida (predicción sobre Test)
	if (argc != 6) {
		cout << "Error, Faltan Argumentos" << endl;
		return 1;
	}
	char* training_set = argv[1];
	int alpha = atoi(argv[2]);
	int k = atoi(argv[3]);
	char* testing_set = argv[4];
	char* out = argv[5];
	
	cout<<"main 00 training_set: "<<training_set<<" - testing_set: "<<testing_set;
	cout<<" - k: "<<k<<" - alpha: "<<alpha<<" - out: "<<out<<endl;

	Matrix temp = load_csv(training_set);

	cout<<"main 01 - temp.size: "<<temp.rows()<<","<<temp.cols()<<endl;
	cout<<"main 01 - temp.col 0: "; for(int j=0;j<50;j++) cout<<temp.coeff(j,0)<<","; cout<<"..."<<endl;
	cout<<"main 01 - temp.col 784: "; for(int j=0;j<50;j++) cout<<temp.coeff(j,784)<<","; cout<<"..."<<endl;

	KNNClassifier knn = KNNClassifier(k);
	cout<<"main 02"<<endl;
	Matrix X = temp.block(0, 1, temp.rows(), temp.cols() - 1);
	Matrix Y = temp.block(0, 0, temp.rows(), 1);
	cout<<"main 03 - X.rows: "<<X.rows()<<", X.cols: "<<X.cols();
	cout<<" - Y.rows: "<<Y.rows()<<", Y.cols: "<<Y.cols()<<endl;

	cout<<"main 03 - Y: "; for(int j=0;j<50;j++) cout<<Y.coeff(j,0)<<","; cout<<"..."<<endl;

	Matrix X_test = load_csv(testing_set);
	cout<<"main 04 - X_test.rows: "<<X_test.rows()<<", X_tests.cols: "<<X_test.cols()<<endl;
	if (alpha>0) {
		PCA pca = PCA(alpha);
		pca.fit(X);
		cout<<"main 05"<<endl;
		X = pca.transform(X);
		cout<<"main 06"<<endl;
		X_test = pca.transform(X_test);
	}

	cout<<"main 07 - X.rows: "<<X.rows()<<", X.cols: "<<X.cols();
	cout<<" - X_test.rows: "<<X_test.rows()<<", X_test.cols: "<<X_test.cols()<<endl;
	knn.fit(X, Y);
	cout<<"main 08"<<endl;
	Vector y_pred = knn.predict(X_test);

	cout<<"main 09 - y_pred: "; 
	for(int j=0;j<(50<y_pred.size()?50:y_pred.size());j++)cout<<y_pred[j]<<","; cout<<"..."<<endl;

	save_to_file(out, y_pred);
	cout << "¡Adiós, mundo!" << endl;
	return 0;
}
