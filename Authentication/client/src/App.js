import React from 'react';
import styled from 'styled-components';
import { BrowserRouter as Router, Route, Link } from 'react-router-dom';

import { AlertBox } from 'components';
import { Home, SignUp, Help } from 'containers';

const Container = styled.div`
    position: absolute;
    left: 50%;
    top: 20%;
    transform: translate(-50%, -20%);
`;

const Header = styled.div`
    margin: 80px;
    font-size: 40px;
    font-weight: bold;
    color: white;
    letter-spacing: 0.3em;
    transition: transform 0.1s ease-in-out;
    :hover { transform: scale(1.05); }
`;

export default function App() {
    return (
        <Container>
            <Router>   
                <Link to="/">        
                    <Header>Heroes</Header>
                </Link> 
                <Route exact path="/" component={Home}/>
                <Route path="/signup" component={SignUp}/>
                <Route path="/help" component={Help}/>
            </Router>
            <AlertBox/>
        </Container>
    );
}