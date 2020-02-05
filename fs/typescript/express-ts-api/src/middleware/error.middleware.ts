import HttpException from "../common/http-exception";
import { Request, Response, NextFunction } from "express";
import { connect } from "http2";


//It's important to note that you must provide four 
//arguments to identify a function as an error-handling 
//middleware function in Express

export const errorHandler = (
  error: HttpException,
  request: Request,
  response: Response,
  next: NextFunction //You must specify the next object to 
  					//maintain the error-handling signature even if you don't use it.
) => {
  const status = error.statusCode || 500; //internal server error
  const message =
    error.message + " middleware.." || "It's not you. It's us. We are having some problems.";

  response.status(status).send(message);
};