import React, {Component} from 'react';
import {Words_list} from "../api/words_list";
import { ListGroupItem } from 'react-bootstrap';
import { ListGroup } from 'react-bootstrap';

export default class List_w extends Component {

    deleteThisList(){
        const id = this.props.list._id;
        Meteor.call('word.remove',id);
        console.log(id);
    }



    render(){
        return(

                <ListGroup>

                    <ListGroupItem >
                        {this.props.list.word}
                    </ListGroupItem>
                    <ListGroupItem >
                        ---------
                    </ListGroupItem>
                    <ListGroupItem >
                        {this.props.list.trans}
                    </ListGroupItem>
                    <ListGroupItem onClick={()=>{
                        this.deleteThisList(this);
                        this.props.updateWordlist(this.props.list._id-1);
                    }}>
                        Delete word</ListGroupItem>
                </ListGroup>)

    }

}