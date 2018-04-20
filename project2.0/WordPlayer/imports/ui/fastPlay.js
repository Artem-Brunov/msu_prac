import React, {Component} from 'react';


export default class FastPLay extends Component{

    goFast(){

    //здесь должен быть ваш код по text-to-speech
    }

    render(){
        return(<div>
                <input type="text" />
                <button onClick={this.goFast()}>GO</button>
            </div>

        );
    }
}