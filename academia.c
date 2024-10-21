#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// Estrutura para dados pessoais
typedef struct {
    char nome[50];
    char sexo;
    char data_nascimento[11];
    char cpf[15];
    char endereco[100];
    char telefone[20];
    char email[50];
} DadosPessoais;

// Estrutura para informações de saúde
typedef struct {
    float peso;
    float altura;
    float imc;
    char exames[200];
    char condicoes_medicas[200];
    char treino[200];
} Saude;

// Estrutura para informações de pagamento
typedef struct {
    char tipo_plano[20];
    char data_inicial[11];
    char data_final[11];
} Pagamento;

// Estrutura principal do aluno
typedef struct Aluno {
    DadosPessoais dados_pessoais;
    Saude saude;
    Pagamento pagamento;
    struct Aluno *prox;
} Aluno;

// Função para calcular IMC
float calcular_imc(float peso, float altura) {
    return peso / (altura * altura);
}

// Função para determinar a situação do IMC
const char* situacao_imc(float imc) {
    if (imc > 40) return "Obesidade grau III";
    if (imc >= 35) return "Obesidade grau II";
    if (imc >= 30) return "Obesidade grau I";
    if (imc >= 25) return "Sobrepeso";
    if (imc >= 18.6) return "Normal";
    return "Abaixo do normal";
}

// Função para cadastrar um aluno
Aluno* cadastrar_aluno(Aluno *lista) {
    Aluno *novo = (Aluno*) malloc(sizeof(Aluno));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        return lista;
    }

    // Informações pessoais
    printf("Nome: ");
    fgets(novo->dados_pessoais.nome, 50, stdin);
    novo->dados_pessoais.nome[strcspn(novo->dados_pessoais.nome, "\n")] = '\0'; // Remover o '\n' do final

    printf("Sexo (M/F): ");
    scanf(" %c", &novo->dados_pessoais.sexo);
    fflush(stdin); // Limpar o buffer

    printf("Data de nascimento (XX/XX/XXXX): ");
    fgets(novo->dados_pessoais.data_nascimento, 11, stdin);
    novo->dados_pessoais.data_nascimento[strcspn(novo->dados_pessoais.data_nascimento, "\n")] = '\0'; // Remover o '\n' do final
    fflush(stdin); // Limpar o buffer

    printf("CPF (xxx.xxx.xxx-xx): ");
    fgets(novo->dados_pessoais.cpf, 15, stdin);
    novo->dados_pessoais.cpf[strcspn(novo->dados_pessoais.cpf, "\n")] = '\0'; // Remover o '\n' do final
    fflush(stdin); // Limpar o buffer


    printf("Endereço: ");
    fgets(novo->dados_pessoais.endereco, 100, stdin);
    novo->dados_pessoais.endereco[strcspn(novo->dados_pessoais.endereco, "\n")] = '\0'; // Remover o '\n' do final
    fflush(stdin); // Limpar o buffer


    printf("Telefone (+xx dd 9xxxx-xxxx): ");
    fgets(novo->dados_pessoais.telefone, 20, stdin);
    novo->dados_pessoais.telefone[strcspn(novo->dados_pessoais.telefone, "\n")] = '\0'; // Remover o '\n' do final
    fflush(stdin); // Limpar o buffer


    printf("Email: ");
    fgets(novo->dados_pessoais.email, 50, stdin);
    novo->dados_pessoais.email[strcspn(novo->dados_pessoais.email, "\n")] = '\0'; // Remover o '\n' do final
    fflush(stdin); // Limpar o buffer

    // Informações de saúde
    printf("Peso (kg): ");
    scanf("%f", &novo->saude.peso);
    fflush(stdin); // Limpar o buffer

    printf("Altura (m): ");
    scanf("%f", &novo->saude.altura);
    fflush(stdin); // Limpar o buffer

    novo->saude.imc = calcular_imc(novo->saude.peso, novo->saude.altura);

    printf("Exames: ");
    fgets(novo->saude.exames, 200, stdin);
    novo->saude.exames[strcspn(novo->saude.exames, "\n")] = '\0'; // Remover o '\n' do final
    fflush(stdin); // Limpar o buffer

    printf("Condições médicas adversas: ");
    fgets(novo->saude.condicoes_medicas, 200, stdin);
    novo->saude.condicoes_medicas[strcspn(novo->saude.condicoes_medicas, "\n")] = '\0'; // Remover o '\n' do final
    fflush(stdin); // Limpar o buffer

     // Informações de pagamento
    printf("Tipo de plano (Anual/Trimestral/Mensal): ");
    fgets(novo->pagamento.tipo_plano, 20, stdin);
    novo->pagamento.tipo_plano[strcspn(novo->pagamento.tipo_plano, "\n")] = '\0'; // Remover o '\n' do final
    fflush(stdin); // Limpar o buffer

    printf("Data de início (XX/XX/XXXX): ");
    fgets(novo->pagamento.data_inicial, 11, stdin);
    novo->pagamento.data_inicial[strcspn(novo->pagamento.data_inicial, "\n")] = '\0'; // Remover o '\n' do final
    fflush(stdin); // Limpar o buffer

    // Calcular data final
    struct tm data_inicial = {0};
    int dia, mes, ano;

    // Converter a data inicial manualmente
    sscanf(novo->pagamento.data_inicial, "%d/%d/%d", &dia, &mes, &ano);
    data_inicial.tm_mday = dia;
    data_inicial.tm_mon = mes - 1; // Ajusta o mês para 0-11
    data_inicial.tm_year = ano - 1900; // Ajusta o ano para o formato da struct tm

    if (strcmp(novo->pagamento.tipo_plano, "Anual") == 0) {
        data_inicial.tm_year += 1; // Adiciona um ano
    } else if (strcmp(novo->pagamento.tipo_plano, "Trimestral") == 0) {
        data_inicial.tm_mon += 3; // Adiciona três meses
    } else if (strcmp(novo->pagamento.tipo_plano, "Mensal") == 0) {
        data_inicial.tm_mon += 1; // Adiciona um mês
    }

    mktime(&data_inicial); // Normaliza a estrutura tm

    strftime(novo->pagamento.data_final, sizeof(novo->pagamento.data_final), "%d/%m/%Y", &data_inicial); // Formata a data final

    system("cls");

    // Adicionar à lista
    novo->prox = lista;
    return novo;
}

