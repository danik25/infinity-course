import jwt from "express-jwt";
import jwksRsa from "jwks-rsa";
import * as dotenv from "dotenv";

dotenv.config();

export const checkJwt = jwt({
	/*To obtain the secret, you need to do some additional work: 
	you use the expressJwtSecret helper function from the jwks-rsa 
	library to query the JSON Web Key Set (JWKS) endpoint of your Auth0 tenant. 
	This endpoint has a set of keys containing the public keys that your 
	application can use to verify any JSON Web Token (JWT) issued by the 
	authorization server and signed using the RS256 signing algorithm.*/
  secret: jwksRsa.expressJwtSecret({
    cache: true,
    rateLimit: true,
    jwksRequestsPerMinute: 5,
    jwksUri: `${process.env.AUTH0_ISSUER}.well-known/jwks.json`
  }),

  // Validate the audience and the issuer.
  /*The audience and issuer of the JWT, which are defined in your .env 
  file and loaded into this module using dotenv.config().*/
  audience: process.env.AUTH0_AUDIENCE,
  issuer: `${process.env.AUTH0_ISSUER}`,
  algorithms: ["RS256"]
});