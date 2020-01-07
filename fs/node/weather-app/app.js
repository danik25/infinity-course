const request = require('request')
const url = 'https://api.darksky.net/forecast/875b9f0c668af681b94b2d878cfc29cc/37.8267,-122.4233'
const urlIsrael = 'https://api.darksky.net/forecast/875b9f0c668af681b94b2d878cfc29cc/31.771959,35.217018?units=si'


request({url:urlIsrael,  json : true}, (error, response) => {
    const temp = response.body.currently.temperature
    const rain = response.body.currently.precipProbability
    const hum = response.body.currently.humidity
    console.log("temp : " + temp)
    console.log(rain + "% of rain")
    console.log("hum: " + hum)
})