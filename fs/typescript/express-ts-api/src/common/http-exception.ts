export default class HttpException extends Error {
	statusCode: number;
	message: string;
	error: string | null;
  
	constructor(statusCode: number, message: string, error?: string) {
	  super(message);
	  this.statusCode = statusCode;
	  this.message = message;
	  this.error = error || null; //error is optional, if there is no 'error', then-> null
	}
  }

  