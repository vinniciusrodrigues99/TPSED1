 ** Vinnicius O. Rodrigues
 */
#include <iostream>
using namespace std;

struct No
{
    float dado;
    No *prox;
};

struct Pilha
{
    No *topo;
};

Pilha *init()
{
    Pilha *p = new Pilha();
    p->topo = NULL;
    return p;
}

int isEmpty(Pilha *p)
{
    return (p->topo == NULL);
}

int count(Pilha *p)
{
    int i = 0;
    No *no = p->topo;
    while (no != NULL)
    {
        i++;
        no = no->prox;
    }
    return i;
}

void print(Pilha *p)
{
    No *no = p->topo;
    cout << "--------------" << endl;
    cout << "Qtde de elementos: " << count(p) << endl;
    cout << "--------------" << endl;
    while (no != NULL)
    {
        cout << no->dado << endl;
        no = no->prox;
    }
    cout << "--------------" << endl;
}

void push(Pilha *p, int v)
{
    No *no = new No();
    no->dado = v;
    no->prox = p->topo;
    p->topo = no;
}

float pop(Pilha *p)
{
    float ret;
    int podeDesempilhar = (!isEmpty(p));
    if (podeDesempilhar)
    {
        No *no = p->topo;
        ret = no->dado;
        p->topo = p->topo->prox;
        free(no);
    }
    else
    {
        ret = -1;
    }
    return ret;
}

void freePilha(Pilha *p)
{
    No *no = p->topo;
    while (no != NULL)
    {
        No *aux = no->prox;
        free(no);
        no = aux;
    }
    free(p);
}

int main(int argc, char **argv)
{
    Pilha *pilhaPar = init();
    Pilha *pilhaImpar = init();
    Pilha *pilha = init();
    int n;

    cout << "Digite 30 números inteiros em ordem crescente:" << endl;

    for (int i = 0; i < 30; i++)
    {
        cout << "Digite o " << i + 1 << "º número: ";
        cin >> n;

        while (pilha->topo != NULL && n <= pilha->topo->dado)
        {
            cout << "O número digitado deve ser maior do que o anterior." << endl;
            cout << "Digite o " << i + 1 << "º número: ";
            cin >> n;
        }

        if (n % 2 == 0)
        {
            push(pilhaPar, n);
        }
        else
        {
            push(pilhaImpar, n);
        }
        push(pilha, n);
    }
    cout << "Pilha de números pares:" << endl;
    print(pilhaPar);
    cout << "Pilha de números ímpares:" << endl;
    print(pilhaImpar);
    cout << "Desempilhando pilha de números pares..." << endl;
    while (!isEmpty(pilhaPar))
    {
        pop(pilhaPar);
    }
    cout << "Desempilhando pilha de números ímpares..." << endl;
    while (!isEmpty(pilhaImpar))
    {
        pop(pilhaImpar);
    }
    freePilha(pilhaPar);
    freePilha(pilhaImpar);
    while (!isEmpty(pilha))
    {
        cout << pop(pilha) << endl;
    }
    freePilha(pilha);

    return 0;
}