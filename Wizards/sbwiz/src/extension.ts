'use strict';

import * as vscode from 'vscode';


export function activate(context: vscode.ExtensionContext) {

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

    let disposable = vscode.commands.registerCommand('extension.createSBEComponent', () => {

        let valueSelection:[number, number] = [0, 0];

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


export function deactivate() {
}
