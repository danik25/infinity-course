const express = require('express')
const router = new express.Router()
const path = require('path')
var validator = require('validator');
var jwt = require('jsonwebtoken');

var User = require('../model/user')
var authFunc = require('../middleware/auth')

// router.get('/users', function (req, res) {
// 	res.sendFile(path.join(__dirname, '../html/page.html'))
//   })


router.post('/users/sign', async function (req, res) {

	if(validator.isEmpty(req.body.name))
	{
		res.status(401).send("name required")
	}
	else{
		const user = new User(req.body)
		var token = jwt.sign({ user_id: user._id }, 'someString');
		user.token = token
		await user.save()
		res.status(200).send(user)
	}
})

router.post('/users/login', authFunc, async function (req, res) {

	
})



module.exports = router