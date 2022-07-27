#include<stdio.h>
#include<stdlib.h>
#include<string.h>
bool SimbolosEspeciais(char);
bool Letras(char );
bool Digitos(char );
bool PalavrasReservadas(char []);
void Proximo(int* , char[] , char*, char*);

bool SimbolosEspeciais(char c){
	if(c == 44 || c == 58 || c == 59 || c == 42 || c == 61 || c == 40 || c == 41 || c == 60 || c == 62 || c == 46 || c == 43 || c == 45)
		return true;
	else 
		return false;		
}

bool Letras(char s){
	if((s<=90 && s>=65) || (s>=97 && s<=122))
		return true;
	else
		return false;
}
	
bool Digitos(char s){
	if(s>=48 && s<=57)
		return true;
	else 
		return false;
}

bool PalavrasReservadas(char c[100]){
	if (strcmp(c,"PROGRAM ") == 0 || strcmp(c,"VAR ") == 0 ||  strcmp(c,"INTEGER ") == 0 || strcmp(c,"PROCEDURE ") == 0 || strcmp(c,"BEGIN ") == 0 || strcmp(c,"IF ") == 0 || strcmp(c,"DIV ") == 0 || strcmp(c,"THEN ") == 0 || strcmp(c,"ELSE ") == 0 || strcmp(c,"END ") == 0 || strcmp(c,"READ ") == 0 || strcmp(c,"WHILE ") == 0 || strcmp(c,"DO ") == 0 || strcmp(c,"WRITE ") == 0)
		return true;
	else
		return false;
}
//funcao principal
int main(){
	char proximo, s, leitor[10000], simbolo[100], atomo[100] ,ch[100];
	int i = 0, linha = 1, j, k, Erro1=0, Erro2=0, linhaErro1[100], linhaErro2[100] , dezenas = 1;
	FILE *entrada;
	FILE *saida;
//abertura de arquivos	
	entrada = fopen("Trab1_Compiladores.txt" , "r");
	if(entrada == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
	}
	saida = fopen("Programa_Analisado.txt" , "w");
//colocando o txt num vetor	
	while ((s = getc(entrada)) != EOF){
		 leitor[i] = s;
		 i++;	
	};
	i=0;
	j=0;
	putc('1', saida);
//processando dados e colocando simbolos numa matriz
	while(leitor[i-1] != 46){
		s = leitor[i];
		proximo = leitor[i+1];		
		printf("%c", s);
		if(s == '\n'){
			putc(s,saida);
			linha++;
			itoa(linha, ch, 10);
			for(dezenas = 0; Digitos(ch[dezenas]);dezenas++)
			putc(ch[dezenas], saida);	
		}
		//Caso seja uma sentença;
		if(Letras(s)){
			putc(32,saida);
			atomo[0] = s;
			j=1;					
			while(Letras(proximo) || Digitos(proximo)){
				atomo[j] = proximo;
				j++;			
				i++;
				s = leitor[i];
				proximo = leitor[i+1];
				printf("%c", s);
				if(proximo == 32 || proximo == '\n'){
					break;
				}
			}
			atomo[j] = 32;
			//maisculo
			for(j =0; atomo[j] != 32; j++){
				if(atomo[j]<=122 && atomo[j]>=97)
			atomo[j] = atomo[j] - 32;
			}	
			k=j;
			//limpeza		
			for(j = 100; j>k; j--){
				atomo[j] = '\0';
			}			
			//checando se é palavra reservada
			if(PalavrasReservadas(atomo)){
				strcpy(simbolo ,"C_");
				strcat(simbolo, atomo);
			}
			else{
			//atribuindo identificador
			strcpy(simbolo ,"ID_");
			strcat(simbolo, atomo);			
			}
			for(j=0 ;simbolo[j] != 32; j++)
				putc(simbolo[j], saida);
			atomo[0] = '\0';

		}
		else{
		//caso seja um digito
			if(Digitos(s)){
				atomo[0] = s;
				j=1;
				while(Digitos(proximo)){
					atomo[j] = proximo;
					j++;				
					i++;
					s = leitor[i];
					proximo = leitor[i+1];
					if(proximo == 32 || proximo == '\n')
							break;						
					}
				//se for um digito mal formado(digito com letras ou simbolos no meio)			
				if(Letras(proximo)){
					linhaErro2[Erro2] = linha;
					Erro2++;	
				}
				atomo[j] = 32;	
				for(j=0; atomo[j] != 32; j++)
					putc(atomo[j],saida);
			}
			//caso seja um simbolo especial
			else{
				if(SimbolosEspeciais(s))
					putc(s,saida);	
				if(s == 32)
					putc(s,saida);
				//caso seja um caracter desconhecido	
				else{
					if(s>32 && !SimbolosEspeciais(s)){
						linhaErro1[Erro1] = linha;
						Erro1++;	
					}				
				}
			} 
		}				
	i++;
	}
	//mostrando os erros
	strcpy(atomo,"\nERRO! Simbolo desconhecido | LINHA: X");	
	for(j = 0; j < Erro1; j++){
		for(i=0;atomo[i] != 88; i++)
			putc(atomo[i], saida);
		itoa(linhaErro1[j], ch, 10);
		for(dezenas = 0; Digitos(ch[dezenas]);dezenas++)
			putc(ch[dezenas], saida);
	}
			
	strcpy(atomo,"\nERRO! Numero mal formado| LINHA: X");
	for(j = 0; j < Erro2; j++){
		for(i=0;atomo[i] != 88;i++)
			putc(atomo[i], saida);
		itoa(linhaErro2[j], ch, 10);
		for(dezenas = 0; Digitos(ch[dezenas]);dezenas++)
			putc(ch[dezenas], saida);
	}
	
	
	fclose(entrada);
	fclose(saida);
}
