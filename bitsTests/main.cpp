#include <iostream>
#include <sstream>
#include <cassert>
#include <string.h>
#include <fstream>
#include <cstdio>
using namespace std;

struct Data {
    int num1;
    char op;
    int num2;
    string name;
    string vers;
};
string ask_data(bool out = true, istream& stream = cin);
void divide_string(string input, struct Data& data);
char nibble_to_hex(int i);
string dec_to_binary(int dec);
string dec_to_hex(int dec);
void print_in_dec(struct Data data);
void print_in_binary(struct Data data);
void print_in_hex(struct Data data);
void InToTXT(string& vers, string& name);
void rec_sys_data(struct Data& data);

int
main() {
    setlocale(LC_ALL, "ru");
    stringstream stream1("1025 & 127");
    stringstream stream2("1000 ^ 255");
    stringstream stream3("987 | 176");
    stringstream stream4("12 ^ 10");
    
    auto input = ask_data();
    Data data;
    divide_string(input, data);
    
    print_in_dec(data);
    print_in_binary(data);
    print_in_hex(data);
    
    cout << endl;
    string name, vers;
    rec_sys_data(data);
    printf("System version is:%s\n", data.vers.c_str());
    printf("Username is:%s\n", data.name.c_str());

    return 0;
}

string
ask_data(bool out, istream& stream) {
    string input;
    if (out)
        cout << "Введите число + &/^/| + число: ";
    getline(stream, input);
    return input;
}
void
divide_string(string input, struct Data& data) {
    istringstream source(input);
    source >> data.num1 >> data.op >> data.num2;
}
char
nibble_to_hex(int i) {
    assert(0x0 <= i && i <= 0xf);
    char res = (char) i;
    if (i >= 0 && i <= 9)
        res = (char) (48 + i);
    else if (i >= 10 && i <= 15)
        res = (char) (65 - 10 + i);
    return res;
}
string
dec_to_binary(int dec) {
    string bin;
    for (size_t j = 0; dec > 0; j++) {
        if (dec % 2 == 1)
            bin.insert(0, "1");
        else
            bin.insert(0, "0");
        dec /= 2;
    }
    bin.insert(0, 16 - bin.length(), '0');
    //Привод к little-endian
    string s;
    s.insert(0, bin, bin.length()/2, bin.length());
    bin.erase(bin.length()/2, bin.length());
    bin.insert(0, s);
    //----------------------
    bin.insert(bin.length()/2, 1, ' ');
    return bin;
}
string
dec_to_hex(int dec) {
    //У меня на системе big-endian => поменял местами
    string hex;
    hex  = nibble_to_hex(dec >> 4 & 0xF);
    hex += nibble_to_hex(dec & 0xF);
    hex += ' ';
    hex += nibble_to_hex(dec >> 12 & 0xF);
    hex += nibble_to_hex(dec >> 8 & 0xF);
    return hex;
}
void print_in_dec(struct Data data) {
    cout << data.num1 << " " << data.op << " " << data.num2 << " = ";
    if (data.op == '&')
        cout << (data.num1 & data.num2);
    else if (data.op == '|')
        cout << (data.num1 | data.num2);
    else
        cout << (data.num1 ^ data.num2);
    cout << endl;
}
void
print_in_binary(struct Data data) {
    cout << dec_to_binary(data.num1) << " " << data.op << " " << dec_to_binary(data.num2) << " = ";
    if (data.op == '&')
        cout << dec_to_binary(data.num1 & data.num2);
    else if (data.op == '|')
        cout << dec_to_binary(data.num1 | data.num2);
    else
        cout << dec_to_binary(data.num1 ^ data.num2);
    cout << endl;
}
void
print_in_hex(struct Data data) {
    cout << dec_to_hex(data.num1) << " " << data.op << " " << dec_to_hex(data.num2) << " = ";
    if (data.op == '&')
        cout << dec_to_hex(data.num1 & data.num2);
    else if (data.op == '|')
        cout << dec_to_hex(data.num1 | data.num2);
    else
        cout << dec_to_hex(data.num1 ^ data.num2);
    cout << endl;
}
void
InToTXT(string& vers, string& name) {
    string sys;
    ifstream in_file;
    in_file.open("/Users/georgijlegkoskurov/Desktop/data.txt");
    while(!in_file.eof()) {
        getline(in_file, sys);
        if (sys.find("System Version:") != -1) {
            vers.insert(0, sys, sys.find("System Version:") + strlen("System Version:"));
        }
        else if (sys.find("User Name:") != -1) {
            name.insert(0, sys, sys.find("User Name:") + strlen("User Name:"));
        }
    }
    in_file.close();
}
void
rec_sys_data(struct Data& data) {
    string sys;
    system("system_profiler SPSoftwareDataType > /Users/georgijlegkoskurov/Desktop/data.txt");
    InToTXT(data.vers, data.name);
    remove("/Users/georgijlegkoskurov/Desktop/data.txt)");
}
