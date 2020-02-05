var jwt = require('jsonwebtoken');

var authFunc = async function (req, res, next){
	try{
		var token = req.header('Authorization').replace('Bearer ', '')
		var decoded = jwt.verify(token, "someString")
		var user = User.findOne({_id : decoded.user_id, token : decoded.token})
	
		if(!user)
		{
			throw Error("no user")
		}
	
		req.user = user
		next()
	}catch(e){
		res.send("please authonticate")
	}
	
}

module.exports = authFunc