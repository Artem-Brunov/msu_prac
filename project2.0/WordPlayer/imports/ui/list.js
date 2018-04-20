import React, {Component} from 'react';
import { Button } from 'react-bootstrap';
import { ButtonToolbar } from 'react-bootstrap';
import { ListGroupItem } from 'react-bootstrap';
import { ListGroup } from 'react-bootstrap';


export default class List extends Component {

    deleteThisList(){
        const id = this.props.list._id;
        Meteor.call('words.remove', id);
        Meteor.call('playlists.remove', id);
        return this.props.count;

    }

    hendleEvent(){
        const id = this.props.list._id;
        //Meteor.call('playlist.word',id);
        //FlowRouter.go('/words');

    }

    render(){
        return(<div>

                <ListGroup>

                    <ListGroupItem onClick={()=>{
                        this.hendleEvent(this);
                        this.props.updatePlaylist(this.props.list._id);
                    }}>
                        {this.props.list.text}</ListGroupItem>
                    <ListGroupItem onClick={() => {
                        this.deleteThisList(this);
                        this.props.updateData();}}>
                        Delete list</ListGroupItem>
                </ListGroup>


        </div>)
    }

}