const express = require('express')
const mongoose = require('mongoose')
const app = express()

const signRouter = require('./routers/sign')

app.use(express.json())
app.use(signRouter)

mongoose.connect('mongodb://127.0.0.1:27017/notes-express', { useNewUrlParser : true, useCreateIndex : true, useUnifiedTopology: true})

app.listen(3000)