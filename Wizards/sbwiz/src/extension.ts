'use strict';

import * as vscode from 'vscode';
import * as cp from 'child_process';

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

    let disposable = vscode.commands.registerCommand('extension.addSBECode', (arg) => {

        if(arg === undefined) {
            vscode.window.showErrorMessage("Add code must be run on a folder");
            return;
        }

        let pick = vscode.window.showQuickPick(["Component", "ServerObject", "PlayerState", "BotState", "Config", "EffectLayer", "Anchor", "Path", "Volume"]);
        pick.then(function (selection) {
            if(selection === undefined) {
                return;
            }

            let valueSelection:[number, number] = [0, 0];

            let options = {
                prompt: "Enter Class Name",
                value: "",
                valueSelection: valueSelection,
                validateInput: identifierValidator
            };
    
            options['value'] = selection;
    
            let result = vscode.window.showInputBox(options);
            if(result == undefined) {
                return;
            }
    
            result.then(function (class_name) {
                if(class_name === undefined) {
                    return;
                }
    
                let command = "\"" + vscode.workspace.rootPath + "/addcode\" ";
                command += selection + " ";
                command += class_name + " ";
                command += "\"" + arg.path + "\" ";
                command += "\"" + vscode.workspace.rootPath + "\" ";
                command += "mv";
                cp.exec(command, {}, function(error, stdout, stderr) {
                    if(error) {
                        vscode.window.showErrorMessage("exec error: " + error);
                        return;
                    }
                });
            });
        });
    });

    context.subscriptions.push(disposable);
}


export function deactivate() {
}
