#include <iostream>
#include <map>
#include <string>
#include <iostream>
#include <functional>
#define RAPIDJSON_HAS_STDSTRING 1


//
// supporting tools and software
//
// Validate and test your json commands
// https://jsonlint.com/

// RapidJSON : lots and lots of examples to help you use it properly
// https://github.com/Tencent/rapidjson
//

// std::function
// std::bind
// std::placeholders
// std::map
// std::make_pair

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

bool g_done = false;

//
// TEST COMMANDS
//
auto help_command = R"(
 {
  "command":"help",
  "payload": {
    "usage":"Enter json command in 'command':'<command>','payload': { // json payload of arguments }",
  }
 }
)";

auto exit_command = R"(
 {
  "command":"exit",
  "payload": {
     "reason":"Exiting program on user request."
  }
 }
)";

auto search_name_command = R"(
 {
  "command":"search_name",
  "payload": {
     "Usage":"Search object/function by name."
  }
 }
)";

class Controller {
public:
    Document document;
    //help::run this command when called by the dispatcher
    //The Controller Class is the “commands” you want to have run by the dispatcher.
public:

    bool help(rapidjson::Value &payload)
    {
        cout << "Controller::help: command: ";
        /*
        // implement
        document.Parse(help_command);
        Value v(payload, document.GetAllocator());
        document.PushBack(v, document.GetAllocator());
        */
        cout<<help_command<<endl;
        return true;
    }
   //What's the use of payload?
    bool exit(rapidjson::Value &payload)
    {
        cout << "Controller::exit: command: \n";

        /*
        // implement
        document.Parse(exit_command);
        Value v(payload, document.GetAllocator());
        document.PushBack(v, document.GetAllocator());
        */
        cout<<exit_command<<endl;
        return true;
    }

    bool search_name(rapidjson::Value &payload)
    {
        cout << "Controller::search_name_command: command: \n";

        /*
        // implement
        document.Parse(search_name_command);
        Value v(payload, document.GetAllocator());
        document.PushBack(v, document.GetAllocator());
        */
        cout<<search_name_command<<endl;
        return true;
    }
};

// Functor that can be treated as though they are a function or function pointer
typedef std::function<bool(rapidjson::Value &)> CommandHandler;



class CommandDispatcher {
public:
    CommandHandler c;
public:
    // ctor - need impl
    CommandDispatcher()
    {
        //This  insert a command “help”, “exit” and the associated function (from Controller) class to run if the command is detected
    }

    // dtor - need impl
    virtual ~CommandDispatcher()
    {

        // question why is it virtual? Is it needed in this case?
        //Deleting a derived class object using a pointer to a base class that has a non-virtual destructor results in undefined behavior.
        // To correct this situation, the base class should be defined with a virtual destructor.
    }

    bool addCommandHandler(std::string command, CommandHandler handler)
    {
        cout << "CommandDispatcher: addCommandHandler: " << command << std::endl;



        return true;
    }

    static rapidjson::Document str_to_json(const char* json) {
        rapidjson::Document document;
        document.Parse(json);
         return std::move(document);
    }
    bool dispatchCommand(std::string command_json)
    {

        cout << "COMMAND: " << command_json << endl;

        // look for command in the function argument
        if(command_json.find("exit") != -1){
            //find the payload
            string command="exit";
            int x=command_json.find("payload");
            x += 9;
            //run the associated function handler

            //const rapidjson::Document handler = str_to_json(command_json.substr(x));
            c=command_json.substr(x));
            //I could not find any proper answer to how to define CommandHandler pointer function taking as input a rapidjason::value
            //That's why I left this ..
            addCommandHandler("exit",true);

            //Controller::exit(command_json);
        }
        else if(command_json.find("help")!= -1){
            //find the payload
            int x=command_json.find("payload");
            x += 9;
            //run the associated command handler
            //const rapidjson::Document handler = str_to_json(command_json.substr(x));
            c= command_json.substr(x);

            addCommandHandler("help",c);
        }
        else{return false;}
        return true;
    }




private:
    std::map<std::string, CommandHandler> command_handlers_;

    // Question: why delete these?
    //The destructor of A will run when its lifetime is over.
    //If you want its memory to be freed and the destructor run, you have to delete it.

    // delete unused constructors
    CommandDispatcher (const CommandDispatcher&) = delete;
    CommandDispatcher& operator= (const CommandDispatcher&) = delete;

};

int main()
{
    std::cout << "COMMAND DISPATCHER: STARTED" << std::endl;

    CommandDispatcher command_dispatcher;
    Controller controller;                 // controller class of functions to "dispatch" from Command Dispatcher


    CommandHandler commandHandler;
    // add command handlers in Controller class to CommandDispatcher using addCommandHandler

    // command line interface for testing
    string command;
    while( ! g_done ) {
        cout << "COMMANDS: {\"command\":\"exit\", \"payload\":{\"reason\":\"User requested exit.\"}}\n";
        cout << "\tenter command : ";
        getline(cin, command);
        command_dispatcher.dispatchCommand(command);
    }

    std::cout << "COMMAND DISPATCHER: ENDED" << std::endl;
    return 0;
}
