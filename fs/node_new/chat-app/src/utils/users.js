// keeping track of our users in a n array

const users = []

const getUser = (id) => {
	
	return users.find((user) => user.id === id)
}

const getUsersInRoom = (room) => {
	return users.filter(user => user.room === room)
}

const removeUser = (id) => {
	const index = users.findIndex((user) => {
		return user.id === id
	})

	if(index != -1){
		//splice let us remove items from an array using the index
		return users.splice(index, 1)[0] //returns an array, so we extract the one item with the []
	}
}

const addUser = ({id, username, room}) => {
	//clean the data
	username = username.trim().toLowerCase()
	room = room.trim().toLowerCase()

	//validate the data
	if(!username || !room){
		return {
			error : "username and room are required"
		}
	}

	//Check for existing user
	const existingUser = users.find((user) => {
		return user.room === room && user.username == username
	})

	//validate user name
	if(existingUser){
		return{
			error : "user name is in use!"
		}
	}

	// Store user
	const user = {id, username, room}

	users.push(user)
	return {user}
}



module.exports = {
	addUser,
	removeUser, 
	getUser, 
	getUsersInRoom
}
