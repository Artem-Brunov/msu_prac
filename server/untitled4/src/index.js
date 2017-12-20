const express = require('express');
const mongoose = require('mongoose');


mongoose.Promise = global.Promise;
mongoose.connect('mongodb://localhost/companies');

const bodyParser = require('body-parser');
const urlencodedParser = bodyParser.urlencoded({ extended: false });

const models = require('./models');

const port = 3000;
const app = express();
app.get('/', (req, res) => res.send('the server is working'));
app.listen(port, () => console.log(`The server are working on a port ${port}`));


app.get('/api/playlist', function (req, res) {
    models.playlist.find((err, data) => {
        if (err) {
            res.status(500).send(err)
        } else {
            res.status(200).send(data);
        }
    });
});
app.post('/api/playlist', urlencodedParser, function (req, res) {
    models.playlist.create({
        name: req.body.name,
        fullName: req.body.fullName,
        information: {
            email: req.body.email,
            phone: req.body.phone,
        },
    }, function (err, playlist) {
        if (err) {
            res.status(500).send(err);

        }
        if (playlist) {
            res.status(200).send(playlist);
        }
    });
});
app.get('/api/playlist/:playlistId', function (req, res) {
    models.playlist.findById(
        new mongoose.Types.ObjectId(req.params.playlistId),
        (err, playlist) => {
            if (err) {
                res.status(500).send(err);
            }
            if (playlist) {
                res.status(200).send(playlist);
            } else {
                res.status(404).send('No found with that ID');
            }
        });
});
app.put('/api/playlist/:playlistId', urlencodedParser, function (req, res) {
    models.playlist.findByIdAndUpdate(
        new mongoose.Types.ObjectId(req.params.playlistId),
        {
            name: req.body.name,
            fullName: req.body.fullName,
            information: {
                email: req.body.email,
                phone: req.body.phone,
            },
        }, function (err, playlist) {
            if (err) {
                res.status(500).send(err);
            }
            if (playlist) {
                res.status(200).send(playlist);
            }
        });
});
app.delete('/api/playlist/:playlistId', function (req, res) {
    models.playlist.findByIdAndRemove(
        new mongoose.Types.ObjectId(req.params.playlistId),
        (err, playlist) => {
            if (err) {
                res.status(500).send(err);
            }
            if (playlist) {
                res.status(200).send('success');
            } else {
                res.status(404).send('No found with that ID');
            }
        });
});

app.get('/api/word', function (req, res) {
    models.word.find((err, data) => {
        if (err) {
            res.status(500).send(err)
        } else {
            res.status(200).send(data);
        }
    });
});
app.post('/api/word', urlencodedParser, function (req, res) {
    const playlistQuery = models.playlist.findById(req.body.playlistId).exec();
    playlistQuery
        .then((compObj) => {
            const newword = new models.word();
            newWord.playlist = compObj;
            newWord.name = req.body.name;
            newWord.fullName = req.body.fullName;
            newWord.information = {
                email: req.body.email,
                phone: req.body.phone,
                birthday: new Date(req.body.birthday),
            };
            return newWord.save();
        })
        .then((result) => {
            res.status(200).send(result);

        })
        .catch((err) => res.status(500).send(err));
});
app.get('/api/word/:wordId', function (req, res) {
    models.word.findById(
        new mongoose.Types.ObjectId(req.params.wordId),
        (err, word) => {
            if (err) {
                res.status(500).send(err);
            }
            if (word) {
                res.status(200).send(word);
            } else {
                res.status(404).send('No found with that ID');
            }
        });
});
app.put('/api/word/:wordId', urlencodedParser, function (req, res) {
    models.word.findByIdAndUpdate(
        new mongoose.Types.ObjectId(req.params.wordId),
        {
            name: req.body.name,
            fullName: req.body.fullName,
            information: {
                email: req.body.email,
                phone: req.body.phone,
                birthday: new Date(req.body.birthday),
            },
        }, function (err, word) {
            if (err) {
                res.status(500).send(err);
            }
            if (word) {
                res.status(200).send(word);
            } else {
                res.status(404).send('No found with that ID');
            }
        });
});
app.delete('/api/word/:wordId', function (req, res) {

    models.word.findByIdAndRemove(
        new mongoose.Types.ObjectId(req.params.wordId),
        (err, word) => {
            if (err) {
                res.status(500).send(err);
            }
            if (word) {
                res.status(200).send('success');
            } else {
                res.status(404).send('No found with that ID');
            }
        });
});

