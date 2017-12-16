#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Morador ou convidado
typedef struct{
	int cod;
	char nome[100];
	int rg;
	int casa;
	char rua[100];
	char telefone[20];
	int tipo;
	char data[20];
	char hora[20];
} Pessoa;

Pessoa * AbrirArquivo(int *numeroRegistros, int *capacidade);
void CadastroPessoa(Pessoa *registro, int *numeroRegistros, int *capacidade);
void EntradaConvidado(Pessoa *registro, int *numeroRegistros, int *capacidade);
void Salvar(Pessoa *registro, int numeroRegistros);
void ListarMoradores(Pessoa *registro, int numeroRegistros);
void ListarCadastros(Pessoa *registro, int numeroRegistros);
void PesquisarNomeMorador(Pessoa *registro, int numeroRegistros);
void PesquisarRgMorador(Pessoa *registro, int numeroRegistros);
void PesquisarRua(Pessoa *registro, int numeroRegistros);
void EditarMorador(Pessoa *registro, int numeroRegistros);
void ApagarMorador(Pessoa *registro, int *numeroRegistros);
void Relatorio(Pessoa *registro, int numeroRegistros);
//void SaidaConvidado(Pessoa *registro, int *numeroRegistros);

int main(void){

	system("title CONTROLE DE CONDOMINIO");

	Pessoa *registro;
	int capacidade, numeroRegistros;
	int opc;

	registro = AbrirArquivo(&numeroRegistros, &capacidade);

	//Menu de acesso
	do{
		printf("CONTROLE DE ACESSO AO CONDOMINIO\n\n");
		printf(" CADASTROS: \n");
		printf("	1. CADASTRO DE NOVO MORADOR\n");
		printf("	2. ENTRADA DE CONVIDADO(S)\n\n");
		printf(" CONSULTAS: \n");
		printf("	3. LISTAR CONVIDADOS\n");
		printf("	4. LISTAR MORADORES\n");
		printf("	5. PESQUISAR MORADOR POR NOME\n");
		printf("	6. PESQUISAR MORADOR POR RG\n");
		printf("	7. PESQUISAR MORADORES POR RUA\n");
		printf("	8. EDITAR MORADOR\n\n");
		printf(" SAIDAS: \n");
		//printf("	9. SAIDA DE CONVIDADO(S)\n");
		printf("	9. APAGAR MORADOR\n\n");
		printf(" RELATORIOS: \n");
		printf("	10. RELATORIO DE CONVIDADOS\n\n");
		printf(" 11. SALVAR\n");
		printf(" 12. SAIR\n\n");
		printf(">> ");
		scanf("%i", &opc);

		switch(opc){
			case 1:
				CadastroPessoa(registro, &numeroRegistros, &capacidade);
				break;
			case 2:
				EntradaConvidado(registro, &numeroRegistros, &capacidade);
				break;
			case 3:
				ListarCadastros(registro, numeroRegistros);
				break;
			case 4:
				ListarMoradores(registro, numeroRegistros);
				break;
			case 5:
				PesquisarNomeMorador(registro, numeroRegistros);
				break;
			case 6:
				PesquisarRgMorador(registro, numeroRegistros);
				break;
			case 7:
				PesquisarRua(registro, numeroRegistros);
				break;
			case 8:
				EditarMorador(registro, numeroRegistros);
				break;
			/*case 9:
				SaidaConvidado(registro, &numeroRegistros);
				break;*/
			case 9:
				ApagarMorador(registro, &numeroRegistros);
				break;
			case 10:
				Relatorio(registro, numeroRegistros);
				break;
			case 11:
				Salvar(registro, numeroRegistros);
				break;
		}

	}while(opc!=12);

	Salvar(registro, numeroRegistros);

	free(registro);

	return 0;
}

