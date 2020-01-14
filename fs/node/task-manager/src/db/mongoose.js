const mongoose = require('mongoose')

mongoose.connect('mongodb://127.0.0.1:27017/task-manager', { useNewUrlParser : true, useCreateIndex : true, useUnifiedTopology: true})





// const newUsr = new User({name : "dani", email : "dani@gmail.com", password : "pass123", age : 26})

// newUsr.save().then(() => {
//     console.log("new task created : " + newUsr)
// }).catch((error) => {
//     console.log("error in  user save: " + error)
// })

