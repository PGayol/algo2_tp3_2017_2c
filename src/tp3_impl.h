#ifndef TP3_IMPL_H
#define TP3_IMPL_H

#include "tp3.h"

#include <limits>
#include <algorithm>
#include <map>
#include <set>

///////////////////////////////////////////////////////////////////////////////
/// EJERCICIO 1
////
template <typename iterator>
inline int minimo(iterator desde, iterator hasta);

template <typename iterator>
inline int maximo(iterator desde, iterator hasta);

template <typename iterator, typename bucket>
vector<bucket> generar_buckets(iterator input_begin, iterator input_end)
{
    vector<bucket> bts;
    bts.resize(0);

    if (input_begin == input_end) return bts;

    int min = minimo(input_begin, input_end);
    int max = maximo(input_begin, input_end);

    int tam = max - min + 1;

    bts.resize(tam);
    auto it = input_begin;

    while(it != input_end)
    {
        int indice = int(*it) - min;
        auto anEnd = bts[indice].end();
        bts[indice].insert(anEnd, *it);
        ++it;
    }

    /*vector<bucket> res;
	for(int i= 0; i < bts.size(); i++)
	{
		//if(bts[i].begin() == bts[i].end()) bts.erase(bts.begin()+i);
	    if(bts[i].begin() != bts[i].end())
        {
            res.push_back(bts[i]);
        }
    }*/
    return bts;
}

template < typename iterator>
int minimo(iterator desde, iterator hasta)
{
    auto it = desde;
    auto minimo = desde;
    while(it != hasta)
    {
        if (*it < *minimo) minimo = it;
        ++it;
    }

    return int(*minimo);

}


template < typename iterator>
int maximo(iterator desde, iterator hasta)
{
    auto it = desde;
    auto maximo = desde;
    while(it != hasta)
    {
        if (*it > *maximo) maximo = it;
        ++it;
    }

    return int(*maximo);

}

template <typename bucket>
vector<typename bucket::value_type> aplanar_buckets(const std::vector<bucket> & B)
{
    vector< typename bucket::value_type > res;

    for(int i = 0; i < B.size(); i++)
    {
        auto it = B[i].begin();

        while(it != B[i].end())
        {
            res.push_back(*it);
            ++it;
        }

    }
    return res;
}

///////////////////////////////////////////////////////////////////////////////
/// EJERCICIO 2
////
inline int anioMaximo(const fajo & falsos);

int anioMaximo(const fajo& falsos)
{
    int max = int(falsos[0]); // acordarse caso borde (si falsos es vacio?)

    for(int i = 0; i < falsos.size(); i++)
    {
        if (int(falsos[i]) > max ) max = int(falsos[i]);
    }
    return max;
}

inline int anioMinimo(const fajo & falsos);
int anioMinimo(const fajo& falsos)
{
    int min = int(falsos[0]); // acordarse caso borde (si falsos es vacio?)

    for(int i = 0; i < falsos.size(); i++)
    {
        if (int(falsos[i]) < min ) min = int(falsos[i]);
    }
    return min;
}

fajo ordenar_por_probabilidad(const fajo& falsos_conocidos, const fajo & a_ordenar)
{
    auto anioMax = anioMaximo(falsos_conocidos);
    auto anioMin = anioMinimo(falsos_conocidos);
    int tam = anioMax - anioMin + 1;
    // tam es el tamaño del vector de años
    fajo res = a_ordenar;
    vector<std::set<billete> > anios(tam);

    for(int i = 0; i < falsos_conocidos.size(); i++ )
    {
        auto aInsertar = falsos_conocidos[i];
        anios[int(aInsertar) -1 - (anioMin-1)].insert(aInsertar);
    }

    for( int j = 0; j < res.size(); j++) //recorro el fajo a ordenar para setear su probabilidad de que sea falso
    {
        if(anios[int(res[j])-1 - (anioMin-1)].count(res[j]) == 0) { // si no encuentro el billete le asigno su probabilidad de que sea falso
            res[j].probabilidad_falso = anios[int(res[j])-1 - (anioMin-1)].size();//si no encuentro el billete en el set, su probabilidad de que sea falso es la cantidad de billetes falsos que el banco tiene en su listado para ese año
        }

    }

    //bucket_sort_list(res.rbegin(), res.rend());
    std::sort(res.begin(), res.end());
    std::reverse(res.begin(), res.end());
    return res;
}
///////////////////////////////////////////////////////////////////////////////
/// EJERCICIO 3
////
inline Matriz sumaMatriz(const Matriz& M1, const Matriz& M2, Matriz& M3 )
{
    //Matriz res(M1.size(), vector<double>(M1.size(), 0.0));
    for(int i=0; i < M1.size(); i++)
    {
        for(int j=0; j < M1.size(); j++)
        {
            M3[j][i] = M1[j][i] + M2[j][i];
        }
    }
    return M3;
}

inline Matriz restaMatriz(const Matriz& M1, const Matriz& M2, Matriz& M3)
{
    //Matriz res(M1.size(), vector<double>(M1.size(), 0.0));
    for(int i=0; i < M1.size(); i++)
    {
        for(int j=0; j < M1.size(); j++)
        {
            M3[j][i] = M1[j][i] - M2[j][i];
        }
    }
    return M3;
}

