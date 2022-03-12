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
#include <fstream>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#define N 100000001
#define Max 10000001

using namespace std;

ifstream fin("sortare.in");
ofstream fout("sortare.out");

int v[N], nt, n, nmax;
int a[N];
int AUX[N], F[N];

//subprogram de initializare a fiecarui vector cu 0;
void Initializare()
{
    for(int i = 0; i < N; i ++)
        {
            F[i] = 0;
            v[i] = 0;
            a[i] = 0;
            AUX[i] = 0;
        }
}

//subprogram afisare vector initial
void AfisareInitial()
{
    cout << "Vectorul initial: \n";
    for(int i = 0; i < n; i ++)
        cout << v[i] << " ";
    cout<<"\n";
}

//subprogram afisare vector sortat
void AfisareFinal()
{
    fout << "Vectorul sortat: \n";
    for(int i = 0; i < n; i ++)
        fout << v[i] << " ";
    fout<<"\n";
}

//subprogram test de verificare ector sortat si identic
int Verificare(int a[], int v[], int n)
{
    sort(a, a + n);
    for(int i = 0; i < n; i ++)
            if(a[i] != v[i]) return 0;
    return 1;
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
        int mijl = st + (dr - st) / 2;
        MergeSort(v, st, mijl);
        MergeSort(v, mijl+1, dr);

        int i = st, j = mijl + 1, k = 0;
        while(i <= mijl && j <= dr)
            if(v[i] < v[j])
                AUX[++k] = v[i++];
            else 
                AUX[++k] = v[j++];
        while(i <= mijl)
            AUX[++k] = v[i++];
        while(j <= dr)
            AUX[++k] = v[j++];
        
        for(i = st, j = 1; i <= dr; i++, j++)
            v[i] = AUX[j];
    }
}
//=============================================================================//


//========================= Quick Sort ========================================//
void QuickSort(int v[], int st, int dr)
{
    int i, j, d;
    if(st < dr)
    {
        int m = st + (dr - st) / 2;
        int aux = v[st];
        v[st] = v[m];
        v[m] = aux;

        i = st; j = dr; d = 0;
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
}
//=============================================================================//


//========================= Radix Sort ========================================//
//o sa foloseasca fungtia de detMax()
//o sa foloseasca un vector de frecventa declarat in interiorul functiei
void countsort(int v[], int n, int exp)
{
    int aux[n];
    int i, f[10] = {0};
    for(i = 0; i < n; i ++)
        f[(v[i] / exp) % 10] ++;
    for(i = 1; i < 10; i++)
        f[i] += f[i-1];
    for(i = n - 1; i >= 0; i --)
        {
            aux[f[(v[i] / exp) % 10] -1] = v[i];
            f[(v[i] / exp) % 10] --;
        }
    for(i = 0; i < n; i ++)
        v[i] = aux[i];
}

void RadixSort(int v[], int n)
{
    int vmax = detMax(v, n);
    for(int exp = 1; vmax / exp > 0; exp *= 10)
        countsort(v, n, exp);
}
//=============================================================================//


//========================= Shell Sort ========================================//
void ShellSort(int v[], int n)
{
    for(int gap = n/2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < n; i++)
        {
            int aux = v[i];
            int j;
            for(j = i; j >= gap && v[j - gap] > aux; j -= gap)
                v[j] = v[j - gap];
            v[j] = aux;
        }
    }
}
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
        AUX[F[v[i]] - 1] = v[i];
        F[v[i]] --;
    }
    for(i = 0; i < n; i ++)
        v[i] = AUX[i];
}
//=============================================================================//


int main()
{   
    fin >> nt;

    for(int t = 1; t <= nt; t ++)
    {
        fin >> n >> nmax;

        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        
        Initializare();

        for(int i = 0; i < n; i ++)
        {
            v[i] = uniform_int_distribution<int>(0, nmax)(rng);
            a[i] = v[i];
        }
        
        auto start = chrono::steady_clock::now();
        
        CountSort(v, n);
        //MergeSort(v, 0, n-1);
        //QuickSort(v, 0, n-1);
        //RadixSort(v, n);
        //ShellSort(v, n);

        
        fout <<"Testul nr." << t << " " << "Ordonat: " << Verificare(a, v, n);
        fout << " Timp: ";

        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        fout << chrono::duration<double, mulli>(diff).count() << " ms" << endl;
        
        fout << "\n";
    } 

    return 0;
}

