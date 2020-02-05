"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const task_1 = require("./task");
function sendCompletionEmail(completable) {
    if (!completable.completed) {
        console.error(`Please, complete '${completable.title}' before sending email.`);
        return;
    }
    console.log(`Sending email about '${completable.title}'`);
}
let bugFix = new task_1.Task(1, 'Weirdo flying bug');
sendCompletionEmail(bugFix);
bugFix.completed = true;
sendCompletionEmail(bugFix);
