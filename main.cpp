#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;
class Gauss
{
    vector<vector<double>> A;
    vector<vector<double>> kopia_A;
    int rozmiar;
    vector<double> B;
    vector<double> kopia_B;
    vector<double> X;
    vector<double> pozycja;
public:
    Gauss()
    {
        char wybor;
        do
        {
        cout << "1. Podaj macierz recznie\n2. Wybierz jedna z macierzy\n0. Zamknij program" << endl;
        cin >> wybor;
        switch(wybor)
        {
            case '1':
            {
                cout << "Podaj rozmiar macierzy nxn ze wspolczymmikami przy niewiadomych" << endl;
                cin >> rozmiar;
                for(int i = 0; i < rozmiar; i++)
                {
                    pozycja.push_back(i);
                    B.push_back(0);
                    X.push_back(0);
                }
                for(int i = 0; i < rozmiar; i++) A.push_back(B);
                for(int i = 0; i < rozmiar; i++)
                {
                    for (int j = 0; j < rozmiar; j++)
                    {
                        cout << "Podaj wspolczynnik na pozycji " << i << "x" << j << endl;
                        cin >> A[i][j];
                    }
                    cout << "Podaj wyraz wolny dla wiersza " << i << endl;
                    cin >> B[i];
                }
                kopia_A = A;
                kopia_B = B;
                this->wyswietl();
                this->menu();
                break;
            }
            case '2':
            {
                this->macierze_wbudowane();
                this->menu();
                break;
            }
            case '0':
                cout << "Zamykam" << endl;
                break;
            default:
            {
                cout << "Nieznany identyfikator.";
                break;
            }
        }
        }
        while(wybor != '0');
    }
        void macierze_wbudowane()
    {
        char wybor;
        cout << "Ktora macierz chcesz wybrac?" << endl;
        cin >> wybor;
        switch(wybor)
        {
            case '1':
            {
                A =
                {
                {2, 3, -4},
                {1, 2, -2},
                {4, -2, 5}
                };
                B = {9, 7, -5};
                break;
            }
            case '2':
            {
                A =
                {
                {1, 1, -3, 1},
                {0, 2, -1, 2},
                {1.5, 3.5, -3.5, 6.5},
                {0.5, 1.5, 0, 7.5}
                };
                B = {3, 4, 14.5, 15.5};
                break;
            }
            case '3':
            {
                A =
                {
                {2, -2, -1, 2},
                {3, 1, -2.5, 5},
                {2, -2, 3, 1},
                {2, 4, -2.5, 4}
                };
                B = {2, 9, -1, 8};
                break;
            }
            case '4':
            {
                A =
                {
                {3, 3, -1, -1},
                {4.5, 6.5, -2.5, 0.5},
                {3, 5, -1, 4},
                {3, 3, -0.5, 2.5}
                };
                B = {5, 11.5, 7, 4};
                break;
            }
            case '5':
            {
                A =
                {
                {3, -2, 0, 2},
                {1.5, -2, -2, 5},
                {0, -1.5, -7, 6},
                {3, -3.5, -5, 4}
                };
                B = {-14, -15, -8, -16};
                break;
            }
            case '6':
            {
                A =
                {
                {3, -10.5, 8.5, -5.5},
                {3.25, 15.75, -15.25, 6.75},
                {-1.5, 0, 2.5, 1.75},
                {3, 21, -7, 9}
                };
                B = {5, -20, -0.5, -24};
                break;
            }
            default:
            {
                cout << "Nieznany identyfikator." << endl;
                break;
            }
        }
        rozmiar=B.size();
        for(int i = 0; i < rozmiar; i++)
        {
            X.push_back(0);
            pozycja.push_back(i);
        }
        kopia_A = A;
        kopia_B = B;
        this->wyswietl();
    }
    void przywroc()
    {
        A = kopia_A;
        B = kopia_B;
        pozycja.clear();
    }
    void menu()
    {
        char wybor;
        while(wybor!='0')
        {
            cout << "WYBIERZ OPCJE:\n1. Eliminacja bez wyboru\n2. Eliminacja z wyborem w kolumnie\n3. Eliminacja z wyborem w wierszu\n4. Eliminacja z wyborem pelnym\n0. Wroc do wybierania macierzy\n";
            cin >> wybor;
            switch(wybor)
            {
                case '1':
                {
                    bool czy0;
                    czy0 = this->eliminacja_podstawowa();
                    if(czy0 == true)
                    {
                        this->wyswietl();
                        this->wyznaczanie_niewiadomych();
                        this->wyswietl_niewiadome(wybor);
                    }
                    this->przywroc();
                    break;
                }
                case '2':
                {
                    this->eliminacja_z_kolumnami();
                    this->wyswietl();
                    this->wyznaczanie_niewiadomych();
                    this->wyswietl_niewiadome(wybor);
                    this->przywroc();
                    break;
                }
                case '3':
                {
                    this->eliminacja_z_wierszami();
                    this->wyswietl();
                    this->wyznaczanie_niewiadomych();
                    this->wyswietl_niewiadome(wybor);
                    this->przywroc();
                    break;
                }
                case '4':
                {
                    this->eliminacja_pelna();
                    this->wyswietl();
                    this->wyznaczanie_niewiadomych();
                    this->wyswietl_niewiadome(wybor);
                    this->przywroc();
                    break;
                }
                case '0':
                    cout << "Wracam do wybierania macierzy.\n";
                    pozycja.clear();
                    break;
                default:
                    cout << "Wybrano nieznana opcje.\n";
            }
        }
    }
    void eliminacja (int i)
    {
        double p;
        for (int w = i+1; w < rozmiar; w++)
        {
            p = A[w][i] / A[i][i];
            B[w] = B[w] - B[i]*p;
            for(int k = i; k < rozmiar; k++)
            {
                A[w][k] = A[w][k] - A[i][k]*p;
            }
            this->wyswietl();
        }
    }
    bool eliminacja_podstawowa()
    {
        for(int i =0; i < rozmiar; i++)
        {
            if(A[i][i] == 0){
                cout << "Jedna z wartosci na przekatnej macierzy jest rowna 0, nie mozna rozwiazac rownania." << endl;
                return false;
            }
            this->eliminacja(i);
        }
        return true;
    }
    void eliminacja_z_kolumnami()
    {
        for(int i =0; i < rozmiar; i++)
        {
            double maximum = fabs(A[i][i]);
            int index=i;
            for(int l = i+1; l < rozmiar; l++)
            {
                if(maximum < fabs(A[l][i]))
                {
                    maximum = fabs(A[l][i]);
                    index = l;
                }
            }
            A[index].swap(A[i]);
            swap(B[index],B[i]);
            this->eliminacja(i);
        }
    }
    void eliminacja_z_wierszami()
    {
        for(int i =0; i < rozmiar; i++)
        {
            double maximum = fabs(A[i][i]);
            int index=i;
            for(int l = i+1; l < rozmiar; l++)
            {
                if(maximum < fabs(A[i][l]))
                {
                    maximum = fabs(A[i][l]);
                    index = l;
                }
            }
            for(int l = 0; l < rozmiar; l++)
            {
                swap(A[l][index], A[l][i]);
            }
            swap(pozycja[index], pozycja[i]);
            this->eliminacja(i);
        }
    }
    void eliminacja_pelna()
    {
        for(int i =0; i < rozmiar; i++)
        {
            double maximum = fabs(A[i][i]);
            int index_wierszy=i;
            int index_kolumn=i;
            for(int l = i; l < rozmiar; l++)
                for(int k = 0; k < rozmiar; k++)
                {
                    if(maximum < fabs(A[l][k]))
                    {
                        maximum = fabs(A[l][k]);
                        index_wierszy = l;
                        index_kolumn = k;
                    }
                }
            for(int l = 0; l < rozmiar; l++)
            {
                swap(A[l][index_kolumn], A[l][i]);
            }
            swap(pozycja[index_kolumn], pozycja[i]);
            A[index_wierszy].swap(A[i]);
            swap(B[index_wierszy],B[i]);
            this->eliminacja(i);
        }
    }
    void wyznaczanie_niewiadomych()
    {
        for(int i = rozmiar-1; i >= 0; i--)
        {
            if(i == rozmiar-1) X[i] = B[i] / A[i][i];
            else
            {
                double temp = B[i];
                for(int j = rozmiar-1; j > i; j--) temp -= X[j]*A[i][j];
                X[i] = temp / A[i][i];
            }
        }
    }
    void wyswietl()
    {
        cout << left << setw(15*rozmiar) << "Macierz A";
        cout << left << setw(15) << "Macierz B";
        cout << left << "Pozycja zmiennych" << endl;
        for(int i=0; i<rozmiar; i++)
        {
            for(int j=0; j<rozmiar; j++) cout << left << setw(15) << A[i][j];
            cout << left << setw(15) << B[i];
            cout << setw(5) << pozycja[i];
            cout << endl;
        }
        cout << endl;
    }
    void wyswietl_niewiadome(char wybor)
    {
        if(wybor == '3' or wybor == '4')
        {
            for(int i=0; i<rozmiar; i++)
                for(int j=0; j<rozmiar; j++)
                {
                    if(i == pozycja[j])
                    {
                        swap(pozycja[j],pozycja[i]);
                        swap(X[j],X[i]);
                        break;
                    }
                }
        }
        cout  << "Rozwiazanie: " << endl;
        for(int i=0; i<rozmiar; i++)
        {
            cout << "x" << i << " = " << X[i] << "\t" << endl;
        }
        cout << endl;
    }
};
int main()
{
    Gauss m1;
    return 0;
}