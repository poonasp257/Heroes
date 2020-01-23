import React from 'react';
import PropTypes from 'prop-types';
import styled from 'styled-components';

import Button from '@material-ui/core/Button';
import CheckIcon from '@material-ui/icons/Check';

export default function VerificationButton({ text, size, fontColor, color, checked,...props }) {
    if(checked) {
        return (
            <CheckIcon fontSize={size} style={{ color: color }}/>
        );
    }
   
    const Container = styled(Button)`   
        color: ${fontColor} !important;
        background-color: ${color} !important;
        font-family: inherit !important;
        font-weight: bold !important; 
    `;

    return (
        <Container fullWidth variant="contained" size={size} {...props}>
            {text}
        </Container>
    );
}

VerificationButton.defaultProps = {
    checked: false
};

VerificationButton.propTypes = {
    text: PropTypes.string.isRequired,
    size: PropTypes.string.isRequired,
    fontColor: PropTypes.string.isRequired,
    color: PropTypes.string.isRequired,
    checked: PropTypes.bool
};