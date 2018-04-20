import React, {Component} from 'react';
import "../api/play_lists.js";
import ReactDOM from 'react-dom';

import { Playlists } from '../api/play_lists.js';


export default class NewPlaylist extends Component{

    goCreateNewList(){
        const text = ReactDOM.findDOMNode(this.refs.textInput).value.trim();
        console.log(text);
        Meteor.call('playlists.insert', text);

       /* Playlists.insert({
            text,
            createdAt: new Date(),
        });*/

        ReactDOM.findDOMNode(this.refs.textInput).value = '';
        FlowRouter.go('/playlists');
    }

    render(){
        return(<div>
                <form onSubmit={this.goCreateNewList.bind(this)}>
                    <input type="text" ref="textInput" />
                    <Button onClick={this.goCreateNewList.bind(this)}>Create</Button>
                </form>
            </div>
        );
    }
}