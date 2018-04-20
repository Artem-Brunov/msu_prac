import { Meteor } from 'meteor/meteor';
import { Mongo } from 'meteor/mongo';
import { check } from 'meteor/check';


export const Playlists = new Mongo.Collection('playlists');


if (Meteor.isServer){
    /*Meteor.publish('playlists', function playlistsPublication(){
        return Playlists.find()
    });*/
}

Meteor.methods({
    'playlists.insert'(text) {
        check(text, String);

        Playlists.insert({
            text,
            createdAt: new Date(),
        });
    },

    'playlists.remove'(listId){
      check(listId,String);
      const list = Playlists.findOne(listId);
      Playlists.remove(listId);
    },


});

