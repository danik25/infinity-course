import { Request, Response, NextFunction } from "express";

// i dont understand why here we dont need 4 arguments... 
// route not existing is not actually considered an error by Express.
// it is a normal middleware, effectively a "catch-all" handler and would get the 
// requests that would end up being a 404.

export const notFoundHandler = (
  request: Request,
  response: Response,
  next: NextFunction
) => {

  const message = "Resource not found";

  response.status(404).send(message);
};