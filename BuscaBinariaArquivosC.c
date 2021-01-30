#include <stdio.h>
#include <stdlib.h>\

typedef struct Funcionario{
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

void povoar_arquivo(int numero_de_pessoas,FILE *arquivo){

    TFunc pessoa_arbitraria = {0,"Pessoa Aleatoria","111.111.111-00","01/01/1972", 1.500};

    for(int i=0;i<numero_de_pessoas;i++){
        pessoa_arbitraria.cod = i;
        fwrite(&pessoa_arbitraria,sizeof(TFunc),1,arquivo);
    }
}
void ler_arquivo_povoado(FILE *arquivo){

    TFunc pessoa_leitura;

    if(!arquivo){
        printf("Erro ao ler o arquivo");
        exit(1);
    }

    while(fread(&pessoa_leitura,sizeof(TFunc),1,arquivo)){
        printf("%d, %s,  %s,  %s,  %f \n", pessoa_leitura.cod,pessoa_leitura.nome,pessoa_leitura.cpf,pessoa_leitura.data_nascimento,pessoa_leitura.salario);
    }
}

int tamanho_arquivo(FILE *arquivo){
    fseek(arquivo,0,SEEK_END);
    int tam = trunc(ftell(arquivo)/sizeof(TFunc));
    return tam;
}

void busca_binaria_arquivo(int cod_buscado, FILE *arquivo, int tamanhoDoArquivo){



    if(cod_buscado>tamanhoDoArquivo){
        printf("Codigo invalido! Numero excede tamanho de registro no arquivo");
        exit(1);
    }

    TFunc pessoa_resultado = {0,"","","",0};

    int inicio = 0, fim = tamanhoDoArquivo, meio = trunc((inicio+fim)/2);
    int codigo=0;

    fseek(arquivo,meio*sizeof(TFunc),SEEK_SET);
    fread(&pessoa_resultado,sizeof(TFunc),1,arquivo);
    codigo = pessoa_resultado.cod;

    printf("Primeira busca -> meio do arquivo: %d\n", codigo);

    int contador_de_interacao = 0;
    while(inicio < fim){

                if(cod_buscado>codigo){

                    inicio = meio+1;
                    meio = trunc((inicio+fim)/2);
                    fseek(arquivo,meio*sizeof(TFunc),SEEK_SET);
                    fread(&pessoa_resultado,sizeof(TFunc),1,arquivo);
                    codigo = pessoa_resultado.cod;
                    int test = ftell(arquivo);
                    printf("Busca numero = %d , Inicio = %d Fim = %d Meio = %d, Cursor possicao > %d : codigo: %d\n",contador_de_interacao,inicio,fim,meio, test, pessoa_resultado.cod);
                    contador_de_interacao++;

                }else{

                    fim = meio;
                    meio = trunc((inicio+fim)/2);
                    fseek(arquivo,meio*sizeof(TFunc),SEEK_SET);
                    fread(&pessoa_resultado,sizeof(TFunc),1,arquivo);
                    codigo = pessoa_resultado.cod;
                    int test = ftell(arquivo);
                    printf("Busca numero = %d , inicio = %d fim = %d meio = %d, Cursor possicaoo < %d  : codigo: %d\n",contador_de_interacao,inicio,fim,meio, test, pessoa_resultado.cod);
                    contador_de_interacao++;

                }

    }
    printf("\n******************************************************\n");
    printf("Codigo do funcionario buscado: %d\n", cod_buscado);
    printf("A posicao do curso deve ser posicionada em '%d bytes', para acessar o registro do funcionario buscado", ftell(arquivo));
    printf("\nNumero de interacao realizadas: %d\n", contador_de_interacao);
    printf("----------- FUNCIONARIO ----------");
    printf("\n  Cod: %d\n  Nome: %s\n  CPF: %s\n  Data de Nascimento: %s\n  Salario: %lf",pessoa_resultado.cod,pessoa_resultado.nome,pessoa_resultado.cpf,pessoa_resultado.data_nascimento,pessoa_resultado.salario);
    printf("\n******************************************************\n");
}

int main()
{
    FILE *base_funcionarios;

    //Cria/le um arquivo binario e povoa com dados ficticios

    /*
    base_funcionarios = fopen("BD.bin","ab");
    povoar_arquivo(10,base_funcionarios);
    fclose(base_funcionarios);


    base_funcionarios = fopen("BD_FUNCIONARIOS.bin", "rb");
    ler_arquivo_povoado(base_funcionarios);
    fclose(base_funcionarios);


    base_funcionarios = fopen("BD_FUNCIONARIOS.bin", "rb");
    printf("%d",tamanho_arquivo(base_funcionarios));
    fclose(base_funcionarios);

*/

    base_funcionarios = fopen("BD_FUNCIONARIOS.bin", "rb");
    busca_binaria_arquivo(6666,base_funcionarios,tamanho_arquivo(base_funcionarios));
    fclose(base_funcionarios);
    return 0;
}
