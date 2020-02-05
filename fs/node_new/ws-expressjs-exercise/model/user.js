const mongoose = require('mongoose');

const Schema = mongoose.Schema;
const ObjectId = Schema.ObjectId;
 
const schema = new Schema({
  name: {
	  type: String
  },
  token: {
	  type: String
  },
});

const User = mongoose.model('User', schema);
module.exports = User

