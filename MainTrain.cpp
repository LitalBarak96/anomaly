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

class StandardIO:public DefaultIO{
    string currentInput;

public:
    StandardIO(){

    }

    virtual string read(){
        cin >> currentInput;
        return currentInput;

    }

    virtual void write(string text){
        cout << text;
    }

    string downloadFile(string path) override{
       if(path == "1"){
           return fileData1;
       }
       else{
           return fileData2;
       }
    }

    void uploadFile(string path) override{
        in.open(path);
        string s;
        in>>s;

        if(fileData1 != "" && fileData2 != ""){
            fileData2 = fileData1;
            fileData1 = "FILE DATA 1";
        }
        else if(fileData1 == ""){
            fileData1 = "FILE DATA 1";
        }
        else{
            fileData2 = "FILE DATA 2";
        }

        in.close();

    }

    virtual void write(float f){

    }

    virtual void read(float* f){

    }

    ~StandardIO(){

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
    }

    virtual void write(float f){
        out<<f;
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
    StandardIO* stdIO = new StandardIO();
    CLI cli(stdIO);
    cli.start();
    cout<<"done"<<endl;
    return 0;
}
