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

fajo ordenar_por_probabilidad(const fajo& falsos_conocidos, const fajo & a_ordenar)
{
    auto anioMax = anioMaximo(falsos_conocidos);

    fajo res = a_ordenar;

    vector<std::set<billete> > anios(anioMax);

    /*for(int i = 0; i < anioMax; i++)
    {
        anios[i] =

    }*/

    for(int i = 0; i < falsos_conocidos.size(); i++ )
    {
        /*auto a_insertar = falsos_conocidos[i];
        std::set<billete> actual = anios[int(a_insertar)];
        actual.insert(actual.begin(), a_insertar);*/
        auto aInsertar = falsos_conocidos[i];
        anios[int(aInsertar)-1].insert(/*anios[int(aInsertar)].begin(),*/ aInsertar);
    }

    for( int j = 0; j < res.size(); j++) //recorro el fajo a ordenar para setear su probabilidad de que sea falso
    {
       // billete  &a_setear = res[j]; // billete a buscar en el set para asignar probabalida

        //std::set<billete>::iterator it;
        //auto & a_buscar = anios[int(a_setear)];
        //auto it = anios[int(res[j])-1].find(res[j]); // busco el billete en el año que fue creado find devuevle un it a la posicion del billete si no esta res end()

        if(/*it != anios[int(res[j])-1].end()*/ anios[int(res[j])-1].count(res[j]) == 0) { // si no encuentro el billete le asigno su probabilidad de que sea falso
            res[j].probabilidad_falso = anios[int(res[j])-1].size();//si no encuentro el billete en el set, su probabilidad de que sea falso es la cantidad de billetes falsos que el banco tiene en su listado para ese año
        }

    }

    //bucket_sort_list(res.rbegin(), res.rend());
    std::sort(res.begin(), res.end());
    std::reverse(res.begin(), res.end());
    return res;
    //return std::reverse(res.begin(),res.end());
}

///////////////////////////////////////////////////////////////////////////////
/// EJERCICIO 3
////

inline Matriz multiplicar_strassen(const Matriz& A, const Matriz& B, int K) {
    return multiplicar(A,B);
}

#endif // TP3_IMPL_H
