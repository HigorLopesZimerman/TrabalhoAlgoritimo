#include <iostream>
#include <conio.h>
#include <cstring>
#include <cctype>
#include <locale.h>
#include <cstdlib>
#include <sstream>

using namespace std;


struct Cidades{
	int cod;
	char nome[30];
	char uf[4];
};

struct Racas{
	int cod;
	char desc[100];
};

struct Animais{
	int cod;
	char nome[30];
	int codRaca;
	int idade;
	float peso;
	int codTutor;	
};

struct Tutores{
	int cod;
	char nome[30];
	char cpf[12];
	char endereco[30];
	int codCidade;
};

struct Veterinarios{
	int cod;
	char nome[30];
	char endereco[30];
	int codCidade;
};

struct Data{
	int dia;
	int mes;
	int ano;
};

struct Consultas{
	int cod;
	int codAnimal;
	int codVet;
	Data dataConsulta;
	float valor;
};

//VALIDAR CPF
bool cpfValido(char cpf[]){
	int i, j, digito1 = 0, digito2 = 0;
	
	if(strlen(cpf) != 11)
		return false;
	for(int i = 0; i<10;i++){
		if(!isdigit(cpf[i]))
		return false;
	}
	
	if (strcmp(cpf, "00000000000") == 0 || strcmp(cpf, "11111111111") == 0 ||
        strcmp(cpf, "22222222222") == 0 || strcmp(cpf, "33333333333") == 0 ||
        strcmp(cpf, "44444444444") == 0 || strcmp(cpf, "55555555555") == 0 ||
        strcmp(cpf, "66666666666") == 0 || strcmp(cpf, "77777777777") == 0 ||
        strcmp(cpf, "88888888888") == 0 || strcmp(cpf, "99999999999") == 0) {
        return false;
    }
    
    for (i = 0, j = 10; i < 9; i++, j--) {
        digito1 += (cpf[i] - '0') * j;
    }
	
	digito1 = digito1 % 11;
	if(digito1 < 2)
		digito1 = 0;
	else
		digito1 = 11 - digito1;
		
	if((cpf[9] - '0') != digito1)
		return false;
		
	
	for (i = 0, j = 11; i < 10; i++, j--) {
        digito2 += (cpf[i] - '0') * j;
    }
    
    digito2 = digito2 % 11;
    if(digito2 < 2)
		digito2 = 0;
	else
		digito2 = 11 - digito2;
		
	if((cpf[10] - '0') != digito2)
		return false;
	
	return true;
}

//FNÇÕES PARA SAIR DO CADASTRO/CONSULTA

bool lerIntComSaida(const char* mensagem, int &destino) {
    string entrada;
    cout << mensagem;
    cin >> entrada;

    if (entrada == "sair" || entrada == "SAIR" || entrada == "-1") {
        cout << "Cadastro cancelado. Voltando ao menu...\n";
        return false;
    }

    stringstream ss(entrada);
    char resto;
    
	if(!(ss >> destino) || (ss >> resto)){
		cout << "Entrada inválida. Digite apenas números. \n";
		return false;
	}
    return true;
}

bool lerFloatComSaida(const char* mensagem, float &destino) {
    string entrada;
    cout << mensagem;
    cin >> entrada;

    if (entrada == "sair" || entrada == "SAIR" || entrada == "-1") {
        cout << "Cadastro cancelado. Voltando ao menu...\n";
        return false;
    }

    stringstream ss(entrada);
    char resto;
    
	if(!(ss >> destino) || (ss >> resto)){
		cout << "Entrada inválida. Digite apenas números. \n";
		return false;
	}
    return true;
}

bool lerLinhaComSaida(const char* mensagem, char destino[], int tamanho) {
    string entrada;
    cout << mensagem;
    cin.ignore();
    getline(cin, entrada);

    if (entrada == "sair" || entrada == "SAIR" || entrada == "-1" || entrada == "sa" || entrada == "SA")  {
        return false;
    }

    strncpy(destino, entrada.c_str(), tamanho);
    return true;
}



//EXIBIR CONSULTAR POR PERIODO POR VETERINÁRIO

