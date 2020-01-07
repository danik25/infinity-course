const express = require('express')
const path = require('path')

const app = express()
app.set('view engine', 'hbs')
app.use(express.static(path.join(__dirname, '../public')))

app.get('', (req, res) => {
    res.render('index', {
    title: 'my weather app',
    name: 'dani'
    })
})


app.listen(3000)