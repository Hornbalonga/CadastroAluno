#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<locale.h>
#include<malloc.h>

typedef struct 
{
	char Nome[7];
	char Turno[8];
	float Mensalidade;
}Cursos;

typedef struct {
	int matricula;
	char nome[50];
	int sexo;
	int idade;
	//int curso;
	//int turno;
	int cursos[2];
}Aluno;

Aluno aluno;

FILE *arquivo;

Aluno alunoNull;
                  
Cursos cursos[6];

void abreArquivo()
{
	arquivo = fopen("arquivo_alunos_matriculados.txt", "r+b");
	if (arquivo == NULL)
	{
		arquivo = fopen("arquivo_alunos_matriculados.txt", "w+b");
	}
}

void cadastraCursos()
{
	strcpy(cursos[0].Nome, "PHP");                   
	strcpy(cursos[0].Turno, "Manhã");
	cursos[0].Mensalidade = 210.00;
	
	strcpy(cursos[1].Nome, "PHP");                   
	strcpy(cursos[1].Turno, "Noite");
	cursos[1].Mensalidade = 260.00;
	
	strcpy(cursos[2].Nome, "Java");                   
	strcpy(cursos[2].Turno, "Manhã");
	cursos[2].Mensalidade = 320.00;
	
	strcpy(cursos[3].Nome, "Java");                   
	strcpy(cursos[3].Turno, "Noite");
	cursos[3].Mensalidade = 390.00;
	
	strcpy(cursos[4].Nome, "Python");                   
	strcpy(cursos[4].Turno, "Manhã");
	cursos[4].Mensalidade = 290.00;
	
	strcpy(cursos[5].Nome, "Python");                   
	strcpy(cursos[5].Turno, "Noite");
	cursos[5].Mensalidade = 310.00;
}

