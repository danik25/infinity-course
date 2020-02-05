// lib/app.ts
import express = require('express');
class App{
	public express

	constructor(){
		this.express = express()
		this.mountRoutes()
	}

	private mountRounts(): void{
		const router = express.Router()
		router.get('/', (req, res) => {
			res.json({
				message: "Hello to you!"
			})
		})
		this.express.use('/', router)
	}
	
}

export default new App().express
// Create a new express application instance
// const app: express.Application = express();

// app.get('/', function (req, res) {
//   res.send('Hello World!');
// });

// app.listen(3000, function () {
//   console.log('Example app listening on port 3000!');
// });