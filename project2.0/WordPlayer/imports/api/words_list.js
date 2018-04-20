import { Meteor } from 'meteor/meteor';
import { Mongo } from 'meteor/mongo';
import { check } from 'meteor/check';
import { HTTP } from 'meteor/http';
import {Playlists} from "./play_lists";

export const Words_list = new Mongo.Collection('words_list');



Meteor.methods({

    'word.insert'(word, translated,list){
        check(word, String);

        Words_list.insert({
            word,
            createdAt: new Date(),
            trans: translated,
            listname: list,
        });
        console.log('inserted word ', word);
        console.log(Words_list.find().fetch());
    },

    'word.remove'(listId){
        check(listId,String);
        const list = Words_list.findOne(listId);
        Words_list.remove(listId);
    },

    'word.translate'(word,list){
        var options = {
            'headers':{
                'Access-Control-Allow-Origin': 'http://api.lingualeo.com',
            }
        };
        check(word,String);
        let url = 'http://api.lingualeo.com/gettranslates?word='+word;
        HTTP.call('GET',url,options,(error,result)=>{
            if(!error){
                var final = JSON.parse(result.content).translate[0].value;

                Meteor.call('word.insert',word,final,list);

            }
        })
    },

    'words.remove'(listId){
        check(listId,String);
        const list = Words_list.find({listname: listId}).fetch();
        for (let i = 0; i < list.length; i++){
            Meteor.call("word.remove",list[i]._id);
        }
    }

});