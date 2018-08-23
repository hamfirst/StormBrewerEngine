'use strict';
// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
import * as vscode from 'vscode';

// this method is called when your extension is activated
// your extension is activated the very first time the command is executed
export function activate(context: vscode.ExtensionContext) {

    // Use the console to output diagnostic information (console.log) and errors (console.error)
    // This line of code will only be executed once when your extension is activated
    console.log('Congratulations, your extension "sbwiz" is now active!');

    let identifierValidator = function(value:string) {
        if(value.length == 0 || 
            (value[0] >= '0' && value[0] <= '9')) {
                return "Invalid Identifier";
            }

        for(let c of value) {
            if( (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9') ||
                (c == '_')) {
                    continue;
                }
            
            return "Invalid Identifier"
        }

        return "";
    }

    // The command has been defined in the package.json file
    // Now provide the implementation of the command with  registerCommand
    // The commandId parameter must match the command field in package.json
    let disposable = vscode.commands.registerCommand('extension.createSBEComponent', () => {
        // The code you place here will be executed every time your command is executed

        let valueSelection:[number, number] = [0, 0];
        // Display a message box to the user
        let options = {
            prompt: "Enter Class Name",
            value: "Component",
            valueSelection: valueSelection,
            validateInput: identifierValidator
        };

        let result = vscode.window.showInputBox(options);
        if(result == undefined) {
            return;
        }

    });

    context.subscriptions.push(disposable);
}

// this method is called when your extension is deactivated
export function deactivate() {
}