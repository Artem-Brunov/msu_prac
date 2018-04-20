import { Meteor } from 'meteor/meteor';
import { Random } from 'meteor/random';
import { assert } from 'chai';

import {Playlists} from "./play_lists.js";

if(Meteor.isServer){
    describe('Playlists',()=>{
        describe('methods',()=>{
            const listId = Random.id();
            let lId;
            beforeEach(()=> {
                Playlists.remove({})
                lId = Playlists.insert({
                    text: "test list",
                    createAt: new Date(),
                });
            });


        });
    });
}