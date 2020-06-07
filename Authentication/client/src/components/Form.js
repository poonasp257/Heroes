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

const Name = styled.h2`
    margin: 40px auto;
    color: #5AAEF6;
    letter-spacing: 0.2em;
`;

const SubmitButton = styled(Button)`
    margin: 40px 0 0 0 !important; 
    color: white !important;
    background-color: #5AAEF6 !important;
    font-family: inherit !important;
    font-weight: bold !important;
`;

export default function Form({ name, children, ...props }) {
    const { submitName, onSubmit } = props;
    return (
        <Container onSubmit={onSubmit}>
            <Name>{name}</Name>
            {children}
            {onSubmit ? <Submit name={submitName} /> : null}
        </Container>
    );
}

Form.propTypes = {
    name: PropTypes.string.isRequired,
    submitName: PropTypes.string,
    onSubmit: PropTypes.func
}

const Submit = ({name}) => {
    return (
        <SubmitButton type="submit" fullWidth variant="contained">
            {name}
        </SubmitButton>
    );
}