void exibirConsultasVet(Consultas consultas[], int qtdConsultas, Animais animais[], int qtdAnimais, Veterinarios veterinarios[], int qtdVet){
	
	system("cls");
	
	int codVet;
    Data inicio, fim;
    float total = 0;

	cout << "\n -- Digite (sair / -1) para voltar ao menu --  ";
    if (!lerIntComSaida("\nInforme o código do veterinário: ", codVet)) return;

    bool encontrado = false;
    for (int i = 0; i < qtdVet; i++) {
        if (veterinarios[i].cod == codVet) {
            cout << "Veterinário encontrado - " << veterinarios[i].nome << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "Veterinário não encontrado. Verifique o código.\n\n";
        return;
    }

    cout << "Informe a data inicial (dia mes ano): ";
    cin >> inicio.dia >> inicio.mes >> inicio.ano;

    cout << "Informe a data final (dia mes ano): ";
    cin >> fim.dia >> fim.mes >> fim.ano;

    cout << "\nConsultas no período informado para o veterinário:\n";

    const char* nomeVet = "Desconhecido";
    for (int i = 0; i < qtdVet; i++) {
        if (veterinarios[i].cod == codVet) {
            nomeVet = veterinarios[i].nome;
            break;
        }
    }

    for (int i = 0; i < qtdConsultas; i++) {
        Data x = consultas[i].dataConsulta;

        if (consultas[i].codVet != codVet)
            continue;

        bool dentroIntervalo =
            (x.ano > inicio.ano || (x.ano == inicio.ano && x.mes > inicio.mes) || (x.ano == inicio.ano && x.mes == inicio.mes && x.dia >= inicio.dia)) &&
            (x.ano < fim.ano || (x.ano == fim.ano && x.mes < fim.mes) || (x.ano == fim.ano && x.mes == fim.mes && x.dia <= fim.dia));

        if (dentroIntervalo) {
            const char* nomeAnimal = "Desconhecido";
            for (int j = 0; j < qtdAnimais; j++) {
                if (animais[j].cod == consultas[i].codAnimal) {
                    nomeAnimal = animais[j].nome;
                    break;
                }
            }

            cout << "\n------------------------";
            cout << "\nAnimal: " << nomeAnimal;
            cout << "\nVeterinário: " << nomeVet;
            cout << "\nData: " << x.dia << "/" << x.mes << "/" << x.ano;
            cout << "\nValor: R$" << consultas[i].valor;
            cout << "\n------------------------";

            total += consultas[i].valor;
        }
    }

    cout << "\n\nTotal em consultas no período: R$" << total << endl;
}


//EXIBIR CONSULTAR POR PERIODO

void exibirConsultas(Consultas consultas[], int qtdConsultas, Animais animais[], int qtdAnimais, Veterinarios veterinarios[], int qtdVet){
	
	system("cls");
	
	Data inicio, fim;
	float total = 0;
	
	
	
	cout << "Informe a data inicial (dia mes ano): ";
    cin >> inicio.dia >> inicio.mes >> inicio.ano;

    cout << "Informe a data final (dia mes ano): ";
    cin >> fim.dia >> fim.mes >> fim.ano;
    
    cout << "\nConsultas no período informado:\n";
    
    for(int i=0; i<qtdConsultas; i++){
    	Data x = consultas[i].dataConsulta;
    	
    	bool dentroIntervalo =
		 	(x.ano > inicio.ano || (x.ano == inicio.ano && x.mes > inicio.mes) || (x.ano == inicio.ano && x.mes == inicio.mes && x.dia >= inicio.dia)) &&
    		(x.ano < fim.ano || (x.ano == fim.ano && x.mes < fim.mes) || (x.ano == fim.ano && x.mes == fim.mes && x.dia <= fim.dia));
    		
    		if(dentroIntervalo){
    			const char* nomeAnimal = "Desconhecido";
    			for(int j=0; j<qtdAnimais; j++){
    				if(animais[j].cod == consultas[i].codAnimal){
    					nomeAnimal = animais[j].nome;
    					break;
					}
				}
				
				const char* nomeVet = "Desconhecido";
				for(int j=0; j<qtdVet; j++){
					if(veterinarios[j].cod == consultas[i].codVet){
						nomeVet = veterinarios[j].nome;
						break;
					}
				}
				
				cout << "\n------------------------";
            	cout << "\nAnimal: " << nomeAnimal;
            	cout << "\nVeterinário: " << nomeVet;
            	cout << "\nData: " << x.dia << "/" << x.mes << "/" << x.ano;
            	cout << "\nValor: R$" << consultas[i].valor;
            	cout << "\n------------------------";
            	
            	total += consultas[i].valor;
			}
	}
	
	cout << "\n\nTotal em consultas no período: R$" << total << endl;
}



//CONSULTAS

void consultar(Consultas consultas[], int &qtdConsultas, Animais animais[], int qtdAnimais, Racas racas[], int qtdRacas, Tutores tutores[],
 int qtdTutores, Veterinarios veterinarios[], int qtdVet, Cidades cidades[], int qtdCidades){
	system("cls");
    Consultas novo;
    novo.cod = qtdConsultas + 1;

    cout << "\n -- Digite (sair / -1) para voltar ao menu --  ";
    cout << "\n Cadastro da Consulta nº " << novo.cod << ": " << endl;

    if (!lerIntComSaida("Codigo do Animal: ", novo.codAnimal)) return;

    bool animalEncontrado = false;
    for (int i = 0; i < qtdAnimais; i++) {
        if (animais[i].cod == novo.codAnimal) {
            cout << "Animal: " << animais[i].nome << endl;
            for (int j = 0; j < qtdRacas; j++) {
                if (racas[j].cod == animais[i].codRaca) {
                    cout << "Raça: " << racas[j].desc << endl;
                    break;
                }
            }
            for (int k = 0; k < qtdTutores; k++) {
                if (tutores[k].cod == animais[i].codTutor) {
                    cout << "Tutor: " << tutores[k].nome << endl << endl;
                    break;
                }
            }
            animalEncontrado = true;
            break;
        }
    }
    if (!animalEncontrado) {
        cout << "Animal não encontrado. Verifique o código.\n";
        return;
    }

    if (!lerIntComSaida("Codigo do Veterinário: ", novo.codVet)) return;

    bool vetEncontrado = false;
    for (int i = 0; i < qtdVet; i++) {
        if (veterinarios[i].cod == novo.codVet) {
            cout << "Veterinário: " << veterinarios[i].nome << endl;
            for (int j = 0; j < qtdCidades; j++) {
                if (cidades[j].cod == veterinarios[i].codCidade) {
                    cout << "Cidade: " << cidades[j].nome << endl << endl;
                    break;
                }
            }
            vetEncontrado = true;
            break;
        }
    }
    if (!vetEncontrado) {
        cout << "Veterinário não encontrado. Verifique o código.\n";
        return;
    }
	
	cout << "Data da Consulta (dia mes ano): ";
    cin >> novo.dataConsulta.dia >> novo.dataConsulta.mes >> novo.dataConsulta.ano;
    
    if (!lerFloatComSaida("Valor da Consulta: ", novo.valor)) return;
	
	consultas[qtdConsultas] = novo;
    qtdConsultas++;
    cout << "\nConsulta cadastrada com sucesso!\n";
}

//LER CIDADES
void cadastrarCidade(Cidades cidades[], int &qtdCidades){
	system("cls");
	Cidades novo;
	
	cout << "\n -- Digite (sair ou sa / -1) para voltar ao menu --  ";	
	cout << "\n Cadastro da Cidade\n";
	
	if (!lerIntComSaida("Codigo da Cidade: ", novo.cod)) return;
	
	for (int i = 0; i < qtdCidades; i++) {
        if (cidades[i].cod == novo.cod) {
            cout << "Código já existente! Cadastro cancelado.\n";
            return;
        }
    }
	
	if (!lerLinhaComSaida("Nome da Cidade: ", novo.nome, 30)) return;
	
	cout << "UF(Unidade Federativa): ";
	cin.getline(novo.uf, 3);
	
	for (int i = 0; novo.uf[i]; i++) {
    	novo.uf[i] = toupper(novo.uf[i]);
	}
	
	cidades[qtdCidades] = novo;
	qtdCidades++;
	cout << "Cidade cadastrada com sucesso!\n";
}


//LER RAÇAS

void cadastrarRaca(Racas racas[],int &qtdRacas){
	system("cls");
	Racas novo;
	
	cout << "\n -- Digite (sair / -1) para voltar ao menu --  ";
	cout << "\n Cadastro da Raça\n";
	
	if (!lerIntComSaida("Codigo da Raça: ", novo.cod)) return;
	
	for (int i = 0; i < qtdRacas; i++) {
        if (racas[i].cod == novo.cod) {
            cout << "Código já existente! Cadastro cancelado.\n";
            return;
        }
    }
	
	if (!lerLinhaComSaida("Nome/Descrição da Raça: ", novo.desc, 100)) return;
	
	racas[qtdRacas] = novo;
	qtdRacas++;
	cout << "Raça cadastrada com sucesso!\n";
}


//lER VETERINARIOS
void cadastrarVet(Veterinarios veterinarios[], int &qtdVet){
	system("cls");
	Veterinarios novo;
	
	cout << "\n -- Digite (sair/ -1) para voltar ao menu --  ";
	cout << "\n Cadastro de Veterinário\n";
	
	if (!lerIntComSaida("Codigo do Veterinário: ", novo.cod)) return;
	
	for (int i = 0; i < qtdVet; i++) {
        if (veterinarios[i].cod == novo.cod) {
            cout << "Código já existente! Cadastro cancelado.\n";
            return;
        }
    }
		
	if (!lerLinhaComSaida("Nome do Veterinário: ", novo.nome, 30)) return;
	
	if (!lerLinhaComSaida("Endereço: ", novo.endereco, 30)) return;
	
	if (!lerIntComSaida("Codigo da Cidade: ", novo.codCidade)) return;
	
	veterinarios[qtdVet] = novo;
	qtdVet++;
	cout << "Veterinário cadastrado com sucesso!\n";
}

//LER ANIMAL
void cadastrarAnimal(Animais animais[], int &qtdAnimais, Racas racas[], int qtdRacas, Tutores tutores[], int qtdTutores, Cidades cidades[], int qtdCidades){
	system("cls");
	Animais novo;
	
	cout << "\n -- Digite (sair / -1) para voltar ao menu --  ";
	cout << "\n Cadastro de animal\n";
	if (!lerIntComSaida("Código do animal: ", novo.cod)) return;
	
	for (int i = 0; i < qtdAnimais; i++) {
        if (animais[i].cod == novo.cod) {
            cout << "Código já existente! Cadastro cancelado.\n";
            return;
        }
    }
	
    if (!lerLinhaComSaida("Nome do animal: ", novo.nome, 30)) return;
	
	bool valido = false;
	do{
		if (!lerIntComSaida("Código da Raça: ", novo.codRaca)) return;
		
		for(int i=0; i<qtdRacas;i++){
			if(racas[i].cod == novo.codRaca){
				cout << "Raca encontrada: " << racas[i].desc << endl;
				valido = true;
				break;
			}
		}
		if(!valido){
			cout << "Raca nao encontrada, tente novamente.\n";
		}
	} while (!valido);
	
	if (!lerIntComSaida("Idade do animal: ", novo.idade)) return;
    if (!lerFloatComSaida("Peso do animal: ", novo.peso)) return;
	
	do {
		valido = false;
		if (!lerIntComSaida("Código do tutor: ", novo.codTutor)) return;
		
		for(int i =0;i<qtdTutores; i++){
			if(tutores[i].cod == novo.codTutor){
				cout << "Tutor encontrado: " << tutores[i].nome;
				
				for(int j=0; j < qtdCidades; j++){
					if(cidades[j].cod == tutores[i].codCidade){
						cout << " - Cidade: " << cidades[j].nome << endl;
					}
				}
				valido = true;
				break;
			}
		}
		if (!valido){
			cout << "Tutor nao encontrado. Tente novamente\n";
		}
	} while(!valido);
	
	animais[qtdAnimais] = novo;
	qtdAnimais++;
	cout << "Animal cadastrado com sucesso!\n";
}


//LER TUTOR
void cadastrarTutor(Tutores tutores[], int &qtdTutores, Cidades cidades[], int &qtdCidades){
	system("cls");
	Tutores novo;
	
	cout << "\n -- Digite (sair / -1) para voltar ao menu --  ";
	cout << "\n Cadastro de Tutor\n";
	
	if (!lerIntComSaida("Código do Tutor: ", novo.cod)) return;
	
	for (int i = 0; i < qtdTutores; i++) {
        if (tutores[i].cod == novo.cod) {
            cout << "Código já existente! Cadastro cancelado.\n";
            return;
        }
    }
	
	if (!lerLinhaComSaida("Nome : ", novo.nome, 30)) return;

    bool valido = false;
    do{
		cout << "CPF (11 digitos): ";
		cin >> novo.cpf;
		cin.ignore();
		//cin.getline(novo.cpf, 12); para nao limitar o tamanho. evitar erro
		valido = cpfValido(novo.cpf);
		if(!valido)
		cout << "CPF invalido! Digite corretamente.\n";
	} while (!valido);
	
	if (!lerLinhaComSaida("Endereco: ", novo.endereco, 30)) return;
	
	do{
		valido = false;
		
		if (!lerIntComSaida("Código da Cidade: ", novo.codCidade)) return;
		
		for(int i=0;i < qtdCidades; i++){
			if(cidades[i].cod == novo.codCidade){
				cout << "Cidade encontrada: " << cidades[i].nome << " - " << cidades[i].uf << endl;
				valido = true;
				break;
			}
		}
		if(!valido){
			cout << "Cidade nao encontrada. Tente novamente.\n";
		}
	} while (!valido);
	
	tutores[qtdTutores] = novo;
	qtdTutores++;
	cout << "Tutor cadastrado com sucesso!\n";
}


int main(){
	setlocale(LC_ALL, "Portuguese");
	struct Racas racas[100] = {
        {1, "Labrador Retriever"},
        {2, "Pastor Alemao"},
        {3, "Poodle"},
        {4, "Bulldog Frances"},
        {5, "Golden Retriever"}
    };
	Cidades cidades[100] = {
		{1, "Sao Paulo", "SP"},
        {2, "Rio de Janeiro", "RJ"},
        {3, "Belo Horizonte", "MG"},
        {4, "Assis", "SP"},
        {5, "Candido Mota", "SP"}
		};
	Tutores tutores[100]= {
		{1, "Carlos Silva", "12345678901", "Rua A, 123", 1},
	    {2, "Maria Souza", "98765432100", "Av. B, 456", 2},
	    {3, "Joao Lima", "45612378900", "Rua C, 789", 3},
	    {4, "Ana Costa", "32165498700", "Rua D, 101", 1},
	    {5, "Pedro Rocha", "78932165400", "Av. E, 202", 2}
	};
	
	Animais animais[100] = {
    	{1, "Thor", 2, 5, 22.5, 1},
    	{2, "Luna", 3, 3, 8.7, 2},
    	{3, "Rex", 1, 7, 30.2, 3},
    	{4, "Belinha", 4, 2, 12.0, 4},
    	{5, "Bob", 5, 6, 18.9, 5}
	};
	Veterinarios veterinarios[100] = {
    	{1, "Dr. Marcos Leal", "Rua das Flores, 100", 1},
    	{2, "Dra. Fernanda Lima", "Av. Central, 200", 2},
    	{3, "Dr. João Pires", "Rua São José, 300", 3},
    	{4, "Dra. Paula Nunes", "Av. Paulista, 400", 4},
    	{5, "Dr. Ricardo Gomes", "Rua XV de Novembro, 500", 5}
	};	
	Consultas consultas[100] = {
    {1, 1, 2, {15, 1, 2024}, 150.00},
    {2, 2, 2, {20, 3, 2024}, 210.00},
    {3, 3, 1, {10, 4, 2024}, 180.00},
    {4, 4, 2, {5, 5, 2024}, 220.00},
    {5, 5, 3, {25, 6, 2024}, 190.00}
	};		
	int qtdAnimais= 0, qtdCidades= 0, qtdRacas= 0, qtdTutores= 0, qtdVet =0, qtdConsultas =0;
	
	
	int escolha; 
	
	do{
		cout << "\n===== MENU =====\n";
		cout << "1. Cadastrar Animal\n";
        cout << "2. Cadastrar Tutor\n";
        cout << "3. Cadastrar Veterinário\n";
        cout << "4. Cadastrar Raça\n";
        cout << "5. Cadastrar Cidade\n";
        cout << "6. Realizar uma Consulta\n";
        cout << "7. Exibir consultas por período\n";
        cout << "8. Exibir consultas do Veterinário por período\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> escolha;
        
        switch(escolha) {
        	case 1:{
        		cadastrarAnimal(animais, qtdAnimais, racas, qtdRacas, tutores, qtdTutores, cidades, qtdCidades);
        		break;
        	}
        	case 2:{
        		cadastrarTutor(tutores, qtdTutores, cidades, qtdCidades);
				break;
			}
			case 3:{
				cadastrarVet(veterinarios, qtdVet);
				break;
			}
			case 4:{
				cadastrarRaca(racas, qtdRacas);
				break;
			}
			case 5:{
				cadastrarCidade(cidades, qtdCidades);
				break;
			}
			case 6:{
				consultar(consultas, qtdConsultas, animais, qtdAnimais, racas, qtdRacas, tutores, qtdTutores, veterinarios, qtdVet, cidades, qtdCidades);
				break;
			}
			case 7:{
				exibirConsultas(consultas, qtdConsultas, animais, qtdAnimais, veterinarios, qtdVet);
				break;
			}
			case 8:{
				exibirConsultasVet(consultas, qtdConsultas, animais, qtdAnimais, veterinarios, qtdVet);
				break;
			}
			case 0:{
				cout << "Saindo do Programa...\n";
				break;
			}
			default:{
				system("cls");
				cout << "opção inválida";
			}
		}
	} while (escolha!=0);
}