inline Matriz Unir(const Matriz& M1, const Matriz& M2, const Matriz& M3, const Matriz& M4, Matriz& C )
{

    int n = M1.size();

    for(int i = 0; i < n; i++)
    {
        vector<double> aux(0);
        aux.insert(aux.end(), M1[i].begin(), M1[i].end());
        aux.insert(aux.end(), M2[i].begin(), M2[i].end());
        C.insert(C.end(), aux);
    }

    for(int i = 0; i <n; i++)
    {
        vector<double> aux(0);
        aux.insert(aux.end(), M3[i].begin(), M3[i].end());
        aux.insert(aux.end(), M4[i].begin(), M4[i].end());
        C.insert(C.end(), aux);
    }

    return C;

}

inline Matriz multiplicar_strassen(const Matriz& A, const Matriz& B, int K)
{
    size_t  n = A.size();

    if (A.size() <= K) // caso base, si el tamaño de la matriz es menor a k se resuelvo con la multiClasic
    {
        return multiplicar(A, B);
    }
    else
    {
        // Divido las matrices A y B en cuatro cuadrantes
        int n2 = n / 2;
        Matriz A11(n2, vector<double>(n2, 0.0));
        Matriz A12(n2, vector<double>(n2, 0.0));
        Matriz A21(n2, vector<double>(n2, 0.0));
        Matriz A22(n2, vector<double>(n2, 0.0));

        Matriz B11(n2, vector<double>(n2, 0.0));
        Matriz B12(n2, vector<double>(n2, 0.0));
        Matriz B21(n2, vector<double>(n2, 0.0));
        Matriz B22(n2, vector<double>(n2, 0.0));

        // Genero las matrices para el vector resultante C
        Matriz C11(n2, vector<double>(n2, 0.0));
        Matriz C12(n2, vector<double>(n2, 0.0));
        Matriz C21(n2, vector<double>(n2, 0.0));
        Matriz C22(n2, vector<double>(n2, 0.0));

        /*Matriz M1(n2, vector<double>(n2, 0.0));
        Matriz M2(n2, vector<double>(n2, 0.0));
        Matriz M3(n2, vector<double>(n2, 0.0));
        Matriz M4(n2, vector<double>(n2, 0.0));
        Matriz M5(n2, vector<double>(n2, 0.0));
        Matriz M6(n2, vector<double>(n2, 0.0));
        Matriz M7(n2, vector<double>(n2, 0.0));
*/
        Matriz auxA(n2, vector<double>(n2, 0.0));
        Matriz auxB(n2, vector<double>(n2, 0.0));

        for(int i=0; i < n2; i++)
        {
            for(int j=0; j < n2; j++)
            {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j+n2];
                A21[i][j] = A[i+n2][j];
                A22[i][j] = A[i+n2][j+n2];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j+n2];
                B21[i][j] = B[i+n2][j];
                B22[i][j] = B[i+n2][j+n2];
            }
        }

        sumaMatriz(A11, A22, auxA);
        sumaMatriz(B11, B22, auxB);
        Matriz M1 = multiplicar_strassen(auxA, auxB, K);

        sumaMatriz(A21, A22, auxA);
        Matriz M2 = multiplicar_strassen(auxA, B11, K);

        restaMatriz(B12, B22, auxB);
        Matriz M3 = multiplicar_strassen(A11, auxB, K);

        restaMatriz(B21, B11, auxB);
        Matriz M4 = multiplicar_strassen(A22, auxB, K);

        sumaMatriz(A11, A12, auxA);
        Matriz M5 = multiplicar_strassen(auxA, B22, K);

        restaMatriz(A21, A11, auxA);
        sumaMatriz(B11, B12, auxB);
        Matriz M6 = multiplicar_strassen(auxA, auxB, K);

        restaMatriz(A12, A22, auxA);
        sumaMatriz(B21, B22, auxB);
        Matriz M7 = multiplicar_strassen(auxA, auxB, K);

        sumaMatriz(M3, M5, C12);
        sumaMatriz(M2, M4, C21);

        sumaMatriz(M1, M4, auxA);
        sumaMatriz(auxA, M7,auxB);
        restaMatriz(auxB, M5, C11);

        sumaMatriz(M1, M3, auxA);
        sumaMatriz(auxA, M6, auxB);
        restaMatriz(auxB, M2, C22);

       Matriz C(0);
       Unir(C11, C12, C21, C22, C);

       /*Matriz C(A.size(), vector<double>(A.size(),0.0) ); // crear una matriz vacia e ir agregandole los elementos

        for(int i=0; i < n2; i++)
        {
            for(int j=0; j < n2; j++)
            {
                C[i][j] = C11[i][j];
                C[i][j+n2] = C12[i][j];
                C[i+n2][j] = C21[i][j];
                C[i+n2][j+n2] = C22[i][j];
            }
        }*/
        return C;
    }


    //return multiplicar(A,B);
}

#endif // TP3_IMPL_H
