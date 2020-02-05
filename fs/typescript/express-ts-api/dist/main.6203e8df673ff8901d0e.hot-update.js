exports.id = "main";
exports.modules = {

/***/ "./src/index.ts":
/*!**********************!*\
  !*** ./src/index.ts ***!
  \**********************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\n/**\n * Required External Modules\n */\nvar __importStar = (this && this.__importStar) || function (mod) {\n    if (mod && mod.__esModule) return mod;\n    var result = {};\n    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];\n    result[\"default\"] = mod;\n    return result;\n};\nvar __importDefault = (this && this.__importDefault) || function (mod) {\n    return (mod && mod.__esModule) ? mod : { \"default\": mod };\n};\nObject.defineProperty(exports, \"__esModule\", { value: true });\nvar dotenv = __importStar(__webpack_require__(/*! dotenv */ \"dotenv\"));\nvar express_1 = __importDefault(__webpack_require__(/*! express */ \"express\"));\nvar cors_1 = __importDefault(__webpack_require__(/*! cors */ \"cors\"));\nvar helmet_1 = __importDefault(__webpack_require__(/*! helmet */ \"helmet\"));\nvar items_router_1 = __webpack_require__(/*! ./items/items.router */ \"./src/items/items.router.ts\");\nvar notFound_middleware_1 = __webpack_require__(/*! ./middleware/notFound.middleware */ \"./src/middleware/notFound.middleware.ts\");\ndotenv.config(); //load any environmental variables from the local .env file\n/**\n * App Variables\n */\nif (!process.env.PORT) { //check if the environmental variable PORT was loaded \n    //into process.env. If so, parse its value as a \n    //number type and create an instance of an Express application\n    process.exit(1);\n}\nvar PORT = parseInt(process.env.PORT, 10);\nvar app = express_1.default();\n/**\n *  App Configuration\n */\napp.use(helmet_1.default());\napp.use(cors_1.default()); //By mounting cors(), you enable all CORS requests.\napp.use(express_1.default.json()); //This is a built-in middleware function in Express. \n//It parses incoming requests with JSON payloads and is based on body-parser.\n//which populates the request object with a new body object containing the parsed data.\napp.use(\"/items\", items_router_1.itemsRouter);\n//mount the errorHandler and notFoundHandler functions.\n/*our application can't reach any routes that you define after mounting the\nerrorHandler middleware function because you close the request-response cycle\nwithin errorHandler by sending a response to the client. As such,\nthe errorHandler middleware function must be mounted\nafter all the controller functions of your application have been mounted.*/\n//app.use(errorHandler);\napp.use(notFound_middleware_1.notFoundHandler);\n/*But, as noted earlier, errorHandler won't catch 404 errors.\nHowever, you can catch these errors by making notFoundHandler the last\nmiddleware function that you mount, which effectively creates a catch-all\nhandler for your app.*/\n/**\n * Server Activation\n */\nvar server = app.listen(PORT, function () {\n    console.log(\"Listening on port \" + PORT);\n});\nif (true) {\n    module.hot.accept();\n    module.hot.dispose(function () { return server.close(); });\n}\n\n\n//# sourceURL=webpack:///./src/index.ts?");

/***/ }),

/***/ "./src/middleware/error.middleware.ts":
false

};