Pessoa *AbrirArquivo(int *numeroRegistros, int *capacidade){

	Pessoa *registro;

	FILE *arquivo = fopen("registros.txt", "r");

	if(arquivo == NULL){
		*capacidade = 10;
		*numeroRegistros = 0;

		registro = (Pessoa *) malloc(sizeof(Pessoa)*(*capacidade));
	}else{
		fread(numeroRegistros, sizeof(int), 1, arquivo);

		*capacidade = (*numeroRegistros)*2;

		registro = (Pessoa *)malloc(sizeof(Pessoa)*(*capacidade));

		fread(registro, sizeof(Pessoa), *numeroRegistros, arquivo);

		fclose(arquivo);
	}

	return registro;
}

void CadastroPessoa(Pessoa *registro, int *numeroRegistros, int *capacidade){

	system("cls");

	printf(" - CADASTRO DE MORADOR - \n\n");

	if(*numeroRegistros == *capacidade){
		*capacidade = *capacidade*2;
		registro = (Pessoa*)realloc(registro, sizeof(Pessoa)*(*capacidade));
	}

	fflush(stdin);

	int cod = *numeroRegistros;
	registro[*numeroRegistros].cod = cod;

	printf(" NOME: ");
	gets(registro[*numeroRegistros].nome);

	printf(" RG: ");
	scanf("%i", &registro[*numeroRegistros].rg);

	printf(" CASA: ");
	scanf("%i", &registro[*numeroRegistros].casa);

	fflush(stdin);
	printf(" RUA: ");
	gets(registro[*numeroRegistros].rua);
	
	fflush(stdin);
	printf(" TELEFONE: ");
	gets(registro[*numeroRegistros].telefone);

	registro[*numeroRegistros].tipo = 1;

	(*numeroRegistros)++;
	system("cls");

	printf("CADASTRO REALIZADO COM SUCESSO.");
	printf("\n\nPressione qualquer tecla para continuar...");
	getch();
	system("cls");
}

void EntradaConvidado(Pessoa *registro, int *numeroRegistros, int *capacidade){

	system("cls");

	printf(" - ENTRADA DE CONVIDADO - \n\n");

	if(*numeroRegistros == *capacidade){
		*capacidade = *capacidade*2;
		registro = (Pessoa*)realloc(registro, sizeof(Pessoa)*(*capacidade));
	}

	fflush(stdin);

	int cod = *numeroRegistros;
	registro[*numeroRegistros].cod = cod;

	printf(" NOME: ");
	gets(registro[*numeroRegistros].nome);

	printf(" RG: ");
	scanf("%i", &registro[*numeroRegistros].rg);
	
	//Casa a ser visitada
	printf(" CASA: ");
	scanf("%i", &registro[*numeroRegistros].casa);

	char data[20];
	char hora[20];

	_strdate(data);
	_strtime(hora);

	strcpy(registro[*numeroRegistros].data, data);
	strcpy(registro[*numeroRegistros].hora, hora);

	registro[*numeroRegistros].tipo = 2;

	(*numeroRegistros)++;
	system("cls");

}

void Salvar(Pessoa *registro, int numeroRegistros){
	system("cls");

	if(numeroRegistros > 0){

		FILE *file = fopen("registros.txt", "w");

		fwrite(&numeroRegistros, sizeof(int), 1, file);

		fwrite(registro, sizeof(Pessoa), numeroRegistros, file);

		fclose(file);

	}

}

void ListarCadastros(Pessoa *registro, int numeroRegistros){

	system("cls");

	printf(" - LISTA DE CONVIDADOS - \n");

	int i;

	for(i=0; i<numeroRegistros; i++){

		if(registro[i].tipo == 2)
			printf("\n%i. %s | %s %s | CASA %i | RG: %i", i+1, registro[i].nome, registro[i].data, registro[i].hora, registro[i].casa, registro[i].rg);

	}

	printf("\n-----------------------------\n");

	printf("\nPressione qualquer tecla para continuar...");
	getch();
	system("cls");

}

void ListarMoradores(Pessoa *registro, int numeroRegistros){

	system("cls");

	printf(" - LISTA DE MORADORES - \n");

	int i;

	for(i=0; i<numeroRegistros; i++){

		if(registro[i].tipo == 1)
			printf("\n%i. %s", i+1, registro[i].nome);

	}

	printf("\n-----------------------------\n");

	printf("\nPressione qualquer tecla para continuar...");
	getch();
	system("cls");

}

