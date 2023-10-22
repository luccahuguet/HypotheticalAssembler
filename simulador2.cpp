#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <limits>

using std::vector;
using std::string;
using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::istringstream;
using std::numeric_limits;
using std::streamsize;

enum OpCode {
    ADD = 1, 
    SUB, 
    MUL, 
    DIV, 
    JMP, 
    JMPN, 
    JMPP, 
    JMPZ, 
    COPY, 
    LOAD, 
    STORE, 
    INPUT, 
    OUTPUT, 
    STOP
};

map<int, int> data;

vector<string> split_code(const string& s) {
    istringstream iss(s);
    vector<string> result;
    string word;
    while (iss >> word) {
        result.push_back(word);
    }
    return result;
}

string opcode_to_string(int opcode) {
    static map<int, string> opcodeNames = {
        {ADD, "ADD"}, 
        {SUB, "SUB"}, 
        {MUL, "MUL"}, 
        {DIV, "DIV"}, 
        {JMP, "JMP"}, 
        {JMPN, "JMPN"}, 
        {JMPP, "JMPP"}, 
        {JMPZ, "JMPZ"}, 
        {COPY, "COPY"}, 
        {LOAD, "LOAD"}, 
        {STORE, "STORE"}, 
        {INPUT, "INPUT"}, 
        {OUTPUT, "OUTPUT"}, 
        {STOP, "STOP"}
    };

    auto it = opcodeNames.find(opcode);
    if (it != opcodeNames.end())
        return it->second;
    else
        return "UNKNOWN";
}

int main() {
    int PC = 0;
    int ACC = 0;  // Initialized ACC

    string input = "12 22 10 22 2 23 8 18 11 21 3 22 11 22 10 21 5 4 13 22 14 0 0 1";
    vector<string> instructions_string = split_code(input);

    vector<int> instructions;
    for (const auto& ins : instructions_string) {
        instructions.push_back(std::stoi(ins));
    }

    // Initialize data map and other pre-execution setup
    // This should be based on your application's requirements

    // Execution loop
    bool terminate = false;
    while (PC < instructions.size() and not terminate) {
        int opcode = instructions[PC++];
    
        // Print the instruction name
        cout << "Executing instruction: " << opcode_to_string(opcode) << endl;

        switch(opcode) {
            case ADD:
                // Ensure PC + 1 is within bounds
                if (PC < instructions.size()) {
                    ACC += data[instructions[PC++]];
                }
                break;
            case SUB:
                // Ensure PC + 1 is within bounds
                if (PC < instructions.size()) {
                    ACC -= data[instructions[PC++]];
                }
                break;
            case MUL:
                // Ensure PC + 1 is within bounds
                if (PC < instructions.size()) {
                    ACC *= data[instructions[PC++]];
                }
                break;
            case DIV:
                // Ensure PC + 1 is within bounds and division by zero check
                if (PC < instructions.size() && data[instructions[PC]] != 0) {
                    ACC /= data[instructions[PC++]];
                }
                break;
            case JMP:
                if (PC < instructions.size()) {
                    int nextInstruction = instructions[PC++];
                    if (data.find(nextInstruction) != data.end()) {
                        PC = data[nextInstruction]; // set the PC to the specific instruction number
                        if (PC >= instructions.size()) {
                            cout << "Error: Jump address out of bounds." << endl;
                            terminate = true;  // Jumped out of valid range, terminate execution
                        }
                    } else {
                        cout << "Error: Jump address " << nextInstruction << " not initialized." << endl;
                        terminate = true;
                    }
                } else {
                    cout << "Error: Invalid instruction pointer." << endl;
                    terminate = true; // Invalid instruction pointer, terminate execution
                }
                break;
            case JMPN:
                if (PC < instructions.size()) {
                    int nextInstruction = instructions[PC++];
                    if (ACC < 0) {
                        if (data.find(nextInstruction) != data.end()) {
                            PC = data[nextInstruction];
                            if (PC >= instructions.size()) {
                                cout << "Error: Jump address out of bounds." << endl;
                                terminate = true;
                            }
                        } else {
                            cout << "Error: Jump address " << nextInstruction << " not initialized." << endl;
                            terminate = true;
                        }
                    }
                } else {
                    ++PC; // move to the next instruction if ACC is not negative
                }
                break;

            case JMPP:
                if (PC < instructions.size()) {
                    int nextInstruction = instructions[PC++];
                    if (ACC > 0) {
                        if (data.find(nextInstruction) != data.end()) {
                            PC = data[nextInstruction];
                            if (PC >= instructions.size()) {
                                cout << "Error: Jump address out of bounds." << endl;
                                terminate = true;
                            }
                        } else {
                            cout << "Error: Jump address " << nextInstruction << " not initialized." << endl;
                            terminate = true;
                        }
                    }
                } else {
                    ++PC; // move to the next instruction if ACC is not positive
                }
                break;

            case JMPZ:
                if (PC < instructions.size()) {
                    int nextInstruction = instructions[PC++];
                    if (ACC == 0) {
                        if (data.find(nextInstruction) != data.end()) {
                            PC = data[nextInstruction];
                            if (PC >= instructions.size()) {
                                cout << "Error: Jump address out of bounds." << endl;
                                terminate = true;
                            }
                        } else {
                            cout << "Error: Jump address " << nextInstruction << " not initialized." << endl;
                            terminate = true;
                        }
                    }
                } else {
                    ++PC; // move to the next instruction if ACC is not zero
                }
                break;
            case COPY:
                // Ensure PC + 2 is within bounds
                if (PC + 1 < instructions.size()) {
                    data[instructions[PC + 1]] = data[instructions[PC]];
                    PC += 2;
                }
                break;
            case LOAD:
                if (PC < instructions.size()) {
                    ACC = data[instructions[PC++]];
                }
                break;
            case STORE:
                if (PC < instructions.size()) {
                    data[instructions[PC++]] = ACC;
                }
                break;
            case INPUT:
                if (PC < instructions.size()) {
                    cout << "Input a value: ";
                    cin >> data[instructions[PC++]];
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            case OUTPUT:
                if (PC < instructions.size()) {
                    cout << "Output: " << data[instructions[PC++]] << endl;
                }
                break;
            case STOP:
                terminate = true;
                break;
            default:
                cout << "Unknown opcode " << opcode << endl;
                terminate = true;
                break;
        }
        // Print or logging here, if needed
    }

    // Post-execution and cleanup

    return 0;
}
