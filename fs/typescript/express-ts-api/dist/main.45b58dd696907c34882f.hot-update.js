exports.id = "main";
exports.modules = {

/***/ "./src/index.ts":
/*!**********************!*\
  !*** ./src/index.ts ***!
  \**********************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\n/**\n * Required External Modules\n */\nvar __importStar = (this && this.__importStar) || function (mod) {\n    if (mod && mod.__esModule) return mod;\n    var result = {};\n    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];\n    result[\"default\"] = mod;\n    return result;\n};\nvar __importDefault = (this && this.__importDefault) || function (mod) {\n    return (mod && mod.__esModule) ? mod : { \"default\": mod };\n};\nObject.defineProperty(exports, \"__esModule\", { value: true });\nvar dotenv = __importStar(__webpack_require__(/*! dotenv */ \"dotenv\"));\nvar express_1 = __importDefault(__webpack_require__(/*! express */ \"express\"));\nvar cors_1 = __importDefault(__webpack_require__(/*! cors */ \"cors\"));\nvar helmet_1 = __importDefault(__webpack_require__(/*! helmet */ \"helmet\"));\nvar items_router_1 = __webpack_require__(/*! ./items/items.router */ \"./src/items/items.router.ts\");\nvar notFound_middleware_1 = __webpack_require__(/*! ./middleware/notFound.middleware */ \"./src/middleware/notFound.middleware.ts\");\ndotenv.config(); //load any environmental variables from the local .env file\n/**\n * App Variables\n */\nif (!process.env.PORT) { //check if the environmental variable PORT was loaded \n    //into process.env. If so, parse its value as a \n    //number type and create an instance of an Express application\n    process.exit(1);\n}\nvar PORT = parseInt(process.env.PORT, 10);\nvar app = express_1.default();\n/**\n *  App Configuration\n */\napp.use(helmet_1.default());\napp.use(cors_1.default()); //By mounting cors(), you enable all CORS requests.\napp.use(express_1.default.json()); //This is a built-in middleware function in Express. \n//It parses incoming requests with JSON payloads and is based on body-parser.\n//which populates the request object with a new body object containing the parsed data.\napp.use(\"/items\", items_router_1.itemsRouter);\n//mount the errorHandler and notFoundHandler functions.\n/*our application can't reach any routes that you define after mounting the\nerrorHandler middleware function because you close the request-response cycle\nwithin errorHandler by sending a response to the client. As such,\nthe errorHandler middleware function must be mounted\nafter all the controller functions of your application have been mounted.*/\n//app.use(errorHandler);\napp.use(function (error, req, res, next) {\n    // Any request to this server will get here, and will send an HTTP\n    // response with the error message 'woops'\n    res.json({ message: error.message });\n});\napp.use(notFound_middleware_1.notFoundHandler);\n/*But, as noted earlier, errorHandler won't catch 404 errors.\nHowever, you can catch these errors by making notFoundHandler the last\nmiddleware function that you mount, which effectively creates a catch-all\nhandler for your app.*/\n/**\n * Server Activation\n */\nvar server = app.listen(PORT, function () {\n    console.log(\"Listening on port \" + PORT);\n});\nif (true) {\n    module.hot.accept();\n    module.hot.dispose(function () { return server.close(); });\n}\n\n\n//# sourceURL=webpack:///./src/index.ts?");

/***/ }),