void PesquisarNomeMorador(Pessoa *registro, int numeroRegistros){

	system("cls");
	char nome[100];
	int i;

	fflush(stdin);
	printf("MORADOR: ");
	gets(nome);

	for(i=0; i<numeroRegistros; i++){

		if(strcmp(nome, registro[i].nome)==0){

			printf("\n\n --- %s --- \n", registro[i].nome);
			printf(" CODIGO: %i\n", registro[i].cod);
			printf(" RG: %i\n", registro[i].rg);
			printf(" CASA: %i\n", registro[i].casa);
			printf(" RUA: %s\n", registro[i].rua);
			printf(" TELEFONE: %s\n", registro[i].telefone);
			printf(" ------------------------ \n\n");
		}
	}

	printf("\nPressione qualquer tecla para continuar...");
	getch();
	system("cls");

}

void PesquisarRgMorador(Pessoa *registro, int numeroRegistros){

	system("cls");
	int rg, i;

	printf("RG-MORADOR: ");
	scanf("%i", &rg);

	for(i=0; i<numeroRegistros; i++){

		if(registro[i].rg == rg){

			printf("\n\n --- %s --- \n", registro[i].nome);
			printf(" CODIGO: %i\n", registro[i].cod);
			printf(" RG: %i\n", registro[i].rg);
			printf(" CASA: %i\n", registro[i].casa);
			printf(" RUA: %s\n", registro[i].rua);
			printf(" TELEFONE: %s\n", registro[i].telefone);
			printf(" ------------------------ \n\n");
		}
	}

	printf("\nPressione qualquer tecla para continuar...");
	getch();
	system("cls");

}

void PesquisarRua(Pessoa *registro, int numeroRegistros){

	system("cls");
	int i;
	char rua[100];

	fflush(stdin);
	printf("RUA: ");
	gets(rua);

	for(i=0; i<numeroRegistros; i++){

		if(strcmp(registro[i].rua, rua)==0){

			printf("\n\n --- %s --- \n", registro[i].nome);
			printf(" CODIGO: %i\n", registro[i].cod);
			printf(" RG: %i\n", registro[i].rg);
			printf(" CASA: %i\n", registro[i].casa);
			printf(" RUA: %s\n", registro[i].rua);
			printf(" TELEFONE: %s\n", registro[i].telefone);
			printf(" ------------------------ \n\n");
		}
	}

	printf("\nPressione qualquer tecla para continuar...");
	getch();
	system("cls");

}

void EditarMorador(Pessoa *registro, int numeroRegistros){

	system("cls");

	int i, rg, opc;
	int verificador=0;

	printf("RG-MORADOR: ");
	scanf("%i", &rg);

	for(i=0; i<numeroRegistros; i++){
		if(registro[i].rg == rg){
			verificador=1;

			do{
				printf("\n-->%s\n", registro[i].nome);

				printf("\nSELECIONE O QUE DESEJA EDITAR: \n");
				printf("\n 1. NOME");
				printf("\n 2. RG");
				printf("\n 3. CASA");
				printf("\n 4. RUA");
				printf("\n 5. TELEFONE");
				printf("\n6. VOLTAR\n");
				printf("\n>> ");
				scanf("%i", &opc);

				switch(opc){
					case 1:
						fflush(stdin);
						printf("\nNOME: ");
						gets(registro[i].nome);
						printf("Nome alterado");
						getch();
						system("cls");
						break;
					case 2:
						printf("\nRG: ");
						scanf("%i", &registro[i].rg);
						printf("RG alterado");
						getch();
						system("cls");
						break;
					case 3:
						printf("\nCASA: ");
						scanf("%i", &registro[i].casa);
						printf("Casa alterada");
						getch();
						system("cls");
						break;
					case 4:
						fflush(stdin);
						printf("\nRUA: ");
						gets(registro[i].rua);
						printf("Rua alterada");
						getch();
						system("cls");
						break;
					case 5:
						fflush(stdin);
						printf("\nTELEFONE: ");
						gets(registro[i].telefone);
						printf("Telefone alterado");
						getch();
						system("cls");
						break;
				}

			}while(opc!=6);
		}

	}

	if(verificador==0)
		printf("\nRG invalido.");


	printf("\nPressione qualquer tecla para continuar...");
	getch();
	system("cls");

	verificador=0;

}

