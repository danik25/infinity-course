exports.id = "main";
exports.modules = {

/***/ "./src/common/http-exception.ts":
/*!**************************************!*\
  !*** ./src/common/http-exception.ts ***!
  \**************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\nvar __extends = (this && this.__extends) || (function () {\n    var extendStatics = function (d, b) {\n        extendStatics = Object.setPrototypeOf ||\n            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||\n            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };\n        return extendStatics(d, b);\n    };\n    return function (d, b) {\n        extendStatics(d, b);\n        function __() { this.constructor = d; }\n        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());\n    };\n})();\nObject.defineProperty(exports, \"__esModule\", { value: true });\nvar HttpException = /** @class */ (function (_super) {\n    __extends(HttpException, _super);\n    function HttpException(statusCode, message, error) {\n        var _this = _super.call(this, message) || this;\n        console.log(statusCode);\n        _this.statusCode = statusCode;\n        _this.message = message;\n        _this.error = error || null; //error is optional, if there is no 'error', then-> null\n        return _this;\n    }\n    return HttpException;\n}(Error));\nexports.default = HttpException;\n\n\n//# sourceURL=webpack:///./src/common/http-exception.ts?");

/***/ })

};