void cadastraAluno()
{
	int desejaCadastrarMais = -1;
	do
	{
		Aluno aluno;
		aluno.cursos[0] = -1;
		aluno.cursos[1] = -1;
		int pergCad;
		int alunoCadastrado = -1;

		do
		{
			printf("\t_________________________________________________________________\n");
			printf("\t |Digite a Matrícula: ");
			scanf("%d", &aluno.matricula);
			
			alunoCadastrado = procurarAluno(aluno.matricula);//respostas possíveis -1 quando não encontra, ou >=0 para todos que encontrar. 
			if ((alunoCadastrado != -1) && (aluno.matricula > 0))
			{
				printf("Aluno(a) já cadastrado(a), deseja editar? 1 = Sim: | 0 = Não: ");
				scanf("%d", &pergCad);
				
				if (pergCad == 1)
				{
					editarAluno();
				
				}
			}
			else if (aluno.matricula <= 0)
			{
				printf("\nMatrícula Inválida!\n");
				alunoCadastrado = 0;
			}
		
		}while(alunoCadastrado != -1);
		
		
		printf("\t_______________________________________________________________|_\n");
		printf("\t |Digite o Nome: ");
		fflush(stdin);
		gets(&aluno.nome);
		
		do
		{
			printf("\t_______________________________________________________________|_\n");
			printf("\t |Digite o Sexo| 1 = Fem: | 2 = Masc: | 3 = Outro: ");
			scanf("%d", &aluno.sexo);
			
			if(aluno.sexo < 1 || aluno.sexo > 3)
			{
				printf("\nOpção de sexo inválida:\n");
			} 
		}while(aluno.sexo < 1 || aluno.sexo > 3);
		
		printf("\t_______________________________________________________________|_\n");
		printf("\t |Digite a Idade: ");
		scanf("%d", &aluno.idade);
		
		int numCursos = 1;
		int maisUm = 0;
		int curso = 0;
		int turno = 0;
		
		do
		{
			do
			{
				printf("O aluno(a) pode ser cadastrado em até dois cursos!\n");
				printf("\t_______________________________________________________________|_\n");
				printf("\t |Digite o Curso| 1 = PHP: | 2 = Java: | 3 = Python: ");
				scanf("%d", &curso);
				
				if(curso < 1 || curso > 3)
				{
					printf("\nOpção de curso inválida:\n");
				}
				else
				{
					if (numCursos == 2)
					{
						int c0 = retornaCursoOuTurno(aluno.cursos[0], 1);//curso casa 0
	
						if (curso == c0)
						{
							printf("\nAluno já matriculado neste curso\n");
							curso = 0;
						}
					}
				}
								
			}while(curso < 1 || curso > 3);
			
			do
			{
				printf("\t_______________________________________________________________|_\n");
				printf("\t |Digite o Turno| 1 = Manhã | 2 = Noite: ");
				scanf("%d", &turno);
				
				if(turno < 1 || turno > 2)
				{
					printf("\nOpção de turno inválida:\n");
				}
				else
				{
					if (numCursos == 2)
					{
						int t0 = retornaCursoOuTurno(aluno.cursos[0], 2);//curso casa 0
	
						if (turno == t0)
						{
							printf("\nAluno(a) já matriculado(a) neste turno\n");
							turno = 0;
						}
					}
				}
				
			}while(turno < 1 || turno > 2);
			
			int indiceCurso = pegarCursosCadastrados(curso, turno);//retorna valores possíveis 0-1-2-3-4-5
			printf("\n%s\t%s\t%.2f\n", cursos[indiceCurso].Nome, cursos[indiceCurso].Turno, cursos[indiceCurso].Mensalidade);
			aluno.cursos[numCursos - 1] = indiceCurso;
			
			maisUm = -1;
			
			if (numCursos < 2)
			{
				printf("\nAluno(a) já matriculado em %d curso(s)\n", numCursos);
				printf("Deseja cadastrar outro curso? 1 = sim | 0 = não\n ");
				scanf("%d", &maisUm);
			}
			else
			{
				maisUm = 0;
			}
			
			if (maisUm == 1)
			{
				numCursos++;
			}
			
		}while(maisUm != 0);
		
		fseek(arquivo, 0, SEEK_END);
		fwrite(&aluno, sizeof(Aluno), 1, arquivo);
		
		do
		{
			printf("\nDeseja Cadastrar outro Aluno(a)? | 1 = Sim | 0 = Não\n");
			scanf("%d", &desejaCadastrarMais);
			
			if (desejaCadastrarMais < 0 || desejaCadastrarMais > 1)
			{
				printf("Opção Inválida\n");
			}
		
		}while(desejaCadastrarMais < 0 || desejaCadastrarMais > 1);
	
		
	}while(desejaCadastrarMais == 1);
			
}

int pegarCursosCadastrados(int curso, int turno)//retorna indices entre 0 e 5
{
	int c = -1;//era 0

	if (curso == 1)
	{
	    c = 0;
	
	    if (turno == 2)
	    {
	        c = 1;
	    }
	}
	else if (curso == 2)
	{
	    c = 2;
	
	    if (turno == 2)
	    {
	        c = 3;
	    }
	}
	else if (curso == 3)
	{
	    c = 4;
	
	    if (turno == 2)
	    {
	        c = 5;
	    }
	}
	
	return c;
}

int retornaCursoOuTurno(int indice, int tipo)//retorna os cursos 1, 2 ou 3 ou o turno 1 ou 2
{
	int curso = -1;
	int turno = -1;
	
	switch(indice)
	{
		case 0:
			curso = 1;
			turno = 1;
			break;
		case 1:
			curso = 1;
			turno = 2;
			break;
		case 2:
			curso = 2;
			turno = 1;
			break;
		case 3:
			curso = 2;
			turno = 2;
			break;
		case 4:
			curso = 3;
			turno = 1;
			break;
		case 5:
			curso = 3;
			turno = 2;
			break;
	}
	
	if (tipo == 1)
	{
		return curso;
	}
	else if (tipo == 2)
	{
		return turno;
	}
	
}

