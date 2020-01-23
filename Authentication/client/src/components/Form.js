import React from 'react';
import PropTypes from 'prop-types';
import styled from 'styled-components';

import Button from '@material-ui/core/Button';

const Container = styled.form`
    width: 400px;
    margin: 0 auto;
    padding: 3px 50px 50px 50px;
    border-radius: 10px;
    box-shadow: 0 10px 20px rgba(0, 0, 0, 0.19), 0 6px 6px rgba(0, 0, 0, 0.23);
    background-color: #fafafa;
    text-align: center;
`;

const Title = styled.h2`
    margin: 40px auto;
    color: #5AAEF6;
    letter-spacing: 0.2em;
`;

const Submit = styled(Button)`
    margin: 40px 0 0 0 !important; 
    color: white !important;
    background-color: #5AAEF6 !important;
    font-family: inherit !important;
    font-weight: bold !important;
`;

export default function Form({ title, submitName, onSubmit, children }) {
    return (
        <Container onSubmit={onSubmit}>
            <Title>{title}</Title>
            {children}
            <Submit type="submit" fullWidth variant="contained">
                {submitName}
            </Submit>
        </Container>
    );
}

Form.propTypes = {
    title: PropTypes.string.isRequired,
    submitName: PropTypes.string.isRequired,
    onSubmit: PropTypes.func
}