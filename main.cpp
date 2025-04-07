#include <Eigen/Dense> // potevo utilizzare anche armadillo che ha comandi molto semplici 
#include <iostream>
#include <iomanip>

using namespace std;
using namespace Eigen;

double errore_PALU (const MatrixXd& A, const VectorXd& b, const VectorXd& x_vero ){
    VectorXd x = A.partialPivLu().solve(b); //fullPivLu è piu lento ma funziona meglio (stabilità numerica)
    double errore = ((x-x_vero).norm())/(x_vero.norm());
    return errore;
}

double errore_QR (const MatrixXd& A, const VectorXd& b, const VectorXd& x_vero ){
    VectorXd x = A.householderQr().solve(b);
    double errore = ((x-x_vero).norm())/(x_vero.norm());
    return errore;
}


//FUNZIONE PER VEDERE QUELLA CON L'ERRORE MINORE ( facoltativo)
void confronto (const MatrixXd& A, const VectorXd& b, const VectorXd& x_vero) {
    if (errore_PALU(A,b,x_vero)>errore_QR(A,b,x_vero)){
        cout<<"il valore QR è migliore"<< endl;
    }else {
        cout<<"il valore PALU è migliore"<<endl;
    }
}

void stampa (const MatrixXd& A, const VectorXd& b, const VectorXd& x_vero, const string& nome) {
    cout << "Errore PALU per " << nome << ": " << setprecision(30) << scientific << errore_PALU(A, b, x_vero) << endl;
    cout << "Errore QR   per " << nome << ": " << setprecision(30) << scientific << errore_QR(A, b, x_vero) << endl;
    cout << "Confronto per " << nome << ": ";
    confronto(A, b, x_vero);
    cout << endl;
}


int main()
{ 
    MatrixXd A(2,2); 
    A << 5.547001962252291e-01,-3.770900990025203e-02, 8.320502943378437e-01,-9.992887623566787e-01;
    VectorXd b(2);
    b << -5.169911863249772e-01, 1.672384680188350e-01;
    MatrixXd A1(2,2) ; 
    A1 << 5.547001962252291e-01,-5.540607316466765e-01, 8.320502943378437e-01,-8.324762492991313e-01;
    VectorXd b1(2);
    b1 << -6.394645785530173e-04, 4.259549612877223e-04;
    MatrixXd A2(2,2);
    A2 <<5.547001962252291e-01,-5.547001955851905e-01, 8.320502943378437e-01,-8.320502947645361e-01;
    VectorXd b2(2);
    b2 << -6.400391328043042e-10, 4.266924591433963e-10;
    
    
    VectorXd x_vero(2);
    x_vero << -1.0e+0,-1.0e+00;

    stampa(A, b, x_vero, "A"); // essendo void non posso usarlo con cout
    stampa(A1, b1, x_vero, "A1");
    stampa(A2, b2, x_vero, "A2");

    
    return 0;

}
