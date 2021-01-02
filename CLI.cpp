#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
}

void CLI::start(){
    Command *upCmd = new UploadCommand(dio);
    Command *detectCmd = new AnomalyDetectCommand(dio);
    commands[0] = upCmd;
    commands[1] = detectCmd;

    dio->write("Welcome ya zalam\n");
    int input = 0;
    while (input != 7){
        dio->write("Please choose command:\n");
        dio->write("1. UPLOAD COMMAND\n");
        dio->write("2. DETECT\n");
        string strInput = dio->read();
        commands[stoi(strInput) - 1]->execute();

        input = stoi(strInput);

    }




}


CLI::~CLI() {
}

