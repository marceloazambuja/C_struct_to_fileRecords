//
//  main.c
//  database2
//
//  Created by Marcelo Cunha de Azambuja on 6/15/18.
//  Copyright © 2018 Marcelo Cunha de Azambuja. All rights reserved.
//

/***************************************************************************
 grava_estruturas.cpp  -  description
 -------------------
 1. Numero do paciente (chave primaria de ate 6 caracteres)
 2. Nome do paciente
 3. Idade (valor entre 0 e 120)
 4. Diagnostico (campo de tamanho livre)
 5. Tratamento (campo de tamanho livre com subcampos separados por um delimitador
 qualquer).
 ***************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15

struct registro {
    int  reg_id;
    char reg_nome[100];
    int  reg_idade;
    char reg_diagnostico[200];
    char reg_tratamento[250];
} stHospital[SIZE];

char menu(void);
void init_list(void);
void enter(void);
void display(void);
void save(void);
void load(void);

int main(void)
{
    char escolha;
    
    init_list();
    
    for(;;) {
        escolha=menu();
        switch(escolha)
        {
            case 'i':enter();
                break;
            case 'v':display();
                break;
            case 'c':load();
                break;
            case 's':save();
                break;
            case 't':exit(0);
        }
    }
}

//inicializa a lista
void init_list(void)
{
    register int t;
    
    for(t=0;t<SIZE;t++) *stHospital[t].reg_nome='\0';
    //um nome de comprimento 0 significa vazio
}

//poe os nomes na lista
void enter(void)
{
    register int i;
    
    for(i=0; i<SIZE; i++)
        if(!*stHospital[i].reg_nome) break;
    
    if(i==SIZE){
        printf("lista cheia!\n");
        return;
    }
    
    printf("ID: ");
    scanf("%d",&stHospital[i].reg_id);
    
    getchar();
    printf("Nome: ");
    gets(stHospital[i].reg_nome);
    
    printf("Idade: ");
    scanf("%d", &stHospital[i].reg_idade);
    
    getchar();
    printf("Diagnostico: ");
    gets(stHospital[i].reg_diagnostico);
    
    printf("Tratamento: ");
    gets(stHospital[i].reg_tratamento);
    
}

//mostra a lista
void display(void)
{
    register int t;
    
    for(t=0;t<SIZE;t++) {
        if(*stHospital[t].reg_nome) {
            printf("%d\n",stHospital[t].reg_id);
            printf("%s\n",stHospital[t].reg_nome);
            printf("%d\n",stHospital[t].reg_idade);
            printf("%s\n",stHospital[t].reg_diagnostico);
            printf("%s\n",stHospital[t].reg_tratamento);
        }
    }
}

//salva a lista
void save(void)
{
    FILE *fp;
    register int i;
    
    if((fp=fopen("ListaHospital.dat","wb"))==NULL) {
        printf ("O arquivo nao pode ser aberto.\n");
        return;
    }
    
    for(i=0;i<SIZE;i++)
        if(*stHospital[i].reg_nome)
            if(fwrite(&stHospital[i],sizeof(struct registro), 1, fp)!=1)
                printf("Erro de escrita no arquivo.\n");
    fclose(fp);
}

//carrega o arquivo
void load(void)
{
    FILE *fp;
    register int i;
    
    if((fp=fopen("ListaHospital.dat","rb"))==NULL) {
        printf("O arquivo nao pode ser aberto.\n");
        return;
    }
    
    init_list();
    
    for(i=0;i<SIZE;i++)
        if(fread(&stHospital[i],sizeof(struct registro), 1, fp)!=1) {
            if(feof(fp)) break;
            printf("Erro de leitura no arquivo.\n");
        }
    
    fclose (fp);
}

//escolha do menu
char menu(void)
{
    char cEscolha;
    
    do{
        printf("[i]nserir\n");
        printf("[v]isualizar\n");
        printf("[c]arregar\n");
        printf("[s]alvar\n");
        printf("[t]erminar\n");
        printf("escolha: ");
        cEscolha=getchar();
    }while(cEscolha!='i' && cEscolha!='v' && cEscolha!='c' && cEscolha!='s' && cEscolha!='t');
    return cEscolha;
}