// Função para exibir informações do aluno
void checar_ficha(Aluno *lista) {
    char cpf[15];
    printf("Informe o CPF do aluno: ");
    fgets(cpf, 15, stdin);
    cpf[strcspn(cpf, "\n")] = '\0'; // Remover o '\n' do final

    Aluno *atual = lista;

    while (atual != NULL) {
        if (strcmp(atual->dados_pessoais.cpf, cpf) == 0) {
            printf("\n----------------------------| Ficha do Aluno: %s |-----------------------------------\n", atual->dados_pessoais.nome);
            printf("| Informações Pessoais |\n");
            printf("Nome: %s\n", atual->dados_pessoais.nome);
            printf("Sexo: %c\n", atual->dados_pessoais.sexo);
            printf("Data de nascimento: %s\n", atual->dados_pessoais.data_nascimento);
            printf("CPF: %s\n", atual->dados_pessoais.cpf);
            printf("Endereço: %s\n", atual->dados_pessoais.endereco);
            printf("Telefone: %s\n", atual->dados_pessoais.telefone);
            printf("Email: %s\n", atual->dados_pessoais.email);
            printf("\n| Saúde |\n");
            printf("Peso: %.2f kg\n", atual->saude.peso);
            printf("Altura: %.2f m\n", atual->saude.altura);
            printf("IMC: %.2f (%s)\n", atual->saude.imc, situacao_imc(atual->saude.imc));
            printf("Exames: %s\n", atual->saude.exames);
            printf("Condições médicas: %s\n", atual->saude.condicoes_medicas);
            printf("\n| Pagamento |\n");
            printf("Tipo de plano: %s\n", atual->pagamento.tipo_plano);
            printf("Data de início: %s\n", atual->pagamento.data_inicial);
            printf("Data final: %s\n", atual->pagamento.data_final); // Certifique-se de preencher isso na matrícula
            return;
        }
        atual = atual->prox;
    }
    printf("Aluno não encontrado.\n");
}

// Função para remover matrícula
Aluno* remover_aluno(Aluno *lista) {
    char cpf[15];
    printf("Informe o CPF do aluno a ser removido: ");
    fgets(cpf, 15, stdin);
    Aluno *atual = lista, *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados_pessoais.cpf, cpf) == 0) {
            if (anterior == NULL) {
                lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Aluno removido com sucesso.\n");
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Aluno não encontrado.\n");
    return lista;
}

// Função para exibir o menu de opções
void exibir_menu() {
    printf("\n----------- Painel de Serviços -----------\n");
    printf("1. Matrícula\n");
    printf("2. Checar ficha do aluno\n");
    printf("3. Atualizar treino\n");
    printf("4. Remover matrícula\n");
    printf("0. Sair\n");
    printf("-----------------------------------------\n");
}




int main() {
    setlocale(LC_ALL, "Portuguese"); // Configura o idioma para Português

    Aluno *lista = NULL;
    int opcao;

    do {


        exibir_menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer

        switch (opcao) {
            case 1:
                lista = cadastrar_aluno(lista);
                break;
            case 2:
                checar_ficha(lista);
                break;
            case 3:
                printf("Funcionalidade de atualizar treino ainda não implementada.\n");
                break;
            case 4:
                lista = remover_aluno(lista);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    // Liberar a memória
    Aluno *temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->prox;
        free(temp);
    }

    return 0;
}
