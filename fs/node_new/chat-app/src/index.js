const express = require('express')
const app = express()
const path = require('path')

const http = require('http')
const server = http.createServer(app)
const socketio = require('socket.io')
const io = socketio(server) //expects to bee called with a http server
const Filter = require('bad-words')

const {generateMessage, generateLocation} = require('./utils/messages')
const{addUser, removeUser, 
	getUser, getUsersInRoom} = require('./utils/users')

const port = process.env.PORT || 3000

app.use(express.static(path.join(__dirname, '../public')))

io.on('connection', (socket) => {
	socket.on('join', ({username, room}, callback) => {
		const {error, user} = addUser({id : socket.id, username, room})

		if(error){
			return callback(error)
		}

		socket.join(user.room)

		socket.emit('message', generateMessage("Admin", 'welcome!'))
		socket.broadcast.to(user.room).emit('message', generateMessage("Admin", `${user.username} has joined!`))
		
		io.to(user.room).emit('roomData', {
			room: user.room,
			users: getUsersInRoom(user.room)
		})

		callback()  //without an error
	})
	
	socket.on('sendMessage', (message, callback) => {
		const user = getUser(socket.id)
		const filter = new Filter()

		if(filter.isProfane(message)){
			return callback("Profanity is not allowed!")
		}

		io.to(user.room).emit('message', generateMessage(user.username, message))
		callback()
	})
	socket.on('disconnect', () => {
		const user = removeUser(socket.id)

		if(user){
			io.to(user.room).emit('message', generateMessage("Admin", `${user.username} has left the room`))
		
			io.to(user.room).emit('roomData', {
				room: user.room,
				users: getUsersInRoom(user.room)
			})
		}
	})
	//providing a link to the location on google maps
	socket.on('sendLocation', (coords, callback) => {
		const user = getUser(socket.id)
        io.to(user.room).emit('locationMessage', generateLocation(user.username, `https://google.com/maps?q=${coords.latitude},${coords.longitude}`))
        callback()
    })
})


//notice it is server, not app
server.listen(port)