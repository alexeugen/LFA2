#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("input.txt");


int **x;
int nc, //numarul de litere
      ns,  //numarul de stari
        pf; //de unde incep pozitiile finale
int partitii[100];
int np;   //numarul de partitii
char* characters;

int check_value(int i, int j, int k)
{
  for(int p = 1; p < np; p++)  //parcurg partitiile
  {
      int q1 = 0;
      int q2 = 0;
      for(int ii = partitii[p-1]; ii < partitii[p] ; ii++) //in acest for i-ul parcurge cate o partitie
      {
        if(x[ii][0] == x[i][k])
          q1 = 1;
        if(x[ii][0] == x[j][k])
          q2 = 1;
      }
      if(q1 && q2)
        return 1;
  }
  return 0;
}

int check_lines(int i, int j)
{
  int q = 1;
  for(int k = 1; k <= nc; k++,cout<<endl) //parcurg numarul de caractere
  {
    cout<<x[i][k]<<" checked with "<<x[j][k];
    cout<<" : result = "<< check_value(i, j, k);
    if(!check_value(i, j, k))
    q = 0;
  }
  if(q)
  {  cout<<"both on the same line"; return 1;}
  else return 0;
}

void exchange(int i, int j)
{
  int* aux;
  aux = x[i];
  x[i] = x[j];
  x[j] = aux;
}

void insert(int par[], int &np, int j, int y)
{
  np += 1;
  for(int i = np - 1; i > j ; i--)
    par[i] = par[i - 1];
  par[j] = y;
}

int check_newpart(int v[], int par[], int &nn, int &np)
{
  int q = 0;
  for(int i = 0; i < nn; i++)
    for(int j = 1; j < np; j++)
      if(par[j] > v[i] && par[j-1] < v[i])
      {
        insert(par, np, j, v[i]);
        j = np;
        q = 1;
      }
  return q;
}

void afisare_matrice()
{
  cout<<endl<<"**AFISARE MATRICE PARTITIONATA**"<<endl;
  for(int p = 1; p < np; p++, cout<<endl)
    for(int i = partitii[p-1]; i < partitii[p] ; i += 1, cout<<endl)
      for(int j = 0; j<nc+1; j++)
        cout<<x[i][j]<<" ";
}

void afisare_minimal()
{
  cout<<endl<<"**AFISARE MINIMAL**"<<endl;

  for(int p = 1; p < np; p++, cout<<endl)
  {
    cout<<p;
    for(int c = 1; c < nc + 1; c++)
    {
      int i = partitii[p-1];
        for(int pp = 1; pp < np; pp++)
          for(int ii = partitii[pp-1]; ii < partitii[pp]; ii += 1)
            if(x[i][c] == x[ii][0])
            {
                cout<<" "<<pp;

                pp = np;
                ii = partitii[p];
            }
    }
  }
}


int main()
{

  fin>>nc;
  characters = new char[nc];
  for(int i = 0; i < nc; i++)
    fin>>characters[i];

  fin>>ns;
  fin>>pf;
  np = 3; partitii[0] = 0; partitii[1] = pf; partitii[2] = ns;


  x = new int*[ns];
  for(int i = 0; i < ns; i++)
    x[i] = new int[nc + 1];

  for(int i = 0; i < ns; i++)
    for(int j = 0; j < nc + 1; j++)
      fin>>x[i][j];


      for(int i = 0; i<np; i++)
        cout<<partitii[i]<<" ";

  int v[100];
  int nn = 0;
  int q = 1;
  while(q)
  {
    nn = 0;
    for(int p = 1; p < np; p++)  //parcurg partitiile
    {
        int lu;
        for(int i = partitii[p-1]; i < partitii[p] - 1; i+= lu + 1, cout<<endl) //in acest for i-ul parcurge cate o partitie
        {
          lu = 0;
          for(int j = i+1; j < partitii[p]; j++, cout<<endl)
            if(check_lines(i, j))
            {
              lu += 1;
              if(lu < j)
               exchange(i+lu, j);
            }
          v[nn++] = i + lu + 1;
        }
    }
    for(int i = 0; i<np; i++)
      cout<<partitii[i]<<" ";
      cout<<endl;
      for(int i = 0; i<nn; i++)
        cout<<v[i]<<" ";
      cout<<endl;
    q = check_newpart(v, partitii, nn, np);
  }

  for(int i = 0; i<np; i++)
    cout<<partitii[i]<<" ";
  cout<<endl;

  afisare_matrice();
  afisare_minimal();
/*
  for(int p = 1; p < np; p++)  //parcurg partitiile
  {
      int lu;
      for(int i = partitii[p-1]; i < partitii[p] ; i+=  1) //in acest for i-ul parcurge cate o partitie
      {
        cout<<x[i][0]<<" ";
      }
      cout<<endl;
  }
  */

}
