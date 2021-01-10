/*
 * run2.cpp
 *
 *  Created on: 8 áãöî× 2019
 *      Author: Eli
 */

#include <iostream>
#include <fstream>
#include "commands.h"
#include "CLI.h"

using namespace std;

class ConsoleIO: public DefaultIO{
    string currentInput;

public:
    ConsoleIO(){

    }

    virtual string read(){
        cin >> currentInput;
        return currentInput;

    }

    virtual void write(string text){
        cout << text;
    }

    const char* downloadFile(string path) override{
        //assuming path is actually a filename
        const char * filePath = path.c_str();
        return filePath;
    }

    void uploadFile(string path) override{
        in.open(path);
        string line;
        string s;
        while ( getline (in,line) ){
            s = s + line;
        }
        // Remove directory if present.
        // Do this before extension removal incase directory has a period character.
        const size_t last_slash_idx = path.find_last_of("\\/");
        if (std::string::npos != last_slash_idx)
        {
            path.erase(0, last_slash_idx + 1);
        }

        out.open(path);
        out<<s;
        out.close();
        in.close();

    }

    virtual void write(float f){

    }

    virtual void read(float* f){

    }

    ~ConsoleIO(){

    }
};

class STDtest:public DefaultIO{
    ifstream in;
    ofstream out;
public:
    STDtest(string inputFile,string outputFile){
        in.open(inputFile);
        out.open(outputFile);
    }
    virtual string read(){
        string s;
        in>>s;
        return s;
    }
    virtual void write(string text){
        out<<text;
        out.flush();
    }

    virtual void write(float f){
        out<<f;
        out.flush();
    }

    const char* downloadFile(string path) override{
        //assuming path is actually a filename
        const char * filePath = path.c_str();
        return filePath;
    }

    void uploadFile(string path) override{
        ofstream ofstream1(path);
        string line;
        line = read();
        while(line != "done"){
            ofstream1 << line + "\n";
            line = read();
        }
        ofstream1.close();

    }

    virtual void read(float* f){
        in>>*f;
    }

    void close(){
        if(in.is_open())
            in.close();
        if(out.is_open())
            out.close();
    }
    ~STDtest(){
        close();
    }
};

void check(string outputFile,string expectedOutputFile){
    size_t chk[]={31,62,63,74,75,86,87,98,99,110,111};
    ifstream st(outputFile);
    ifstream ex(expectedOutputFile);
    size_t i=1,j=0;
    string lst,lex;
    while(!st.eof() && !ex.eof()){
        getline(st,lst);
        getline(ex,lex);
        if(i<13 && lst.compare(lex)!=0){ // 12
            cout<<"line "<<i<<" expected: "<<lex<<" you got "<<lst<<endl;
            cout<<"wrong output (-1)"<<endl;
        }else
        if(j<11 && i==chk[j]){
            if(lst.compare(lex)!=0){ // 88
                cout<<"line "<<i<<" expected: "<<lex<<" you got "<<lst<<endl;
                cout<<"wrong output (-8)"<<endl;
            }
            j++;
        }
        i++;
    }
    if(j<11)
        cout<<"wrong output size (-"<<(11-j)*8<<")"<<endl;
    st.close();
    ex.close();
}

//small test
int main(){
    //ConsoleIO* stdIO = new ConsoleIO();
    STDtest std("input.txt","output.txt");
    CLI cli(&std);
    cli.start();
    cout<<"done"<<endl;
    return 0;
}