void listagemGeral()
{
	Aluno aluno;
	int i;
	rewind(arquivo);
	fread(&aluno, sizeof(Aluno), 1, arquivo);
	printf("\n%9s%50s%5s%6s%30s%12s\n","Matrícula","Nome do Aluno(a)","Sexo","Idade","Cursos     e Turno","Mensalidade");
	
	while (feof(arquivo) ==0)
	{	
		if (aluno.matricula > 0)
		{
			char nomeCursos[84];
			float totalValorMatricula = 0;
			int numCursos = 0;
		

			for (i = 0; i < 2; i++)
			{
				if (aluno.cursos[i] != -1)
				{
					Cursos curso = cursos[aluno.cursos[i]];
					totalValorMatricula = totalValorMatricula + curso.Mensalidade;
					numCursos++;
			
					if (i == 0)
				    {
						strcpy(nomeCursos, curso.Nome);
						strcat(nomeCursos, " (");
						strcat(nomeCursos, curso.Turno);
						strcat(nomeCursos, ")");
				    }
				    else
				    {
						strcat(nomeCursos, " / ");//concatenar strings
						strcat(nomeCursos, curso.Nome);
						strcat(nomeCursos, " (");
						strcat(nomeCursos, curso.Turno);
						strcat(nomeCursos, ")");	
					}	
				}	
			}
			
			char sexo = 'F'; 
			if (aluno.sexo == 2)
			{
				sexo = 'M';
			}
			else if (aluno.sexo == 3)
			{
				sexo = 'O';
			}
			
			if (numCursos > 1)
			{
				totalValorMatricula = totalValorMatricula * 0.70; //desconto de 30%
			}
			else if (aluno.idade >= 45)
			{
				totalValorMatricula = totalValorMatricula * 0.85; //desconto de 15%
			}
			printf("%9d%50s%5c%6d%30s R$%9.2f\n", aluno.matricula, aluno.nome, sexo, aluno.idade, nomeCursos, totalValorMatricula);
		}
		
		fread(&aluno, sizeof(Aluno), 1, arquivo);
	}
	
	getche();
}

/*int contaTamanhoCursos()
{
	Aluno aluno;
	
	rewind(arquivo);
	fread(&aluno, sizeof(Aluno), 1, arquivo);
	
	int tamanho =  0;
	
	while (feof(arquivo)==0)
	{
		
		if (aluno.matricula!= 0)
		{
			tamanho++;
		}
		
		fread(&aluno, sizeof(Aluno), 1, arquivo);
	}
	
	return tamanho;
}*/

int procurarAluno(int matricula)//retorna valores possíveis -1 (quando não encontra) ou todos os outros números >= zero.
{
	int indice = 0;
	Aluno aluno;
	
	rewind(arquivo);
	fread(&aluno, sizeof(Aluno), 1, arquivo);
	
	while (feof(arquivo)==0)
	{
		if (aluno.matricula== matricula)
		{
			return indice;
		}
		else
		{
			fread(&aluno, sizeof(Aluno), 1, arquivo);
			indice++;
		}	
	}
	return -1;
}

Aluno mostrarAlunoantesdeEditar(int indice)
{
	//Aluno aluno;
	fseek(arquivo, indice * sizeof(Aluno), SEEK_SET);
	fread(&aluno, sizeof(Aluno), 1, arquivo);
	printf("\n\n");
	printf("%d\t%d\t%s\t%d\t%d\n", indice, aluno.matricula, aluno.nome, aluno.sexo, aluno.idade);//aluno.curso, aluno.turno
	return aluno;
}

