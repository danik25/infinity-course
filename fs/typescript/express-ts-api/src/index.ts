/**
 * Required External Modules
 */

import * as dotenv from "dotenv";
import express from "express";
import cors from "cors";
import helmet from "helmet";
import { itemsRouter } from "./items/items.router";

// error-handling middleware functions
import {errorHandler} from "./middleware/error.middleware";
import {notFoundHandler} from "./middleware/notFound.middleware";

dotenv.config(); //load any environmental variables from the local .env file

/**
 * App Variables
 */

if (!process.env.PORT) { //check if the environmental variable PORT was loaded 
						//into process.env. If so, parse its value as a 
						//number type and create an instance of an Express application
	process.exit(1);
 }
 
 const PORT: number = parseInt(process.env.PORT as string, 10);
 
 const app = express();

/**
 *  App Configuration
 */

app.use(helmet());
app.use(cors()); //By mounting cors(), you enable all CORS requests.
app.use(express.json()); //This is a built-in middleware function in Express. 
						//It parses incoming requests with JSON payloads and is based on body-parser.
						//which populates the request object with a new body object containing the parsed data.
app.use("/items", itemsRouter);

//mount the errorHandler and notFoundHandler functions.

/*our application can't reach any routes that you define after mounting the 
errorHandler middleware function because you close the request-response cycle 
within errorHandler by sending a response to the client. As such, 
the errorHandler middleware function must be mounted 
after all the controller functions of your application have been mounted.*/

app.use(errorHandler);
app.use(notFoundHandler);

/*But, as noted earlier, errorHandler won't catch 404 errors. 
However, you can catch these errors by making notFoundHandler the last 
middleware function that you mount, which effectively creates a catch-all 
handler for your app.*/

/**
 * Server Activation
 */

const server = app.listen(PORT, () => {
	console.log(`Listening on port ${PORT}`);
});

/**
 * Webpack HMR Activation
 */

type ModuleId = string | number;

interface WebpackHotModule {
  hot?: {
    data: any;
    accept(
      dependencies: string[],
      callback?: (updatedDependencies: ModuleId[]) => void,
    ): void;
    accept(dependency: string, callback?: () => void): void;
    accept(errHandler?: (err: Error) => void): void;
    dispose(callback: (data: any) => void): void;
  };
}

declare const module: WebpackHotModule;

if (module.hot) {
  module.hot.accept();
  module.hot.dispose(() => server.close());
}