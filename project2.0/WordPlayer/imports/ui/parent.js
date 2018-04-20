import React, {Component} from 'react';
import ReactDOM from 'react-dom';
import PlayLists from "./playLists";
import Words from "./words";



export default class Parent extends Component{
    constructor(props){
        super(props);
        this.state =
            {
                currentList: null,
                renderWords: false,
        }
    }

    updateWords = (state)=>{
        this.setState({renderWords: state});
    };

    updateCurrentList = (value) => {
        this.setState({currentList: value});
        this.setState({renderWords:true})
    };

    render(){

        return(
            <div>
        <PlayLists
            updateCurrentList={this.updateCurrentList}
            renderWords={this.state.renderWords}
        />
        <Words
            renderWords={this.state.renderWords}
            updateWords={this.updateWords}
            currentList={this.state.currentList}

        />
            </div>);
    }
}