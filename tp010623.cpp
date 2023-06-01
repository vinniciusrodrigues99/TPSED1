#include <iostream>
using namespace std;
#define MAX 5

/**
 * Vinnicius Oliveira Rodrigues
*/

struct Fila
{
    int ini;
    int fim;
    float nos[MAX];
};

Fila *init()
{
    Fila *f = new Fila;
    f->ini = 0;
    f->fim = 0;
    return f;
}

struct Guiche
{
    int id;
    Fila *senhasAtendidas;
    Guiche *prox;
};

Guiche *initGuiche(int id)
{
    Guiche *g = new Guiche;
    g->id = id;
    g->senhasAtendidas = init();
    g->prox = NULL;
    return g;
}

int isEmpty(Fila *f)
{
    return (f->ini == f->fim);
}

int incrementa(int i)
{
    return (i == MAX ? 0 : ++i);
}

int count(Fila *f)
{
    int qtde = 0;
    int i = f->ini;
    while (i != f->fim)
    {
        qtde++;
        i = incrementa(i);
    }
    return qtde;
}

void print(Fila *f)
{
    int i = f->ini;
    cout << "------------" << endl;
    while (i != f->fim)
    {
        cout << f->nos[i] << endl;
        i = incrementa(i);
    }
    cout << "------------" << endl;
}

void freeFila(Fila *f)
{
    free(f);
}

int enqueue(Fila *f, float v)
{
    int podeEnfileirar = (incrementa(f->fim) != f->ini);
    if (podeEnfileirar)
    {
        f->nos[f->fim] = v;
        f->fim = incrementa(f->fim);
    }
    return podeEnfileirar;
}

float dequeue(Fila *f)
{
    float ret;
    if (isEmpty(f))
    {
        ret = -1;
    }
    else
    {
        ret = f->nos[f->ini];
        f->ini = incrementa(f->ini);
    }
    return ret;
}

int checarGuicheAberto(int id, Guiche *guiches)
{
    Guiche *aux = guiches;
    int guicheJaAberto = 0;
    while (aux != NULL)
    {
        if (aux->id == id)
        {
            guicheJaAberto = 1;
            break;
        }
        aux = aux->prox;
    }
    return guicheJaAberto;
}

int guicheExiste (int id, Guiche *guiches) {
    Guiche *aux = guiches;
    int guicheExiste = 0;
    while (aux != NULL)
    {
        if (aux->id == id)
        {
            guicheExiste = 1;
            break;
        }
        aux = aux->prox;
    }
    return guicheExiste;
}

void atenderSenha(int id, Guiche *guiche, Fila *senhasGeradas, Fila *senhasAtendidas)
{
    float senha = dequeue(senhasGeradas);
    enqueue(senhasAtendidas, senha);
    Guiche *aux = guiche;
    while (aux != NULL)
    {
        if (aux->id == id)
        {
            enqueue(aux->senhasAtendidas, senha);
            cout << "Senha " << senha << " atendida no guichê " << id << endl;
            break;
        }
        aux = aux->prox;
    }
}

int main()
{
    Fila *senhasGeradas = init();
    Fila *senhasAtendidas = init();
    Guiche *guiches = NULL;

    int primeiraExecucao = 1;
    int opcao = -1;
    while (opcao != 0)
    {

        cout << "Seletor:" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Abrir guichê" << endl;
        cout << "3. Realizar atendimento" << endl;
        cout << "4. Listar senhas atendidas" << endl;
        cin >> opcao;

        if (opcao == 1)
        {
            float novaSenha = count(senhasGeradas) + 1;
            if (enqueue(senhasGeradas, novaSenha))
            {
                cout << "Senha que foi gerada: " << novaSenha << endl;
            }
            else
            {
                cout << "Limite de senhas atingido." << endl;
            }
        }
        else if (opcao == 2)
        {
            int id;
            int guicheJaAberto = 0;
            Guiche *aux = guiches;

            cout << "Digite o id do guichê: ";
            cin >> id;

            guicheJaAberto = checarGuicheAberto(id, guiches);

            while (guicheJaAberto)
            {
                cout << "Guichê iniciado." << endl;
                cout << "Digite o id do guichê: ";
                cin >> id;
                guicheJaAberto = checarGuicheAberto(id, guiches);
            }

            Guiche *g = initGuiche(id);
            if (guiches != NULL)
            {
                guiches->prox = g;
            }
            else
            {
                guiches = g;
            }
            cout << "Guichê " << id << " aberto." << endl;
        }
        else if (opcao == 3)
        {
            int id;
            cout << "Informe o id do guichê: ";
            cin >> id;
            if (guicheExiste(id, guiches))
            {
                atenderSenha(id, guiches, senhasGeradas, senhasAtendidas);
            }
            else
            {
                cout << "Guichê não existe." << endl;
            }
        }
        else if (opcao == 4) {
            Guiche *aux = guiches;
            while (aux != NULL)
            {
                cout << "Senhas atendidas pelo guichê " << aux->id << endl;
                print(aux->senhasAtendidas);
                aux = aux->prox;
            }
        }
        else if (opcao == 0)
        {
            if (isEmpty(senhasGeradas))
            {
                cout << "Não há senhas aguardando atendimento." << endl;
                opcao = 0;
            }
            else
            {
                cout << "Ainda há senhas aguardando atendimento." << endl;
                opcao = -1;
            }
        }
        primeiraExecucao = 0;
    }

    cout << "Quantidade de senhas atendidas: " << count(senhasAtendidas) << endl;

    freeFila(senhasGeradas);
    freeFila(senhasAtendidas);

    return 0;
}