#include <queue>

vector<ExecuteBase*>  ExeDriver(vector<string> &command_collection) {
    string AND = "&&", OR = "||" , SEMICOLON = ";";

    queue<Token*> commandQ; // temporary vector to hold processed token(commands & connectors)
    queue<Token*> connectorQ; // holds connectors
    vector<ExecuteBase*> runV;
    queue<ExecuteBase*> runQ;
    Token* left_token;
	Token* right_token;
    Token* token = new Token();
    //first pass, turn token into commands and connectors




							
    for(unsigned int i = 0 ; i < command_collection.size() ; i++){
        //
        if(command_collection[i] == SEMICOLON 
            || command_collection[i] == AND 
            || command_collection[i] == OR){
            
            //cout << "First iteration: "; token->print();
            
            commandQ.push(token);
            token = new Token();
            token->addArgs(command_collection[i]);
            connectorQ.push(token);
            token = new Token();
        }else if(command_collection.at(i) != SEMICOLON && command_collection.at(i) != OR && command_collection.at(i) != AND){
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
   	
    if(connectorQ.size() == 0)
	{
		runV.push_back(token);
		token->run();
		return runV;
	}



    //second pass to build command tree
    while(!connectorQ.empty()) {
        left_token = commandQ.front();   commandQ.pop();
		if(!commandQ.empty())
		{
        	right_token = commandQ.front(); //commandQ.pop();
    	}
        //******Debugging*******//
        //left_token->print(); 
        //cout << "|";
        //right_token->print();

        if(connectorQ.front()->getString() == SEMICOLON){
            CommaConnector* cc = new CommaConnector(left_token);
            runV.push_back(cc);
            //runQ.push(cc);
            left_token = commandQ.front();
			connectorQ.pop();
			commandQ.pop();
			continue;
        }else if(connectorQ.front()->getString() == AND){
            right_token = commandQ.front();
            AndConnector* ac = new AndConnector(left_token, right_token);
            runV.push_back(ac);
            connectorQ.pop();
			commandQ.pop();
			continue;
            //runQ.push(ac);
        }else if(connectorQ.front()->getString() == OR){
            right_token = commandQ.front();
            OrConnector* oc = new OrConnector(left_token, right_token);
            runV.push_back(oc);
			connectorQ.pop();
			commandQ.pop();
			if(connectorQ.empty())
			{
					break;
			}

			if(connectorQ.front()->getString() == SEMICOLON)
			{
					connectorQ.pop();
			}
			continue;
            //runQ.push(oc);
        }else{
            runV.push_back(left_token);
            //runQ.push(right_token);
        }
    }
    for (unsigned int i = 0; i < runV.size(); i++) {
        //runV[i]->print(); //print out the command being run
        runV.at(i)->run();
        //runQ.front()->run();
        //runQ.pop();
    }
    
    
    // for (unsigned int i = 0; i < runV.size(); i++) {
    //     //runV[i]->print(); //print out the command being run
    //     runV[i]->run();
    // }
    
   return runV; 
}