void editarAluno()
{
	int matricula;
	int i;
	int editar = -1;
	int sexo = 0;
	int curso = 0;
	int turno = 0;
	int indiceCurso = -1;
	int confirma = 0;
	
	do
	{
		printf("Informe a Matrícula para localizar o cadastro: ");
		scanf("%d", &matricula);
		
		int indice = procurarAluno(matricula);
		
		if ((indice != -1) && (matricula != 0))
		{
			aluno = mostrarAlunoantesdeEditar(indice);
			
			do
			{
				printf("\nO que você deseja editar? \n\n");
				printf("\t1 - Matrícula: \n");
				printf("\t2 - Nome: \n");
				printf("\t3 - Sexo: \n");
				printf("\t4 - Idade: \n");
				printf("\t5 - Curso: \n");
				printf("\t6 - Turno: \n");
				printf("\t7 - Excluir Curso e Turno: \n");
				printf("\t0 - Sair: \n");
				scanf("%d", &editar);
				
				switch(editar)
				{
					case 1:
						printf("Informe a matrícula: ");
						scanf("%d", &matricula);
						
						if (procurarAluno(matricula) == -1)
						{
							aluno.matricula = matricula;
						}
						else
						{
							printf("Matrícula já existe! ");//melhorar o texto
						}
						
						break;
					case 2:
						printf("Informe o Nome: \n");
						fflush(stdin);
						gets(&aluno.nome);
						break;
					case 3:
						printf("Informe o Sexo = 1 Fem: | 2 = Masc: | 3 = Outros: ");
						scanf("%d", &sexo);
						
						if (sexo == 1 || sexo == 2 || sexo == 3)
						{
							aluno.sexo = sexo;
						}
						else
						{
							printf("Sexo Inválido\n");
						}
						break;
					case 4:
						printf("Informe a nova idade: ");
						scanf("%d", &aluno.idade);
						break;
					case 5:
						for(i = 0; i < 2; i++)
						{
							printf("%d\t%s\t\t\t%s\tR$ %.2f\n", i+1, cursos[aluno.cursos[i]].Nome, cursos[aluno.cursos[i]].Turno, cursos[aluno.cursos[i]].Mensalidade);
						}
						printf("Escolha o curso que deseja editar: \n");
						scanf("%d", &indiceCurso);
						
						if (indiceCurso < 1 || indiceCurso > 2)
						{
							printf("Indice inválido");
						}
						else
						{
							int c0 = retornaCursoOuTurno(aluno.cursos[0], 1);//curso casa 0
							int c1 = retornaCursoOuTurno(aluno.cursos[1], 1);//curso casa 1
							
							do
							{
								//printf("Informe o curso que pretende editar!\n");
								printf("\t_______________________________________________________________|_\n");
								printf("\t |Digite o Curso| 1 = PHP | 2 = Java | 3 = Python: ");
								scanf("%d", &curso);
								
								if(curso < 1 || curso > 3)
								{
									printf("\nOpção de curso inválida:\n");
								}
								else
								{
									if ((curso == c0) || (curso == c1))
									{
										printf("\nAluno já matriculado neste curso\n");
										curso = 0;
									}
									else
									{
										turno = retornaCursoOuTurno(aluno.cursos[indiceCurso - 1], 2);
										aluno.cursos[indiceCurso - 1] = pegarCursosCadastrados(curso, turno);
									}
								}
										
							}while(curso < 1 || curso > 3);
						}
						//não vai conter break para que o turno seja editado também.
					case 6:
						if (indiceCurso == -1)
						{
							for(i = 0; i < 2; i++)
							{
								printf("%d\t%s\t\t\t%s\tR$ %.2f\n", i+1, cursos[aluno.cursos[i]].Nome, cursos[aluno.cursos[i]].Turno, cursos[aluno.cursos[i]].Mensalidade);
							}
							printf("Escolha o turno que deseja editar: \n");
							scanf("%d", &indiceCurso);
						}
						
						if (indiceCurso < 1 || indiceCurso > 2)
						{
							printf("Indice inválido");
						}
						else
						{
							int t0 = retornaCursoOuTurno(aluno.cursos[0], 2);//turno da casa do curso 0
							int t1 = retornaCursoOuTurno(aluno.cursos[1], 2);//turno da casa do curso 1
							
							do
							{
								printf("Informe o Turno: | 1 = Manhã: | 2 = Noite: ");
								scanf("%d", &turno);
								
								if (turno < 1 || turno > 2)
								{
									printf("\nOpção de turno inválida:\n");
								}
								else
								{
									if ((turno == t0) || (turno == t1))
									{
										printf("\nAluno já matriculado neste turno\n");
										turno = 0;
									}
									else
									{
										curso = retornaCursoOuTurno(aluno.cursos[indiceCurso - 1], 1);
										aluno.cursos[indiceCurso - 1] = pegarCursosCadastrados(curso, turno);
									}
								}
								
							}while(turno < 1 || turno > 2);
						}
	
						break;
					case 7:
						for(i = 0; i < 2; i++)
						{
							printf("%d\t%s\t\t\t%s\tR$ %.2f\n", i+1, cursos[aluno.cursos[i]].Nome, cursos[aluno.cursos[i]].Turno, cursos[aluno.cursos[i]].Mensalidade);
						}
						printf("Escolha o curso que deseja excluir: \n");
						scanf("%d", &indiceCurso);
						
						if (indiceCurso < 1 || indiceCurso > 2)
						{
							printf("Indice inválido");
						}
						else
						{
							aluno.cursos[indiceCurso - 1] = - 1;
						}
						break;
						
				}
		
			}while(editar != 0);
			
			fseek(arquivo, indice * sizeof(Aluno), SEEK_SET);
			fwrite(&aluno, sizeof(Aluno), 1, arquivo);
			
			aluno = mostrarAlunoantesdeEditar(indice);
		}
		else
		{
			printf("\nRegistro não encontrado!\n");
		}
		
		do
		{
			printf("\nDeseja realizar outra pesquisa?| 1 = Sim | 0 = Não:\n");
			scanf("%d", &confirma);
		
		}while(confirma < 0 || confirma > 1);
		
	}while(confirma == 1);
	
}

