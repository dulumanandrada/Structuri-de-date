/*===============================================================================
    Scrieti 5 algoritmi de sortare diferiti.
Verificati-i pe fiecare pe testele proprii, iar apoi observati si realizati o 
diferenta intre aceste sortari. 

1. Radix Sort ----> O(n+k)  [in cazul de fata: LSD]
2. Merge Sort ----> O(nlogn)
3. Shell Sort ----> O(n^2)
4. Count Sort ----> O(n+maxn)
5. Quick Sort ----> O(nlogn)
===============================================================================*/

#include <iostream>
#define N 1001
using namespace std;

int v[N],n;
int aux[N], F[N];

//subprogram de citire n si vector v[]
void Citire()
{
    cin >> n;
    for(int i = 0; i < n; i ++)
        cin >> v[i];
}

//subprogram afisare vector sortat
void Afisare()
{
    for(int i = 0; i < n; i ++)
        cout << v[i] << " ";
}

//subprogram de determinare a valorii maxime dintr-un vector:
int detMax(int v[], int n)
{
    int i, vmax = v[0];
    for(i = 1; i < n; i ++)
        if(v[i] > vmax)
            vmax = v[i];
    return vmax;
}

//========================= Merge Sort ========================================//
//NU UITA SA DECLARI AUX[] de aceeasi dimensiune ca si v[]
void MergeSort(int v[], int st, int dr)
{
    if(st < dr)
    {
        int mijl = (st + dr) / 2;
        MergeSort(v, st, mijl);
        MergeSort(v, mijl+1, dr);

        int i = st, j = mijl + 1, k = 0;
        while(i <= mijl && j <= dr)
            if(v[i] < v[j])
                aux[++k] = v[i++];
            else 
                aux[++k] = v[j++];
        while(i <= mijl)
            aux[++k] = v[i++];
        while(j <= dr)
            aux[++k] = v[j++];
        
        for(i = st, j = 1; i <= dr; i++, j++)
            v[i] = aux[j];
    }
}
//=============================================================================//


//========================= Quick Sort ========================================//
void QuickSort(int v[], int st, int dr)
{
    //alegem pivotul piv = v[st]
    int m = (st + dr) / 2;
    int aux = v[st];
    v[st] = v[m];
    v[m] = aux;
    int i = st, j = dr, d = 0;
    while(i < j)
    {
        if(v[i] > v[j])
        {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            d = 1 - d;
        }
        i += d;
        j -= 1 - d;
    }
    QuickSort(v, st, i-1);
    QuickSort(v, i+1, dr);
}
//=============================================================================//


//========================= Radix Sort ========================================//


//=============================================================================//


//========================= Shell Sort ========================================//


//=============================================================================//


//========================= Count Sort ========================================//
//NU UITA SA DECLARI GLOBAL F[] = vectorul de frecventa
//NU UITA SA DECLARI AUX[] de aceeasi dimensiune ca si v[]
void CountSort(int v[], int n)
{
    int vmax = detMax(v, n);
    int i;
    for(i = 0; i < n; i ++)
        F[v[i]]++;
    for(i = 1; i <= vmax; i++)
        F[i] += F[i-1];
    for(i = n - 1; i >= 0; i --)
    {
        aux[F[v[i]] - 1] = v[i];
        F[v[i]] --;
    }
    for(i = 0; i < n; i ++)
        v[i] = aux[i];
}
//=============================================================================//

int main()
{
    Citire();
    CountSort(v, n);
    Afisare();
    return 0;
}