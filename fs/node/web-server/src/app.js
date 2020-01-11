const express = require('express')
const path = require('path')

const app = express()

app.use(express.static(path.join(__dirname, '../public')))

app.set('views', path.join(__dirname, '../views'))
app.set('view engine', 'hbs')


app.get('', (req, res) => {
    res.render('index', {
    title: 'my weather app',
    name: 'dani'
    })
})

app.get('/weather', (req, res) => {
    if(!req.query.address)
    {
        return res.send("address")
    }
    res.send({
        forecast: "im snowing",
        address: req.query.address
    })
})

app.get('*', (req, res) => {
    res.sendFile(path.join(__dirname, '../public/404.html'))
})

app.listen(3000)