void excluirAluno()
{
	int confirma = -1;
	do
	{
		int matricula;
		int excluir = -1;
		Aluno aluno;
		confirma = -1;
		
		printf("Informe a Matrícula para localizar o cadastro: ");
		scanf("%d", &matricula);
		
		int indice = procurarAluno(matricula);
		
		if ((indice != -1) && (matricula !=0))
		{
			mostrarAlunoantesdeEditar(indice);
			
			printf("Tem certeza que deseja excluir este cadastro? sim = 1 | não = 0: ");
			scanf("%d", &excluir);
			
			if (excluir == 1)
			{
				fseek(arquivo, indice * sizeof(Aluno), SEEK_SET);
				fwrite(&alunoNull, sizeof(Aluno), 1, arquivo);
				printf("Exclusão realizada!\n");
			}
			else
			{
				printf("Exclusão não realizada!\n");
			}
		
		}
		else
		{
			do
			{
				printf("Aluno(a) não encontrado, deseja fazer outra pesquisa?| 1 = Sim | 0 = Não\n");
				scanf("%d", &confirma);
			}while(confirma < 0 || confirma > 1);
		}
	}while(confirma == 1);
	
}

void listarFiltro(int tipodeFiltro, int filtro)
{  
    Aluno aluno;
    int i;
    
	rewind(arquivo);
	fread(&aluno, sizeof(Aluno), 1, arquivo);
	printf("%9s%50s%5s%6s%30s%12s\n","Matrícula","Nome do Aluno(a)","Sexo","Idade","Cursos     e Turno","Mensalidade");
	
	while (feof(arquivo)==0)
	{
		if (aluno.matricula!= 0)
		{
			if (((aluno.sexo == filtro) && (tipodeFiltro == 1)) || ((tipodeFiltro == 2)))
			{
				int possuiCurso = 0;
				char nomeCursos[84];
				float totalValorMatricula = 0;
				int numCursos = 0;
			
				for (i = 0; i < 2; i++)
				{
					if (aluno.cursos[i] != -1)
					{
						Cursos curso = cursos[aluno.cursos[i]];
						totalValorMatricula = totalValorMatricula + curso.Mensalidade;
						numCursos++;
						
						if (((pegarCursosCadastrados(filtro, 1) == aluno.cursos[i]) || (pegarCursosCadastrados(filtro, 2) == aluno.cursos[i])) && (tipodeFiltro == 2))
						{
							possuiCurso++;
						}
						
						if (i == 0)
					    {
							strcpy(nomeCursos, curso.Nome);
							strcat(nomeCursos, " (");
							strcat(nomeCursos, curso.Turno);
							strcat(nomeCursos, ")");
					    }
					    else
					    {
							strcat(nomeCursos, " / ");
							strcat(nomeCursos, curso.Nome);
							strcat(nomeCursos, " (");
							strcat(nomeCursos, curso.Turno);
							strcat(nomeCursos, ")");	
						}	
					}	
				}
				
				char sexo = 'F'; 
				if (aluno.sexo == 2)
				{
					sexo = 'M';
				}
				else if (aluno.sexo == 3)
				{
					sexo = 'O';
				}
				
				if (numCursos > 1)
				{
					totalValorMatricula = totalValorMatricula * 0.70; //desconto de 30%
				}
				else if (aluno.idade >= 45)
				{
					totalValorMatricula = totalValorMatricula * 0.85; //desconto de 15%
				}
				
				if ((possuiCurso > 0 ) || (tipodeFiltro == 1))
				{
			    	printf("%9d%50s%5c%6d%30s R$%9.2f\n", aluno.matricula, aluno.nome, sexo, aluno.idade, nomeCursos, totalValorMatricula);
				}
			}
		}
		
		fread(&aluno, sizeof(Aluno), 1, arquivo);
	}
}

