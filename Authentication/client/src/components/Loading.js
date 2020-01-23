import React from 'react';
import PropTypes from 'prop-types';
import styled from 'styled-components';

import { CommonLoading } from 'react-loadingg';

const Container = styled.div`
    position: relative;
    margin: ${props => props.spacing} auto;
`;

export default function Loading({ size, color, spacing }) {
    return (
        <Container spacing={spacing}>
            <CommonLoading size={size} color={color} />
        </Container>
    );
}

Loading.defaultProps = {
    spacing: '0px'
};

Loading.propTypes = {
    size: PropTypes.string.isRequired,
    color: PropTypes.string.isRequired,
    spacing: PropTypes.string
};