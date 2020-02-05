"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const entity_1 = require("./entity");
class Project extends entity_1.Entity {
    get released() {
        return this._released;
    }
    set released(value) {
        this._released = value;
    }
    addStory(story) {
        this._stories.push(story);
    }
    get stories() {
        return this._stories;
    }
    removeStory(story) {
        let storyPosition = this._stories.indexOf(story);
        this._stories.splice(storyPosition, 1);
    }
}
exports.Project = Project;
