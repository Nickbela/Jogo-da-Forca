#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "JogoForca.h" //header files pra acrescentar arquivos ao código

char palavraSecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesDados = 0;

void titulo(){
    printf("__________________________\n");
    printf("|          Jogo          |\n");
    printf("|           da           |\n");
    printf("|          Forca         |\n");
    printf("__________________________\n");
}

void escolhePalavra(){
    FILE* words;

    words = fopen("palavras.txt", "r");

    if(words == 0){
        printf("Banco de dados não disponivel");
        exit(1);
    }

    int quantDePalavras;
    fscanf(words, "%d", &quantDePalavras);

    srand(time(0));
    int randomico = rand() % quantDePalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(words, "%s", palavraSecreta);
    }

    fclose(words);
}

void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

int jachutou(char letra){
    //verifica se o chute esta correto
    int achou = 0;
    for(int j = 0; j < chutesDados; j++){
        if(chutes[j] == letra){
        achou = 1;
        break;
        }
    }
    return achou;
}

void desenharForca(){

    int erros = chutesErrados();

    printf("  _______      \n");
    printf(" |/      |     \n"); //cria uma condição ternária onde coloca a condição, depois o ? para verificar se verdadeiro o falso, se v imprime o primeiro se f imprime o segundo
    printf(" |      %c%c%c \n", (erros >=1 ? '(' : ' '), (erros>=1 ? '_' : ' '), (erros>=1 ? ')' : ' '));
    printf(" |      %c%c%c \n", (erros >=3 ? '\\' : ' '), (erros >=2 ? '|' : ' '), (erros >=3 ? '/' : ' '));
    printf(" |       %c    \n", (erros >=2 ? '|' : ' '));
    printf(" |      %c %c  \n", (erros >=4 ? '/' : ' '),(erros >=4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");

    printf("Você ja deu %d chutes\n", chutesDados);
        //strlen conta o numero de itens do array, nesse caso letras.
    for(int i = 0; i < strlen(palavraSecreta); i++){
        if(jachutou(palavraSecreta[i])) {
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int ganhou(){
    for(int i = 0; i < strlen(palavraSecreta); i++){
        //le o array e se alguma letra da palavra secreta n tiver sido encontrada, significa q o user n ganhou
        if(!jachutou(palavraSecreta[i])){
            return 0;
        }
    }

    return 1;
}

int chutesErrados(){
    int erros = 0;

    for(int i = 0; i < chutesDados; i++){
        int existe = 0;
        for(int j = 0; j < strlen(palavraSecreta); j++){
            if(chutes[i] == palavraSecreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe)erros++;
    }
    return erros;
}

int enforcou(){
    return chutesErrados() >=5;
}

void adicionarPalavra(){
    printf("Deseja adicionar uma palavra ao banco de dados?\n");
    printf("1 - sim\n2 - não\n");

    int resposta;
    scanf("%d", &resposta);

    if (resposta == 1){

        char novaPalavra [TAMANHO_PALAVRA];
        printf("Ok, digite sua palavra: ");
        scanf("%s", novaPalavra);

        FILE* words;
        words = fopen("palavras.txt", "r+"); //leitura + escrita

        if (words == 0){
            printf("Erro");
            exit (1);
        }

        int qtd = 0;
        fscanf(words, "%d", &qtd);
        qtd++;

        fseek(words, 0, SEEK_SET); //MANDA PARA A PRIMEIRA LINHA DO ARQUIVO
        fprintf(words, "%d", qtd);

        fseek(words, 0, SEEK_END);
        fprintf(words, "\n%s", novaPalavra);

        fclose(words);
        printf("Obrigada por jogar");
    }else{
        printf("Ok, obrigada por jogar\n");
    }

}

int main(){

    titulo();
    escolhePalavra();

    do{

        desenharForca();
        chuta();

    }while(!ganhou() && !enforcou()); //rodar enquanto as variaveis forem falsas

    printf("%s", palavraSecreta);

    if(ganhou()){
        printf("\nParabéns!!");
    }else{
        printf("\nQue pena,\n a palvra era **%s**\n\n", palavraSecreta);
    }

    adicionarPalavra();
}
