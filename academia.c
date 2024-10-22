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

// Estrutura para informaes de sade
typedef struct {
    float peso;
    float altura;
    float imc;
    char exames[200];
    char condicoes_medicas[200];
    char treino[500];
} Saude;

// Estrutura para informaes de pagamento
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

// Funo para calcular IMC
float calcular_imc(float peso, float altura) {
    return peso / (altura * altura);
}

// Funo para determinar a situao do IMC
const char* situacao_imc(float imc) {
    if (imc > 40) return "Obesidade grau III";
    if (imc >= 35) return "Obesidade grau II";
    if (imc >= 30) return "Obesidade grau I";
    if (imc >= 25) return "Sobrepeso";
    if (imc >= 18.6) return "Normal";
    return "Abaixo do normal";
}

// Funo para cadastrar um aluno
Aluno* cadastrar_aluno(Aluno *lista) {
    Aluno *novo = (Aluno*) malloc(sizeof(Aluno));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        return lista;
    }

    // Informaes pessoais
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

    // Informaes de sade
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

     // Informaes de pagamento
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
    data_inicial.tm_mon = mes - 1; // Ajusta o ms para 0-11
    data_inicial.tm_year = ano - 1900; // Ajusta o ano para o formato da struct tm

    if (strcmp(novo->pagamento.tipo_plano, "Anual") == 0) {
        data_inicial.tm_year += 1; // Adiciona um ano
    } else if (strcmp(novo->pagamento.tipo_plano, "Trimestral") == 0) {
        data_inicial.tm_mon += 3; // Adiciona trs meses
    } else if (strcmp(novo->pagamento.tipo_plano, "Mensal") == 0) {
        data_inicial.tm_mon += 1; // Adiciona um ms
    }

    mktime(&data_inicial); // Normaliza a estrutura tm

    strftime(novo->pagamento.data_final, sizeof(novo->pagamento.data_final), "%d/%m/%Y", &data_inicial); // Formata a data final

    // Adicionar  lista
    novo->prox = lista;
    return novo;
}

// Funo para exibir informaes do aluno
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
            printf("Condiçõees médicas: %s\n", atual->saude.condicoes_medicas);
            printf("\n| Pagamento |\n");
            printf("Tipo de plano: %s\n", atual->pagamento.tipo_plano);
            printf("Data de início: %s\n", atual->pagamento.data_inicial);
            printf("Data final: %s\n", atual->pagamento.data_final); // Certifique-se de preencher isso na Matricular
            printf("Treino: %s\n", atual->saude.treino);
            return;
        }
        atual = atual->prox;
    }
    printf("Aluno não encontrado.\n");
}

// Funo para remover Matricular
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


