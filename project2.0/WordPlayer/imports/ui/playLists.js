import React, {Component} from 'react';
import { withTracker } from 'meteor/react-meteor-data';
import { Button } from 'react-bootstrap';
import ReactDOM from 'react-dom';
import { Form } from 'react-bootstrap';
import { FormGroup } from 'react-bootstrap';
import { FormControl } from 'react-bootstrap';
import { Playlists } from '../api/play_lists.js';
import List from './list.js';




export default class PlayLists extends Component{

    constructor(props){
        super(props);
        this.state ={
            count: Playlists.find().count(),
            list: null,
        }
    }

    goBack(){
        FlowRouter.go('/');
    }

    updateData = (value) => {
        this.setState({ count: Playlists.find().count()});
    };

    updatePlaylist = (value) =>{
        console.log(value);
        this.setState({ list: value});
        this.props.updateCurrentList(value);
    };

    goCreateNewList(event){
        event.preventDefault();
        const text = ReactDOM.findDOMNode(this.refs.textInput).value.trim();
        Meteor.call('playlists.insert', text);
        ReactDOM.findDOMNode(this.refs.textInput).value = '';
        this.setState({count: this.state.count+1})
    }


    render() {
    if(!this.props.renderWords) {
        return (
            <div>
                <Form inline>
                    <FormGroup controlId="formInlineName">
                        <FormControl type="text" placeholder="Enter playlist name" ref = "textInput"/>
                    </FormGroup>{' '}

                    <Button
                        type = "submit"
                        onClick={
                            this.goCreateNewList.bind(this)
                        }>
                        Create</Button>
                </Form>
                <div>
                {Playlists.find().fetch().map((list) => (
                    <div>
                        <List key={list._id} list={list}
                              updatePlaylist={this.updatePlaylist}
                              updateData={this.updateData}
                        />
                    </div>
                ))}
                </div>

                    <Button bsStyle="primary" onClick={this.goBack}>Main</Button>
            </div>
        );
    }
    else{
        return(<div></div>)
    }
    }
}
