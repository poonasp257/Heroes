import React, { PureComponent } from 'react';
import { Link } from 'react-router-dom';
import styled from 'styled-components';

const Container = styled.div`
    margin: 0 auto;
`;

const Button = styled.div`
    width: 150px;
    margin: 50px auto;
    padding: 15px;
    color: #5AAEF6;
    font-weight: bold;
    background-color: white;
    border-radius: 5px;
    box-shadow: 0 10px 20px rgba(0, 0, 0, 0.19), 0 6px 6px rgba(0, 0, 0, 0.23);
    transition: transform 0.1s ease-in-out;
    :hover { transform: scale(1.05); }
`;

export default class Home extends PureComponent {
    render() {
        return (
            <Container>
                <Link to="/signup">
                    <Button>회원가입</Button>
                </Link>
                <Link to="/help">
                    <Button>비밀번호 재설정</Button>
                </Link>
            </Container>
        );
    }
}

