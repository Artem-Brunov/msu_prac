import React, {Component} from 'react';
import { Button } from 'react-bootstrap';
import {PageHeader} from 'react-bootstrap';


export default class StartPage extends Component{

    goFastplay(){
        return FlowRouter.go('/fastplay');
    }

    goNewplaylist(){
        return FlowRouter.go('/create_new');
    }

    goPlaylist(){
        return FlowRouter.go('/playlists');
    }
    goWords(){
        return FlowRouter.go('/words');
    }

    render(){
        return(
            <div className="container">
                <header>
                    <PageHeader>Word Player</PageHeader>
                </header>



                    <Button bsStyle="primary" bsSize="large" onClick={this.goPlaylist}>Playlists</Button>


            </div>
        );
    }
}
/*<button onClick={this.goWords}>words</button>*/