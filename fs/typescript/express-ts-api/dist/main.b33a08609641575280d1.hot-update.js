exports.id = "main";
exports.modules = {

/***/ "./src/middleware/notFound.middleware.ts":
/*!***********************************************!*\
  !*** ./src/middleware/notFound.middleware.ts ***!
  \***********************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\nObject.defineProperty(exports, \"__esModule\", { value: true });\n// i dont understand why here we dont need 4 arguments... \nexports.notFoundHandler = function (request, response, next) {\n    var message = \"Resource not found\";\n    response.status(404).send(message);\n};\n\n\n//# sourceURL=webpack:///./src/middleware/notFound.middleware.ts?");

/***/ })

};