exports.id = "main";
exports.modules = {

/***/ "./src/common/http-exception.ts":
/*!**************************************!*\
  !*** ./src/common/http-exception.ts ***!
  \**************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\nvar __extends = (this && this.__extends) || (function () {\n    var extendStatics = function (d, b) {\n        extendStatics = Object.setPrototypeOf ||\n            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||\n            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };\n        return extendStatics(d, b);\n    };\n    return function (d, b) {\n        extendStatics(d, b);\n        function __() { this.constructor = d; }\n        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());\n    };\n})();\nObject.defineProperty(exports, \"__esModule\", { value: true });\nvar HttpException = /** @class */ (function (_super) {\n    __extends(HttpException, _super);\n    function HttpException(statusCode, message, error) {\n        var _this = _super.call(this, message) || this;\n        console.log(\"constructor: \" + statusCode);\n        _this.statusCode = statusCode;\n        _this.message = message;\n        _this.error = error || null; //error is optional, if there is no 'error', then-> null\n        return _this;\n    }\n    return HttpException;\n}(Error));\nexports.default = HttpException;\n\n\n//# sourceURL=webpack:///./src/common/http-exception.ts?");

/***/ }),

/***/ "./src/items/items.service.ts":
/*!************************************!*\
  !*** ./src/items/items.service.ts ***!
  \************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\n/**\n * Data Model Interfaces\n */\nvar __assign = (this && this.__assign) || function () {\n    __assign = Object.assign || function(t) {\n        for (var s, i = 1, n = arguments.length; i < n; i++) {\n            s = arguments[i];\n            for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))\n                t[p] = s[p];\n        }\n        return t;\n    };\n    return __assign.apply(this, arguments);\n};\nvar __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {\n    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }\n    return new (P || (P = Promise))(function (resolve, reject) {\n        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }\n        function rejected(value) { try { step(generator[\"throw\"](value)); } catch (e) { reject(e); } }\n        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }\n        step((generator = generator.apply(thisArg, _arguments || [])).next());\n    });\n};\nvar __generator = (this && this.__generator) || function (thisArg, body) {\n    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;\n    return g = { next: verb(0), \"throw\": verb(1), \"return\": verb(2) }, typeof Symbol === \"function\" && (g[Symbol.iterator] = function() { return this; }), g;\n    function verb(n) { return function (v) { return step([n, v]); }; }\n    function step(op) {\n        if (f) throw new TypeError(\"Generator is already executing.\");\n        while (_) try {\n            if (f = 1, y && (t = op[0] & 2 ? y[\"return\"] : op[0] ? y[\"throw\"] || ((t = y[\"return\"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;\n            if (y = 0, t) op = [op[0] & 2, t.value];\n            switch (op[0]) {\n                case 0: case 1: t = op; break;\n                case 4: _.label++; return { value: op[1], done: false };\n                case 5: _.label++; y = op[1]; op = [0]; continue;\n                case 7: op = _.ops.pop(); _.trys.pop(); continue;\n                default:\n                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }\n                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }\n                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }\n                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }\n                    if (t[2]) _.ops.pop();\n                    _.trys.pop(); continue;\n            }\n            op = body.call(thisArg, _);\n        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }\n        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };\n    }\n};\nvar __importDefault = (this && this.__importDefault) || function (mod) {\n    return (mod && mod.__esModule) ? mod : { \"default\": mod };\n};\nObject.defineProperty(exports, \"__esModule\", { value: true });\nvar http_exception_1 = __importDefault(__webpack_require__(/*! ../common/http-exception */ \"./src/common/http-exception.ts\"));\n/**\n * In-Memory Store\n */\nvar items = {\n    1: {\n        id: 1,\n        name: \"Burger\",\n        price: 5.99,\n        description: \"Tasty\",\n        image: \"https://cdn.auth0.com/blog/whatabyte/burger-sm.png\"\n    },\n    2: {\n        id: 2,\n        name: \"Pizza\",\n        price: 2.99,\n        description: \"Cheesy\",\n        image: \"https://cdn.auth0.com/blog/whatabyte/pizza-sm.png\"\n    },\n    3: {\n        id: 3,\n        name: \"Tea\",\n        price: 1.99,\n        description: \"Informative\",\n        image: \"https://cdn.auth0.com/blog/whatabyte/tea-sm.png\"\n    }\n};\n/**\n * Service Methods\n */\nexports.findAll = function () { return __awaiter(void 0, void 0, void 0, function () {\n    return __generator(this, function (_a) {\n        return [2 /*return*/, items];\n    });\n}); };\nexports.find = function (id) { return __awaiter(void 0, void 0, void 0, function () {\n    var record;\n    return __generator(this, function (_a) {\n        record = items[id];\n        if (record) {\n            return [2 /*return*/, record];\n        }\n        throw new Error(\"No record found!\");\n    });\n}); };\nexports.create = function (newItem) { return __awaiter(void 0, void 0, void 0, function () {\n    var id;\n    return __generator(this, function (_a) {\n        id = new Date().valueOf();\n        items[id] = __assign(__assign({}, newItem), { id: id });\n        return [2 /*return*/];\n    });\n}); };\nexports.update = function (updatedItem) { return __awaiter(void 0, void 0, void 0, function () {\n    return __generator(this, function (_a) {\n        if (items[updatedItem.id]) {\n            items[updatedItem.id] = updatedItem;\n            return [2 /*return*/];\n        }\n        throw new http_exception_1.default(600, \"No record found to update\");\n    });\n}); };\nexports.remove = function (id) { return __awaiter(void 0, void 0, void 0, function () {\n    var record;\n    return __generator(this, function (_a) {\n        record = items[id];\n        if (record) {\n            delete items[id];\n            return [2 /*return*/];\n        }\n        throw new Error(\"No record found to delete\");\n    });\n}); };\n\n\n//# sourceURL=webpack:///./src/items/items.service.ts?");

/***/ }),

/***/ "./src/middleware/error.middleware.ts":
/*!********************************************!*\
  !*** ./src/middleware/error.middleware.ts ***!
  \********************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\nObject.defineProperty(exports, \"__esModule\", { value: true });\n//It's important to note that you must provide four \n//arguments to identify a function as an error-handling \n//middleware function in Express\nexports.errorHandler = function (error, request, response, next //You must specify the next object to \n//maintain the error-handling signature even if you don't use it.\n) {\n    console.log(error.statusCode);\n    var status = error.statusCode || 500; //internal server error\n    var message = error.message + \" middleware..\" || false;\n    response.status(status).send(message);\n};\n\n\n//# sourceURL=webpack:///./src/middleware/error.middleware.ts?");

/***/ })

};