// Funo para atualizar treino
void atualizar_treino(Aluno *lista) {
    char cpf[15];
    char nivel[20];
    char categoria[20];
    Aluno *atual = lista;

    printf("Informe o CPF do aluno: ");
    fflush(stdin); // Limpar o buffer
    fgets(cpf, 15, stdin);
    cpf[strcspn(cpf, "\n")] = '\0'; // Remover o '\n' do final

    fflush(stdin); // Limpar o buffer

    while (atual != NULL) {
        if (strcmp(atual->dados_pessoais.cpf, cpf) == 0) {
            // Pede as informaes do treino
            printf("Escolha o nível de treino (Iniciante/Intermediario/Avancado): ");
            fflush(stdin); // Limpar o buffer
            fgets(nivel, 20, stdin);
            nivel[strcspn(nivel, "\n")] = '\0'; // Remover o '\n' do final

            printf("Escolha a categoria (Jovem/Adulto/Idoso/Comorbidade): ");
            fflush(stdin); // Limpar o buffer
            fgets(categoria, 20, stdin);
            categoria[strcspn(categoria, "\n")] = '\0'; // Remover o '\n' do final

            // Atribuindo o treino de acordo com as informaes
            if (strcmp(nivel, "Iniciante") == 0) {
                if (strcmp(categoria, "Jovem") == 0) {
                    strcpy(atual->saude.treino, "Treino_Iniciante_Jovem:\n1. Aquecimento: 5-10 minutos de caminhada ou bicicleta\n2. Agachamento livre: 3x12\n3. Supino com halteres: 3x10\n4. Remada sentada: 3x12\n5. Prancha: 3x20 segundos\n6. Aeróbico: 10-15 minutos de caminhada ou elíptico\n7. Alongamento: pernas, braços\n");
                } else if (strcmp(categoria, "Idoso") == 0) {
                    strcpy(atual->saude.treino, "Treino_Iniciante_Idoso:\n1. Aquecimento: 5-10 minutos de caminhada leve\n2. Leg press com pouco peso: 3x10\n3. Desenvolvimento com halteres sentado: 3x8\n4. Remada na polia baixa: 3x10\n5. Elevações de calcanhares: 3x15\n6. Aeróbico: 10 minutos de bicicleta em ritmo leve\n7. Alongamento: flexibilidade de quadris e ombros\n");
                } else if (strcmp(categoria, "Comorbidade") == 0) {
                    strcpy(atual->saude.treino, "Treino_Iniciante_Comorbidades:\n1. Aquecimento: 10 minutos de caminhada leve\n2. Leg press com pouca carga: 3x10\n3. Flexo na parede: 3x8\n4. Pulldown na polia: 3x10\n5. Prancha modificada: 3x15 segundos\n6. Aeróbico: 10 minutos de bicicleta moderada\n7. Alongamento: parte inferior das costas e pernas\n");
                }
            } else if (strcmp(nivel, "Intermediario") == 0) {
                if (strcmp(categoria, "Jovem") == 0) {
                    strcpy(atual->saude.treino, "Treino_Intermediario_Jovem:\n1. Aquecimento: 10 minutos de bicicleta\n2. Agachamento com barra: 4x10\n3. Supino reto: 4x8\n4. Remada curvada: 4x10\n5. Desenvolvimento com halteres: 3x12\n6. Aeróbico: 20 minutos de HIIT\n7. Alongamento: grupos musculares trabalhados\n");
                } else if (strcmp(categoria, "Idoso") == 0) {
                    strcpy(atual->saude.treino, "Treino_Intermediario_Idoso:\n1. Aquecimento: 10 minutos de bicicleta ou elíptico\n2. Leg press: 4x8-10\n3. Supino com halteres inclinado: 3x8\n4. Remada máquina: 3x10\n5. Rosca direta com halteres: 3x12\n6. Aeróbico: 15 minutos de bicicleta\n7. Alongamento: quadris e ombros\n");
                } else if (strcmp(categoria, "Comorbidade") == 0) {
                    strcpy(atual->saude.treino, "Treino_Intermediario_Comorbidades:\n1. Aquecimento: 10 minutos de caminhada\n2. Agachamento na máquina: 3x12\n3. Supino com halteres: 3x8\n4. Pulldown: 3x10\n5. Prancha modificada: 3x15 segundos\n6. Aeróbico: 20 minutos de caminhada ou bicicleta em ritmo moderado\n7. Alongamento: articulações e membros superiores\n");
                }
            } else if (strcmp(nivel, "Avancado") == 0) {
                if (strcmp(categoria, "Jovem") == 0) {
                    strcpy(atual->saude.treino, "Treino_Avançado_Jovem:\n1. Aquecimento: 10 minutos de elíptico\n2. Agachamento livre pesado: 5x6-8\n3. Supino com barra: 4x6-8\n4. Levantamento terra: 4x6-8\n5. Desenvolvimento militar: 4x8-10\n6. Aeróbico: 20 minutos de HIIT\n7. Alongamento: todos os grupos musculares\n");
                } else if (strcmp(categoria, "Idoso") == 0) {
                    strcpy(atual->saude.treino, "Treino_Avançado_Idoso:\n1. Aquecimento: 10 minutos de bicicleta\n2. Leg press com carga média: 4x8-10\n3. Supino máquina: 4x8-10\n4. Pulldown: 4x10\n5. Desenvolvimento com halteres sentado: 3x12\n6. Aeróbico: 20 minutos em bicicleta\n7. Alongamento: quadris, coluna e ombros\n");
                } else if (strcmp(categoria, "Comorbidade") == 0) {
                    strcpy(atual->saude.treino, "Treino_Avançado_Comorbidades:\n1. Aquecimento: 10 minutos de caminhada leve\n2. Agachamento na máquina com carga moderada: 3x8-10\n3. Supino com halteres: 3x8\n4. Pulldown: 3x8-10\n5. Prancha modificada: 3x20 segundos\n6. Aeróbico: 20 minutos de bicicleta ou caminhada\n7. Alongamento: alongamentos suaves\n");
                }
            }

            printf("Treino atribuído com sucesso!\n");
            return;
        }
        atual = atual->prox;
    }
    printf("Aluno não encontrado.\n");
}

// Funo para exibir o menu de opes
void exibir_menu() {
    printf("\n----------- Painel de Serviços -----------\n");
    printf("1. Matricular\n");
    printf("2. Checar ficha do aluno\n");
    printf("3. Atualizar treino\n");
    printf("4. Remover Matrícula\n");
    printf("0. Sair\n");
    printf("-----------------------------------------\n");
}

