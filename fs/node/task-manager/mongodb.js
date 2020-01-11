const mongodb = require('mongodb')
const MongoClient = mongodb.MongoClient
const connectionURL = 'mongodb://127.0.0.1:27017'
const databaseName = 'task-manager'
MongoClient.connect(connectionURL, { useNewUrlParser: true, useUnifiedTopology: true }, (error, client) => {
    if (error) {
    return console.log('Unable to connect to database!')
    }
    const db = client.db(databaseName)
    db.collection('users').insertOne({
        name: 'Andrew',
        age: 27
    })

    db.collection('tasks').insertMany([
        {
            description : 'buy milk',
            completed : true
        },
        {
            description : 'fix car',
            completed : true
        },
        {
            description : 'study',
            completed : false
        }
    ], (error, result) => {
        if(error)
        {
            return console.log("failed")
        }
        console.log("inserted successfully")
    })

})