/*void SaidaConvidado(Pessoa *registro, int *numeroRegistros){

	system("cls");

	int rg, i, j, opc;
	int verificador;

	fflush(stdin);
	printf("RG-CONVIDADO: ");
	scanf("%i", &rg);

	for(i=0; i< *numeroRegistros; i++){
		if(registro[i].rg == rg && registro[i].tipo==2){

			printf("\n--> %s", registro[i].nome);

			printf("\n\nVoce tem certeza?");
			printf("\n1. SIM");
			printf("\n2. NAO");
			printf("\n>> ");
			scanf("%i", &opc);

			if(opc==1){
				verificador=1;
				for(j=i; j<*numeroRegistros; j++)
					registro[j] = registro[j+1];

				(*numeroRegistros)--;
				i = *numeroRegistros;
			}
		}
	}

	if(verificador==1){
		system("cls");
		printf("\nSaida confirmada\n");
	}
	else if(opc!=1)
		system("cls");
	else{
		system("cls");
		printf("\nConvidado nao encontrado\n");
	}

	printf("\nPressione qualquer tecla para continuar...");
	getch();
	system("cls");

	verificador=0;

}*/

void ApagarMorador(Pessoa *registro, int *numeroRegistros){

	system("cls");

	int rg, i, j, opc;
	int verificador;

	fflush(stdin);
	printf("RG-CONVIDADO: ");
	scanf("%i", &rg);

	for(i=0; i< *numeroRegistros; i++){
		if(registro[i].rg == rg && registro[i].tipo==1){

			printf("\n--> %s", registro[i].nome);

			printf("\n\nVoce tem certeza?");
			printf("\n1. SIM");
			printf("\n2. NAO");
			printf("\n>> ");
			scanf("%i", &opc);

			if(opc==1){
				verificador=1;
				for(j=i; j<*numeroRegistros; j++)
					registro[j] = registro[j+1];

				(*numeroRegistros)--;
				i = *numeroRegistros;
			}
		}
	}

	if(verificador==1){
		system("cls");
		printf("\nSaida confirmada\n");
	}
	else if(opc!=1)
		system("cls");
	else{
		system("cls");
		printf("\nConvidado nao encontrado\n");
	}

	printf("\nPressione qualquer tecla para continuar...");
	getch();
	system("cls");

	verificador=0;

}

void Relatorio(Pessoa *registro, int numeroRegistros){
	
	system("cls");
	
	int i;
	
	
	FILE *relatorio;
	relatorio = fopen("Relatorio.html", "w");
	char *titulo, *data;
	
	data = __DATE__;
	titulo = "Relatorio de convidados";
	
	fprintf(relatorio, "<html><head><title>%s</title></head><body><style>header{text-align: center; height: 100px; border: 1px solid #000} table, th, td{text-align: center; border: 1px solid #000; border-collapse: collapse} th{font-family: sans-serif; height: 30px; background: #f5f5f5} h1, h3{font-family: sans-serif}</style>", titulo);
	fprintf(relatorio, "<header><h1>RELATORIO DE CONVIDADOS</h1><h3>%s</h3><br></header><center><table style='margin-top: 10px; width: 1080px;'><tr><th> * </th><th>NOME</th><th>CASA</th><th>RG</th><th>DATA</th><th>HORA</th></tr>", data);

	for(i=0; i<numeroRegistros; i++){
		if(registro[i].tipo==2)
			fprintf(relatorio, "<tr><td>%i</td><td>%s</td><td>%i</td><td>%i</td><td>%s</td><td>%s</td></tr>", i, registro[i].nome, registro[i].casa, registro[i].rg,registro[i].data, registro[i].hora);
	}

	fprintf(relatorio, "</table><br><hr><br></center></body></html>");
	fclose(relatorio);
	
	printf("Arquivo gerado na pasta raiz\n");
	printf("\nPressione qualquer tecla para continuar...");
	getch();
	system("cls");
}

