
const fs = require('fs')

const data = JSON.parse(fs.readFileSync("./jsonFile.json"))
console.log(data)

data.name = "dani"
data.age = 26

const newJosn = JSON.stringify(data)
fs.writeFileSync("./jsonFile.json", newJosn)
console.log(data)


