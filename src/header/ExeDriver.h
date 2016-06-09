#include <queue>

void  ExeDriver(vector<string> &command_collection) {
    string AND = "&&", OR = "||" , SEMICOLON = ";", REDIRIN = "<", REDIROUT1 = ">", REDIROUT2 = ">>", PIPE = "|";

    queue<Token*> commandQ; // temporary vector to hold processed token(commands & connectors)
    queue<Token*> connectorQ; // holds connectors
    vector<ExecuteBase*> runV;
    //queue<ExecuteBase*> runQ;
    Token* left_token;
    Token* right_token;
    Token* token = new Token();
    
    
    //first pass, turn token into commands and connectors
    for(unsigned int i = 0 ; i < command_collection.size() ; i++){
        if(command_collection[i] == SEMICOLON
            || command_collection[i] == AND
            || command_collection[i] == OR
            || command_collection[i] == REDIRIN
            || command_collection[i] == REDIROUT1
            || command_collection[i] == REDIROUT2
            || command_collection[i] == PIPE){

            //cout << "First iteration: "; token->print();

            commandQ.push(token);
            token = new Token();
            token->addArgs(command_collection[i]);
            
            //cout << "Connector" ; token->print();
            connectorQ.push(token);
            token = new Token();
        }else if(command_collection.at(i) != SEMICOLON 
                && command_collection.at(i) != OR 
                && command_collection.at(i) != AND
                && command_collection.at(i) != REDIRIN
                && command_collection.at(i) != REDIROUT1
                && command_collection.at(i) != REDIROUT2
                && command_collection.at(i) != PIPE){
            //cout << "create new token: " <<command_collection[i]<< endl; // see what token is being added
            token->addArgs(command_collection[i]);
        }
        //looks at the end of the token string.
        //if it's at the end, push the last token onto queue
        if(i == (command_collection.size() - 1)){
            //cout << "push last command: "; token->print(); //see last token pushed
            commandQ.push(token);
        }
    }
    
    // Just run the token since there is no connector
    if(connectorQ.size() == 0){
        runV.push_back(token);
        token->run();
        return;
    }

    //second pass to build command tree
    while(!connectorQ.empty()){
        if(connectorQ.front()->getString() == SEMICOLON){
            if(runV.size() == 0){
                left_token = commandQ.front();
                commandQ.pop();
                CommaConnector* c = new CommaConnector(left_token);
                runV.push_back(c);
                connectorQ.pop();
                continue;
            }else if(runV.at(runV.size()-1)->getString() == SEMICOLON){
                left_token = commandQ.front();
                commandQ.pop();
                CommaConnector* cc = new CommaConnector(left_token);
                runV.push_back(cc);
                connectorQ.pop();
            }else if(runV.at(runV.size()-1)->getString() == AND 
                    || runV.at(runV.size()-1)->getString() == OR
                    || runV.at(runV.size()-1)->getString() == REDIRIN
                    || runV.at(runV.size()-1)->getString() == REDIROUT1
                    || runV.at(runV.size()-1)->getString() == REDIROUT2
                    || runV.at(runV.size()-1)->getString() == PIPE){
                CommaConnector* tc = new CommaConnector(runV.at(runV.size()-1));
                runV.push_back(tc);
                commandQ.pop();
                connectorQ.pop();
            }
        }else if(connectorQ.front()->getString() == AND){
            if(runV.size() == 0){
                left_token = commandQ.front();
                commandQ.pop();
                right_token = commandQ.front();
                AndConnector* ac = new AndConnector(left_token, right_token);
                runV.push_back(ac);
                connectorQ.pop();
                continue;
            }else if(runV.at(runV.size()-1)->getString() == SEMICOLON){
                left_token = commandQ.front();
                commandQ.pop();
                right_token = commandQ.front();
                AndConnector* acc = new AndConnector(left_token, right_token);
                runV.push_back(acc);
                connectorQ.pop();
            }else if(runV.at(runV.size()-1)->getString() == AND 
                    || runV.at(runV.size()-1)->getString() == OR
                    || runV.at(runV.size()-1)->getString() == REDIRIN
                    || runV.at(runV.size()-1)->getString() == REDIROUT1
                    || runV.at(runV.size()-1)->getString() == REDIROUT2
                    || runV.at(runV.size()-1)->getString() == PIPE){
                commandQ.pop();
                right_token = commandQ.front();
                AndConnector* aac = new AndConnector(runV.at(runV.size()-1), right_token);
                runV.push_back(aac);
                connectorQ.pop();
            }
        }else if(connectorQ.front()->getString() == OR){
            if(runV.size() == 0){
                left_token = commandQ.front();
                commandQ.pop();
                right_token = commandQ.front();
                OrConnector* oc = new OrConnector(left_token, right_token);
                runV.push_back(oc);
                connectorQ.pop();
            }else if(runV.at(runV.size()-1)->getString() == SEMICOLON){
                left_token = commandQ.front();
                commandQ.pop();
                right_token = commandQ.front();
                OrConnector* occ = new OrConnector(left_token, right_token);
                runV.push_back(occ);
                connectorQ.pop();
            }else if(runV.at(runV.size()-1)->getString() == AND 
                    || runV.at(runV.size()-1)->getString() == OR
                    || runV.at(runV.size()-1)->getString() == REDIRIN
                    || runV.at(runV.size()-1)->getString() == REDIROUT1
                    || runV.at(runV.size()-1)->getString() == REDIROUT2
                    || runV.at(runV.size()-1)->getString() == PIPE){
                commandQ.pop();
                right_token = commandQ.front();
                OrConnector* ooc = new OrConnector(runV.at(runV.size()-1), right_token);
                runV.push_back(ooc);
                connectorQ.pop();
            }
        }else if(connectorQ.front()->getString() == REDIRIN){
            if(runV.size() == 0){
                left_token = commandQ.front();
                commandQ.pop();
                right_token = commandQ.front();
                RedirectIn* rdIn1 = new RedirectIn(left_token, right_token);
                runV.push_back(rdIn1);
                connectorQ.pop();
            }else if(runV.at(runV.size()-1)->getString() == SEMICOLON){
                left_token = commandQ.front();
                commandQ.pop();
                right_token = commandQ.front();
                RedirectIn* rdIn2 = new RedirectIn(left_token, right_token);
                runV.push_back(rdIn2);
                connectorQ.pop();
            }else if(runV.at(runV.size()-1)->getString() == AND 
                    || runV.at(runV.size()-1)->getString() == OR
                    || runV.at(runV.size()-1)->getString() == REDIRIN
                    || runV.at(runV.size()-1)->getString() == REDIROUT1
                    || runV.at(runV.size()-1)->getString() == REDIROUT2
                    || runV.at(runV.size()-1)->getString() == PIPE){
                commandQ.pop();
                right_token = commandQ.front();
                RedirectIn* rdIn3 = new RedirectIn(runV.at(runV.size()-1), right_token);
                runV.push_back(rdIn3);
                connectorQ.pop();
            }
        }else if(connectorQ.front()->getString() == REDIROUT1 || connectorQ.front()->getString() == REDIROUT2 ){
            if(runV.size() == 0){
                //cout << "Command Queue Size before: " << commandQ.size() << endl;
                left_token = commandQ.front();
                commandQ.pop();
                right_token = commandQ.front();
                RedirectOut* rdOut1 = new RedirectOut(left_token, right_token);
                runV.push_back(rdOut1);
                connectorQ.pop();
                commandQ.pop();
                //cout << "Command Queue Size after: " << commandQ.size() << endl;
            }else if(runV.at(runV.size()-1)->getString() == SEMICOLON){
                left_token = commandQ.front();
                commandQ.pop();
                right_token = commandQ.front();
                RedirectOut* rdOut2 = new RedirectOut(left_token, right_token);
                runV.push_back(rdOut2);
                connectorQ.pop();
                commandQ.pop();
            }else if(runV.at(runV.size()-1)->getString() == AND 
                    || runV.at(runV.size()-1)->getString() == OR
                    || runV.at(runV.size()-1)->getString() == REDIRIN
                    || runV.at(runV.size()-1)->getString() == PIPE){
                //commandQ.pop();
                right_token = commandQ.front();
                RedirectOut* rdOut3 = new RedirectOut(runV.at(runV.size()-1), right_token);
                runV.push_back(rdOut3);
                connectorQ.pop();
                commandQ.pop();
            }
        }else if(connectorQ.front()->getString() == PIPE){
            if(runV.size() == 0){
                left_token = commandQ.front();
                commandQ.pop();
                right_token = commandQ.front();
                Pipes* pipe = new Pipes(left_token, right_token);
                runV.push_back(pipe);
                connectorQ.pop();
            }else if(runV.at(runV.size()-1)->getString() == SEMICOLON){
                left_token = commandQ.front();
                commandQ.pop();
                right_token = commandQ.front();
                Pipes* pipe2 = new Pipes(left_token, right_token);
                runV.push_back(pipe2);
                connectorQ.pop();
            }else if(runV.at(runV.size()-1)->getString() == AND 
                    || runV.at(runV.size()-1)->getString() == OR
                    || runV.at(runV.size()-1)->getString() == REDIRIN
                    || runV.at(runV.size()-1)->getString() == REDIROUT1
                    || runV.at(runV.size()-1)->getString() == REDIROUT2){
                commandQ.pop();
                right_token = commandQ.front();
                Pipes* pipe3 = new Pipes(runV.at(runV.size()-1), right_token);
                runV.push_back(pipe3);
                connectorQ.pop();
            }
        }

    }

    if(!commandQ.empty()){
        runV.push_back(commandQ.front());
        commandQ.pop();
    }




    for (unsigned int i = 0; i < runV.size(); i++) {
        //cout << "runV size " << runV.size()  << endl;
        //runV[i]->print();  //print out the command being run
       //if(runV.at(i)->getString() == SEMICOLON){
	   if(runV.at(i)->getString() == SEMICOLON)
	   {
             runV.at(i)->run();
	   }


       //}
    }

	if(runV.at(runV.size()-1)->getString() != SEMICOLON)
	{
		runV.at(runV.size()-1)->run();
	}


}
