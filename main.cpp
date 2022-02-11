//
//  main.cpp
//  Program4
//
//  Created by Danny Webb-McClain on 10/26/21.
//

#include <iostream>
#include <cctype>
#include "Stack.h"
#include "Node.h"
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    Stack<char> postFix; //stack for postfix
    Stack<int> Eval; //stack for result of postfix operation
    string userInput; //user input
    string postExpression; //postfix concat string
    int parenTrack = 0; //used for tracking how many operators need to be popped of the stack in the case of parenthesis
    int j = 0; //used for tracking parenthesis loop
    int result = 0; //tracks the result of the postfix operation
    char temp;
    int int1, int2; //will be used for evaluation for the stack
    int convert;//used for going from ASCII to int
    bool failFlag = false;
    
    while(userInput != "exit"){ //continue looping until user opts to exit
        failFlag = false;
        cout << "Enter expression (or exit to end): ";
        getline(cin, userInput);
        //check user input to ensure it is valid, if so proceed
        if (!(isdigit(userInput[0])) && userInput[0] != 'e' && userInput[0] != '(') {
            cout << "Invalid Expression" << endl;
            failFlag = true;
        } else if(userInput != "exit" && failFlag != true){
            cout << "Expression: " << userInput << endl; //print original expression
            postExpression = "";
            for (int i = 0; i < userInput.length(); ++i) {
                if (isdigit(userInput[i])) {
                    //convert = userInput[i] - 48;
                    postExpression = postExpression + " " + userInput[i];
                } else{
                    // if an operator is found in the string push it to the operator stack
                    parenTrack = 0;//reset parenTrack every iteration
                    if (userInput[i] == '+' || userInput[i] == '-' || userInput[i] == '/' || userInput[i] == '*') {
                        postFix.push(userInput[i]);
                    } else if(userInput[i] == '('){ //handle the case of parenthesis
                        j = i;
                        while(userInput[j] != ')'){
                            if (isdigit(userInput[j])) {
                                postExpression = postExpression + " " + userInput[j];
                            } else{
                                if (userInput[j] != ' ') {
                                    parenTrack++;
                                    postFix.push(userInput[j]);
                                }
                                
                            }
                            j++;
                        }
                        i = j;//pick up from where the parenthesis loop left off
                    }
                    
                }
                for(int z = 0; z < parenTrack-1 ; ++z){
                    if (postFix.getTop() == '(') {
                        postFix.pop();
                    }else{
                        postExpression = postExpression + " " + postFix.getTop();
                        postFix.pop();
                    }
                    
                }
                
                
            }
        }
        while (!(postFix.empty())) {
            if (postFix.getTop() == '(') {
                postFix.pop();
            } else{
                postExpression = postExpression + " " + postFix.getTop();
                postFix.pop();
            }
        }
        for(int i = 0; i < postExpression.length(); ++i){
            if (isdigit(postExpression[i])) {
                convert = postExpression[i] - 48;
                Eval.push(convert);//push digit onto the stack
            } else{
                temp = postExpression[i];
                switch(temp){
                    case '*':
                        int1 = Eval.getTop();
                        Eval.pop();
                        int2 = Eval.getTop();
                        Eval.pop();
                        result = int1 * int2;
                        Eval.push(result);
                        break;
                    case '/':
                        int1 = Eval.getTop();
                        Eval.pop();
                        int2 = Eval.getTop();
                        Eval.pop();
                        result = int2 / int1;
                        Eval.push(result);
                        break;
                    case '+':
                        int1 = Eval.getTop();
                        Eval.pop();
                        int2 = Eval.getTop();
                        Eval.pop();
                        result = int1 + int2;
                        Eval.push(result);
                        break;
                    case '-':
                        int1 = Eval.getTop();
                        Eval.pop();
                        int2 = Eval.getTop();
                        Eval.pop();
                        result = int2 - int1;
                        Eval.push(result);
                        break;
                    default:
                        break;
                }
            }
        }
        if (userInput == "exit") {
            cout << "Exiting program ..." << endl;
        }else if(failFlag != true){
            cout << "Postfix form:";
            cout << postExpression << endl;
            cout << "Result:" << Eval.getTop() << endl;
            Eval.pop();
        }
        
    }
    return 0;
}
