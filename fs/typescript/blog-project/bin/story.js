"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const entity_1 = require("./entity");
class Story extends entity_1.Entity {
    constructor() {
        super(...arguments);
        this._tasks = [];
    }
    get completed() {
        return this._completed;
    }
    set completed(value) {
        this._completed = value;
    }
    get responsible() {
        return this._responsible;
    }
    set responsible(value) {
        this._responsible = value;
    }
    addTask(task) {
        this._tasks.push(task);
    }
    get tasks() {
        return this._tasks;
    }
    removeTask(task) {
        let taskPosition = this._tasks.indexOf(task);
        this._tasks.splice(taskPosition, 1);
    }
}
exports.Story = Story;