/***/ "./src/items/items.router.ts":
/*!***********************************!*\
  !*** ./src/items/items.router.ts ***!
  \***********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\nvar __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {\n    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }\n    return new (P || (P = Promise))(function (resolve, reject) {\n        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }\n        function rejected(value) { try { step(generator[\"throw\"](value)); } catch (e) { reject(e); } }\n        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }\n        step((generator = generator.apply(thisArg, _arguments || [])).next());\n    });\n};\nvar __generator = (this && this.__generator) || function (thisArg, body) {\n    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;\n    return g = { next: verb(0), \"throw\": verb(1), \"return\": verb(2) }, typeof Symbol === \"function\" && (g[Symbol.iterator] = function() { return this; }), g;\n    function verb(n) { return function (v) { return step([n, v]); }; }\n    function step(op) {\n        if (f) throw new TypeError(\"Generator is already executing.\");\n        while (_) try {\n            if (f = 1, y && (t = op[0] & 2 ? y[\"return\"] : op[0] ? y[\"throw\"] || ((t = y[\"return\"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;\n            if (y = 0, t) op = [op[0] & 2, t.value];\n            switch (op[0]) {\n                case 0: case 1: t = op; break;\n                case 4: _.label++; return { value: op[1], done: false };\n                case 5: _.label++; y = op[1]; op = [0]; continue;\n                case 7: op = _.ops.pop(); _.trys.pop(); continue;\n                default:\n                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }\n                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }\n                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }\n                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }\n                    if (t[2]) _.ops.pop();\n                    _.trys.pop(); continue;\n            }\n            op = body.call(thisArg, _);\n        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }\n        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };\n    }\n};\nvar __importDefault = (this && this.__importDefault) || function (mod) {\n    return (mod && mod.__esModule) ? mod : { \"default\": mod };\n};\nvar __importStar = (this && this.__importStar) || function (mod) {\n    if (mod && mod.__esModule) return mod;\n    var result = {};\n    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];\n    result[\"default\"] = mod;\n    return result;\n};\nObject.defineProperty(exports, \"__esModule\", { value: true });\n/**\n * Required External Modules and Interfaces\n */\nvar express_1 = __importDefault(__webpack_require__(/*! express */ \"express\"));\nvar ItemService = __importStar(__webpack_require__(/*! ./items.service */ \"./src/items/items.service.ts\"));\n/**\n * Router Definition\n */\nexports.itemsRouter = express_1.default.Router();\n/**\n * Controller Definitions\n */\n// GET items/\nexports.itemsRouter.get(\"/\", function (req, res) { return __awaiter(void 0, void 0, void 0, function () {\n    var items, e_1;\n    return __generator(this, function (_a) {\n        switch (_a.label) {\n            case 0:\n                _a.trys.push([0, 2, , 3]);\n                return [4 /*yield*/, ItemService.findAll()];\n            case 1:\n                items = _a.sent();\n                res.status(200).send(items);\n                return [3 /*break*/, 3];\n            case 2:\n                e_1 = _a.sent();\n                res.status(404).send(e_1.message);\n                return [3 /*break*/, 3];\n            case 3: return [2 /*return*/];\n        }\n    });\n}); });\n// GET items/:id\nexports.itemsRouter.get(\"/:id\", function (req, res, next) { return __awaiter(void 0, void 0, void 0, function () {\n    var id, item, e_2;\n    return __generator(this, function (_a) {\n        switch (_a.label) {\n            case 0:\n                id = parseInt(req.params.id, 10);\n                _a.label = 1;\n            case 1:\n                _a.trys.push([1, 3, , 4]);\n                throw new Error(\"i had enough!\");\n            case 2:\n                item = _a.sent();\n                res.status(200).send(item);\n                return [3 /*break*/, 4];\n            case 3:\n                e_2 = _a.sent();\n                next(e_2);\n                return [3 /*break*/, 4];\n            case 4: return [2 /*return*/];\n        }\n    });\n}); });\n// POST items/\nexports.itemsRouter.post(\"/\", function (req, res) { return __awaiter(void 0, void 0, void 0, function () {\n    var item, e_3;\n    return __generator(this, function (_a) {\n        switch (_a.label) {\n            case 0:\n                _a.trys.push([0, 2, , 3]);\n                item = req.body.item;\n                return [4 /*yield*/, ItemService.create(item)];\n            case 1:\n                _a.sent();\n                res.sendStatus(201);\n                return [3 /*break*/, 3];\n            case 2:\n                e_3 = _a.sent();\n                res.status(404).send(e_3.message);\n                return [3 /*break*/, 3];\n            case 3: return [2 /*return*/];\n        }\n    });\n}); });\n// PUT items/\nexports.itemsRouter.put(\"/\", function (req, res) { return __awaiter(void 0, void 0, void 0, function () {\n    var item, e_4;\n    return __generator(this, function (_a) {\n        switch (_a.label) {\n            case 0:\n                _a.trys.push([0, 2, , 3]);\n                item = req.body.item;\n                return [4 /*yield*/, ItemService.update(item)];\n            case 1:\n                _a.sent();\n                res.sendStatus(200);\n                return [3 /*break*/, 3];\n            case 2:\n                e_4 = _a.sent();\n                res.status(500).send(e_4.message);\n                return [3 /*break*/, 3];\n            case 3: return [2 /*return*/];\n        }\n    });\n}); });\n// DELETE items/:id\nexports.itemsRouter.delete(\"/:id\", function (req, res) { return __awaiter(void 0, void 0, void 0, function () {\n    var id, e_5;\n    return __generator(this, function (_a) {\n        switch (_a.label) {\n            case 0:\n                _a.trys.push([0, 2, , 3]);\n                id = parseInt(req.params.id, 10);\n                return [4 /*yield*/, ItemService.remove(id)];\n            case 1:\n                _a.sent();\n                res.sendStatus(200);\n                return [3 /*break*/, 3];\n            case 2:\n                e_5 = _a.sent();\n                res.status(500).send(e_5.message);\n                return [3 /*break*/, 3];\n            case 3: return [2 /*return*/];\n        }\n    });\n}); });\n\n\n//# sourceURL=webpack:///./src/items/items.router.ts?");

/***/ })

};