void listagemPorSexo()
{
	int sexo;
	do
	{
		printf("\nEscolha o Sexo que deseja listar: 1 = Fem: | 2 = Masc: | 3 = Outros: |0 = Sair: \n");
		scanf("%d", &sexo);
		
		if (sexo == 1 || sexo == 2 || sexo == 3)
		{
			listarFiltro(1, sexo);
		}
		else if (sexo != 0)
		{
			printf("\nSexo Inválido!\n");
		}
		
		getche();
		
	}while(sexo != 0);
	
}

void listagemPorCurso()
{
	int curso;
	do
	{
		printf("\nEscolha o Curso que deseja listar: 1 = PHP: | 2 = Java: | 3 = Python: | 0 = Sair:\n");
		scanf("%d", &curso);
		
		if (curso == 1 || curso == 2 || curso == 3)
		{
			listarFiltro(2, curso);
			printf("\nAperte qualquer tecla para continuar: !\n");

		}
		else if(curso != 0)
		{
			printf("\nCurso Inválido!\n");
		}
		
		getche();
		
	}while(curso !=0);
	
}


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	abreArquivo();
	cadastraCursos();
	
	int menu;
	
	do{

		printf("\t\t\t_________________________________\n");
		printf("\t\t\t |          TI CURSOS          |\n");
		printf("\t\t\t_|_____________________________|_\n");
		printf("\t\t\t |                             |\n");
		printf("\t\t\t |1 - Cadastro Aluno           |\n");
		printf("\t\t\t |2 - Editar Aluno             |\n"); 
		printf("\t\t\t |3 - Remover Aluno            |\n");
		printf("\t\t\t |4 - Listagem Geral           |\n");
		printf("\t\t\t |5 - Listagem por Curso       |\n");
		printf("\t\t\t |6 - Listagem por Sexo        |\n");
		printf("\t\t\t |0 - Sair                     |\n");
		printf("\t\t\t_|_____________________________|_\n");
		printf("\t\t\t     Escolha uma das opções: ");
		scanf("%d", &menu);
		
		switch(menu)
		{
			case 1:
				cadastraAluno();
				break;
		    case 2:
		    	editarAluno();
				break;
			case 3:
				excluirAluno();
				break;
			case 4:
				listagemGeral();
				break;
			case 5:
				listagemPorCurso();
				break;
			case 6:
				listagemPorSexo();
				break;
			case 0:
				fclose(arquivo);
				break;	
			default:
				printf("Opção Inválida!");
				break;
		}
	system("pause");
	system("cls");
    }while (menu != 0);
    
    
    
    
    
	return 0;
}