// Funo para carregar a lista de alunos de um arquivo
Aluno* carregar_dados() {
    FILE *arquivo = fopen("alunos.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para carregar os dados.\n");
        return NULL;
    }

    Aluno *lista = NULL;
    Aluno *novo;
    while (1) {
        novo = (Aluno*) malloc(sizeof(Aluno));
        if (!novo) {
            printf("Erro ao alocar memória.\n");
            fclose(arquivo);
            return lista;
        }

        // Ler os dados do aluno
        if (fgets(novo->dados_pessoais.nome, 50, arquivo) == NULL) break;
        novo->dados_pessoais.nome[strcspn(novo->dados_pessoais.nome, "\n")] = '\0'; // Remover o '\n' do final

        fscanf(arquivo, " %c\n", &novo->dados_pessoais.sexo);
        fgets(novo->dados_pessoais.data_nascimento, 11, arquivo);
        novo->dados_pessoais.data_nascimento[strcspn(novo->dados_pessoais.data_nascimento, "\n")] = '\0';
        fgets(novo->dados_pessoais.cpf, 15, arquivo);
        novo->dados_pessoais.cpf[strcspn(novo->dados_pessoais.cpf, "\n")] = '\0';
        fgets(novo->dados_pessoais.endereco, 100, arquivo);
        novo->dados_pessoais.endereco[strcspn(novo->dados_pessoais.endereco, "\n")] = '\0';
        fgets(novo->dados_pessoais.telefone, 20, arquivo);
        novo->dados_pessoais.telefone[strcspn(novo->dados_pessoais.telefone, "\n")] = '\0';
        fgets(novo->dados_pessoais.email, 50, arquivo);
        novo->dados_pessoais.email[strcspn(novo->dados_pessoais.email, "\n")] = '\0';
        fscanf(arquivo, "%f\n", &novo->saude.peso);
        fscanf(arquivo, "%f\n", &novo->saude.altura);
        fscanf(arquivo, "%f\n", &novo->saude.imc);
        fgets(novo->saude.exames, 200, arquivo);
        novo->saude.exames[strcspn(novo->saude.exames, "\n")] = '\0';
        fgets(novo->saude.condicoes_medicas, 200, arquivo);
        novo->saude.condicoes_medicas[strcspn(novo->saude.condicoes_medicas, "\n")] = '\0';
        fgets(novo->saude.treino, 200, arquivo);
        novo->saude.treino[strcspn(novo->saude.treino, "\n")] = '\0';
        fgets(novo->pagamento.tipo_plano, 20, arquivo);
        novo->pagamento.tipo_plano[strcspn(novo->pagamento.tipo_plano, "\n")] = '\0';
        fgets(novo->pagamento.data_inicial, 11, arquivo);
        novo->pagamento.data_inicial[strcspn(novo->pagamento.data_inicial, "\n")] = '\0';
        fgets(novo->pagamento.data_final, 11, arquivo);
        novo->pagamento.data_final[strcspn(novo->pagamento.data_final, "\n")] = '\0';

        // Adiciona o novo aluno  lista
        novo->prox = lista;
        lista = novo;
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso.\n");
    return lista;
}

// Funo para salvar a lista de alunos em um arquivo
void salvar_dados(Aluno *lista) {
    FILE *arquivo = fopen("alunos.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    Aluno *atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "%s\n", atual->dados_pessoais.nome);
        fprintf(arquivo, "%c\n", atual->dados_pessoais.sexo);
        fprintf(arquivo, "%s\n", atual->dados_pessoais.data_nascimento);
        fprintf(arquivo, "%s\n", atual->dados_pessoais.cpf);
        fprintf(arquivo, "%s\n", atual->dados_pessoais.endereco);
        fprintf(arquivo, "%s\n", atual->dados_pessoais.telefone);
        fprintf(arquivo, "%s\n", atual->dados_pessoais.email);
        fprintf(arquivo, "%.2f\n", atual->saude.peso);
        fprintf(arquivo, "%.2f\n", atual->saude.altura);
        fprintf(arquivo, "%.2f\n", atual->saude.imc);
        fprintf(arquivo, "%s\n", atual->saude.exames);
        fprintf(arquivo, "%s\n", atual->saude.condicoes_medicas);
        fprintf(arquivo, "%s\n", atual->saude.treino);
        fprintf(arquivo, "%s\n", atual->pagamento.tipo_plano);
        fprintf(arquivo, "%s\n", atual->pagamento.data_inicial);
        fprintf(arquivo, "%s\n", atual->pagamento.data_final);
        fprintf(arquivo, "\n"); // Adiciona uma linha em branco entre os alunos
        atual = atual->prox;
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso.\n");
}


int main() {

    setlocale(LC_ALL, "Portuguese"); // Configura o idioma para Portugus

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
                atualizar_treino(lista);
                break;
            case 4:
                lista = remover_aluno(lista);
                break;
            case 0:
                salvar_dados(lista); // Salva os dados ao sair
                printf("Saindo...\n");
                break;
            default:
                printf("opção inválida.\n");
        }
    } while (opcao != 0);

    // Liberar a memria
    Aluno *temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->prox;
        free(temp);
    }

    return 0;
}
