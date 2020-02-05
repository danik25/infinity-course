exports.id = "main";
exports.modules = {

/***/ "./src/middleware/error.middleware.ts":
/*!********************************************!*\
  !*** ./src/middleware/error.middleware.ts ***!
  \********************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\nObject.defineProperty(exports, \"__esModule\", { value: true });\n//It's important to note that you must provide four \n//arguments to identify a function as an error-handling \n//middleware function in Express\nexports.errorHandler = function (error, request, response, next //You must specify the next object to \n//maintain the error-handling signature even if you don't use it.\n) {\n    var status = error.statusCode || 500; //internal server error\n    var message = error.message + \" middleware..\" || false;\n    response.status(status).send(message);\n};\n\n\n//# sourceURL=webpack:///./src/middleware/error.middleware.ts?");

/***/ })

};