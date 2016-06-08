#include <queue>

void  ExeDriver(vector<string> &command_collection) {
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
		return;
	}



    //second pass to build command tree
    while(!connectorQ.empty()) {
		if(connectorQ.front()->getString() == SEMICOLON)
		{
				if(runV.size() == 0)
				{
						left_token = commandQ.front();
						commandQ.pop();
						CommaConnector* c = new CommaConnector(left_token);
						runV.push_back(c);
						connectorQ.pop();
						continue;
				}

				if(runV.at(runV.size()-1)->getString() == SEMICOLON)
				{
						left_token = commandQ.front();
						commandQ.pop();
						CommaConnector* cc = new CommaConnector(left_token);
						runV.push_back(cc);
						connectorQ.pop();
				}
				else if(runV.at(runV.size()-1)->getString() == AND || runV.at(runV.size()-1)->getString() == OR)
				{
						CommaConnector* tc = new CommaConnector(runV.at(runV.size()-1));						
						runV.push_back(tc);				
						commandQ.pop();
						connectorQ.pop();
				}

		}

		else if(connectorQ.front()->getString() == AND)
		{
				if(runV.size() == 0)
				{

						left_token = commandQ.front();
						commandQ.pop();
						right_token = commandQ.front();
						AndConnector* ac = new AndConnector(left_token, right_token);
						runV.push_back(ac);
						connectorQ.pop();
						continue;
				}
				
				else if(runV.at(runV.size()-1)->getString() == SEMICOLON)
				{

						left_token = commandQ.front();
						commandQ.pop();
						right_token = commandQ.front();
						AndConnector* acc = new AndConnector(left_token, right_token);
						runV.push_back(acc);
						connectorQ.pop();

				}

				else if(runV.at(runV.size()-1)->getString() == AND || runV.at(runV.size()-1)->getString() == OR)
			    {
					commandQ.pop();
					right_token = commandQ.front();
					AndConnector* aac = new AndConnector(runV.at(runV.size()-1), right_token);
					runV.push_back(aac);
					connectorQ.pop();
				}
		}
		

		else if(connectorQ.front()->getString() == OR)
		{
				if(runV.size() == 0)
				{

						left_token = commandQ.front();
						commandQ.pop();
						right_token = commandQ.front();
						OrConnector* oc = new OrConnector(left_token, right_token);
						runV.push_back(oc);
						connectorQ.pop();
				}
  
				else if(runV.at(runV.size()-1)->getString() == SEMICOLON)
				{

						left_token = commandQ.front();
						commandQ.pop();
						right_token = commandQ.front();
						OrConnector* occ = new OrConnector(left_token, right_token);
						runV.push_back(occ);
						connectorQ.pop();

				}
				else if(runV.at(runV.size()-1)->getString() == AND || runV.at(runV.size()-1)->getString() == OR)
			    {
					commandQ.pop();
					right_token = commandQ.front();
					OrConnector* ooc = new OrConnector(runV.at(runV.size()-1), right_token);
					runV.push_back(ooc);
					connectorQ.pop();
				}
		}	

       // left_token = commandQ.front();   commandQ.pop();
		//if(!commandQ.empty())
		//{
        //	right_token = commandQ.front(); //commandQ.pop();
    	//
        //******Debugging*******//
        //left_token->print(); 
        //cout << "|";
        //right_token->print();

        //if(connectorQ.front()->getString() == SEMICOLON){

          //  CommaConnector* cc = new CommaConnector(left_token);
           // runV.push_back(cc);
            //runQ.push(cc);
           // left_token = commandQ.front();
		//	connectorQ.pop();
		//	commandQ.pop();
		//	continue;
        //}else if(connectorQ.front()->getString() == AND){
           // right_token = commandQ.front();
        //    AndConnector* ac = new AndConnector(left_token, right_token);
         //   runV.push_back(ac);
         //   connectorQ.pop();
		//	continue;
            //runQ.push(ac);
        //}else if(connectorQ.front()->getString() == OR){
           // right_token = commandQ.front();
         //   OrConnector* oc = new OrConnector(left_token, right_token);
         //   runV.push_back(oc);
	//		connectorQ.pop();
			//commandQ.pop();

	//		continue;
            //runQ.push(oc);
      //  }else{
		//		cout << "OTHER" << endl;
         //   runV.push_back(left_token);
            //runQ.push(right_token);
      //  }
	} 
	 
    for (unsigned int i = 0; i < runV.size(); i++) {
        //runV[i]->print(); //print out the command being run
       if(runV.at(i)->getString() == SEMICOLON)
	   {
			 runV.at(i)->run();
			 continue;
	   }
	   

        //runQ.front()->run();
        //runQ.pop();
    }
   	 
   if(runV.at(runV.size()-1)->getString() != SEMICOLON)
   {
		   runV.at(runV.size()-1)->run();
   }

    
    // for (unsigned int i = 0; i < runV.size(); i++) {
    //     //runV[i]->print(); //print out the command being run
    //     runV[i]->run();
    // }
   
}
