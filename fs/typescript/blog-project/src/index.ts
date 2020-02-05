import {Task} from "./task";
import {Completable} from "./completable";

function sendCompletionEmail(completable: Completable) {
  if (!completable.completed) {
    // ignore incompleted entities
    console.error(`Please, complete '${completable.title}' before sending email.`);
    return;
  }
  console.log(`Sending email about '${completable.title}'`);
  // ...
}

let bugFix = new Task(1, 'Weirdo flying bug');
sendCompletionEmail(bugFix);
bugFix.completed = true;
sendCompletionEmail(bugFix);