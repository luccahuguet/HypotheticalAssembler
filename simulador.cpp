#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <fstream>

using namespace std;

// ED que guarda data section
// <endereco, valor>
map<int, int> dados;

// Função que pega string de código máquina e separa cada número em uma string distinta
vector<string> split_code(string s) {

    string del = " ";
    vector<string> return_vec;
    int end = s.find(del); 

    while (end != -1) {
        return_vec.push_back(s.substr(0, end));        
        s.erase(s.begin(), s.begin() + end + 1);
        end = s.find(del);
    }

    return return_vec;
}

int main(int argc, char *argv[]){

    string filename = argv[1];
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open the file." << endl;
        return 1;
    }

    string input;
    getline(file, input);

    // Close the file
    file.close();

    if(input[input.size()-1] != ' ')
        input.append(" ");

    int PC = 0, ACC;

    vector<string> instructions_string;
    vector<int> instructions;

    instructions_string = split_code(input);

    // Converte codigo objeto de strings para inteiros
    for (int i = 0; i < instructions_string.size(); i++)
    {
        instructions.push_back(stoi(instructions_string[i]));
    }

    // Faz uma passagem para identificar labels e encontrar section data
    // Inicializa map de dados
    for (int i = 0; i < instructions.size(); i++)
    {
        if((instructions[i] >= 1 && instructions[i] <= 4) || (instructions[i] >= 10 && instructions[i] <= 13) )     // Instrucoes com 2 enderecos
        {
            // Checa se label já está nos maps dos dados
            if(!dados.count(instructions[i+1]))
            {
                dados.insert({instructions[i+1], instructions[instructions[i+1]]});
                i++;
            }
            else
            {
                i++;
            }

        }
        else if(instructions[i] >= 5 && instructions[i] <= 8)
        {
            i++;
        }
        else if(instructions[i] == 9)   // COPY
        {
            // Checa se label já está nos maps dos dados
            if(!dados.count(instructions[i+1]))
            {
                dados.insert({instructions[i+1], instructions[instructions[i+1]]});
            }
            if(!dados.count(instructions[i+2]))
            {
                dados.insert({instructions[i+2], instructions[instructions[i+2]]});
            }
            i+=2;

        }
        else if(instructions[i] == 14)  // STOP
        {
            break;
        }

        else    // SALTOS
        {
            i++;
        }
        

    }

    int first_data_address = instructions.size()-1;
    map<int, int>::iterator it_dados = dados.begin();
    
    // identifica qual é o primeiro endereço de dados
    while(it_dados != dados.end())
    {
        if(it_dados->first < first_data_address)
            first_data_address = it_dados->first;
        
        it_dados++;
    }

    // Executa arquivo objeto
    bool encerra = false;
    for (int i = 0; i < instructions.size(); i++)
    {
        if(PC >= first_data_address)
            cout << "SEGMENTATION FAULT: o PC acessou a secao de dados" << endl;

        if(instructions[i] != 12)
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

        switch(instructions[i]) {

            case 1:     //ADD

                PC += 2;
                i++;
                ACC += dados[instructions[i]];
                cout << "ADD PC <- " << PC << " ACC <- " << ACC << endl;
                break;
            
            case 2:     // SUB
                
                PC += 2;
                i++;
                ACC -= dados[instructions[i]];
                cout << "SUB PC <- " << PC << " ACC <- " << ACC << endl;
                break;

            case 3:     // MUL
                
                PC += 2;
                i++;
                ACC *= dados[instructions[i]];
                cout << "MUL PC <- " << PC << " ACC <- " << ACC << endl;
                break;

            case 4:     // DIV
                
                PC += 2;
                i++;
                ACC /= dados[instructions[i]];
                cout << "DIV PC <- " << PC << " ACC <- " << ACC << endl;
                break;

            case 5:     // JMP
                
                i = instructions[i+1];
                PC = i;
                i-=1;

                cout << "JMP PC <- " << PC << " ACC <- " << ACC << endl;
                break;
            
            case 6:     // JMPN
                
                if(ACC < 0)
                {
                    i = instructions[i+1];
                    PC = i;
                    i-=1;
                }
                else{
                    PC += 2;
                    i++;
                }

                cout << "JMPN PC <- " << PC << " ACC <- " << ACC << endl;
                break;
            
            case 7:     // JUMPP
                
                if(ACC > 0)
                {
                    i = instructions[i+1];
                    PC = i;
                    i-=1;
                }
                else{
                    PC += 2;
                    i++;
                }

                cout << "JMPP PC <- " << PC << " ACC <- " << ACC << endl;
                break;
            
            case 8:     // JMPZ
                
                if(ACC == 0)
                {
                    i = instructions[i+1];
                    PC = i;
                    i-=1;
                }
                else{
                    PC += 2;
                    i++;
                }

                cout << "JMPZ PC <- " << PC << " ACC <- " << ACC << endl;
                break;

            case 9:     // COPY

                dados[instructions[i+2]] = dados[instructions[i+1]];
                PC += 3;
                i+=2;
                cout << "COPY PC <- " << PC << " ACC <- " << ACC << endl;

            break;

            case 10:     // LOAD

                // cout << "endereco em que esta fazendo load: " << instructions[i+1] << endl;
                ACC = dados[instructions[i+1]];
                PC += 2;
                i++;
                cout << "LOAD PC <- " << PC << " ACC <- " << ACC << endl;

            break;

            case 11:     // STORE

                // cout << "endereco em que esta fazendo store: " << instructions[i+1] << endl;
                dados[instructions[i+1]] = ACC;
                PC += 2;
                i++;
                cout << "STORE PC <- " << PC << " ACC <- " << ACC << endl;

            break;

            case 12:     // INPUT

                cin >> dados[instructions[i+1]];
                PC += 2;
                i++;
                cout << "INPUT PC <- " << PC << " ACC <- " << ACC << endl;

            break;

            case 13:     // OUTPUT
                PC += 2;
                i++;
                cout << "OUTPUT PC <- " << PC << " ACC <- " << ACC << " SAIDA: " << dados[instructions[i]] << endl;
            break;

            case 14:     // STOP
                encerra = true;
                PC += 2;
                i++;
                cout << "STOP PC <- " << PC << " ACC <- " << ACC << endl;
            break;


        }

    }

    return 0;
}