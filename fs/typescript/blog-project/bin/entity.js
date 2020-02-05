"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Entity {
    constructor(id, title) {
        this._id = id;
        this._title = title;
        this._creationDate = new Date();
    }
    get id() {
        return this._id;
    }
    get title() {
        return this._title;
    }
    set title(title) {
        this._title = title;
    }
    get creationDate() {
        return this._creationDate;
    }
}
exports.Entity = Entity;
