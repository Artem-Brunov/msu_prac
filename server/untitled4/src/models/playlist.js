const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const playlistSchema = new Schema({
    name: {type: String, required: true, unique: true},
    fullName: String,
    information: {
        email: String,
        phone: String
    }
});
module.exports = mongoose.model('Playlist', playlistSchema);


