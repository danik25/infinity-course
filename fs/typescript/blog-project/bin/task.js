"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const entity_1 = require("./entity");
class Task extends entity_1.Entity {
    get completed() {
        return this._completed;
    }
    set completed(value) {
        this._completed = value;
    }
    get priority() {
        return this._priority;
    }
    set priority(value) {
        this._priority = value;
    }
}
exports.Task = Task;
