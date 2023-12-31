#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <limits>

using namespace std;

// <OPCode, qnt_enderecos>
// map<int, int> instructions_table = 
// {
//     {1 , 2},    // ADD
//     {2 , 2},    // SUB
//     {3 , 2},    // MUL
//     {4 , 2},    // DIV
//     {5 , 2},    // JMP
//     {6 , 2},    // JMPN
//     {7 , 2},    // JMPP
//     {8 , 2},    // JMPZ
//     {9 , 3},    // COPY
//     {10 , 2},   // LOAD
//     {11 , 2},   // STORE
//     {12 , 2},   // INPUT
//     {13 , 2},   // OUTPUT
//     {8 , 1}     // STOP
// };

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

int main(){

    int PC = 0, ACC;

    string input = "12 22 10 22 2 23 8 18 11 21 3 22 11 22 10 21 5 4 13 22 14 0 0 1 ";
    vector<string> instructions_string;
    vector<int> instructions;

    instructions_string = split_code(input);

    // Converte codigo objeto de strings para inteiros
    for (int i = 0; i < instructions_string.size(); i++)
    {
        instructions.push_back(stoi(instructions_string[i]));
        // cout << instructions[i] << " ";
    }
    // cout << endl;



    // Faz uma passagem para identificar labels e encontrar section data
    // Inicializa map de dados

    for (int i = 0; i < instructions.size(); i++)
    {
        // cout << instructions[i] << endl;
        if((instructions[i] >= 1 && instructions[i] <= 4) || (instructions[i] >= 10 && instructions[i] <= 13) )     // Instrucoes com 2 enderecos
        {
            // Checa se label já está nos maps dos dados
            if(!dados.count(instructions[i+1]))
            {
                // if(instructions[i+1] == 23)
                //     cout << "BATATA " << instructions[instructions[i+1]] << endl;
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
    
    // cout << "tamanho: " << dados.size() << endl;

    // map<int, int>::iterator it_dados = dados.begin();
    // while(it_dados != dados.end())
    // {
    //     cout << it_dados->first << " " << it_dados->second << endl;
    //     it_dados++;
    // }


    int first_data_address = instructions.size()-1;
    map<int, int>::iterator it_dados = dados.begin();
    
    // identifica qual é o primeiro endereço de dados
    while(it_dados != dados.end())
    {
        if(it_dados->first < first_data_address)
            first_data_address = it_dados->first;
        
        it_dados++;
    }
    // cout << first_data_address << endl;    

    // it_dados = dados.begin();
    // while(it_dados != dados.end())
    // {
    //     cout << it_dados->first << " " << it_dados->second << endl;
    //     it_dados++;
    // }





    

    int conta = 0;
    bool encerra = false;
    for (int i = 0; i < instructions.size(); i++)
    {
        conta ++;
        // if(encerra)
        //     break;

        // if(conta == 26)
        //     break;

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

            // cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    }




    return 0;
}